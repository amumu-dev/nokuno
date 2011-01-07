#include <iostream>
#include <vector>
using namespace std;

bool sub_summation(int n, int a[], int k, int depth, int sum) {
  if (sum == k) return true;
  if (depth ==n) return false;
  bool left = sub_summation(n, a, k, depth+1, sum);
  bool right = sub_summation(n, a, k, depth+1, sum+a[depth]);
  return left || right;
}

int main(){
  int a[] = {1,2,4,7};
  cout << sub_summation(4,a,13,0,0) << endl;
  cout << sub_summation(4,a,15,0,0) << endl;
}
