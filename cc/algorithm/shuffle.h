#ifndef SHUFFLE_H
#define SHUFFLE_H

#include <stdlib.h>
#include <vector>

// shuffle entire array
template<typename T>
void shuffle(std::vector<T> &array) {
  for (int i = 0; i < (int)array.size(); i++) {
    // sample index from rest of array
    int index = i + (int)(((double)rand() / ((double)RAND_MAX+1.0)) * ((double)array.size()-i));
    // swap array[i] and array[index]
    swap(array[i], array[index]);
  }
}

#endif
