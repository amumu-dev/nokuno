#include <iostream>
#include "hire.h"
using namespace std;

int main() {
  srand(time(NULL)); rand();
  for (int i = 0; i < 100; i++) {
    cout << average_hire(1000, i) << endl;
  }
  return 0;
}
