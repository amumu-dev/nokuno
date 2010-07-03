
/*
 *  $Id: data.c,v 1.1 2007/07/05 11:42:29 terry Exp $
 *
 *  Functions for loading data and verifying results
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "gmbp.h"

typedef long rand_t;
typedef unsigned seed_t;

extern int pid, nprocs;

static data_t (*const sqrt_func)(data_t) = sqrt;
static data_t (*const sin_func)(data_t) = sin;
static data_t (*const cos_func)(data_t) = cos;
static data_t (*const atan_func)(data_t) = atan;
static data_t (*const exp_func)(data_t) = exp;
static data_t (*const log_func)(data_t) = log;
static rand_t (*const rand_func)() = random;
static void (*const srand_func)(seed_t) = srandom;
static int (*const finite_func)(data_t) = finite;
static const data_t rand_norm = 1.0/((data_t)RAND_MAX+1.0);
static const data_t pi = M_PI;
static const data_t epsilon = 1e-15;

static const char *const data_dir = "/etc/skel/data";
static const int nprobs = 5;

#ifdef USE_MPI
static const int mpi_seed_t = MPI_UNSIGNED;
#endif

static data_t min = -1.0, max = 1.0;
static data_t m = 0.0, sigma = 1.0;
static data_t lambda_exp = 1.0;
static data_t mu = 0.0, b = 1.0;
static data_t lambda_poi = 1.0;
static seed_t seed = 0;
static int prob_no = 0;
static int fixed_flag = 0;
static int random_flag = 0;

static __inline data_t
sq(data_t x)
{
  return x*x;
}

static __inline data_t
norm2(vector_t p)
{
  return sq(p.x)+sq(p.y)+sq(p.z);
}

static __inline data_t
norm(vector_t p)
{
  return sqrt_func(norm2(p));
}

static __inline data_t
rand_regular()
{
  return rand_norm*rand_func();
}

static __inline data_t
rand_uniform()
{
  return min+(max-min)*rand_regular();
}

static __inline data_t
rand_normal()
{
  static data_t next;
  static int dup = 0;
  data_t t, u;

  if (dup) {
    dup = 0;
    return next;
  }
  else {
    t = sigma*sqrt_func(-2.0*log_func(1.0-rand_regular()));
    u = 2.0*pi*rand_regular();

    dup = 1;
    next = m+t*sin_func(u);
    return m+t*cos_func(u);
  }
}

static __inline data_t
rand_exponential()
{
  return -(log_func(1.0-rand_regular())/lambda_exp);
}

static __inline data_t
rand_laplace()
{
  return rand_func()%2 ? mu-b*log_func(1.0-rand_regular())
                       : mu+b*log_func(1.0-rand_regular());
}

static __inline data_t
rand_poisson()
{
  data_t t;
  int k;

  t = exp_func(lambda_poi)*rand_regular();
  for (k = 0; t > 1.0; k++)  t *= rand_regular();

  return k;
}

static void
set_seed()
{
  if (fixed_flag)  seed = 0;
  else {
    seed = time(NULL);
#ifdef USE_MPI
    MPI_Bcast(&seed, 1, mpi_seed_t, 0, MPI_COMM_WORLD);
#endif
  }

  srand_func(seed);
}

static void
generate_mass_array(data_t a[])
{
  data_t (*rand_next)();
  int dist, i;

  m = mu = 1.0/(data_t)N;
  min = m*0.5;  max = m*1.5;

  dist = fixed_flag ? 2 : rand_func()%3;

  switch (dist) {
  case 0:   /* [1/2N, 3/2N) */
    rand_next = rand_uniform;
    break;
  case 1:   /* N(1/N, 1/10N) */
    sigma = m*1e-1;
    rand_next = rand_normal;
    break;
  default:  /* La(1/N, 1/10N) */
    b = m*1e-1;
    rand_next = rand_laplace;
    break;
  }

  for (i = 0; i < N; i++)
    do  a[i] = rand_next();  while (a[i] < min || a[i] > max);
}

static void
generate_vector_array(vector_t p[])
{
  data_t (*rand_next[3])();
  int dist, i;

  for (i = 0; i < 3; i++) {
    dist = fixed_flag ? 2 : rand_func()%3;

    switch (dist) {
    case 0:   /* [-1, 1) */
      min = -1.0;  max = 1.0;
      rand_next[i] = rand_uniform;
      break;
    case 1:   /* N(0, 1) */
      m = 0.0;  sigma = 1.0;
      rand_next[i] = rand_normal;
      break;
    default:  /* La(0, 1) */
      mu = 0.0;  b = 1.0;
      rand_next[i] = rand_laplace;
      break;
    }
  }

  for (i = 0; i < N; i++) {
    p[i].x = rand_next[0]();
    p[i].y = rand_next[1]();
    p[i].z = rand_next[2]();
  }
}

static int
read_data_file(const char fname[], data_t m[], vector_t x[], vector_t v[])
{
  FILE *fp;
  int i;

  if ((fp = fopen(fname, "r")) == NULL)  return 0;

  for (i = 0; i < N; i++)
    fscanf(fp, "%lg %lg %lg %lg %lg %lg %lg",
           &m[i], &x[i].x, &x[i].y, &x[i].z, &v[i].x, &v[i].y, &v[i].z);
  fclose(fp);

  return 1;
}

