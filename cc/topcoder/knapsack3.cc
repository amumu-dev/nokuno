#include <iostream>
using namespace std;

int w[] = {2,1,3,2};
int v[] = {3,2,4,2};
const int n = 4;
const int W = 5;
int dp[n+1][W+1];

int knapsack(int k, int weight) {
  if (dp[k][weight] >= 0) {
    return dp[k][weight];
  }

  int result;
  if (k == n) {
    result = 0;
  } else if (weight < w[k]) {
    result = knapsack(k+1, weight);
  } else {
    result = max(knapsack(k+1, weight), knapsack(k+1, weight-w[k]) + v[k]);
  }
  dp[k][weight] = result;
  return result;
}

int main() {
  memset(dp, -1, sizeof(dp));
  cout << knapsack(0, W) << endl;
}
