#include <stdio.h>
#include <math.h>

int multiple(int k) {
    double a = (sqrt(5)-1.0)/2.0;
    double temp = (double)k * a;
    int m = 1000;
    return (int) m * (temp - (int)temp);
}
int main() {
    printf("%d\n", multiple(1));
    printf("%d\n", multiple(2));
    printf("%d\n", multiple(3));
    printf("%d\n", multiple(61));
    printf("%d\n", multiple(62));
    printf("%d\n", multiple(63));
    printf("%d\n", multiple(64));
    printf("%d\n", multiple(65));
    return 0;
}
