#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

#define MSIZE 3

int main(int argc, char **argv){
  int i;
  double msg[MSIZE];
  int pid, nprocs;
  MPI_Status status;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

  if (pid == 0) {
    for (i = 0; i < nprocs; i++) {
      double result = 0.0;
      MPI_Recv(msg, MSIZE, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &status);
      printf("%lf %lf %lf\n", msg[0], msg[1], msg[2]);
    }
  }
    msg[0] = 0.0;
    msg[1] = 0.5;
    msg[2] = 1.0;
    MPI_Send(msg, MSIZE, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);

  MPI_Finalize();
  return 0;
}

