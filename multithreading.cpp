#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <fstream>
using namespace std;
using namespace chrono;

const int SIZE = 1000;        
const int NUM_MATRICES = 20;  

using Matrix = vector<vector<int>>;

Matrix generateMatrix() {
    Matrix mat(SIZE, vector<int>(SIZE));
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            mat[i][j] = rand() % 10;
    return mat;
}

Matrix multiply(const Matrix &A, const Matrix &B) {
    Matrix C(SIZE, vector<int>(SIZE, 0));
    for (int i = 0; i < SIZE; i++)
        for (int k = 0; k < SIZE; k++)
            for (int j = 0; j < SIZE; j++)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

void worker(int start, int end, vector<Matrix> &matrices, const Matrix &constant) {
    for (int i = start; i < end; i++) {
        multiply(matrices[i], constant);
    }
}

double runThreads(int t, vector<Matrix> &matrices, const Matrix &constant) {
    vector<thread> threads;
    int chunk = NUM_MATRICES / t;

    auto start = high_resolution_clock::now();

    for (int i = 0; i < t; i++) {
        int s = i * chunk;
        int e = (i == t - 1) ? NUM_MATRICES : s + chunk;

        threads.push_back(thread(worker, s, e, ref(matrices), ref(constant)));
    }

    for (auto &th : threads)
        th.join();

    auto end = high_resolution_clock::now();

    return duration<double>(end - start).count();
}

int main() {
    cout << "Generating matrices...\n";

    vector<Matrix> matrices;
    for (int i = 0; i < NUM_MATRICES; i++)
        matrices.push_back(generateMatrix());

    Matrix constant = generateMatrix();

    ofstream file("results.csv");
    file << "Threads,Time\n";

    cout << "Running...\n";

    for (int t = 1; t <= 8; t++) {
        double timeTaken = runThreads(t, matrices, constant);

        cout << "Threads: " << t << " -> Time: " << timeTaken << " sec\n";
        file << t << "," << timeTaken << "\n";
    }

    file.close();

    cout << "Results saved in results.csv\n";
    return 0;
}
