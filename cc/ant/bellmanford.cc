#include <stdio.h>
#define MAX_E 20
#define MAX_V 7
#define INF 100000

struct edge {int from, to, cost; };

edge es[MAX_E] = {
  {0, 1, 2},
  {0, 2, 5},
  {1, 2, 4},
  {1, 3, 6},
  {1, 4, 10},
  {2, 3, 2},
  {3, 5, 1},
  {4, 5, 3},
  {4, 6, 5},
  {5, 6, 9},
  {1, 0, 2},
  {2, 0, 5},
  {2, 1, 4},
  {3, 1, 6},
  {4, 1, 10},
  {3, 2, 2},
  {5, 3, 1},
  {5, 4, 3},
  {6, 4, 5},
  {6, 5, 9},
};

int d[MAX_V];

void shortest_path(int s) {
  for (int i = 0; i < MAX_V; i++) d[i] = INF;
  d[s] = 0;
  while (true) {
    bool update = false;
    for (int i = 0; i < MAX_E; i++) {
      edge e = es[i];
      if (d[e.from] != INF && d[e.to] > d[e.from] + e.cost) {
        d[e.to] = d[e.from] + e.cost;
        update = true;
      }
    }
    if (!update) break;
  }
}

int main() {
  shortest_path(0);
  printf("%d", d[6]);
  return 0;
}
