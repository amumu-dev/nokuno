#include <iostream>
#include <vector>
using namespace std;

#include "succinct_bit_vector.h"

int GetValue(const SuccinctBitVector &b, const vector<int> &v, int i) {
  if (b.Get(i) == false) { return 0; }
  return v[b.Rank(i) - 1];
}

int main() {
  SuccinctBitVector         b;
  vector<int> v;

  b.Set(5); v.push_back(10);
  b.Set(100); v.push_back(20);
  b.Set(180); v.push_back(30);
  b.Build();

  cout << "5: " << GetValue(b, v, 5) << endl;
  cout << "100: " << GetValue(b, v, 100) << endl;
  cout << "180: " << GetValue(b, v, 180) << endl;
  cout << "200: " << GetValue(b, v, 200) << endl;
  return 0;
}

