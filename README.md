# Single-and-Multi-threaded-File-Processor
Here is a detailed README file for your GitHub repository based on the provided assignment details.

---

# Multi-threaded File Processor

## Overview

This project is a multi-threaded file processor implemented in C using the POSIX Threads API. The program reads a large dataset from a file, processes it using multiple threads, and computes the sum, minimum, and maximum values in the dataset. The project demonstrates the use of synchronization mechanisms to ensure thread safety and efficient resource utilization.

## Objectives

- Develop a multi-threaded C program that processes a large dataset concurrently.
- Use synchronization mechanisms to ensure thread safety.
- Efficiently manage resources and avoid memory leaks.
- Implement proper error handling for file operations and thread creation.

## Features

- **Single-threaded processing**: Computes the sum, minimum, and maximum values using a single thread.
- **Multi-threaded processing**: Uses multiple threads to partition and process the dataset, ensuring thread-safe computation of sum, minimum, and maximum values.
- **Timing**: Measures and compares the processing time for single-threaded and multi-threaded implementations.
- **Command-line arguments**: The program takes input file name and number of threads as command-line arguments.
- **Dynamic memory allocation**: Allocates memory dynamically based on the dataset size.

## File Structure

- `processor_singlethreaded.c`: Single-threaded implementation.
- `processor_multithreaded.c`: Multi-threaded implementation.
- `Makefile`: Contains compile, build, and clean targets for the project.
- `report.pdf`: Documentation on data structures, algorithms, and performance comparison.

## Requirements

- POSIX Threads API
- C Compiler (gcc)

## Usage

### Compilation

To compile the project, run the following command:

```sh
make
```

### Running the Program

#### Single-threaded Program

```sh
./processor_singlethreaded <data_file>
```

#### Multi-threaded Program

```sh
./processor_multithreaded <data_file> <num_threads>
```

- `<data_file>`: Path to the dataset file (e.g., `data_small.txt`).
- `<num_threads>`: Number of threads to launch for processing. If not provided, defaults to 4 threads.

### Cleaning Up

To clean the build files, run:

```sh
make clean
```

## Implementation Details

### Single-threaded Program

1. Reads the dataset from a file into a dynamic array.
2. Calculates the sum, minimum, and maximum values in the dataset.
3. Measures and prints the processing time.

### Multi-threaded Program

1. Reads the dataset from a file into a dynamic array.
2. Creates a specified number of worker threads to process the dataset.
3. Partitions the data among the threads.
4. Computes the sum, minimum, and maximum values using thread-safe mechanisms.
5. Measures and prints the processing time.

### Timing

The timing code for both single-threaded and multi-threaded implementations measures the elapsed time for processing the dataset. It uses `clock` and `clock_gettime` functions to ensure accurate time measurement.

## Error Handling

- Proper error handling for file operations and thread creation.
- Ensures that memory allocated dynamically is freed after use.

