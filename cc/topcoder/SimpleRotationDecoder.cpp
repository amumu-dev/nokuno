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

class SimpleRotationDecoder {
public:
  bool is_valid(string candidate) {
    vector<string> words = split(candidate, ' ');
    for (int i = 0; i < words.size(); i++) {
      string word = words[i];
      if (word.length() < 2 || word.length() > 8)
        return false;
      bool flag = false;
      for (int j = 0; j < word.length(); j++) {
        if (word[j] == 'a' || word[j] == 'e' || word[j] == 'i' || word[j] == 'o' || word[j] == 'u') {
          flag = true;
          break;
        }
      }
      if (!flag) return false;
    }
    return true;
  }
  string try_decode(string text, string password) {
    string result;
    for (int l = 0; l < text.length(); l++) {
      int t;
      if (text[l] == ' ') t = 0;
      else t = (int)(text[l] - 'a') + 1;
      int p = (int)(password[l%3] - 'a') + 1;
      int n = t - p;
      if (n < 0) n += 27;
      if (n == 0) result += ' ';
      else result += ('a' + (char)(n-1));
    }
    return result;
  }
  string decode(string cipherText) {
    for (char i = 0; i < 26; i++) {
      for (char j = 0; j < 26; j++) {
        for (char k = 0; k < 26; k++) {
          string password;
          password += 'a' + i;
          password += 'a' + j;
          password += 'a' + k;
          string result = try_decode(cipherText, password);
          if (is_valid(result)) {
            return result;
          }
        }
      }
    }
    return "no match";
  }


  // BEGIN CUT HERE
public:
  void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
private:
  template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
  void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
  void test_case_0() { string Arg0 = "mmbtvrbhhtgohaktklqegnrmlelojotyeyeiudvtil ey ffg"; string Arg1 = "the quick brown fox jumps over the lazy dog again"; verify_case(0, Arg1, decode(Arg0)); }
  void test_case_1() { string Arg0 = "ntgntgntgntofwlfwlfwlnookookook"; string Arg1 = "he he he heh he he heh he he he"; verify_case(1, Arg1, decode(Arg0)); }
  void test_case_2() { string Arg0 = "f sgnzslhzquq ydyuinmqiwfyrtdvn"; string Arg1 = "abkbprnn usmlbqz mdpelkoa jofni"; verify_case(2, Arg1, decode(Arg0)); }
  void test_case_3() { string Arg0 = "shxnaaeqjlofhhsuurbhpdgt z"; string Arg1 = "naeiui jrghnca pnzxaxz avs"; verify_case(3, Arg1, decode(Arg0)); }

  // END CUT HERE

};

// BEGIN CUT HERE
int main() {
  SimpleRotationDecoder ___test;
  ___test.run_test(-1);
}
// END CUT HERE
