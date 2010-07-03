
/*
 *  hello.c
 */

#include <stdio.h>
#include <mpi.h>

#define MSIZE 64

int
main(int argc, char **argv)
{
  char msg[MSIZE];
  int pid, nprocs, i;
  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

  if (pid == 0) {
    for (i = 1; i < nprocs; i++) {
      MPI_Recv(msg, MSIZE, MPI_CHAR, i, 0, MPI_COMM_WORLD, &status);
      fputs(msg, stdout);
    }
  }
  else {
    sprintf(msg, "Hello, nokuno! (from process #%d)\n", pid);
    MPI_Send(msg, MSIZE, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
  }

  MPI_Finalize();

  return 0;
}

