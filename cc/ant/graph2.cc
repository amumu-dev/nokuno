#include <vector>
using namespace std;

const size_t MAX_V = 10;
struct vertex {
  vector<vertex*> edge;
  int cost;
};
vertex G[MAX_V];

int main() {
  int V, E;
  scanf("%d %d", &V, &E);
  for (int i = 0; i < E; i++) {
    int s, t;
    scanf("%d %d", &s, &t);
    G[s].edge.push_back(&G[t]);
  }
  for (int i = 0; i < MAX_V; i++) {
    for (int j = 0; j < G[i].edge.size(); j++) {
      printf("%d ", G[i].edge[j]->cost);
    }
    printf("\n");
  }
  return 0;
}
