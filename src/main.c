#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <windows.h>
    #define SLEEP(ms) Sleep(ms)
    #define GENERATOR "dataset_generator.exe"
    #define ANALYSIS "break_even_analysis.exe"
    #define GNUPLOT "gnuplot"
    #define BACKGROUND_CMD " /B " // Windows background execution
#else
    #include <unistd.h>
    #define SLEEP(ms) sleep(ms/1000)
    #define GENERATOR "./dataset_generator"
    #define ANALYSIS "./break_even_analysis"
    #define GNUPLOT "gnuplot"
    #define BACKGROUND_CMD " &" // Unix background execution
#endif

int main()
{
    printf("=== Profit Analysis Program ===\n\n");
    
    // Run dataset generator
    printf("1. Generating datasets...\n");
    system(GENERATOR);
    
    // Small delay to ensure file writing is complete
    SLEEP(1000);
    
    // Run break-even analysis
    printf("\n2. Running break-even analysis...\n");
    system(ANALYSIS);
    
    // Run gnuplot for all 5 plots simultaneously
    printf("\n3. Generating plots...\n");
    for (int i = 1; i <= 5; i++) {
        char cmd[100];
        sprintf(cmd, "%s plot_%d.gnu%s", GNUPLOT, i, BACKGROUND_CMD);
        system(cmd);
    }
    
    // Small delay to keep program running while plots display
    SLEEP(2000);
    printf("\nProgram completed successfully!\n");
    return 0;
}