#include <iostream>
#include "mpi.h"
#include <vector>

int main (int argc, char** argv){
    int processRank, sizeOfCluster;
    int distro_Array[4] = {39, 72, 129, 42};
    int scattered_Data;
    std::vector<int> vec_data;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &sizeOfCluster);
    MPI_Comm_rank(MPI_COMM_WORLD, &processRank);

    vec_data.resize(sizeOfCluster);

    // MPI_Scatter(&distro_Array, 1, MPI_INT, &scattered_Data, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(&distro_Array, vec_data.size(), MPI_INT, &vec_data.front(), vec_data.size(), MPI_INT, 0, MPI_COMM_WORLD);
    std::cout << "Process " << processRank << " has received " << vec_data.at(0) << " and " << vec_data.at(1) << std::endl;
    MPI_Finalize();
    return 0;
}