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

class VariableAddition {
public:
  int add(string eq, vector <string> vars) {
    map<string, int> dictionary;

    for (int i = 0; i < (int)vars.size(); i++) {
      string name;
      int value;
      istringstream iss(vars[i]);
      iss >> name >> value;
      dictionary[name] = value;
    }

    int result = 0;
    vector<string> elements = split(eq, '+');
    for (int i = 0; i < (int)elements.size(); i++) {
      map<string, int>::iterator itr = dictionary.find(elements[i]);
      if (itr != dictionary.end()) {
        result += itr->second;
      } else {
        result += strtol(elements[i].c_str(), NULL, 10);
      }
    }
    return result;
  }

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "1+2+3"; string Arr1[] = {}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 6; verify_case(0, Arg2, add(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "a+aa+aaa"; string Arr1[] = {"a 1","aa 2","aaa 1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 4; verify_case(1, Arg2, add(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "1+3+a+xyz+33+num+num"; string Arr1[] = {"a 999","xyz 0","num 11"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1058; verify_case(2, Arg2, add(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
  VariableAddition ___test;
  ___test.run_test(-1);
}
// END CUT HERE
