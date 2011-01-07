#include <iostream>
#include <stack>
#include <queue>

using namespace std;

int main(){
  cout << "stack" << endl;
  stack<int> s;
  s.push(1);
  s.push(2);
  s.push(3);
  cout << s.top() << endl;
  s.pop();
  cout << s.top() << endl;
  s.pop();
  cout << s.top() << endl;
  s.pop();

  cout << "queue" << endl;
  queue<int> que;
  que.push(1);
  que.push(2);
  que.push(3);
  cout << que.front() << endl;
  que.pop();
  cout << que.front() << endl;
  que.pop();
  cout << que.front() << endl;
  que.pop();
}

