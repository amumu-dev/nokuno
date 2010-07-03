#include <stdlib.h>
#include <stdio.h>

int data[] = {
	-50,
	50,
	600,
	-100,
	5,
	-200,
	10,
	-300,
	200,
	500,
	300,
	0,
	100,
};
int size = sizeof(data)/sizeof(int);
int i,j;
void marge(int *left, int*right, int f) {
	int n=right-left;
	if(n>1)
		marge(left,left+n/2,n%2);
	if(n+f>1)
		marge(right,right+(n+f)/2,(n+f)%2);
	{
		int copy[n*2+f];
		for(i=0;i<n*2+f;i++){
			copy[i]=*(left+i);
		}
		int *l = copy;
		int *r = copy+n;
		for(i=0;i<n*2+f;i++){
			if(l<copy+n && r<copy+n*2+f) {
				if(*l < *r) {
					left[i]=*l; l++;
				} else {
					left[i]=*r; r++;
				}
			} else if(l<copy+n) {
				left[i]=*l; l++;
			} else if(r<copy+n*2+f){
				left[i]=*r; r++;
			} else
				fprintf(stderr,"error\n");
		}
	}
}

int main(){
	marge(data,data+size/2,size%2);
	//printf("%d\n",size);
	for(i=0;i<size;i++){
		printf("%d\n",data[i]);
	}
	return 0;
}
