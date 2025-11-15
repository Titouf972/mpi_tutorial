#include <iostream>
#include "mpi.h"

int main(int argc, char* argv[]){

    int processRank, sizeOfCluster;
    //Initialize the MPI environment
    MPI_Init(&argc, &argv);

    //Get info about the cluster of processors
    MPI_Comm_size(MPI_COMM_WORLD, &sizeOfCluster);
    MPI_Comm_rank(MPI_COMM_WORLD, &processRank);

    //Loop so that program prints out each process in order of thread ID
    for (int i = 0; i < sizeOfCluster; i++){
        //Conditional statement to print only when the loop iteration matches the process rank
        if(i==processRank){
        //Print info to the user
        std::cout << "Hello World from process " << processRank << " of " << sizeOfCluster << std::endl;
        }
        //implements Barrier function to ensure that all processes are synchronized when passing through the loop
        MPI_Barrier(MPI_COMM_WORLD);
    }

    //Close environment (cut communication)
    MPI_Finalize();

    return 0;
}