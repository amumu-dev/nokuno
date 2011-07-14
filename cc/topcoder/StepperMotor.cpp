#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <climits>
#include <cfloat>
#include <map>
#include <utility>
#include <set>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <sstream>
#include <complex>
#include <stack>
#include <queue>
using namespace std;
static const double EPS = 1e-5;
typedef long long ll;

long long mod(long long t, long long n) {
  return (t < 0) ? t % n + n : t % n;
}
class StepperMotor {
public:
  int rotateToNearest(int n, int current, vector <int> target) {
    long long result = 2147483647;
    long long c = mod(current, n);
    for (int i = 0; i < (int)target.size(); i++) {
      long long temp = mod((long long)target[i] - c, n);
      if (temp > n / 2) {
        temp -= n;
      }
      if (abs(temp) < abs(result)) {
        result = temp;
      }
      if (abs(temp) == abs(result) && temp > result) {
        result = temp;
      }
    }
    return result;
  }

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 10; int Arg1 = 0; int Arr2[] = {-2, -3, 4, 5, 6, 9999999}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = -1; verify_case(0, Arg3, rotateToNearest(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 314159; int Arr2[] = {10, 8, 6, 4, 2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 1; verify_case(1, Arg3, rotateToNearest(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 1; int Arg1 = -2147483648; int Arr2[] = {-2147483648, -2147483648, 2147483647, 2147483647}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 0; verify_case(2, Arg3, rotateToNearest(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 23; int Arg1 = 10; int Arr2[] = {64077, -567273, 105845, -279980, 35557,
-286190, -652879, -431665, -634870, -454044}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = -11; verify_case(3, Arg3, rotateToNearest(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 1000000000; int Arg1 = 1403466951; int Arr2[] = {1233321992, 11423750, 1356595134, 1130863021, 1183514764,
1943494859, 1714480374, 1529875954, 1738756510, 1190153525}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = -46871817; verify_case(4, Arg3, rotateToNearest(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
  StepperMotor ___test;
  ___test.run_test(-1);
}
// END CUT HERE
