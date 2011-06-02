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

class CheckFunction {
public:
  int newFunction(string code) {
    int result = 0;
    int dashes[] = {6,2,5,5,4,5,6,3,7,6};
    for (int i = 0; i < (int)code.size(); i++) {
      int index = (int)(code.at(i) - '0');
      result += dashes[index]; 
    }
    return result;
  }

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "13579"; int Arg1 = 21; verify_case(0, Arg1, newFunction(Arg0)); }
	void test_case_1() { string Arg0 = "02468"; int Arg1 = 28; verify_case(1, Arg1, newFunction(Arg0)); }
	void test_case_2() { string Arg0 = "73254370932875002027963295052175"; int Arg1 = 157; verify_case(2, Arg1, newFunction(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
  CheckFunction ___test;
  ___test.run_test(-1);
}
// END CUT HERE
