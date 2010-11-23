#include <stdio.h>
#include <math.h>

int data[] = {
	6,
	3,
	8,
	1,
	4,
	7,
	11,
	-3,
	2,
};
int size = sizeof(data)/sizeof(int);
int pow2(int x) {
	int result = 1;
	for(int i=0;i<x;i++)
		result = result*2;
	return result;
}
int search(int x){
	int i=0, j=0, k=0;
	while(i<size){
		int k2=k+pow2(j);
		if(data[i]==x)
			return 1;
		else if(data[i]>x)
			i=k2+(i-k)*2;
		else if(data[i]<x)
			i=k2+(i-k)*2+1;
		k=k2;
		j++;
	}
	return 0;
}
int main(){
	printf("%d\n",search(2));
	return 0;
}

