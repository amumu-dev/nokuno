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

class TheLargestLuckyNumber {
 public:
  void next(vector<bool> &v) {
    for (int i = 0; i < (int)v.size(); i++) {
      if (v[i] == true) {
        v[i] = false;
      } else {
        v[i] = true;
        return;
      }
    }
    v.push_back(false);
  }
  int bit2int(vector<bool> v) {
    int result = 0;
    for (int i = 0; i < (int)v.size(); i++) {
      result += (int)pow(10., i) * (v[i]?7:4);
    }
    return result;
  }
  int find(int n) {
    vector<bool> v(1);
    v[0] = false;
    int current;
    while (true) {
      int old = bit2int(v);
      next(v);
      current = bit2int(v);
      if (current > n)
        return old;
    }
  }


  // BEGIN CUT HERE
 public:
  void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
 private:
  template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
  void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
  void test_case_0() { int Arg0 = 100; int Arg1 = 77; verify_case(0, Arg1, find(Arg0)); }
  void test_case_1() { int Arg0 = 75; int Arg1 = 74; verify_case(1, Arg1, find(Arg0)); }
  void test_case_2() { int Arg0 = 5; int Arg1 = 4; verify_case(2, Arg1, find(Arg0)); }
  void test_case_3() { int Arg0 = 474747; int Arg1 = 474747; verify_case(3, Arg1, find(Arg0)); }

  // END CUT HERE

};

// BEGIN CUT HERE
int main() {
  TheLargestLuckyNumber ___test;
  ___test.run_test(-1);
}
// END CUT HERE
