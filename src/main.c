#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
    #define SLEEP(ms) Sleep(ms)
    #define GENERATOR "dataset_generator.exe"
    #define ANALYSIS "break_even_analysis.exe"
    #define GNUPLOT "start gnuplot -persist"
#else
    #include <unistd.h>
    #define SLEEP(ms) usleep((ms) * 1000) 
    #define GENERATOR "./src/dataset_generator"
    #define ANALYSIS "./src/break_even_analysis"
    #define GNUPLOT "gnuplot -persist"
#endif

int main()
{
    printf("=== Profit Analysis Program ===\n\n");

    // Step 1: Generate datasets
    printf("1. Generating datasets...\n");
    system(GENERATOR);

    // Step 2: Delay to ensure data files are ready
    SLEEP(1000);

    // Step 3: Run break-even analysis
    printf("\n2. Running break-even analysis...\n");
    system(ANALYSIS);

    // Step 4: Run gnuplot for all 5 plots concurrently (no threading)
    printf("\n3. Generating plots...\n");
    printf("Please press enter or Ctrl+C to exit after plots are displayed.\n");

    for (int i = 1; i <= 5; i++) {
        char cmd[128];
#ifdef _WIN32
        sprintf(cmd, "%s plot_%d.gnu", GNUPLOT, i);
#else
        sprintf(cmd, "%s plot_%d.gnu &", GNUPLOT, i);
#endif
        system(cmd);
        SLEEP(300);
    }

    printf("\nProgram completed successfully!\n");
    return 0;
}
