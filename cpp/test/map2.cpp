#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{
  map<string, string> itms;  // 文字×文字のmapを指定
  cout << itms.insert(pair<string, string>("01", "C++")).second << endl;  // 値を挿入
  cout << itms.insert(pair<string, string>("02", "C#")).second << endl;
  cout << itms.insert(pair<string, string>("03", "VB")).second << endl;
  cout << itms.insert(pair<string, string>("04", "Java")).second << endl;
  cout << itms.insert(pair<string, string>("05", "XML")).second << endl;

  map<string, string>::iterator p;  // 反復子=ポインタのようなもの

  // 検索
  p=itms.find("03");    // "03"という値の検索

  if(p != itms.end())   // end()=コンテナの最後、()を忘れない様に
  {
    cout << p->first << "は" ;
    cout << p->second << "です" << endl;
  }
  else
  {
    cout << "03は見つかりません" << endl;
  }

  // 一覧
  for(p=itms.begin(); p!=itms.end(); p++)
  {
    cout << p->second << endl;
  }
  return 0;
}
