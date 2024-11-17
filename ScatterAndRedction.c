#include <mpi.h>
#include <stdio.h>
// SCATTER + REDUCTION 
int main(int argc, char* argv[]) {
    int A[4][4]; // 2D array for initial data
    int rang;      // Rank of the process
    int p;         // Total number of processes
    int N = 4;    // Size of the matrix
    int tranche;   // Number of rows per process
    int PF;        // Final product result
    int PR = 1;    // Partial product result
    MPI_Status status;

    MPI_Init(&argc, &argv);  // Initialize MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rang);  // Get process rank
    MPI_Comm_size(MPI_COMM_WORLD, &p);  // Get total number of processes

    tranche = (N / p) * N;  // Divide total elements among processes
    int B[tranche];         // 1D array buffer for scattered rows

    // Initialize the matrix A on process 1
    if (rang == 1) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                A[i][j] = (i + 1);  // Example initialization
            }
        }
    }

    // Scatter the rows of matrix A to all processes
    MPI_Scatter(A, tranche, MPI_INT, B, tranche, MPI_INT, 1, MPI_COMM_WORLD);

    // Compute the partial product of all elements in the received rows
    for (int i = 0; i < tranche; i++) {
        PR *= B[i];
    }

    // Perform a global reduction to compute the total product
    MPI_Allreduce(&PR, &PF, 1, MPI_INT, MPI_PROD, MPI_COMM_WORLD);

    // Print the final result from each process
    printf("I am process %d, final product: %d\n", rang, PF);

    MPI_Finalize();  // Finalize MPI
    return 0;
}
