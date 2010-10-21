
/*
 *  $Id: gmbp.h,v 1.1 2007/07/05 12:05:13 terry Exp $
 */

#define N 512			/* number of particles */
#define T 4000			/* number of time steps */
#define DT 0.001		/* interval of time steps */
#define G 6.67428e-2		/* the gravitational constant */
/* #define G 6.67428e-11 */	/* real value, currently not used */

#define USE_MPI
/* #define USE_RANDOM_DATA */
/* #define USE_FIXED_DATA */

#define INFO_STEP 200
#define DUMP_STEP 0

#ifdef __STDC__
#ifdef USE_MPI
#ifdef __cplusplus
#include <mpi++.h>
using namespace MPI;
#else
#include <mpi.h>
#endif
#endif

typedef double data_t;
#ifdef __cplusplus
struct vector_t { data_t x, y, z; };
#else
typedef struct vector_t { data_t x, y, z; } vector_t;
#endif

#ifdef __cplusplus
extern "C" {
#endif
extern void start_timer();
extern void stop_timer();
extern void initialize(int *, char ***);
extern void finalize();
extern void dump_data(data_t [], vector_t [], vector_t [], int);
extern void load_data(data_t [], vector_t [], vector_t []);
extern void verify_results(vector_t [], vector_t [], const char lang[]);
extern void solve_gmbp(data_t [], vector_t [], vector_t []);
#ifdef __cplusplus
}
#endif
#else
#ifdef USE_MPI
      include 'mpif.h'
#endif
#endif

