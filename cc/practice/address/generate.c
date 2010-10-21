#include <stdio.h>
#include <stdlib.h>

char *str[] = {
  "nokuno@nokuno.jp",
  "test@test.jp",
  "moe@moemoe.ac.jp",
  "okuno@soft.ics.keio.ac.jp",
  "fr020473@ics.keio.ac.jp",
  "nokuno@social-ime.com",
  "english@difficult.en",
};
int main(int argc, char **argv){
  int i;
  srand(time());
  int num = argc>1 ? atoi(argv[1]) : 100;
  for( i=0; i<num; i++){
    int size = sizeof(str) / sizeof(char*);
    int index = (double)size*rand()/RAND_MAX;
    printf("%s\n", str[index]);
  }
  return 0;
}
