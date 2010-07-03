#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;

void shuffle(int a[], int n) {
    for (int i = 0; i < n; i++) {
        int j = rand() % (n-i);
        int tmp = a[i];
        a[i] = a[i+j];
        a[i+j] = tmp;
    }
}
int main() {
    srand(time(NULL));
    int a[] = {4,1,8,3};
    int n = sizeof(a)/sizeof(int);
    shuffle(a, n);
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}
