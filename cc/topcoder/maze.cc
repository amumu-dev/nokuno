#include <iostream>
#include <queue>
using namespace std;

struct Pos {
  int x, y;
  Pos(int x_, int y_) {x=x_;y=y_;}
};
int main(){
  string maze[] = {
    "#S#.",
    "...#",
    ".#.#",
    "#G.#",
  };
  int width = 4, height = 4;

  queue<Pos> que;
  que.push(Pos(0,1));
  int i;
  for (i = 0; i < width*height; i++) {
    queue<Pos> temp(que);
    cout << "stage " << i << endl;
    while (!que.empty()) {
      Pos p = que.front(); que.pop();
      if (p.x<0 || p.x>=width || p.y<0 || p.y>=height)
        continue;
      if (maze[p.y][p.x] == 'G') {
        cout << "goal: " << p.x << ", " << p.y << endl;
        goto goal;
      }
      if (maze[p.y][p.x] != '.')
        continue;
      cout << p.x << ", " << p.y << endl;
      maze[p.y][p.x] = '*';
      temp.push(Pos(p.x+1,p.y));
      temp.push(Pos(p.x-1,p.y));
      temp.push(Pos(p.x,p.y+1));
      temp.push(Pos(p.x,p.y-1));
    }
    que = temp;
  }
goal:
  cout << "result: " << i << endl;
}
