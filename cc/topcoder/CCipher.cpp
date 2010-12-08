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

class CCipher {
public:
  string decode(string cipherText, int shift) {
    string result;
    for (int i = 0; i < cipherText.length(); i++) {
      int c = (int)cipherText[i];
      if (c - shift >= 'A')
        result += (char)(c - shift);
      else
        result += (char)(c - shift + (int)('Z'-'A'+1));
    }
    return result;
  }


  // BEGIN CUT HERE
public:
  void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
private:
  template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
  void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
  void test_case_0() { string Arg0 = "VQREQFGT"; int Arg1 = 2; string Arg2 = "TOPCODER"; verify_case(0, Arg2, decode(Arg0, Arg1)); }
  void test_case_1() { string Arg0 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; int Arg1 = 10; string Arg2 = "QRSTUVWXYZABCDEFGHIJKLMNOP"; verify_case(1, Arg2, decode(Arg0, Arg1)); }
  void test_case_2() { string Arg0 = "TOPCODER"; int Arg1 = 0; string Arg2 = "TOPCODER"; verify_case(2, Arg2, decode(Arg0, Arg1)); }
  void test_case_3() { string Arg0 = "ZWBGLZ"; int Arg1 = 25; string Arg2 = "AXCHMA"; verify_case(3, Arg2, decode(Arg0, Arg1)); }
  void test_case_4() { string Arg0 = "DBNPCBQ"; int Arg1 = 1; string Arg2 = "CAMOBAP"; verify_case(4, Arg2, decode(Arg0, Arg1)); }
  void test_case_5() { string Arg0 = "LIPPSASVPH"; int Arg1 = 4; string Arg2 = "HELLOWORLD"; verify_case(5, Arg2, decode(Arg0, Arg1)); }

  // END CUT HERE

};

// BEGIN CUT HERE
int main() {
  CCipher ___test;
  ___test.run_test(-1);
}
// END CUT HERE
