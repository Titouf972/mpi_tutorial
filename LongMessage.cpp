#include <iostream>
#include <string>
#include "mpi.h"

int main(int argc, char *argv[]) {
  int processRank;
  int dest = 0;
  int tag = 0;
  int sizeOfCluster;
  std::string message;
  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &sizeOfCluster);
  MPI_Comm_rank(MPI_COMM_WORLD, &processRank);
  if(processRank != dest){
    message = "Greeting from process " + std::to_string(processRank);
    MPI_Send(message.c_str(), message.size(), MPI_CHAR, dest, tag, MPI_COMM_WORLD);
  }else{
    for (int source = 1; source < sizeOfCluster; source++){

      char buffer[100];

      MPI_Recv(buffer, 100, MPI_CHAR, source, tag,
               MPI_COMM_WORLD, &status);

        //Number of elements received
      int count_element;
      MPI_Get_count(&status, MPI_CHAR, &count_element);

      auto mes = std::string{buffer, count_element};
      message = mes;
      std::cout << message << std::endl;
    }
  }
  MPI_Finalize();

  return 0; 
}
