#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    int T[10]; 
    int rang;
    int p;
    int N = 10;
    
    MPI_Init(&argc, &argv);  // Initialize MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rang);  // Get process rank
    MPI_Comm_size(MPI_COMM_WORLD, &p);  // Get total number of processes
    
    // initialiser le tableau 
    if (rang == 0) { 
        for (int i = 0; i < N; i++) {
            T[i] = i;
        }
    }

    // MPI_Bcast doit etre executee pour tous les processus; pas besoin de faire de if rang
    MPI_Bcast(T, 10, MPI_INT, 0, MPI_COMM_WORLD);  // l'initiateur envoie et reçoit; les autres ne font que recevoir
    /* ( buffer , nbr val a diffuser , type des valeurs , initiateur numero , le groupe COMM_WORLD ça veut dire tous les processus ) */

    printf("I am process %d \n", rang);
    for (int i = 0; i < N; i++) {
        printf("%d ", T[i]);
    }
    printf("\n");

    MPI_Finalize();  // Finalize MPI
    return 0;
}
