#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to generate one set of coefficients
void generateCoefficients(double *a, double *b, double *c, double *d, double *e) {
    *a = 100 + (rand() % 51); // Random value between 100-150 (higher revenue rate)
    *b = 0.05 + ((double)(rand() % 5) / 100); // Random value between 0.05-0.10 (lower decay)
    *c = 0.02 + ((double)(rand() % 3) / 100); // Random value between 0.02-0.05 (lower quadratic cost)
    *d = 30 + (rand() % 21); // Random value between 30-50 (reasonable variable cost)
    *e = 500 + (rand() % 501); // Random value between 500-1000 (lower fixed cost)
}

int main() {
    FILE *fp;
    fp = fopen("dataset.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Seed random number generator
    srand(time(NULL));

    printf("Generating 5 datasets:\n\n");

    // Generate 5 sets of coefficients
    for (int i = 0; i < 5; i++) {
        double a, b, c, d, e;
        generateCoefficients(&a, &b, &c, &d, &e);

        // Write coefficients to file
        fprintf(fp, "%.2f %.2f %.2f %.2f %.2f\n", a, b, c, d, e);

        printf("Dataset %d:\n", i + 1);
        printf("Revenue function: R(x) = %.2fx - %.2fx^2\n", a, b);
        printf("Cost function: C(x) = %.2fx^2 + %.2fx + %.2f\n\n", c, d, e);
    }

    fclose(fp);
    printf("All datasets generated successfully!\n");

    return 0;
}
