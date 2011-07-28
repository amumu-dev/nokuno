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

vector<string> split(const string &str, char delim){
  istringstream iss(str); string tmp; vector<string> res;
  while(getline(iss, tmp, delim)) res.push_back(tmp);
  return res;
}
class Diving {
public:
  double solve(double difficulty, double need, vector<double> ratings) {
    double result = 0.;
    double sum = 0.;
    for (int i = 0; i < (int)ratings.size(); i++) {
      sum += ratings[i];
    }
    for (double r = 0.; r <= 10.; r += .5) {
      double temp =  sum + r - min(r, ratings.front()) - max(r, ratings.back());
      temp *= difficulty;
      if (temp >= need - 1e-10) {
        return r;
      }
    }
    return -1.;
  }
  string needed(string difficulty, string need, string ratings) {
    double d = atof(difficulty.c_str());
    double n = atof(need.c_str());
    vector<string> rs = split(ratings, ' ');
    vector<double> r;
    for (int i = 0; i < rs.size(); i++) {
      if (rs[i][0] != '?') {
        double temp = atof(rs[i].c_str());
        r.push_back(temp);
      }
    }
    sort(r.begin(), r.end());
    double s = solve(d, n, r);
    char result[256];
    sprintf(result, "%1.1f", s);
    return string(result);
  }

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "3.2"; string Arg1 = "50.32"; string Arg2 = "5.5 7.5 10.0 ?.? 4.5"; string Arg3 = "0.0"; verify_case(0, Arg3, needed(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arg0 = "3.2"; string Arg1 = "50.32"; string Arg2 = "5.5 5.5 10.0 ?.? 4.5"; string Arg3 = "5.0"; verify_case(1, Arg3, needed(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arg0 = "4.0"; string Arg1 = "120.00"; string Arg2 = "9.5 10.0 ?.? 10.0 10.0"; string Arg3 = "10.0"; verify_case(2, Arg3, needed(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arg0 = "4.0"; string Arg1 = "120.00"; string Arg2 = "9.5 10.0 ?.? 9.5 10.0"; string Arg3 = "-1.0"; verify_case(3, Arg3, needed(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arg0 = "2.3"; string Arg1 = ".01"; string Arg2 = "0.0 0.0 ?.? 0.0 0.5"; string Arg3 = "0.5"; verify_case(4, Arg3, needed(Arg0, Arg1, Arg2)); }
	void test_case_5() { string Arg0 = "3.3"; string Arg1 = "47.85"; string Arg2 = "0.5 5.5 3.5 7.0 ?.?"; string Arg3 = "5.5"; verify_case(5, Arg3, needed(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
  Diving ___test;
  ___test.run_test(-1);
}
// END CUT HERE
