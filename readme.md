# Multithreading Matrix Multiplication Assignment

The assignment focuses on analyzing the performance of multithreading using matrix multiplication:

### 1. Matrix Generation
- Generated multiple random matrices of size \( N \times N \).
- Used a constant matrix for multiplication with all generated matrices.

### 2. Multithreading Implementation
- Implemented multithreading using `std::thread` in C++.
- Divided the workload across threads (T = 1 to 8).
- Each thread processes a subset of matrices.

### 3. Performance Analysis
- Measured execution time for different thread counts.
- Observed how increasing threads affects performance.
- Stored results in a CSV file for further analysis.

---

##  Solution

- The solution is implemented in **C++ using multithreading**.
- Execution results are saved in a CSV file:

 `results.csv`


##  Observations

- Execution time decreases initially as the number of threads increases.
- After a certain point, performance gain reduces due to:
  - Thread management overhead
  - CPU core limitations
  - Context switching
 
  <img width="568" height="419" alt="image" src="https://github.com/user-attachments/assets/7a2a8584-1037-4f16-96aa-b3a84629871c" />


