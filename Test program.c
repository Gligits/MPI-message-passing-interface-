#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    int rang;
    int p;

    MPI_Init(&argc, &argv);  // Initialize MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rang);  // Get process rank
    MPI_Comm_size(MPI_COMM_WORLD, &p);  // Get total number of processes

    printf("I am process %d out of %d\n", rang, p);


    MPI_Finalize();  // Finalize MPI
    return 0;
}
