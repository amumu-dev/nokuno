// codecvt example
#include <iostream>
#include <locale>
#include <string>
using namespace std;

int main ()
{
    // please set locale
    locale::global(locale(""));

    locale mylocale;
    mbstate_t mystate;

    wstring mywstring;

    const codecvt<wchar_t,char,mbstate_t>& myfacet = 
        use_facet<codecvt<wchar_t,char,mbstate_t> >(mylocale);

    codecvt<wchar_t,char,mbstate_t>::result myresult;

    // in() test
    if (false) {
        char mystr[] = "テストです";
        const size_t size = sizeof(mystr);
        wchar_t pwstr[size];

        const char* pc;
        wchar_t* pwc;

        myresult = myfacet.in (mystate,
                mystr, mystr+size, pc,
                pwstr, pwstr+size, pwc);

        if ( myresult == codecvt<wchar_t,char,mbstate_t>::ok )
        {
            wcout << L"Translation successful: ";
            wcout << pwstr << endl;
        }

        // out() test
    } else {
        wchar_t mystr[] = L"ワイド文字テスト";
        const size_t size = sizeof(mystr) * 3 + 1;
        char pstr[size];

        const wchar_t* pwc;
        char* pc;

        // translate characters:
        myresult = myfacet.out (mystate,
                mystr, mystr+size, pwc,
                pstr, pstr+size, pc);

        if ( myresult == codecvt<wchar_t,char,mbstate_t>::ok )
            cout << "Translation successful: ";
            cout << pstr << endl;
    }

    return 0;
}


