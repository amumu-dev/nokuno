#include <tr1/unordered_map>
#include <string>
#include <iostream>
using namespace std;
using namespace std::tr1;
int main(){
    unordered_map<string , int> m;
    string line;
    while(getline(cin , line))
        m[line]++;
    unordered_map<string , int>::iterator it;
    for(it = m.begin(); it != m.end(); ++it)
        cout << it->first << " " << it->second << endl;
    return 0;
}
