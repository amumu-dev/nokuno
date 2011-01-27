#include <iostream>
using namespace std;

int L[] = {8,5,8};
int N = sizeof(L) / sizeof(int);

int main() {
  int ans = 0;
  while (N > 1) {
    int mii1 = 0, mii2 = 1;
    if (L[mii1] > L[mii2]) swap(mii1, mii2);
    for (int i = 2; i < N; i++) {
      if (L[i] < L[mii1]) {
        mii2 = mii1;
        mii1 = i;
      } else if (L[i] < L[mii2]) {
        mii2 = i;
      }
    }
    int t = L[mii1] + L[mii2];
    ans += t;
    
    if (mii1 == N - 1) swap(mii1, mii2);
    L[mii1] = t;
    L[mii2] = L[N-1];
    N--;
  }
  cout << ans << endl;
}
