#include <iostream>
using namespace std;

void max_heapify(int *array, int size, int i) {
  while(true) {
    int left = i * 2 + 1;
    int right = i * 2 + 2;
    int largest = i;
    if (left < size && array[left] > array[i]) {
      largest = left;
    }
    if (right < size && array[right] > array[i]) {
      largest = right;
    }
    if (largest != i) {
      swap(array[i], array[largest]);
      i = largest;
    } else {
      break;
    }
  }
}
void heap_sort(int *array, int size) {
  for (int i = size/2-1; i>=0; i--) {
    max_heapify(array, size, i);
  }
  for (int i = size-1; i >= 0; i--) {
    swap(array[0], array[i]);
    size --;
    max_heapify(array, size, 0);
  }
}

int main() {
  int array[] = {5,4,3,2,1};
  int size = 5;
  heap_sort(array, size);
  for (int i = 0; i < size; i++)
    cout << array[i] << " ";
  cout << endl;
  return 0;
}
