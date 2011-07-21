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

class RPGRobot {
public:
  vector <string> where(vector <string> map, string movements) {
    vector <string> result;
    return result;
  }

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); if ((Case == -1) || (Case == 7)) test_case_7(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = {"* *",
 "| |",
 "*-*"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "N"; string Arr2[] = { "1,1" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, where(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"* *-*",
 "| | |",
 "* * *",
 "| | |",
 "*-*-*"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "N,N NS"; string Arr2[] = { "1,3" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, where(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"*-*-*",
 "     ",
 "* * *",
 "     ",
 "* * *"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "SWE,S NSWE"; string Arr2[] = { "1,1",  "3,1" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, where(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"* *-* *",
 "|     |",
 "* *-* *",
 "|     |",
 "* *-* *"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "NSE,E WE,E NSW,N NSW"; string Arr2[] = { "1,1",  "1,3" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, where(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"* *-*",
 "| | |",
 "* * *",
 "| | |",
 "*-*-*"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "N,N S"; string Arr2[] = { "3,3" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(4, Arg2, where(Arg0, Arg1)); }
	void test_case_5() { string Arr0[] = {"*-*",
 "| |",
 "*-*"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "N"; string Arr2[] = { }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(5, Arg2, where(Arg0, Arg1)); }
	void test_case_6() { string Arr0[] = {"* * * *",
 "       ",
 "*-*-*-*"}
 ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "NWE,N NSE,E SWE,S NWE"; string Arr2[] = { "1,1",  "3,1",  "5,1" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(6, Arg2, where(Arg0, Arg1)); }
	void test_case_7() { string Arr0[] = {"* * * *-* * * *-*-* * * * * *-* *",  
 "  |     | |     |   |         |  ",  
 "* * *-* * *-* * * * * * * * *-* *",
 "| | |   | | |       |     |     |",
 "* * *-*-* *-*-*-* * * * * * *-*-*", 
 "  |     | |   | |   |   |     | |", 
 "*-* *-* * *-*-* *-*-*-* * *-* *-*", 
 "    | |     |     | |   |   | |  ", 
 "*-*-* *-*-*-*-* *-*-*-* *-*-* * *", 
 "| |   |         | | |       |    ", 
 "*-*-* * * *-* *-*-* * * * *-*-* *", 
 "  | |     | | | | | |     | | |  ", 
 "*-* *-* * * *-* *-*-* *-* * *-*-*", 
 "  | |   | | | |   |   | | |   |  ", 
 "*-* * * *-* * *-*-*-* * * * * * *", 
 "|     | | |   |   |   | | |      ", 
 "* *-*-*-*-*-* *-* * * *-* *-* *-*", 
 "  | | |         |   | |   |   |  ", 
 "* * *-*-*-* *-* *-*-*-*-*-*-*-*-*", 
 "| |     |   | | | |     |     | |", 
 "* *-* * *-* *-*-*-*-* * *-*-*-* *", 
 "    | | | | |   | | | |     | |  ", 
 "* *-*-*-*-* *-*-* *-* *-*-* * *-*", 
 "  | | | | |   |         | | |    ", 
 "*-*-*-* *-*-* * *-* *-* * * *-*-*", 
 "|   | |           |   | | |     |", 
 "* *-* * * *-*-* *-*-*-* *-* * *-*", 
 "      |     | | | |     |       |", 
 "*-* * * * * *-*-* * * * * *-* * *", 
 "|           | |       |   | |   |", 
 "* * *-*-* *-*-* * * *-*-* * * *-*", 
 "|   | | | | |   | | | | | |   | |", 
 "*-* * *-* * * * * * *-* *-* *-*-*", 
 "  |     | | |   |             | |", 
 "*-* *-* *-* * * * *-* *-* *-*-*-*"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "NW,W SE,S NSW,W NSWE"; string Arr2[] = { "1,23" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(7, Arg2, where(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
  RPGRobot ___test;
  ___test.run_test(-1);
}
// END CUT HERE
