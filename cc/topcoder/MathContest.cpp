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

class MathContest {
public:
  int countBlack(string ballSequence, int repetitions) {
    int result = 0;
    string balls;
    for (int i = 0; i < repetitions; i++) {
      balls += ballSequence;
    }
    int start = 0;
    int end = balls.size()-1;
    bool swaped = false;
    bool reversed = false;

    while (start <= end) {
      char c = !reversed ? balls.at(start) : balls.at(end);
      if (!reversed)
        start ++;
      else
        end --;
      if (c == 'W' && !swaped|| c == 'B' && swaped) {
        reversed = !reversed;
      } else {
        result ++;
        swaped = !swaped;
      }
    }
    return result;
  }
  string reverse(string input) {
    string result = "";
    for (int i = 0; i < input.size(); i++) {
      result += input.at(input.size()-i-1);
    }
    return result;
  }
  string swap(string input) {
    string result = "";
    for (int i = 0; i < input.size(); i++) {
      result += (input.at(i) == 'W') ? 'B' : 'W';
    }
    return result;
  }


  // BEGIN CUT HERE
public:
  void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
private:
  template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
  void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
  void test_case_0() { string Arg0 = "BBWWB"; int Arg1 = 1; int Arg2 = 2; verify_case(0, Arg2, countBlack(Arg0, Arg1)); }
  void test_case_1() { string Arg0 = "BBB"; int Arg1 = 10; int Arg2 = 1; verify_case(1, Arg2, countBlack(Arg0, Arg1)); }
  void test_case_2() { string Arg0 = "BW"; int Arg1 = 10; int Arg2 = 20; verify_case(2, Arg2, countBlack(Arg0, Arg1)); }
  void test_case_3() { string Arg0 = "WWWWWWWBWWWWWWWWWWWWWW"; int Arg1 = 1; int Arg2 = 2; verify_case(3, Arg2, countBlack(Arg0, Arg1)); }

  // END CUT HERE

};

// BEGIN CUT HERE
int main() {
  MathContest ___test;
  ___test.run_test(-1);
}
// END CUT HERE
