# Single-and-Multi-threaded-File-Processor


## Overview

The project contrasts a single-threaded approach with a multi-threaded solution to process data from various input files. It evaluates the efficiency of multi-threading in handling computational tasks, particularly beneficial for large datasets and intensive data processing operations.

## Key Components

### 1. Data Handling

- **Input Files:** Reads integer data from input files.
- **Memory Management:** Dynamically allocates memory for data storage.
- **File Operations:** Manages file I/O operations efficiently using standard C functions.

### 2. Single-Threaded Approach

- **Functionality:** Computes total sum, minimum, and maximum values using a sequential (single-threaded) method.
- **Performance Evaluation:** Measures execution times for different dataset sizes (`data_tiny`, `data_small`, `data_medium`, `data_large`) to establish baseline performance.

### 3. Multi-Threaded Implementation

- **Concurrency:** Utilizes `pthread` library for multi-threading.
- **Thread Management:** Spawns multiple threads to concurrently compute local sums, minima, and maxima across segmented datasets.
- **Mutex Locks:** Ensures thread safety with mutex locks (`sum_mutex` and `min_max_mutex`) when updating shared global variables (`total_sum`, `global_min`, `global_max`).

### 4. Performance Evaluation

- **Comparative Analysis:** Evaluates and compares execution times between single-threaded and multi-threaded approaches.
- **Scalability:** Highlights benefits of multi-threading for reducing computation time, especially for large-scale data processing tasks.

## Features

- **Single-threaded processing**: Computes the sum, minimum, and maximum values using a single thread.
- **Multi-threaded processing**: Uses multiple threads to partition and process the dataset, ensuring thread-safe computation of sum, minimum, and maximum values.
- **Timing**: Measures and compares the processing time for single-threaded and multi-threaded implementations.
- **Command-line arguments**: The program takes input file name and number of threads as command-line arguments.
- **Dynamic memory allocation**: Allocates memory dynamically based on the dataset size.


## Requirements

- Ensure a POSIX-compliant operating system that supports pthreads (e.g., Linux, macOS).
- GCC compiler for C programming (`gcc` and `g++`).

### Running the Project

1. **Compile:** 
To compile the project, run the following command:

```sh
make
```

### Running the Program

#### Single-threaded Program

```sh
./file_processor_singlethreaded <data_file>
```

#### Multi-threaded Program

```sh
./file_processor_multithreaded <data_file> <num_threads>
```

- `<data_file>`: Path to the dataset file (e.g., `data_small.txt`).
- `<num_threads>`: Number of threads to launch for processing. If not provided, defaults to 4 threads.

### Cleaning Up

To clean the build files, run:

```sh
make clean
```

