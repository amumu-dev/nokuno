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

int log10(int x) { return ceil(log(x) / log(10)); }
int pow10(int x) { return floor(pow(10., x)); }
int get(int n, int i) { return (n / pow10(i)) % 10; }

class UniqueDigits {
public:
  bool isUnique(int n) {
    for (int i = 0; i < log10(n) - 1; i++) {
      int ii = get(n, i);
      for (int j = i+1; j < log10(n); j++) {
        int jj = get(n, j);
        if (ii == jj) {
          return false;
        }
      }
    }
    return true;
  }
  int count(int n) {
    int result = 0;
    for (int i = 1; i < n; i++) {
      if (isUnique(i)) {
        result ++;
      }
    }
    return result;
  }

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 21; int Arg1 = 19; verify_case(0, Arg1, count(Arg0)); }
	void test_case_1() { int Arg0 = 101; int Arg1 = 90; verify_case(1, Arg1, count(Arg0)); }
	void test_case_2() { int Arg0 = 1001; int Arg1 = 738; verify_case(2, Arg1, count(Arg0)); }
	void test_case_3() { int Arg0 = 1; int Arg1 = 0; verify_case(3, Arg1, count(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
  UniqueDigits ___test;
  ___test.run_test(-1);
}
// END CUT HERE
