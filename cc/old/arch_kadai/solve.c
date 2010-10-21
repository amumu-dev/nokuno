/*
 *  $Id: solve.c,v 1.1 2007/07/05 11:42:29 terry Exp $
 *
 *  Simulator of the Gravitational Many-body Problem
 */

#include <stdio.h>
#include <math.h>
#include "gmbp.h"

extern int pid;		/* my process ID */
extern int nprocs;	/* # of parallel processes */

void
solve_gmbp(data_t m[], vector_t x[], vector_t v[])
{
  int n = ceil((double) N / (nprocs-1));
  int step, size, start, end, i, j;
  MPI_Status status;

  if (pid == 0) {
    for (step = 1; step <= T; step++) {
      MPI_Bcast(x, N*3, MPI_DOUBLE, 0, MPI_COMM_WORLD );

      for (i = 1; i < nprocs; i++) {
        size = (i*n > N) ? N-(i-1)*n : n;
        MPI_Recv(&x[(i-1)*n], size*3, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &status);
      }

      if (INFO_STEP > 0 && (step%INFO_STEP == 0 || step == 1 || step == T)) {
        printf(" Time step %5d\n", step);
      }
    }
    for (i = 1; i < nprocs; i++) {
      size = (i*n > N) ? N-(i-1)*n : n;
      MPI_Recv(&v[(i-1)*n], size*3, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &status);
    }
  } else {  // pid > 0
    vector_t a, r;
    data_t tmp, cnst = G*DT;
    start = (pid-1)*n;
    size = (pid*n > N) ? N-(pid-1)*n : n;
    end = start + size;
    for (step = 1; step <= T; step++) {
      MPI_Bcast(x, N*3, MPI_DOUBLE, 0, MPI_COMM_WORLD );

      for (i = start; i < end; i++) {
        a.x = a.y = a.z = 0.0;
        for (j = 0; j < N; j++) {
          if(i != j) {
            r.x = x[j].x - x[i].x;
            r.y = x[j].y - x[i].y;
            r.z = x[j].z - x[i].z;

            tmp = sqrt(r.x*r.x+r.y*r.y+r.z*r.z);
            tmp = 1.0 / (tmp*tmp*tmp) * m[j];
            
            a.x += r.x * tmp;
            a.y += r.y * tmp;
            a.z += r.z * tmp;
            
          }
        }
        v[i].x += a.x*cnst;
        v[i].y += a.y*cnst;
        v[i].z += a.z*cnst;
      }

      for (i = start; i < end; i++) {
        x[i].x += v[i].x*DT;
        x[i].y += v[i].y*DT;
        x[i].z += v[i].z*DT;
      }

      MPI_Send(&x[start], size*3, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }
    MPI_Send(&v[start], size*3, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
  }
}

