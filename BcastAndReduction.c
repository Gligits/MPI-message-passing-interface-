#include <mpi.h>
#include <stdio.h>

// Bcast + Reduction
int main(int argc, char* argv[]) {
    int A[4][4];  // 2D array for initial data
    int rang;     // Rank of the process
    int p;        // Total number of processes
    int N = 4;    // Size of the matrix (NxN)
    int tranche;  // Number of rows per process
    int PF;       // Final product result
    int PR = 1;   // Partial product result

    MPI_Init(&argc, &argv);  // Initialize MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rang);  // Get process rank
    MPI_Comm_size(MPI_COMM_WORLD, &p);  // Get total number of processes

    tranche = N / p;  // Rows per process
    if (N % p != 0) {
        if (rang == 0) {
            printf("Error: Number of processes must evenly divide %d rows.\n", N);
        }
        MPI_Finalize();
        return -1;
    }

    // Initialize the matrix A on process 1
    if (rang == 1) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                A[i][j] = i + 1;  // Example initialization
            }
        }
    }

    // Broadcast the matrix A to all processes
    MPI_Bcast(A, N * N, MPI_INT, 1, MPI_COMM_WORLD);

    // Each process computes the partial product for its assigned rows
    for (int i = rang * tranche; i < (rang + 1) * tranche; i++) {
        for (int j = 0; j < N; j++) {
            PR *= A[i][j];  // Multiply elements in the row
        }
    }

    // Perform a global reduction to compute the total product
    MPI_Allreduce(&PR, &PF, 1, MPI_INT, MPI_PROD, MPI_COMM_WORLD);

    // Print the final result from each process
    printf("I am process %d, final product: %d\n", rang, PF);

    MPI_Finalize();  // Finalize MPI
    return 0;
}
