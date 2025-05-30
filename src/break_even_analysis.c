#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MIN_QUANTITY 0
#define MAX_QUANTITY 500
#define TRUE_VALUE 250  // Assumed true value for error calculation
#define STEP 20
#define MAX_ITERATIONS 100
#define EPSILON 0.0001

// Function to calculate profit derivative at a given quantity
// P'(x) = a - 2bx - 2cx - d
double calculateProfitDerivative(double x, double a, double b, double c, double d, double e) {
    return a - 2*b*x - 2*c*x - d;
}

// Function to calculate profit at a given quantity
double calculateProfit(double x, double a, double b, double c, double d, double e) {
    // Revenue: R(x) = ax - bx^2
    // Cost: C(x) = cx^2 + dx + e
    // Profit: P(x) = R(x) - C(x)
    return (a*x - b*pow(x,2)) - (c*pow(x,2) + d*x + e);
}

// Secant method implementation with detailed output
double secantMethod(double x0, double x1, double a, double b, double c, double d, double e, 
                   double (*func)(double, double, double, double, double, double), int* iter_count) {
    double f0, f1, x2;
    int iterations = 0;
    
    printf("\nSecant Method Iterations:\n");
    printf("--------------------------------\n");
    printf("Iter |    x0    |    x1    |    x2    \n");
    printf("--------------------------------\n");
    
    do {
        f0 = func(x0, a, b, c, d, e);
        f1 = func(x1, a, b, c, d, e);
        
        if (fabs(f1 - f0) < EPSILON) {
            printf("Method failed - division by zero\n");
            return -1;
        }
        
        x2 = x1 - f1 * (x1 - x0) / (f1 - f0);
        printf("%3d  | %8.4f | %8.4f | %8.4f\n", iterations, x0, x1, x2);
        
        x0 = x1;
        x1 = x2;
        
        iterations++;
    } while (fabs(func(x2, a, b, c, d, e)) > EPSILON && iterations < MAX_ITERATIONS);
    
    if (iterations >= MAX_ITERATIONS) {
        printf("Method failed to converge\n");
        return -1;
    }
    
    *iter_count = iterations;
    return x2;
}

// Calculate relative error
double calculateError(double approximate, double true_value) {
    return fabs((true_value - approximate) / true_value) * 100;
}

void displayCoefficients(double a, double b, double c, double d, double e) {
    printf("\nCoefficients Table:\n");
    printf("+---+--------+\n");
    printf("| a | %6.2f |\n", a);
    printf("| b | %6.2f |\n", b);
    printf("| c | %6.2f |\n", c);
    printf("| d | %6.2f |\n", d);
    printf("| e | %6.2f |\n", e);
    printf("+---+--------+\n");
}

void saveMetadataToFile(FILE *fp, double a, double b, double c, double d, double e,
                       double x0, double x1, double optimalPoint, double optimalProfit,
                       int iterations, double error) {
    fprintf(fp, "Coefficients:\n");
    fprintf(fp, "a = %.2f\n", a);
    fprintf(fp, "b = %.2f\n", b);
    fprintf(fp, "c = %.2f\n", c);
    fprintf(fp, "d = %.2f\n", d);
    fprintf(fp, "e = %.2f\n\n", e);
    
    fprintf(fp, "Initial Points:\n");
    fprintf(fp, "x0 = %.2f\n", x0);
    fprintf(fp, "x1 = %.2f\n\n", x1);
    
    fprintf(fp, "Results:\n");
    fprintf(fp, "Optimal quantity = %.2f\n", optimalPoint);
    fprintf(fp, "Maximum profit = %.2f\n", optimalProfit);
    fprintf(fp, "Error percentage = %.2f%%\n", error);
    fprintf(fp, "Total iterations = %d\n\n", iterations);
    
    fprintf(fp, "\nData Points:\n");
    fprintf(fp, "%-10s %-12s %-12s %-12s\n", "Quantity", "Revenue", "Cost", "Profit");
    fprintf(fp, "------------------------------------------------\n");
}

void saveDataPoint(FILE *fp, double quantity, double revenue, double cost, double profit) {
    fprintf(fp, "%-10.2f %-12.2f %-12.2f %-12.2f\n", quantity, revenue, cost, profit);
}

void saveToFile(double quantity, double revenue, double cost, double profit, FILE *fp) {
    saveDataPoint(fp, quantity, revenue, cost, profit);
}

void printTableRow(double quantity, double revenue, double cost, double profit) {
    printf("| %8.2f | %10.2f | %10.2f | %10.2f |\n", quantity, revenue, cost, profit);
}

