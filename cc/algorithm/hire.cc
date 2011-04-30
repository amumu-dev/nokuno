#include <iostream>
#include "hire.h"
using namespace std;

int main() {
  srand(time(NULL)); rand();
  cout << max_hire(10000, 100) << endl;
  return 0;
}
