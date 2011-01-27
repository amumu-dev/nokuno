#include <iostream>
#include <algorithm>
using namespace std;

int main() {
  const int V[] = {1,5,10,50,100,500};
  int C[] = {3,2,1,3,0,2};
  int A = 620;
  int ans = 0;

  for (int i = 5; i >= 0; i--) {
    int num = min(C[i], A/V[i]);
    ans += num;
    A -= V[i] * num;
  }
  cout << ans << endl;
}
