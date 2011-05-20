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

class KindAndCruel {
 public:
  int mymin(int a, int b) {
    if (a < 0) return b;
    if (b < 0) return a;
    return min(a,b);
  }
  int dfs(string &field, int K, int C, int x, int t) {
    if (t > K * C * field.size())
      return -1;
    if (x == field.size()-1)
      return t;

    switch (field[x]) {
      case '.':
        switch (field[x+1]) {
          case '.':
            return dfs(field, K, C, x+1, t+1);
          case 'K':
            if ((t+1) % K != 0)
              return mymin(
                  dfs(field, K, C, x+1, t+1),
                  dfs(field, K, C, x, t+1));
            else
              return dfs(field, K, C, x, t+1);
          case 'C':
            if ((t+1) % C == 0)
              return mymin(
                  dfs(field, K, C, x+1, t+1),
                  dfs(field, K, C, x, t+1));
            else
              return dfs(field, K, C, x, t+1);
        }
        break;
      case 'K':
        switch (field[x+1]) {
          case '.':
            return dfs(field, K, C, x+1, t+1);
          case 'K':
          case 'C':
            if ((t+1) % C == 0)
              return dfs(field, K, C, x+1, t+1);
            else if (x>0 && field[x-1] =='.')
              return dfs(field, K, C, x-1, t+1);
            else
              return -1;
        }
        break;
      case 'C':
        switch (field[x+1]) {
          case '.':
            return dfs(field, K, C, x+1, t+1);
          case 'K':
            if ((t+1) % K != 0)
              return dfs(field, K, C, x+1, t+1);
            else if (x>0 && field[x-1] =='.')
              return dfs(field, K, C, x-1, t+1);
            else
              return -1;
          case 'C':
            return -1;
        }
        break;
    }
  }
  int crossTheField(string field, int K, int C) {
    // TODO if K==1 replace 'K' with '.'
    return dfs(field, K, C, 0, 0);
  }


  // BEGIN CUT HERE
 public:
  void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
 private:
  template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
  void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
  void test_case_0() { string Arg0 = "..."; int Arg1 = 2; int Arg2 = 5; int Arg3 = 2; verify_case(0, Arg3, crossTheField(Arg0, Arg1, Arg2)); }
  void test_case_1() { string Arg0 = ".K.C."; int Arg1 = 3; int Arg2 = 4; int Arg3 = 5; verify_case(1, Arg3, crossTheField(Arg0, Arg1, Arg2)); }
  void test_case_2() { string Arg0 = ".CCCC."; int Arg1 = 3; int Arg2 = 5; int Arg3 = -1; verify_case(2, Arg3, crossTheField(Arg0, Arg1, Arg2)); }
  void test_case_3() { string Arg0 = ".CKKKKCKKKKC.KKKKCKKKKC.CKKKKCKKKKCKKKKCKKKKCKKKK."; int Arg1 = 5; int Arg2 = 5; int Arg3 = 60; verify_case(3, Arg3, crossTheField(Arg0, Arg1, Arg2)); }

  // END CUT HERE

};

// BEGIN CUT HERE
int main() {
  KindAndCruel ___test;
  ___test.run_test(-1);
}
// END CUT HERE
