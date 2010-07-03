#include <stdio.h>

struct List {
	int x;
	List *next;
};
List *add(List *first,int x){
	List n = {x,first};
	return new List(n);
}
void print_list(List *first) {
	List *list = first;
	while( list != NULL ) {
		printf("%d\n",list->x);
		list = list->next;
	}
}

List *reverse(List *first) {
	List *result = NULL;
	while( first != NULL ){
		List n = {first->x,result};
		result = new List(n);
		first = first->next;
	}
	return result;
}
int main(){
	List *first = NULL;
	first = add(first,0);
	first = add(first,1);
	first = add(first,2);
	print_list(first);
	printf("----\n");
	List *result = reverse(first);
	print_list(result);
	return 0;
}