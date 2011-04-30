#ifndef HIRE_H
#define HIRE_H

#include "shuffle.h"

int hire(std::vector<int> &candidates) {
  int result = 0;
  int best = 0;
  for (int i = 1; i < (int)candidates.size(); i++) {
    if (candidates[i] > candidates[best]) {
      best = i;
      result ++;
    }
  }
  return result;
}
int test_hire(int m) {
  std::vector<int> candidates(m);
  for (int i = 0; i < (int)candidates.size(); i++) {
    candidates[i] = i;
  }
  shuffle<int>(candidates);
  return hire(candidates);
}

int max_hire(int n, int m) {
  int result = 0;
  for (int j = 0; j < n; j++) {
    int hired = test_hire(m);
    if (hired > result)
      result = hired;
  }
  return result;
}
#endif
