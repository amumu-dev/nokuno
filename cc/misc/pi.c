#include <stdlib.h>
#include <stdio.h>

#define LOOP 1000000000000.0
#define sqr(x) ((x)*(x))

/* モンテカルロ法による円周率計算 */
int main(){
  double i;
  double count = 0;
  srand(time());
  for(i = 0; i < LOOP; i++){
    double x = 2.0 * rand() / RAND_MAX;
    double y = 2.0 * rand() / RAND_MAX;
    if( sqr(x-1.0) + sqr(y-1.0) < 1.0 )
      count++;
    if( (int)i % 10000000 == 0 )
      printf("%f\n",4.0 * count / i);
  }
  return 0;
}
