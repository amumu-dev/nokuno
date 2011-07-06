#include <stdlib.h>
#include <stdio.h>
#define MAX 100000

int main(int argc, char *argv[]){
    int i,j,f;
    int max = MAX;
    if(argc > 1)
        max = atof(argv[1]);
    for(i = 3; i <= max; i++){
        f = 0;
        for(j = 2; j < i-1; j++){
            if( i % j == 0 ) {
                f = 1;
                break;
            }
        }
        if( f == 0 )
            printf("%d\n",i);
    }
    return 0;
}
