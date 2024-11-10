#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    int T[10];
    int rang, p;
    int N = 10;
    MPI_Status status;
    int tag = 0;

    MPI_Init(&argc, &argv);  // Initialize MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rang);  // Get process rank
    MPI_Comm_size(MPI_COMM_WORLD, &p);  // Get total number of processes

    // Initialize the array on process 0
    if (rang == 0) {
        for (int i = 0; i < N; i++) {
            T[i] = i;
        }
    }

    // Peer-to-peer communication: Process 0 sends data to all other processes
    if (rang == 0) {
        for (int dest = 1; dest < p; dest++) {  // Skip sending to itself
            MPI_Send(T, N, MPI_INT, dest, tag, MPI_COMM_WORLD);
        }
    } else {
        // All other processes receive data from process 0
        MPI_Recv(T, N, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
    }

    // Print the array on each process to verify peer-to-peer communication
    printf("I am process %d, received array: ", rang);
    for (int i = 0; i < N; i++) {
        printf("%d ", T[i]);
    }
    printf("\n");

    MPI_Finalize();  // Finalize MPI
    return 0;
}
