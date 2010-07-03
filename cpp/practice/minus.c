#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv){
	int x = 100;
	if( argc == 2 )
		x = atoi(argv[1]);
	x = ~x+1;
	printf("%d\n",x);
	return 0;
}
