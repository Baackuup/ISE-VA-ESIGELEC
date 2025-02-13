# Parallel Programming Laboratory Setup and Exercises

This guide provides a detailed overview of the setup and exercises for the ESIGELEC Parallel Programming course. You will use a high-performance server with advanced CPU and GPU hardware to explore parallel programming concepts.

---

## Hardware and Environment
- **CPU**: High-end server CPUs with 16 cores (32 cores total, 64 threads).
- **RAM**: 512 GB.
- **GPU**: NVIDIA A100 Ampere GPUs with 80 GB memory.

All coding will be performed on a server environment accessed via the ROOC platform, using Visual Studio Code (VSCode).

---

## Setting Up the Environment

### 1. Connect to the Server
1. Open your browser and go to: [https://rooc.esigelec.fr](https://rooc.esigelec.fr).
2. Log in using your ESIGELEC credentials.
3. Select the "Parallel Programming and Computer Vision" virtual laboratory.
   - For **Laboratories 1 and 2**, choose "CPU uniquement".
   - For **Laboratory 3**, choose "Accélération GPU".

### 2. Prepare the Workspace
1. Open a terminal and create a workspace folder in your home directory.
2. Use the following steps if your environment crashes:
   - Go to `File > Hub Control Panel`.
   - Click "Stop My Server" and then "Start My Server".
3. Always log out of the server when finished.

### 3. Tools Used
- **VSCode**: Used for editing and running code.
- **Makefile**: Automates the build process.
- **CUDA**: For GPU programming in Laboratory 3.
- **Spreadsheet Software**: For plotting and analyzing results.

---

## Laboratory Exercises

### Laboratory 1: Benchmarks

#### Objective:
- Understand code performance measurements.
- Learn how to use benchmarking tools.

#### Steps:
1. Download and uncompress the benchmark project into your workspace.
2. Open the project in VSCode, compile, and run it.
3. Analyze the execution time of a function for different input data sizes. The results are saved in a CSV file.
4. Plot the execution time against data size using spreadsheet software.
5. Modify the `run_once` function to measure the following:
   - `sum_array`
   - `nbdiv_array`
   - `frequencies_array`
6. Compare execution time trends (e.g., linear, quadratic) for each function.

---

### Laboratory 2: Threads

#### Part A: Hello World (CPU)
1. Create a `hello-cpu` directory in your workspace.
2. Write a multithreaded "Hello World" program in `hello.cpp` using `pthread`.
3. Compile and run the code using the following `Makefile`:
   ```makefile
   CC := g++
   CCFLAGS := -Wall -Wextra
   PROJECT := hello

   $(PROJECT): hello.cpp
       $(CC) $(FLAGS) $< -o $@

   clean:
       rm -f $(PROJECT)
   ```
4. Modify the program to observe thread synchronization and barriers.

#### Part B: Conway’s Game of Life (CPU)
1. Parallelize Conway's Game of Life using `pthread`.
2. Measure the performance with different world sizes and thread counts.
3. Analyze the results and submit them in the required format.

---

### Laboratory 3: GPGPU & CUDA

#### Part A: Hello World (GPU)
1. Create a `hello-gpu` directory in your workspace.
2. Write a simple CUDA program (`hello.cu`) that outputs thread and block information.
3. Compile and run using the following `Makefile`:
   ```makefile
   CC := nvcc
   CCFLAGS := -Wall
   PROJECT := hello

   INCLUDE := /usr/local/cuda/include
   LIBRARY := /usr/local/cuda-11.8/targets/x86_64-linux/lib

   $(PROJECT): $(PROJECT).cu
       $(CC) $(FLAGS) -I$(INCLUDE) $^ -o $@ -L$(LIBRARY)

   clean:
       rm -f $(PROJECT)
   ```
4. Experiment with CUDA variables (`gridDim`, `blockIdx`, `blockDim`, `threadIdx`) to understand their behavior.

#### Part B: Conway’s Game of Life (GPU)
1. Parallelize Conway's Game of Life using CUDA.
2. Measure performance with different grid sizes and block sizes.
3. Compare the execution time to the CPU implementation.

---

## Submission
- Submit all required results and reports through the Teams assignment platform.
- Ensure your source code is clean, well-commented, and formatted correctly.

---

For additional information on Conway’s Game of Life, check these references:
- [Wikipedia: Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)
- [ConwayLife](https://conwaylife.com)
