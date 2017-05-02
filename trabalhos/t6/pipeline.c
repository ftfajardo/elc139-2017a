#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int ntasks, rank, msgin = 0,msgout;
    MPI_Status status;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    //mestre
    if (rank == 0) {        
        MPI_Send(&msgin, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
        printf("ID %d envia %d \n", rank, msgin);
    }
    //outros processos	
    else if (rank < ntasks-1) {
            MPI_Recv(&msgout, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            printf("ID %d recebe %d \n", rank, msgout);
            msgin = msgout+1;// somei soh aqui nao sei se era pra somar antes e depois
            MPI_Send(&msgin, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
            printf("ID %d envia %d \n", rank, msgin);
    }	
	//final	
    else {     
        MPI_Recv(&msgout, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);       
	printf("ID %d recebe %d\n", rank, msgout);
    }

    MPI_Finalize();

}
