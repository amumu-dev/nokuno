// STLを使うとwarningが出る可能性があるので、それを出さないようにする
#pragma warning (disable:4786)

#include<map>
#include<iostream>
using namespace std;

int main(){
    // mapを宣言
    map<char, int> m;

    int     i;
    char    ch;

    // データを追加
    for( i = 'a' ; i <= 'z' ; i++ )
        m.insert( pair<char, int>((char)i, i) );


    while( cout << endl << "Enter Key : " << flush, cin >> ch ){
        // map型イタレーターの宣言
        map<char, int>::iterator itr;

        // 検索
        itr = m.find(ch);

        if( itr == m.end() )
            // 見つからなかった？
            cout << "No entry!!" << endl;
        else
            // 見つかった
            // イタレーターはpair型を指している
            // itr->second が値を保持している
            // itr->first  がキーを保持している
            cout << "ASCII Code : " << itr->second << endl;
    }
    return 0;
}
