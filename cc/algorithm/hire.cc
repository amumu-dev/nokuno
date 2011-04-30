#include <iostream>
#include "shuffle.h"
using namespace std;

int hire(vector<int> &candidates) {
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
int max_hire(int n, int m) {
  int result = 0;
  for (int j = 0; j < n; j++) {
    vector<int> candidates(m);
    for (int i = 0; i < (int)candidates.size(); i++) {
      candidates[i] = i;
    }
    shuffle<int>(candidates);
    int hired = hire(candidates);
    if (hired > result)
      result = hired;
  }
  return result;
}
int main() {
  srand(time(NULL)); rand();
  cout << max_hire(10000, 100) << endl;
  return 0;
}
