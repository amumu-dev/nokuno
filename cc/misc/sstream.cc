#include <sstream>
#include <iostream>
using namespace std;

int main() {
    int i;
    wstringstream(L"1234 567") >> i;
    wcout << i << endl;;
    return 0;
}
