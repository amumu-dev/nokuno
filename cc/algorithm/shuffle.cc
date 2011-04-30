#include <iostream>
#include "shuffle.h"
using namespace std;

int main() {
  srand(time(NULL)); rand();
  const int size = 10;
  vector<int> array(size);
  for (int i = 0; i < (int)array.size(); i++) {
    array[i] = i;
  }
  shuffle<int>(array);
  for (int i = 0; i < (int)array.size(); i++) {
    cout << array.at(i) << " ";
  }
  cout << endl;
  return 0;
}
