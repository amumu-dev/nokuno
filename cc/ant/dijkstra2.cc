#include <stdio.h>
#include <queue>
#include <vector>
using namespace std;

#define MAX_E 20
#define MAX_V 7
#define INF 100000

struct edge {
  int to, cost;
  edge(int _to, int _cost) {to = _to; cost=_cost;}
};
typedef pair<int, int> P;

int V;
vector<edge> G[MAX_V];
int d[MAX_V];

void dijkstra(int s) {
  priority_queue<P, vector<P>, greater<P> > que;
  fill(d, d + MAX_V, INF);
  d[s] = 0;
  que.push(P(0, s));

  while(!que.empty()) {
    P p = que.top(); que.pop();
    int v = p.second;
    if (d[v] < p.first) continue;
    for (int i = 0; i < G[v].size(); i++) {
      edge e = G[v][i];
      if (d[e.to] > d[v] + e.cost) {
        d[e.to] = d[v] + e.cost;
        que.push(P(d[e.to], e.to));
      }
    }
  }
}

int main() {
  G[0].push_back(edge(1,2));
  G[0].push_back(edge(2,5));
  G[1].push_back(edge(2,4));
  G[1].push_back(edge(3,6));
  G[1].push_back(edge(4,10));
  G[2].push_back(edge(3,2));
  G[3].push_back(edge(5,1));
  G[4].push_back(edge(5,3));
  G[4].push_back(edge(6,5));
  G[5].push_back(edge(6,9));
  for (int i = 0; i < MAX_V; i++) {
    for (int j = 0; j < G[i].size(); j++) {
      G[G[i][j].to].push_back(edge(i, G[i][j].cost));
    }
  }

  dijkstra(0);
  printf("%d", d[6]);
  return 0;
}
