#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to generate one set of coefficients
void generateCoefficients(double *a, double *b, double *c, double *d, double *e) {
    // Revenue coefficients (R(x) = a*x - b*x^3)
    *a = 200 + (rand() % 101);  // 200–300 (higher revenue per unit)
    *b = 0.0005 + (rand() % 6)/10000.0;  // 0.0005–0.0011 (gentler decay)
    
    // Cost coefficients (C(x) = c*x^2 + d*exp(0.01x) + e)
    *c = 0.10 + (rand() % 15)/100.0;  // 0.10–0.25 (steeper cost growth)
    *d = 100 + (rand() % 101);  // 100–200 (faster cost acceleration)
    *e = 2000 + (rand() % 3001);  // 2000–5000
}


int main(int argc, char **argv) {
    // Seed random number generator
    srand(argc > 1 ? atoi(argv[1]) : time(NULL)); // Use CLI arg seed if specified

    FILE *fp;
    fp = fopen("dataset.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    printf("Generating 5 datasets:\n\n");

    // Generate 5 sets of coefficients
    for (int i = 0; i < 5; i++) {
        double a, b, c, d, e;
        generateCoefficients(&a, &b, &c, &d, &e);

        // Write coefficients to file
        fprintf(fp, "%.2f %.4f %.2f %.2f %.2f\n", a, b, c, d, e);

        printf("Dataset %d:\n", i + 1);
        printf("Revenue function: R(x) = %.2fx - %.4fx^3\n", a, b);
        printf("Cost function: C(x) = %.2fx^2 + %.2fe^(0.01x) + %.2f\n\n", c, d, e);
    }

    fclose(fp);
    printf("All datasets generated successfully!\n");

    return 0;
}
