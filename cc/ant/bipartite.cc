#include <vector>
using namespace std;

const int V = 4;
vector<int> G[V];
int color[V];   // 1 or -1

bool dfs(int v, int c) {
  color[v] = c;
  for (int i = 0; i < G[v].size(); i++) {
    if (color[G[v][i]] == c) return false;
    if (color[G[v][i]] == 0 && !dfs(G[v][i], -c)) return false;
  }
  return true;
}
int main() {
  /* Sample 1 
  G[0].push_back(1);
  G[0].push_back(2);
  G[1].push_back(2);
  G[1].push_back(0);
  G[2].push_back(0);
  G[2].push_back(1);
  */
  G[0].push_back(1);
  G[0].push_back(3);
  G[2].push_back(1);
  G[2].push_back(3);
  G[1].push_back(0);
  G[1].push_back(2);
  G[3].push_back(0);
  G[3].push_back(2);
  memset(color, 0, sizeof(color));
  for (int i = 0; i < V; i++) {
    if (color[i] == 0) {
      if (!dfs(i, 1)) {
        printf("No\n");
        return 0;
      }
    }
  }
  printf("Yes\n");
  return 0;
}
