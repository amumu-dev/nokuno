#include <stdio.h>

void func(int array[]) {
    printf("func: %d\n", sizeof(array)/sizeof(int));
}
void func2(int *array) {
    printf("func2: %d\n", sizeof(array)/sizeof(int));
}
void func3(int array[3]) {
    printf("func3: %d\n", sizeof(array)/sizeof(int));
}
int main() {
    int array[] = {1,2,3};
    printf("main: %d\n", sizeof(array)/sizeof(int));
    func(array);
    func2(array);
    func3(array);
    return 0;
}
