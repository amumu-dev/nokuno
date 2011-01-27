#include <iostream>
using namespace std;

int w[] = {2,1,3,2};
int v[] = {3,2,4,2};
int n = 4;
int W = 5;

int knapsack(int k, int weight) {
  if (k >= n)
    return 0;
  int left = knapsack(k+1, weight);
  if (weight-w[k] < 0)
    return left;
  int right = knapsack(k+1, weight-w[k]) + v[k];
  return left>right ? left : right;
}

int main() {
  cout << knapsack(0, W) << endl;
}