void
load_data(data_t m[], vector_t x[], vector_t v[])
{
  char fname[256], pname[256];

#ifdef USE_RANDOM_DATA
  random_flag = 1;
#endif
#ifdef USE_FIXED_DATA
  fixed_flag = 1;
#endif
  set_seed();

  if (!random_flag) {
    if (!fixed_flag)  prob_no = rand_func()%nprobs;
    sprintf(fname, "%s/%d/prob%d.dat", data_dir, N, prob_no);
    if (!read_data_file(fname, m, x, v))  random_flag = 1;
  }
  if (random_flag) {
    if (fixed_flag)  prob_no = nprobs;
    generate_mass_array(m);
    generate_vector_array(x);
    generate_vector_array(v);
  }

  if (pid == 0) {
    if (!random_flag || fixed_flag)
      sprintf(pname, "%d", prob_no);
    else
      strcpy(pname, "random");

    printf("\n*** Simulation parameters ***\n"
           "Number of particles: %d\n"
           "Number of time steps: %d\n"
           "Interval of time steps: %.1g\n"
           "Data set No.: %s\n",
           N, T, DT, pname);
  }
}

static void
print_coordinate(FILE *fp, vector_t p)
{
  fprintf(fp, "%.20g %.20g %.20g", p.x, p.y, p.z);
}

static void
print_coordinate_polar(FILE *fp, vector_t p)
{
  data_t r, th, ph;

  r = norm(p);
  th = atan_func(sqrt_func(sq(p.x)+sq(p.y))/p.z)/pi*180.0;
  ph = atan_func(p.y/p.x)/pi*180.0;
  ph += (p.x < 0.0) ? 180.0 : (p.y < 0.0) ? 360.0 : 0.0;

  fprintf(fp, "%.20g %.20g %.20g", r, th, ph);
}

static void
print_momentum(FILE *fp, data_t m, vector_t v)
{
  fprintf(fp, "%.20g %.20g %.20g", m*v.x, m*v.y, m*v.z);
}

static void
print_momentum_total(FILE *fp, data_t m[], vector_t v[])
{
  vector_t p;
  int i;

  p.x = p.y = p.z = 0.0;
  for (i = 0; i < N; i++) {
    p.x += m[i]*v[i].x;
    p.y += m[i]*v[i].y;
    p.z += m[i]*v[i].z;
  }

  fprintf(fp, "%.20g %.20g %.20g", p.x, p.y, p.z);
}

static void
print_momentum_angular(FILE *fp, data_t m, vector_t r, vector_t v)
{
  vector_t L;

  L.x = m*(r.y*v.z-r.z*v.y);
  L.y = m*(r.z*v.x-r.x*v.z);
  L.z = m*(r.x*v.y-r.y*v.x);

  fprintf(fp, "%.20g %.20g %.20g", L.x, L.y, L.z);
}

static void
print_energy_total(FILE *fp, data_t m[], vector_t x[], vector_t v[])
{
  data_t Ek, Ep;
  vector_t r;
  int i, j;

  Ek = Ep = 0.0;
  for (i = 0; i < N; i++) {
    Ek += m[i]*norm2(v[i]);

    for (j = i+1; j < N; j++) {
      r.x = x[j].x - x[i].x;
      r.y = x[j].y - x[i].y;
      r.z = x[j].z - x[i].z;
      Ep += m[i]*m[j]/norm(r);
    }
  }
  Ek *= 0.5;
  Ep *= -G;

  fprintf(fp, "%.20g", Ek+Ep);
}

void
dump_data(data_t m[], vector_t x[], vector_t v[], int step)
{
  FILE *fp;
  char fname[256];
  int i;

  sprintf(fname, "step%d.dat", step);
  if ((fp = fopen(fname, "w")) == NULL)  return;

  for (i = 0; i < N; i++) {
    fprintf(fp, "%.20g ", m[i]);
    print_coordinate(fp, x[i]);
    putc(' ', fp);
    print_coordinate(fp, v[i]);
    putc('\n', fp);
  }
  fclose(fp);
}

static data_t
quality_index(vector_t a[], vector_t b[])
{
  data_t n1, n2;
  vector_t tmp;
  int i;

  n1 = n2 = 0.0;
  for (i = 0; i < N; i++) {
    n1 += norm2(a[i]);

    tmp.x = b[i].x-a[i].x;
    tmp.y = b[i].y-a[i].y;
    tmp.z = b[i].z-a[i].z;
    n2 += norm2(tmp);
  }

  return sqrt_func(n2/n1);
}

void
verify_results(vector_t x[], vector_t v[], const char lang[])
{
  char fname[256], qx[256], qv[256], verif[256];
  vector_t xT[N], vT[N];
  data_t m[N], ex, ev;

  if (pid != 0)  return;

  sprintf(fname, "%s/%d/%s/result%d.dat", data_dir, N, lang, prob_no);
  if ((!random_flag || fixed_flag) && read_data_file(fname, m, xT, vT)) {
    ex = quality_index(xT, x);
    ev = quality_index(vT, v);

    sprintf(qx, "%.1e", ex);
    sprintf(qv, "%.1e", ev);
    strcpy(verif,
           finite_func(ex) && ex < epsilon &&
           finite_func(ev) && ev < epsilon ? "Successful" : "FAILED");
  }
  else {
    strcpy(qx, "N/A");
    strcpy(qv, "N/A");
    strcpy(verif, "not performed");
  }

  printf("\n*** Overall results ***\n"
         "# of processes: %d\n"
         "Quality index (2-norm) of x: %s\n"
         "Quality index (2-norm) of v: %s\n"
         "Verification: %s\n",
         nprocs, qx, qv, verif);
}

/* for calling from Fortran */
void
load_data_(data_t m[], vector_t x[], vector_t v[])
{
  load_data(m, x, v);
}

/* for calling from Fortran */
void
dump_data_(data_t m[], vector_t x[], vector_t v[], int *sp)
{
  dump_data(m, x, v, *sp);
}

/* for calling from Fortran */
void
verify_results_(vector_t x[], vector_t v[])
{
  verify_results(x, v, "f90");
}

