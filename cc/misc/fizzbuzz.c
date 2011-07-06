#include <stdio.h>

int main() {
    int i;
    printf("Hello, World!\n");
    for (i = 0; i < 100; i++) {
        if (i % 3 == 0)
            printf("Fizz");
        if (i % 5 == 0)
            printf("Buzz");
        if (i % 3 != 0 && i % 5 != 0)
            printf("%d", i);
        printf("\n");
    }
    return 0;
}
