#include <stdio.h>
#include <queue>
using namespace std;

#define MAX_E 20
#define MAX_V 7
#define INF 100000

struct edge {int from, to, cost; };

int cost[MAX_V][MAX_V] = {
  {INF, 2,    5,    INF,  INF,  INF,  INF},
  {2,   INF,  4,    6,    10,   INF,  INF},
  {5,   4,    INF,  2,    INF,  INF,  INF},
  {INF, 6,    2,    INF,  INF,  1,    INF},
  {INF, 10,   INF,  INF,  INF,  3,    5},
  {INF, INF,  INF,  1,    3,    INF,  9},
  {INF, INF,  INF,  INF,  5,    9,    INF},
};

int d[MAX_V];
bool used[MAX_V];

void dijkstra(int s) {
  fill(d, d + MAX_V, INF);
  fill(used, used + MAX_V, false);
  d[s] = 0;

  while(true) {
    int v = -1;
    for (int u = 0; u < MAX_V; u++) {
      if (!used[u] && (v == -1 || d[u] < d[v])) v = u;
    }
    if (v == -1) break;
    used[v] = true;

    for (int u = 0; u < MAX_V; u++) {
      d[u] = min(d[u], d[v] + cost[v][u]);
    }
  }
}

int main() {
  dijkstra(0);
  printf("%d", d[6]);
  return 0;
}
