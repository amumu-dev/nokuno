#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

uint64_t hash_function (char *kbuf) {
	char *str = kbuf;
	uint64_t result = 751; 
	uint64_t ksiz = strlen(kbuf);
	while(ksiz--) {
		result = result * 37 + *(uint8_t *)kbuf++; 
	}
	uint64_t hash = result % 999983;
	printf("hash of %s is %d\n", str, hash);
	return hash;
}

int main(){
	hash_function("okunoyou");
	hash_function("okuno");
	hash_function("nokuno");
	hash_function("t");
	hash_function("s");
	hash_function("r");
	hash_function("q");
	return 0;
}
