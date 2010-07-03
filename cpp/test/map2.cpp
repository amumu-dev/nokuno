#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{
  map<string, string> itms;  // ʸ����ʸ����map�����
  cout << itms.insert(pair<string, string>("01", "C++")).second << endl;  // �ͤ�����
  cout << itms.insert(pair<string, string>("02", "C#")).second << endl;
  cout << itms.insert(pair<string, string>("03", "VB")).second << endl;
  cout << itms.insert(pair<string, string>("04", "Java")).second << endl;
  cout << itms.insert(pair<string, string>("05", "XML")).second << endl;

  map<string, string>::iterator p;  // ȿ����=�ݥ��󥿤Τ褦�ʤ��

  // ����
  p=itms.find("03");    // "03"�Ȥ����ͤθ���

  if(p != itms.end())   // end()=����ƥʤκǸ塢()��˺��ʤ��ͤ�
  {
    cout << p->first << "��" ;
    cout << p->second << "�Ǥ�" << endl;
  }
  else
  {
    cout << "03�ϸ��Ĥ���ޤ���" << endl;
  }

  // ����
  for(p=itms.begin(); p!=itms.end(); p++)
  {
    cout << p->second << endl;
  }
  return 0;
}
