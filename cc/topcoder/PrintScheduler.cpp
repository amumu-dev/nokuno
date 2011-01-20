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

//split
inline vector<string> split(string s, char c) {
  vector<string> v;
  for (size_t p = 0; (p = s.find(c)) != s.npos; ) {
    v.push_back(s.substr(0, p));
    s = s.substr(p + 1);
  }
  v.push_back(s);
  return v;
}

class PrintScheduler {
public:
  string getOutput(vector <string> threads, vector <string> slices) {
    string result;
    vector<int> counter(threads.size(), 0);
    for (int i = 0; i < slices.size(); i++) {
      vector<string> splited = split(slices[i], ' ');
      int num = strtol( splited[0].c_str(), NULL, 0);
      int time = strtol( splited[1].c_str(), NULL, 0);
      for ( int j = 0; j < time; j++) {
        result += threads[num][counter[num]];
        counter[num] ++;
        counter[num] %= threads[num].size();
      }
    }
    return result;
  }

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"AB","CD"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"0 1","1 1","0 1","1 2"} ; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "ACBDC"; verify_case(0, Arg2, getOutput(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"ABCDE"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"0 20","0 21"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "ABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEA"; verify_case(1, Arg2, getOutput(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"A","B"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"1 10","0 1","1 10","0 2"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "BBBBBBBBBBABBBBBBBBBBAA"; verify_case(2, Arg2, getOutput(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"A"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"0 1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "A"; verify_case(3, Arg2, getOutput(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
  PrintScheduler ___test;
  ___test.run_test(-1);
}
// END CUT HERE
