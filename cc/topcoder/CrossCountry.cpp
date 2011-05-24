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

class CrossCountry {
public:
 struct Team {
   double score;
   int num;
   int index;
   Team() {score = .0; num = 0;}
 };
 struct Comparator {
  bool operator ()(const Team &a, const Team &b) {
    if (a.score == b.score)
      return a.index < b.index;
    return a.score < b.score;
  }
 };
  string scoreMeet(int numTeams, string finishOrder) {
    vector<Team> teams(numTeams);
    for (size_t i = 0; i < numTeams; i++) {
      teams[i].index = i;
    }
    for (size_t i = 0; i < finishOrder.size(); i++) {
      int t = (int)(finishOrder[i] - 'A');
      teams[t].num ++;
      if (teams[t].num < 6) {
        teams[t].score += i+1;
      } else if (teams[t].num == 6) {
        teams[t].score += (double)(i+1) / 100.0;
      }
    }
    for (size_t i = 0; i < numTeams; i++) {
      if (teams[i].num == 5) {
        teams[i].score += 0.9;
      }
    }
    sort(teams.begin(), teams.end(), Comparator());
    string result = "";
    for (size_t i = 0; i < teams.size(); i++) {
      if (teams[i].num >= 5) {
        char c = (char)('A' + (char)teams[i].index);
        result += c;
      }
    }
    return result;
  }

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; string Arg1 = "AABBABBABBA"; string Arg2 = "AB"; verify_case(0, Arg2, scoreMeet(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 3; string Arg1 = "CCCBBBBBAAACC"; string Arg2 = "BC"; verify_case(1, Arg2, scoreMeet(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 4; string Arg1 = "ABDCBADBDCCDBCDBCAAAC"; string Arg2 = "BDCA"; verify_case(2, Arg2, scoreMeet(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 10; string Arg1 = "BDHCEAJBIDBCCHGCBDJEBAAHEGAGGADHGIECJEHAEBDADJCDHG"; string Arg2 = "BCDAHEG"; verify_case(3, Arg2, scoreMeet(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 3; string Arg1 = "BABCAABABAB"; string Arg2 = "AB"; verify_case(4, Arg2, scoreMeet(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
  CrossCountry ___test;
  ___test.run_test(-1);
}
// END CUT HERE
