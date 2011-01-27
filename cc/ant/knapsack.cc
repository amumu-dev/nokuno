#include <iostream>
using namespace std;

int w[] = {2,1,3,2};
int v[] = {3,2,4,2};
int n = 4;
int W = 5;

int knapsack(int k, int weight, int value) {
  if (weight > W)
    return 0;
  if (k >= n)
    return value;
  int left = knapsack(k+1, weight, value);
  int right = knapsack(k+1, weight+w[k], value+v[k]);
  return left>right ? left : right;
}

int main() {
  cout << knapsack(0, 0, 0) << endl;
}
