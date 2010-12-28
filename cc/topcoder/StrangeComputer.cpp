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

class StrangeComputer {
public:
  int setMemory(string mem) {
    int result = 0;
    char old = '0';
    for (int i = 0; i < mem.length(); i++) {
      if (mem[i] != old) {
        result ++;
        old = mem[i];
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
	void test_case_0() { string Arg0 = "0011"; int Arg1 = 1; verify_case(0, Arg1, setMemory(Arg0)); }
	void test_case_1() { string Arg0 = "000"; int Arg1 = 0; verify_case(1, Arg1, setMemory(Arg0)); }
	void test_case_2() { string Arg0 = "0100"; int Arg1 = 2; verify_case(2, Arg1, setMemory(Arg0)); }
	void test_case_3() { string Arg0 = "111000111"; int Arg1 = 3; verify_case(3, Arg1, setMemory(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
  StrangeComputer ___test;
  ___test.run_test(-1);
}
// END CUT HERE
