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

class FindingSquareInTable {
public:
  bool isPerfectSquare(int i) {
    double s = sqrt((double)i);
    return ceil(s) == floor(s);
  }
  int findMaximalSquare(vector <string> table) {
    int result = -1;
    for (int i = -10; i <= 10; i++) {
      for (int j = -10; j <= 10; j++) {
        for (int x = 0; x < 10; x++) {
          for (int y = 0; y < 10; y++) {
            string s = "";
            for (int l = 0; l < 10; l++) {
              int xx = x + i * l;
              int yy = y + j * l;
              if (xx >= 0 && xx < (int)table.size() && yy >= 0 && yy < (int)table[0].size()) {
                s += table[xx][yy];
                int cand = strtol(s.c_str(), NULL, 10);
                if (isPerfectSquare(cand) && cand > result) {
                  result = cand;
                }
              } else {
                break;
              }
            }
          }
        }
      }
    }
    return result;
  }

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"123",
 "456"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 64; verify_case(0, Arg1, findMaximalSquare(Arg0)); }
	void test_case_1() { string Arr0[] = {"00000",
 "00000",
 "00200",
 "00000",
 "00000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(1, Arg1, findMaximalSquare(Arg0)); }
	void test_case_2() { string Arr0[] = {"3791178",
 "1283252",
 "4103617",
 "8233494",
 "8725572",
 "2937261"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 320356; verify_case(2, Arg1, findMaximalSquare(Arg0)); }
	void test_case_3() { string Arr0[] = {"135791357",
 "357913579",
 "579135791",
 "791357913",
 "913579135"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 9; verify_case(3, Arg1, findMaximalSquare(Arg0)); }
	void test_case_4() { string Arr0[] = {"553333733",
 "775337775",
 "777537775",
 "777357333",
 "755553557",
 "355533335",
 "373773573",
 "337373777",
 "775557777"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(4, Arg1, findMaximalSquare(Arg0)); }
	void test_case_5() { string Arr0[] = {"257240281",
 "197510846",
 "014345401",
 "035562575",
 "974935632",
 "865865933",
 "684684987",
 "768934659",
 "287493867"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 95481; verify_case(5, Arg1, findMaximalSquare(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
  FindingSquareInTable ___test;
  ___test.run_test(-1);
}
// END CUT HERE
