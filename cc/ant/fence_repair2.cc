#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int L[] = {8,5,8};
int N = sizeof(L) / sizeof(int);

int main() {
  int ans = 0;
  
  priority_queue<int, vector<int>, greater<int> > que;
  for (int i = 0; i < N; i++) {
    que.push(L[i]);
  }

  while (que.size() > 1) {
    int l1, l2;
    l1 = que.top();
    que.pop();
    l2 = que.top();
    que.pop();

    ans += l1 + l2;
    que.push(l1 + l2);
  }
  cout << ans << endl;
}
