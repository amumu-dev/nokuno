#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

#define MSIZE 64

#define LOOP 1000000000000.0
#define sqr(x) ((x)*(x))

int main(int argc, char **argv){
  int i;
  char msg[MSIZE];
  int pid, nprocs;
  MPI_Status status;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

  if (pid == 0) {
    while(1) {
      double average = 0.0;
      for (i = 1; i < nprocs; i++) {
        double result = 0.0;
        MPI_Recv(msg, MSIZE, MPI_CHAR, i, 0, MPI_COMM_WORLD, &status);
        sscanf(msg, "%lf", &result);
        average += result;
      }
      printf("%lf\n", average / (nprocs-1) );
    }
  } else {
    srand(time(0)+pid);
    int count = 0;
    for(i = 0; i < LOOP; i++){
      double x = 2.0 * rand() / RAND_MAX;
      double y = 2.0 * rand() / RAND_MAX;
      if( sqr(x-1.0) + sqr(y-1.0) < 1.0 )
        count++;
      if( i % 100000 == 0 ){
        sprintf(msg, "%lf\n", 4.0 * count / i);
        MPI_Send(msg, MSIZE, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
     }
    }
  }

  MPI_Finalize();
  return 0;
}

