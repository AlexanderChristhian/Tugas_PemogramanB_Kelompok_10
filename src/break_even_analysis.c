#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MIN_QUANTITY 0
#define MAX_QUANTITY 500
#define STEP 20
#define MAX_ITERATIONS 100
#define EPSILON 0.0001

// Function to calculate profit at a given quantity
double calculateProfit(double x, double a, double b, double c, double d, double e) {
    // Revenue: R(x) = a*x - b*x^3 (cubic revenue decay)
    double revenue = a * x - b * pow(x, 3);
    
    // Cost: C(x) = c*x^2 + d*exp(0.01*x) + e (quadratic + exponential costs)
    double cost = c * x * x + d * exp(0.01 * x) + e;
    
    // Profit: P(x) = R(x) - C(x)
    return revenue - cost;
}

// Secant method implementation with detailed output
double secantMethod(double x0, double x1, double a, double b, double c, double d, double e, 
                   double (*func)(double, double, double, double, double, double), int* iter_count) {
    double f0, f1, x2;
    int iterations = 0;
    
    printf("\nSecant Method Iterations:\n");
    printf("---------------------------------------------\n");
    printf("Iter |    x0    |    x1    |    x2    |  P'(x2)  \n");
    printf("---------------------------------------------\n");
    
    do {    
        f0 = func(x0, a, b, c, d, e);
        f1 = func(x1, a, b, c, d, e);
        
        if (fabs(f1 - f0) < EPSILON) {
            printf("Method failed - division by zero\n");
            return -1;
        }
        
        x2 = x1 - f1 * (x1 - x0) / (f1 - f0);
        printf("%3d  | %8.4f | %8.4f | %8.4f | %9.6f\n", 
               iterations, x0, x1, x2, func(x2, a, b, c, d, e));
        
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

void displayCoefficients(double a, double b, double c, double d, double e) {
    printf("\nCoefficients Table:\n");
    printf("+---+--------+\n");
    printf("| a | %6.2f |\n", a);
    printf("| b | %6.4f |\n", b);
    printf("| c | %6.2f |\n", c);
    printf("| d | %6.2f |\n", d);
    printf("| e | %6.2f |\n", e);
    printf("+---+--------+\n");
}

void saveMetadataToFile(FILE *fp, double a, double b, double c, double d, double e,
                       double x0, double x1, double lowBreak,
                       int lowIter, double highBreak, int highIter) {
    fprintf(fp, "Coefficients:\n");
    fprintf(fp, "a = %.2f\n", a);
    fprintf(fp, "b = %.4f\n", b);
    fprintf(fp, "c = %.2f\n", c);
    fprintf(fp, "d = %.2f\n", d);
    fprintf(fp, "e = %.2f\n\n", e);
    
    fprintf(fp, "Initial Points:\n");
    fprintf(fp, "x0 = %.2f\n", x0);
    fprintf(fp, "x1 = %.2f\n\n", x1);
    
    fprintf(fp, "Results:\n");

    double profitRange = highBreak - lowBreak;

    if (fabsl(profitRange) < 0.01) {
        fprintf(fp, "Failed to find Profit-Range");
        fprintf(fp, "\nBreak-Even Result:\n");
        fprintf(fp, "---------------------------\n");
        fprintf(fp, "Break-Even quantity\t: %.2f\n", lowBreak);
        fprintf(fp, "Total iterations\t: %d\n", lowIter);
    } else {
        fprintf(fp, "\nBreak-Even Results:\n");
        fprintf(fp, "---------------------------\n");
        fprintf(fp, "Low Break-Even quantity\t: %.2f\n", lowBreak);
        fprintf(fp, "Total iterations\t: %d\n", lowIter);
        fprintf(fp, "High Break-Even quantity\t: %.2f\n", highBreak);
        fprintf(fp, "Total iterations\t: %d\n", highIter);
        fprintf(fp, "---------------------------\n");
        fprintf(fp, "Profit range\t: %.2f\n", profitRange);
    }
    
    fprintf(fp, "\nData Points:\n");
    fprintf(fp, "%-10s %-12s %-12s %-12s\n", "Quantity", "Revenue", "Cost", "Profit");
    fprintf(fp, "------------------------------------------------\n");
}

void saveDataPoint(FILE *fp, double quantity, double revenue, double cost, double profit) {
    fprintf(fp, "%-10.2f %-12.2f %-12.2f %-12.2f\n", quantity, revenue, cost, profit);
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

    displayCoefficients(a, b, c, d, e);

    FILE *output = fopen(resultsFile, "w");
    if (output == NULL) {
        printf("Error: Cannot create %s\n", resultsFile);
        return;
    }

    // Initial guesses
    double x0 = 0;
    double x1 = 500;

    double xmid = (x0 + x1) / 2;

    printf("\nFinding break-even points...\n");

    int lowIter = 0;
    double lowBreak = secantMethod(x0, xmid, a, b, c, d, e, calculateProfit, &lowIter);
    
    if (lowBreak < 0) {
        printf("Failed to find break-even point\n");
        fclose(output);
        return;
    }

    int highIter = 0;
    double highBreak = secantMethod(xmid, x1, a, b, c, d, e, calculateProfit, &highIter);
    
    if (highBreak < 0) {
        printf("Failed to find break-even point\n");
        fclose(output);
        return;
    }

    // Swap if high break is greater
    if (lowBreak > highBreak) {
        {
            int temp = highIter;
            highIter = lowIter;
            lowIter = temp;
        }
        {
            double temp = highBreak;
            highBreak = lowBreak;
            lowBreak = temp;
        }
    }

    double profitRange = highBreak - lowBreak;

    if (fabsl(profitRange) < 0.01) {
        printf("Failed to find Profit-Range");
        printf("\nBreak-Even Result:\n");
        printf("---------------------------\n");
        printf("Break-Even quantity\t: %.2f\n", lowBreak);
        printf("Total iterations\t: %d\n", lowIter);
    } else {
        printf("\nBreak-Even Results:\n");
        printf("---------------------------\n");
        printf("Low Break-Even quantity\t: %.2f\n", lowBreak);
        printf("Total iterations\t: %d\n", lowIter);
        printf("High Break-Even quantity\t: %.2f\n", highBreak);
        printf("Total iterations\t: %d\n", highIter);
        printf("---------------------------\n");
        printf("Profit range\t: %.2f\n", profitRange);
    }

    saveMetadataToFile(output, a, b, c, d, e, x0, x1, lowBreak, lowIter, highBreak, highIter); 

    printTableHeader();
    for (double quantity = MIN_QUANTITY; quantity <= MAX_QUANTITY; quantity += STEP) {
        double revenue = a * quantity - b * pow(quantity, 3);
        double cost = c * pow(quantity, 2) + d * exp(0.01 * quantity) + e;
        double profit = revenue - cost;

        printf("| %8.2f | %10.2f | %10.2f | %10.2f |\n", quantity, revenue, cost, profit);
        saveDataPoint(output, quantity, revenue, cost, profit);
    }
    printTableFooter();
    
    fclose(output);

    // Create GNUplot script
    FILE *gnuplot = fopen(plotFile, "w");
    fprintf(gnuplot, "set title 'Profit Analysis - Dataset %d'\n", datasetNum);
    fprintf(gnuplot, "set xlabel 'Quantity'\n");
    fprintf(gnuplot, "set ylabel 'Amount'\n");
    fprintf(gnuplot, "set grid\n");
    fprintf(gnuplot, "plot '%s' using 1:2 title 'Revenue' with lines, \\\n", resultsFile);
    fprintf(gnuplot, "     '%s' using 1:3 title 'Cost' with lines, \\\n", resultsFile);
    fprintf(gnuplot, "     '%s' using 1:4 title 'Profit' with lines\n", resultsFile);
    fprintf(gnuplot, "pause -1\n");
    fclose(gnuplot);

    printf("\nResults saved to %s\n", resultsFile);
    printf("Visualize with: gnuplot %s\n", plotFile);
}

int main() {
    FILE *input = fopen("dataset.txt", "r");
    if (input == NULL) {
        printf("Error: Cannot open dataset.txt\n");
        return 1;
    }

    for (int i = 1; i <= 5; i++) {
        double a, b, c, d, e;
        if (fscanf(input, "%lf %lf %lf %lf %lf", &a, &b, &c, &d, &e) != 5) {
            printf("Error reading dataset %d\n", i);
            continue;
        }
        processDataset(i, a, b, c, d, e);
    }

    fclose(input);
    return 0;
}