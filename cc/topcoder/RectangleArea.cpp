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

class RectangleArea {
public:
  int minimumQueries(vector <string> known) {
    int result = 0;
    for (int x = 0; x < (int)known.size(); x++) {
      for (int y = 0; y < (int)known[0].size(); y++) {
        for (int i = 0; i < (int)known.size(); i++) {
          for (int j = 0; j < (int)known[0].size(); j++) {
            if (x!=i && y!=j) {
              if (known[x][y] == 'N' && known[i][j] == 'Y' && known[x][j] == 'Y' && known[i][y] == 'Y') {
                known[x][y] = 'Y';
              }
            }
          }
        }
        if (known[x][y] == 'N') {
          known[x][y] = 'Y';
          result ++;
        }

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
  void test_case_0() { string Arr0[] = {"NN",
    "NN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(0, Arg1, minimumQueries(Arg0)); }
  void test_case_1() { string Arr0[] = {"YNY",
    "NYN",
    "YNY"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(1, Arg1, minimumQueries(Arg0)); }
  void test_case_2() { string Arr0[] = {"YY",
    "YY",
    "YY",
    "YY"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(2, Arg1, minimumQueries(Arg0)); }
  void test_case_3() { string Arr0[] = {"NNNNNNNNNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; verify_case(3, Arg1, minimumQueries(Arg0)); }
  void test_case_4() { string Arr0[] = {"NNYYYNN",
    "NNNNNYN",
    "YYNNNNY",
    "NNNYNNN",
    "YYNNNNY"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(4, Arg1, minimumQueries(Arg0)); }

  // END CUT HERE

};

// BEGIN CUT HERE
int main() {
  RectangleArea ___test;
  ___test.run_test(-1);
}
// END CUT HERE
