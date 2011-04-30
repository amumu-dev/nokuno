#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;

// shuffle entire array
template<typename T>
void shuffle(vector<T> &array) {
  for (int i = 0; i < array.size(); i++) {
    // sample index from rest of array
    int index = i + (int)(((double)rand() / ((double)RAND_MAX+1.0)) * ((double)array.size()-i));
    // swap array[i] and array[index]
    T temp = array[i];
    array[i] = array[index];
    array[index] = temp;
  }
}

int main() {
  srand(time(NULL)); rand();
  const int size = 10;
  vector<int> array(size);
  for (int i = 0; i < array.size(); i++) {
    array[i] = i;
  }
  shuffle<int>(array);
  for (int i = 0; i < array.size(); i++) {
    cout << array.at(i) << " ";
  }
  cout << endl;
  return 0;
}
