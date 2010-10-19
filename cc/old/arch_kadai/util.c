
/*
 *  $Id: util.c,v 1.1 2007/07/05 11:42:29 terry Exp $
 *
 *  Functions for setup and completion, etc.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "gmbp.h"

typedef double wtime_t;

int pid;	/* my process ID */
int nprocs;	/* # of parallel processes */

static wtime_t start, stop;

static __inline wtime_t
get_wtime()
{
  struct timeval tm;

  gettimeofday(&tm, NULL);

  return tm.tv_sec + (wtime_t)tm.tv_usec*1e-6;
}

void
start_timer()
{
#ifdef USE_MPI
  MPI_Barrier(MPI_COMM_WORLD);
#endif
  start = get_wtime();
}

void
stop_timer()
{
#ifdef USE_MPI
  MPI_Barrier(MPI_COMM_WORLD);
#endif
  stop = get_wtime();
}

void
initialize(int *argcp, char ***argvp)
{
#ifdef USE_MPI
  MPI_Init(argcp, argvp);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
#else
  pid = 0;
  nprocs = 1;
#endif
}

void
finalize()
{
  if (pid == 0)
    printf("Elapsed time for simulation: %.6f [sec]\n\n", stop-start);

#ifdef USE_MPI
  MPI_Finalize();
#endif
}

/* for calling from Fortran */
void
start_timer_()
{
  start_timer();
}

/* for calling from Fortran */
void
stop_timer_()
{
  stop_timer();
}

/* for calling from Fortran */
void
initialize_()
{
  initialize(NULL, NULL);
}

/* for calling from Fortran */
void
finalize_()
{
  finalize();
}

