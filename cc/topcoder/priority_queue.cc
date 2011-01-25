#include <queue>
#include <iostream>
#include <stdlib.h>
using namespace std;

int main() {
  priority_queue<int> pque;

  for (int i = 0; i < 10; i++) {
    pque.push(rand() % 10);
  }
  
  while (!pque.empty()) {
    cout << pque.top() << endl;
    pque.pop();
  }
}
