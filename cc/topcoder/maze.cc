#include <iostream>
#include <queue>
using namespace std;

struct Pos {
  int x, y;
};
int main(){
  const char *m[] = {
    "#S#.",
    "...#",
    ".#.#",
    "#G.#",
  };
  queue<Pos> que;
  Pos start = {1,0};
  Pos goal = {1,3};
  que.push(start);
  while (que.size()) {
  }
}
