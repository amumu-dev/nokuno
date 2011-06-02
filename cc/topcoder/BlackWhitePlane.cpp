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

class BlackWhitePlane {
public:
 struct Circle {
   int x, y, r;
   bool color;
 };
 static bool compare(const Circle &c1, const Circle &c2) {
   return c1.r > c2.r;
 }
 bool contain(Circle &c1, Circle &c2) const {
   return (c1.x - c2.x) * (c1.x - c2.x) + (c1.y - c2.y) * (c1.y - c2.y) <= c2.r * c2.r;
 }

 double area(vector <string> circles) {
   double result = 0;
   vector<Circle> array;
   for (int i = 0; i < (int)circles.size(); i++) {
     Circle c;
     sscanf( circles.at(i).c_str(), "%d %d %d", &c.x, &c.y, &c.r);
     array.push_back(c);
   }
   sort(array.begin(), array.end(), compare);
   for (int i = 0; i < (int)circles.size(); i++) {
     bool color = true;
     for (int j = i-1; j >= 0; j--) {
       if (contain(array[i], array[j])) {
         color = !array[j].color;
         break;
       }
     }
     result += (color?1.:-1.) * array[i].r * array[i].r * M_PI;
     array[i].color = color;
   }
   return result;
 }


 // BEGIN CUT HERE
public:
 void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
private:
 template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
 void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
 void test_case_0() { string Arr0[] = {"1 1 1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 3.141592653589793; verify_case(0, Arg1, area(Arg0)); }
 void test_case_1() { string Arr0[] = {"4 3 1", "3 2 3", "8 1 1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 28.274333882308138; verify_case(1, Arg1, area(Arg0)); }
 void test_case_2() { string Arr0[] = {"15 15 4", "15 25 4", "25 25 4", "25 15 4", "25 25 100"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 31214.86460606818; verify_case(2, Arg1, area(Arg0)); }
 void test_case_3() { string Arr0[] = {"2549 8482 11", "9175 5927 35", "2747 6177 93", "5512 8791 81", "4487 8456 60",
   "6899 610 77", "9716 2202 3", "9312 5625 79", "4020 9851 85", "1640 7179 54", 
   "5761 4348 51","5917 3436 88","6547 386 33","182 7676 1","6329 4496 89"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 194250.95695676407; verify_case(3, Arg1, area(Arg0)); }

 // END CUT HERE

};

// BEGIN CUT HERE
int main() {
  BlackWhitePlane ___test;
  ___test.run_test(-1);
}
// END CUT HERE
