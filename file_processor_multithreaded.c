#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include <time.h>

 
//two separate mutexes for two different shared variables: `total_sum` and the pair of `global_min` and `global_max`.
pthread_mutex_t sum_mutex, min_max_mutex;

// Global variables for the total sum, and the global minimum and maximum values
long long total_sum = 0; // To keep track of the sum of all elements
long long global_min = LLONG_MAX; // Initialize to maximum possible long long value
long long global_max = LLONG_MIN; // Initialize to minimum possible long long value

// Struct to pass multiple arguments to the thread function
typedef struct {
    long long *data; // Pointer to the array segment each thread will process
    int start_index; // Starting index of the segment
    int end_index;   // Ending index of the segment
} ThreadArgs;

// The function executed by each thread
void *thread_function(void *arg) {
    // Cast the argument to ThreadArgs pointer
    ThreadArgs *args = (ThreadArgs *)arg;

    // Local variables for each thread to calculate sum, min, and max
    long long local_sum = 0;
    long long local_min = LLONG_MAX;
    long long local_max = LLONG_MIN;

    // Loop through the assigned segment of the array
    for (int i = args->start_index; i < args->end_index; i++) {
        local_sum += args->data[i]; // Add the value to the local sum
        if (args->data[i] < local_min) local_min = args->data[i]; // Update local min
        if (args->data[i] > local_max) local_max = args->data[i]; // Update local max
    }

    // Lock the sum_mutex before updating the global sum
    pthread_mutex_lock(&sum_mutex);
    total_sum += local_sum; // Update the global sum
    pthread_mutex_unlock(&sum_mutex); // Unlock the mutex

    // Lock the min_max_mutex before updating global min and max
    pthread_mutex_lock(&min_max_mutex);
    if (local_min < global_min) global_min = local_min; // Update global min
    if (local_max > global_max) global_max = local_max; // Update global max
    pthread_mutex_unlock(&min_max_mutex); // Unlock the mutex

    return NULL; 
}

int main(int argc, char *argv[]) {
    // Check for proper command-line argument usage
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open the file for reading
    FILE *file = fopen(argv[1], "r");
    if (!file) { // Check if file opening failed then display error message
        perror("File opening failed");
        exit(EXIT_FAILURE);
    }

    // Count the number integers in the file
    int count = 0, temp;
    while (fscanf(file, "%d", &temp) == 1) count++;
    rewind(file); // Go back to the beginning of the file

    // Allocate memory for the array
    long long *array = malloc(count * sizeof(long long));
    if (!array) {
        perror("Memory allocation failed");
        fclose(file); // Close the file if memory allocation fails
        exit(EXIT_FAILURE);
    }

    // Read the integers from the file into the array
    for (int i = 0; i < count; i++) fscanf(file, "%lld", &array[i]);
    fclose(file); // Close the file

    // Determine the number of threads to create, default is 4
    int num_threads = (argc == 3) ? atoi(argv[2]) : 4;
    pthread_t threads[num_threads]; // Array to store thread identifiers
    ThreadArgs args[num_threads]; // Array of arguments for each thread

    // Calculate the length of the array segment each thread will process
    int segment_length = count / num_threads;

    // Initialize the mutexes
    pthread_mutex_init(&sum_mutex, NULL);
    pthread_mutex_init(&min_max_mutex, NULL);

    // Start the clock to measure the computation time
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    // Create the threads
    for (int i = 0; i < num_threads; i++) {
        args[i].data = array; // Assign array pointer
        args[i].start_index = i * segment_length; // Calculate start index
        args[i].end_index = (i == num_threads - 1) ? count : (i + 1) * segment_length; // Calculate end index
        pthread_create(&threads[i], NULL, thread_function, (void *)&args[i]); // Create thread
    }

    // Wait for all threads to complete
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Stop the clock and calculate elapsed time
    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;

    // Output the computed results
    printf("Final Sum: %lld\n", total_sum);
    printf("Minimum: %lld\n", global_min);
    printf("Maximum: %lld\n", global_max);
    printf("Elapsed Time: %f seconds\n", elapsed_time);

    // Cleanup: Destroy the mutexes and free the allocated memory
    pthread_mutex_destroy(&sum_mutex);
    pthread_mutex_destroy(&min_max_mutex);
    free(array);

    return 0;
}
