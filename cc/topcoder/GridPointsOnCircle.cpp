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

class GridPointsOnCircle {
public:
  bool isPerfectSquare(int i) {
    double s = sqrt((double)i);
    return ceil(s) == floor(s);
  }
  int countPoints(int rSquare) {
    int result = 0;
    for (int i = 1; i <= (int)sqrt(rSquare); i++) {
      if (isPerfectSquare(rSquare - i * i)) {
        result ++;
      }
    }
    return result * 4;
  }

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 4; verify_case(0, Arg1, countPoints(Arg0)); }
	void test_case_1() { int Arg0 = 25; int Arg1 = 12; verify_case(1, Arg1, countPoints(Arg0)); }
	void test_case_2() { int Arg0 = 3; int Arg1 = 0; verify_case(2, Arg1, countPoints(Arg0)); }
	void test_case_3() { int Arg0 = 44; int Arg1 = 0; verify_case(3, Arg1, countPoints(Arg0)); }
	void test_case_4() { int Arg0 = 50; int Arg1 = 12; verify_case(4, Arg1, countPoints(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
  GridPointsOnCircle ___test;
  ___test.run_test(-1);
}
// END CUT HERE
