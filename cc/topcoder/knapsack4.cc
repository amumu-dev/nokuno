#include <iostream>
using namespace std;

int w[] = {2,1,3,2};
int v[] = {3,2,4,2};
const int n = 4;
const int W = 5;
int dp[n+1][W+1];

int knapsack(int k, int weight) {
  memset(dp, 0, sizeof(dp));
  for (int i = n-1; i >= 0; i--) {
    for (int j = 0; j <= W; j++) {
      if (j < w[i]) {
        dp[i][j] = dp[i+1][j];
      } else {
        dp[i][j] = max(dp[i+1][j], dp[i+1][j-w[i]]+v[i]);
      }
    }
  }
  return dp[0][W];
}

int main() {
  cout << knapsack(0, W) << endl;
}
