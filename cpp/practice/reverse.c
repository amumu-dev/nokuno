#define _GNU_SOURCE
#include <stdio.h>
#include <math.h>

int reverse(int x);
void print_result(int y);

int main(int argc,char **argv){
  int y;
  if( argc < 2 ){
    y = reverse( 127 );
    print_result(y);
  }
  else{
    int i;
    for( i = 1; i < argc; i++){
      int x;
      sscanf(argv[i], "%d", &x);
      y = reverse( x );
      print_result(y);
    }
  }
  printf("\n");
  return 0;
}
int reverse(int x){
  int keta = 1 + (int)log10(x);
  int i,y=0;
  for( i=0; i<keta; i++){
    y += (int)(x / pow10(i)) % 10 * pow10(keta-i-1);
  }
  //  printf("x:%d keta:%d, y:%d, test:%d",x,keta,y,pow10(2));
  return y;
}
void print_result(int y){
  printf("%d ",y);
}
