#include <iostream>
using namespace std;

int fact(int n){
  if (n==0) return 1;
  return n*fact(n-1);
}
int fib(int n){
  if (n<=1) return n;
  return fib(n-1) + fib(n-2);
}
#define MAX_N 1000
int memo[MAX_N + 1];
int fib_memo(int n) {
  if (n<=1) return n;
  if (memo[n] != 0) return memo[n];
  return memo[n] = fib_memo(n-1) + fib_memo(n-2);
}
int main(){
  cout << fact(10) << endl;
  cout << fib_memo(40) << endl;
  cout << fib(40) << endl;
}
