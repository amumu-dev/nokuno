#include <iostream>
using namespace std;

string s("abcd");
string t("becd");

int lcs(int i, int j) {
  int result = 0;
  if (i == 0 && j == 0)
    return 0;
  if (i > 0) 
    result = max(lcs(i-1, j) , result);
  if (j > 0) 
    result = max(lcs(i, j-1) , result);
  if (s[i] == t[j])
    result = max(lcs(i-1, j-1)+1, result);
  return result;
}
int main() {
  cout << lcs(s.length()-1, t.length()-1) << endl;
  return 0;
}
