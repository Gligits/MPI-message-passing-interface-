#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    int T[10];
    int rang, p;
    int N = 10;
    int suiv, prec;
    MPI_Status status;
    int tag = 0;

    MPI_Init(&argc, &argv);  // Initialize MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rang);  // Get process rank
    MPI_Comm_size(MPI_COMM_WORLD, &p);  // Get total number of processes
    
    suiv = (rang + 1) % p;  // Next process in the ring
    prec = (rang - 1 + p) % p;  // Previous process in the ring (with wrap-around)

    // Initialize the array on process 0
    if (rang == 0) {
        for (int i = 0; i < N; i++) {
            T[i] = i;
        }
    }

    // Send data to the next process and receive from the previous process
    if (rang == 0) {
        // Process 0 starts by sending its data to the next process
        MPI_Send(T, N, MPI_INT, suiv, tag, MPI_COMM_WORLD);
        MPI_Recv(T, N, MPI_INT, prec, tag, MPI_COMM_WORLD, &status);
    } else {
        // Other processes receive from their previous neighbor, then send to the next
        MPI_Recv(T, N, MPI_INT, prec, tag, MPI_COMM_WORLD, &status);
        MPI_Send(T, N, MPI_INT, suiv, tag, MPI_COMM_WORLD);
    }
   
    // Print the array on each process to verify the ring communication
    printf("I am process %d, received array: ", rang);
    for (int i = 0; i < N; i++) {
        printf("%d ", T[i]);
    }
    printf("\n");

    MPI_Finalize();  // Finalize MPI
    return 0;
}
