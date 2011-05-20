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

class BlackWhiteMagic {
public:
  bool valid(string &creatures) {
    bool flag = false;
    for (int i = 0; i < (int)creatures.size(); i++) {
      if (creatures.at(i) == 'B') {
        flag = true;
      }
      if (flag && creatures.at(i) == 'W') {
        return false;
      }
    }
    return true;
  }
  int count(string creatures) {
    int result = 0;
    while (!valid(creatures)) {
      int left = -1;
      for (int i = 0; i < (int)creatures.size(); i++) {
        if (creatures.at(i) == 'B') {
          left = i;
          break;
        }
      }
      if (left == -1)
        break;
      int right = -1;
      for (int i = (int)creatures.size()-1; i >= 0; i--) {
        if (creatures.at(i) == 'W') {
          right = i;
          break;
        }
      }
      if (right == -1)
        break;
      swap(creatures[left], creatures[right]);
      result++;
    }
    return result;
  }

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "WBBW"; int Arg1 = 1; verify_case(0, Arg1, count(Arg0)); }
	void test_case_1() { string Arg0 = "WWWWBBBB"; int Arg1 = 0; verify_case(1, Arg1, count(Arg0)); }
	void test_case_2() { string Arg0 = "BBWW"; int Arg1 = 2; verify_case(2, Arg1, count(Arg0)); }
	void test_case_3() { string Arg0 = "BWWWWWWWBBBBBBBW"; int Arg1 = 1; verify_case(3, Arg1, count(Arg0)); }
	void test_case_4() { string Arg0 = "WBWBWBWBWWBWBWBWBBBWBW"; int Arg1 = 5; verify_case(4, Arg1, count(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
  BlackWhiteMagic ___test;
  ___test.run_test(-1);
}
// END CUT HERE
