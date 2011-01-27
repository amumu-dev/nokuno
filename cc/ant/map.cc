#include <iostream>
#include <string>
#include <map>
using namespace std;

int main() {
  map<int, const char*> m;

  m.insert(make_pair(1, "ONE"));
  m.insert(make_pair(10, "TEN"));
  m[100] = "HUNDRED";

  map<int, const char*>::iterator ite;
  ite = m.find(1);
  puts(ite->second);

  ite = m.find(2);
  if (ite == m.end()) puts("not found");
  else puts(ite->second);

  puts(m[10]);

  m.erase(10);

  for (ite = m.begin(); ite != m.end(); ++ite) {
    cout << ite->first << " " << ite->second << endl;
  }
}
