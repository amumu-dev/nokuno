#include <string>
#include <iostream>
#include <stdlib.h>
using namespace std;

// wide to multi
void narrow(const wstring &src, string &dest) {
    char *mbs = new char[src.length() * MB_CUR_MAX + 1];
    wcstombs(mbs, src.c_str(), src.length() * MB_CUR_MAX + 1);
    dest = mbs;
    delete [] mbs;
}

// multi to wide
void widen(const string &src, wstring &dest) {
    wchar_t *wcs = new wchar_t[src.length() + 1];
    mbstowcs(wcs, src.c_str(), src.length() + 1);
    dest = wcs;
    delete [] wcs;
}

// caution! we can't mix wcout and cout!
int main() {
    setlocale(LC_CTYPE, "");

    //multi to wide
    string multi = "あいうえお";
    wstring wide;
    widen(multi, wide);
    wcout << wide << endl;
    
    //wide to multi;
    wide = L"日本語テスト";
    narrow(wide, multi);
    cout << multi << endl;
    cout << "MB_CUR_MAX: " << MB_CUR_MAX << endl;
    cout << "sizeof(wchar_t): " << sizeof(wchar_t) << endl;
}
