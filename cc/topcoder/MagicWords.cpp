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

class MagicWords {
 public:
  bool is_magic_word(string word, int K) {
    int count = 1;
    for (int i = 1; i < word.size(); i++) {
      string temp = word.substr(i) + word.substr(0, i);
      if (temp == word)
        count ++;
    }
    //cout << word << ":" << count << endl;
    return count == K;
  }
  vector<vector<int> > permutate(vector<int> &p) {
    vector<vector<int> > result;
    if (p.size() == 1) {
      result.push_back(p);
      return result;
    }
    for (int i = 0; i < p.size(); i++) {
      vector<int> next(p.size());
      for (int j = 0; j < p.size(); j++)
        next[j] = p[j];
      swap(next[i], next[next.size()-1]);
      int last = next.back();
      next.pop_back();
      vector<vector<int> > permutated = permutate(next);
      for (int j = 0; j < permutated.size(); j++) {
        permutated[j].push_back(last);
        result.push_back(permutated[j]);
      }
    }
    return result;
  }
  int count(vector <string> S, int K) {
    int result = 0;
    vector<int> p;
    for (int i = 0; i < S.size(); i++) {
      p.push_back(i);
    }
    vector<vector<int> > permutation = permutate(p);
    for (int i = 0; i < permutation.size(); i++) {
      string word;
      for (int j = 0; j < permutation[i].size(); j++) {
        word += S[permutation[i][j]];
      }
      if (is_magic_word(word, K)) {
        result ++;
      }
    }
    return result;
  }


  // BEGIN CUT HERE
 public:
  void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
 private:
  template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
  void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
  void test_case_0() { string Arr0[] = {"CAD","ABRA","ABRA"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 6; verify_case(0, Arg2, count(Arg0, Arg1)); }
  void test_case_1() { string Arr0[] = {"AB","RAAB","RA"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 3; verify_case(1, Arg2, count(Arg0, Arg1)); }
  void test_case_2() { string Arr0[] = {"AA","AA","AAA","A"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 0; verify_case(2, Arg2, count(Arg0, Arg1)); }
  void test_case_3() { string Arr0[] = {"AA","AA","AAA","A","AAA","AAAA"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 15; int Arg2 = 720; verify_case(3, Arg2, count(Arg0, Arg1)); }
  void test_case_4() { string Arr0[] = {"ABC","AB","ABC","CA"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 0; verify_case(4, Arg2, count(Arg0, Arg1)); }
  void test_case_5() { string Arr0[] = {"A","B","C","A","B","C"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 672; verify_case(5, Arg2, count(Arg0, Arg1)); }
  void test_case_6() { string Arr0[] = {"AAAAAAAAAAAAAAAAAAAA",
    "AAAAAAAAAAAAAAAAAAAA",
    "AAAAAAAAAAAAAAAAAAAA",
    "AAAAAAAAAAAAAAAAAAAA",
    "AAAAAAAAAAAAAAAAAAAA",
    "AAAAAAAAAAAAAAAAAAAA",
    "AAAAAAAAAAAAAAAAAAAA",
    "AAAAAAAAAAAAAAAAAAAB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 40320; verify_case(6, Arg2, count(Arg0, Arg1)); }

  // END CUT HERE

};

// BEGIN CUT HERE
int main() {
  MagicWords ___test;
  ___test.run_test(-1);
}
// END CUT HERE
