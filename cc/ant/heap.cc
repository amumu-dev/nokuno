#include <iostream>
#include <stdlib.h>
using namespace std;

#define MAX_N 10
int heap[MAX_N], sz = 0;

void push(int x) {
  int i = sz++;

  while (i > 0) {
    int p = (i - 1) / 2;

    if (heap[p] <= x) break;
    // swap
    heap[i] = heap[p];
    i = p;
  }
  heap[i] = x;
}

int pop() {
  int ret = heap[0];
  int x = heap[--sz];
  int i = 0;
  while (i * 2 + 1 < sz) {
    int a = i * 2 + 1, b = i * 2 + 2;
    if ( b < sz && heap[b] < heap[a]) a = b;
    if (heap[a] >= x) break;
    heap[i] = heap[a];
    i = a;
  }
  heap[i] = x;
  return ret;
}

int main() {
  for (int i = 0; i < 10; i++) {
    push(rand() % 10);
  }
  
  while (sz > 0) {
    cout << pop() << endl;
  }
}
