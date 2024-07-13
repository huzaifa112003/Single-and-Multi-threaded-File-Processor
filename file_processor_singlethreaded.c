#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

// Global variables for the total sum, and the global minimum and maximum values
long long total_sum = 0; // To keep track of the sum of all elements
long long global_min = LLONG_MAX; // Initialize to maximum possible long long value
long long global_max = LLONG_MIN; // Initialize to minimum possible long long value

// Struct to pass multiple arguments to the processing function
typedef struct {
    long long *data; // Pointer to the array
    int start_index; // Starting index of the segment
    int end_index;   // Ending index of the segment
} ThreadArgs;

// The function executed for processing the data
void process_data(ThreadArgs *args) {
    // Local variables to calculate sum, min, and max
    long long local_sum = 0;
    long long local_min = LLONG_MAX;
    long long local_max = LLONG_MIN;

    // Loop through the assigned segment of the array
    for (int i = args->start_index; i < args->end_index; i++) {
        local_sum += args->data[i]; // Add the value to the local sum
        if (args->data[i] < local_min) local_min = args->data[i]; // Update local min
        if (args->data[i] > local_max) local_max = args->data[i]; // Update local max
    }

    // Update the global variables
    total_sum += local_sum;
    if (local_min < global_min) global_min = local_min;
    if (local_max > global_max) global_max = local_max;
}

int main(int argc, char *argv[]) {
    // Check for proper command-line argument usage
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open the file for reading
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("File opening failed");
        exit(EXIT_FAILURE);
    }

    // Count the number integers in the file
    int count = 0, temp;
    while (fscanf(file, "%d", &temp) == 1) count++;
    rewind(file); 

    // Allocate memory for the array
    long long *array = malloc(count * sizeof(long long));
    if (!array) {
        perror("Memory allocation failed");// If memory allocation failed
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Read the integers from the file into the array
    for (int i = 0; i < count; i++) fscanf(file, "%lld", &array[i]);
    fclose(file);

    ThreadArgs args; // Create an instance of ThreadArgs
    args.data = array;
    args.start_index = 0; // Start from the beginning
    args.end_index = count; // Process till the end

    // Start the clock to measure the computation time
    clock_t start_time = clock();

    // Process the data
    process_data(&args);

    // Stop the clock and calculate elapsed time
    clock_t end_time = clock();
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Output the computed results
    printf("Final Sum: %lld\n", total_sum);
    printf("Minimum: %lld\n", global_min);
    printf("Maximum: %lld\n", global_max);
    printf("Elapsed Time: %f seconds\n", elapsed_time);

    // Cleanup
    free(array);

    return 0;
}
