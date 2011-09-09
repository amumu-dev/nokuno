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

class CheapestFlights {
public:
 double solve(vector<vector<double> > prices, int startLocation, int endLocation, int num) {
    if (num == 0) {
      if (startLocation == endLocation) {
        return 0.;
      } else {
        return 1e10;
      }
    }
    double result = 1e10;
    //cout << "S:" << num << " " << startLocation << " " << endLocation << endl;
    for (int i = 0; i < (int)prices.size(); i++) {
      if (i == startLocation) continue;
      double price = prices[startLocation][i];
      vector<vector<double> > copy(prices);
      for (int j = 0; j < (int)prices.size(); j++) {
        copy[j][i] /= 2.;
      }
      double cost = price + solve(copy, i, endLocation, num-1);
      result = min(result, cost);
    }
    return result;
 }
  double getLowest(vector <string> prices, int startLocation, int endLocation, int num) {
    vector<vector<double> > dprices(prices.size());
    for (int i = 0; i < (int)prices.size(); i++) {
      dprices[i].resize(prices.size());
      for (int j = 0; j < (int)prices.size(); j++) {
        dprices[i][j] = (double)(prices[i][j] - '0');
      }
    }

    return solve(dprices, startLocation, endLocation, num);
  }

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"019",
 "909",
 "990"
}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 1; int Arg3 = 2; double Arg4 = 18.0; verify_case(0, Arg4, getLowest(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { string Arr0[] = {"099",
 "909",
 "990"
}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 1; int Arg3 = 3; double Arg4 = 22.5; verify_case(1, Arg4, getLowest(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { string Arr0[] = {"099",
 "909",
 "990"
}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 1; int Arg3 = 7; double Arg4 = 32.625; verify_case(2, Arg4, getLowest(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { string Arr0[] = {"111",
 "111",
 "111"
}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 1; int Arg3 = 8; double Arg4 = 3.75; verify_case(3, Arg4, getLowest(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
  CheapestFlights ___test;
  ___test.run_test(-1);
}
// END CUT HERE
