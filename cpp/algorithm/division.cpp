#include <stdio.h>
#include <string.h>

unsigned int division(const char *str) {
    unsigned int result = 0;
    unsigned int m = 259;
    for (int i = 0; i < strlen(str); i++) {
        unsigned int r = (unsigned int)str[i];
        unsigned int x = 1;
        for (int j = 0; j < 32 * i; j++) {
            x = (x * 2) % m;
        }
        result = (result + (x * r) % m) % m;
    }
    return result;
}
int main() {
    printf("test: %d\n", division("test"));
    printf("est: %d\n", division("est"));
    printf("st: %d\n", division("st"));
    printf("t: %d\n", division("t"));
    printf("tes: %d\n", division("tes"));
    printf("te: %d\n", division("te"));
    printf("t: %d\n", division("t"));
    return 0;
}
