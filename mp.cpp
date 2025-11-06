#include <iostream>
#include <mpi.h>

int main(int argc, char* argv[]){
    int processRank, sizeOfCluster, message_Item;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &sizeOfCluster);
    MPI_Comm_rank(MPI_COMM_WORLD, &processRank);

    //Create conditionals that specify appropriate process to call MPI_Send et MPI_Recv functions
    //For the example process 1 will try to send out a message to process 2 containing the number 42

    if(processRank == 0){
        message_Item = 42;
        MPI_Send(&message_Item, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
        std::cout << "Sending mesaage containing "<< message_Item << std::endl;
    }
    else if(processRank == 1){
        MPI_Recv(&message_Item, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Received message containing " << message_Item << std::endl;
    }

    MPI_Finalize();

    return 0;
}