void printTableHeader() {
    printf("\n+----------+------------+------------+------------+\n");
    printf("| Quantity |   Revenue  |    Cost    |   Profit   |\n");
    printf("+----------+------------+------------+------------+\n");
}

void printTableFooter() {
    printf("+----------+------------+------------+------------+\n");
}

void processDataset(int datasetNum, double a, double b, double c, double d, double e) {
    char resultsFile[50], plotFile[50];
    sprintf(resultsFile, "results_%d.txt", datasetNum);
    sprintf(plotFile, "plot_%d.gnu", datasetNum);

    printf("\n===============================================\n");
    printf("Analyzing Dataset %d\n", datasetNum);
    printf("===============================================\n");

    // Display coefficients
    displayCoefficients(a, b, c, d, e);

    // Open output file
    FILE *output = fopen(resultsFile, "w");
    if (output == NULL) {
        printf("Error: Cannot create %s\n", resultsFile);
        return;
    }

    // Initial points for secant method
    double x0 = 0;
    double x1 = MAX_QUANTITY/2;

    // Find optimal profit point using secant method on the derivative
    printf("\nFinding optimal profit point...\n");
    int iter_count = 0;
    double optimalPoint = secantMethod(x0, x1, a, b, c, d, e, calculateProfitDerivative, &iter_count);
    
    if (optimalPoint < 0) {
        printf("Failed to find optimal point\n");
        fprintf(output, "Failed to find optimal point\n\n");
        fprintf(output, "Data Points:\n");
        fprintf(output, "Quantity Revenue Cost Profit\n");
        return;
    }

    // If we get here, we have a valid optimal point
    double optimalProfit = calculateProfit(optimalPoint, a, b, c, d, e);
    double error = calculateError(optimalPoint, TRUE_VALUE);
    
    // Save metadata at the start of the file
    saveMetadataToFile(output, a, b, c, d, e, x0, x1, optimalPoint, optimalProfit, iter_count, error);
    
    printf("\nOptimal Results:\n");
    printf("---------------------------\n");
    printf("Optimal quantity: %.2f\n", optimalPoint);
    printf("Maximum profit: %.2f\n", optimalProfit);
    printf("Total iterations: %d\n", iter_count);
    printf("Error percentage: %.2f%%\n", error);

    // Calculate and display data points for plotting
    printTableHeader();


    // Analyze range of quantities
    for (double quantity = MIN_QUANTITY; quantity <= MAX_QUANTITY; quantity += STEP) {
        double revenue = a * quantity - b * pow(quantity, 2);
        double cost = c * pow(quantity, 2) + d * quantity + e;
        double profit = revenue - cost;

        if (revenue < 0) break;

        printTableRow(quantity, revenue, cost, profit);
        saveToFile(quantity, revenue, cost, profit, output);
    }
    
    printTableFooter();
    fclose(output);

    // Create GNUplot script
    FILE *gnuplot = fopen(plotFile, "w");
    fprintf(gnuplot, "set title 'Break-Even Analysis - Dataset %d'\n", datasetNum);
    fprintf(gnuplot, "set xlabel 'Quantity'\n");
    fprintf(gnuplot, "set ylabel 'Amount'\n");
    fprintf(gnuplot, "set grid\n");
    fprintf(gnuplot, "plot '%s' using 1:2 title 'Revenue' with lines, \\\n", resultsFile);
    fprintf(gnuplot, "     '%s' using 1:3 title 'Cost' with lines, \\\n", resultsFile);
    fprintf(gnuplot, "     '%s' using 1:4 title 'Profit' with lines\n", resultsFile);
    fprintf(gnuplot, "pause -1 'Press any key to continue...'\n");
    fclose(gnuplot);

    printf("\nResults have been saved to %s\n", resultsFile);
    printf("Use 'gnuplot %s' to view the graphical analysis\n", plotFile);
}

int main() {
    double a, b, c, d, e;
    
    FILE *input = fopen("dataset.txt", "r");
    if (input == NULL) {
        printf("Error: Cannot open dataset.txt\n");
        return 1;
    }

    // Process each dataset
    for (int i = 1; i <= 5; i++) {
        if (fscanf(input, "%lf %lf %lf %lf %lf", &a, &b, &c, &d, &e) != 5) {
            printf("Error: Invalid data format in dataset.txt\n");
            fclose(input);
            return 1;
        }
        processDataset(i, a, b, c, d, e);
    }

    fclose(input);

    return 0;
}
