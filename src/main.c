#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#ifdef _WIN32
    #include <windows.h>
    #define SLEEP(ms) Sleep(ms)
    #define GENERATOR "dataset_generator.exe"
    #define ANALYSIS "break_even_analysis.exe"
    #define GNUPLOT "gnuplot"
#else
    #include <unistd.h>
    #define SLEEP(ms) sleep(ms/1000)
    #define GENERATOR "./src/dataset_generator"
    #define ANALYSIS "./src/break_even_analysis"
    #define GNUPLOT "gnuplot"
#endif

// Function to run gnuplot for a specific plot file
void* run_gnuplot(void* arg) {
    int plot_number = *(int*)arg;
    char cmd[100];
    sprintf(cmd, "%s plot_%d.gnu", GNUPLOT, plot_number);
    system(cmd);
    return NULL;
}

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
    
    // Run gnuplot for all 5 plots using threads
    printf("\n3. Generating plots...\n");
    pthread_t threads[5];
    int plot_numbers[5];

    printf("Please press enter of ctrl + c multiple times to stop the program.\n");
    
    for (int i = 0; i < 5; i++) {
        plot_numbers[i] = i + 1;
        pthread_create(&threads[i], NULL, run_gnuplot, &plot_numbers[i]);
    }
    
    // Wait for all threads to finish
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("\nProgram completed successfully!\n");
    return 0;
}