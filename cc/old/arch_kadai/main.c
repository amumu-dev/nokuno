
/*
 *  $Id: main.c,v 1.1 2007/07/05 11:42:29 terry Exp $
 */

#include "gmbp.h"

int
main(int argc, char **argv)
{
  data_t m[N];
  vector_t x[N], v[N];

  initialize(&argc, &argv);
  load_data(m, x, v);

  start_timer();
  solve_gmbp(m, x, v);
  stop_timer();

  verify_results(x, v, "c");
  finalize();

  return 0;
}

