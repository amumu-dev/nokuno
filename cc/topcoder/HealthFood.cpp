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

class HealthFood {
public:
  vector <int> selectMeals(vector <int> protein, vector <int> carbs, vector <int> fat, vector <string> dietPlans) {
    size_t size = protein.size();
    vector <int> calories(size, 0);
    for (size_t i = 0; i < size; i++) {
      calories[i] = protein.at(i) * 5 + carbs.at(i) * 5 + fat.at(i) * 9;
    }
    vector <vector <int> > dietInfo;
    dietInfo.push_back(protein);
    dietInfo.push_back(carbs);
    dietInfo.push_back(fat);
    dietInfo.push_back(calories);

    vector <int> result;
    for (size_t i = 0; i < dietPlans.size(); i++) {
      int meal = selectOneMeal(dietInfo, dietPlans.at(i));
      result.push_back(meal);
    }
    cout << endl;
    return result;
  }
  int selectOneMeal(vector <vector <int> > &dietInfo, string& dietPlan) {
    int result = 0;
    for (int i = 1; i < dietInfo[0].size(); i++) {
      if (compareMeal(dietInfo, dietPlan, result, i) > 0) {
        result = i;
      }
    }
    cout << result << " ";
    return result;
  }
  int compareMeal(vector <vector <int> > &dietInfo, string& dietPlan, int a, int b) {
    for (size_t i = 0; i < dietPlan.size(); i++) {
      char c = dietPlan.at(i);
      pair<int, int> code = dietCode(c);
      //cout << i << " " << code.first << " " << code.second << endl;
      int diff = dietInfo[code.second][a] - dietInfo[code.second][b];
      if (diff == 0)
        continue;
      return ((diff>0) == (code.first==1)) ? -1 : 1;
    }
    return 0;
  }
  pair<int,int> dietCode(char c) {
    pair<int, int> result;
    result.first = isupper(c);
    switch (toupper(c)) {
      case 'P':
        result.second = 0;
        break;
      case 'C':
        result.second = 1;
        break;
      case 'F':
        result.second = 2;
        break;
      case 'T':
        result.second = 3;
        break;
    }
    return result;
  }

  /*
  int selectOneMeal(vector <vector <int> > &dietInfo, string& dietPlan) {
    for (size_t i = 0; i < dietPlan.size(); i++) {
      char c = dietPlan.at(i);
      pair<int, int> code = dietCode(c);
      //cout << i << " " << code.first << " " << code.second << endl;
      //dietInfo[code.second]
    }
    return 0;
 }
  vector<int> argminmax(vector <vector <int> > &dietInfo, int upper, int index) {
    vector<int> result;
    //int value = upper ? *(min_element(dietInfo[index].begin(), dietInfo[index].end())) : *(max_element(dietInfo[index]));
    int value = *(min_element(dietInfo[index].begin(), dietInfo[index].end()));
    for (size_t i = 0; i < dietInfo[0].size(); i++) {
      if (dietInfo[index][i] == value)
        result.push_back(i);
    }
    return result;
  }
  */

  // BEGIN CUT HERE
public:
  void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
private:
  template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
  void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
  void test_case_0() { int Arr0[] = {3, 4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2, 8}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {5, 2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arr3[] = {"P", "p", "C", "c", "F", "f", "T", "t"}; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = { 1,  0,  1,  0,  0,  1,  1,  0 }; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); verify_case(0, Arg4, selectMeals(Arg0, Arg1, Arg2, Arg3)); }
  void test_case_1() { int Arr0[] = {3, 4, 1, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2, 8, 5, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {5, 2, 4, 4}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arr3[] = {"tFc", "tF", "Ftc"}; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = { 3,  2,  0 }; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); verify_case(1, Arg4, selectMeals(Arg0, Arg1, Arg2, Arg3)); }
  void test_case_2() { int Arr0[] = {18, 86, 76,  0, 34, 30, 95, 12, 21}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {26, 56,  3, 45, 88,  0, 10, 27, 53}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {93, 96, 13, 95, 98, 18, 59, 49, 86}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arr3[] = {"f", "Pt", "PT", "fT", "Cp", "C", "t", "",
    "cCp", "ttp", "PCFt", "P", "pCt", "cP", "Pc"}
    ; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = { 2,  6,  6,  2,  4,  4,  5,  0,  5,  5,  6,  6,  3,  5,  6 }; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); verify_case(2, Arg4, selectMeals(Arg0, Arg1, Arg2, Arg3)); }

    // END CUT HERE

};

// BEGIN CUT HERE
int main() {
  HealthFood ___test;
  ___test.run_test(-1);
}
// END CUT HERE
