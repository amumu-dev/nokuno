#include <string>
#include <iostream>
#include <stdlib.h>
using namespace std;

int main(){
    string url = "http://ja.wikipedia.org/wiki/%E6%97%A5%E6%9C%AC%E8%AA%9E\n";
    string buffer = "";

    for (int i = 0; i < url.length(); i++) {
        int j = i ;
        char ch = url.at(j);
        if (ch == '%'){
            char tmpstr[] = "0x0__";
            int chnum;
            tmpstr[3] = url.at(j+1);
            tmpstr[4] = url.at(j+2);
            chnum = strtol(tmpstr, NULL, 16);	  
            buffer += chnum;
            i += 2;
        } else {
            buffer += ch;
        }
    }
    cout << buffer << endl;
    return 0;
}
