// Дан взвешенный неориентированный граф. 
// Требуется найти вес минимального пути между двумя вершинами.

#include <iostream>
#include <vector>
#include <limits>
#include <queue>

using namespace std;

const int inf = numeric_limits<int>::max();

struct adjacentVertex {
  int to;
  int cost;
  adjacentVertex(int t, int c) : to(t), cost(c) {}
};

class WeightedGraph {
public:
  WeightedGraph(const vector<vector<adjacentVertex>>& g) : graph(g) {}
  const vector<adjacentVertex>& adjacentVertices(size_t vertex) const;
  size_t numberOfVertices() const;
private:
  vector<vector<adjacentVertex>> graph;
};
 
const vector<adjacentVertex>& 
                        WeightedGraph::adjacentVertices(size_t vertex) const {
  return graph[vertex];
}
size_t WeightedGraph::numberOfVertices() const {
  return graph.size();
}

int findDistanceBetweenVertices(const WeightedGraph& graph, int s, int t) {
  vector<int> dist(graph.numberOfVertices(), inf);
  dist[--s] = 0;
  priority_queue<pair<int, int>> q;
  q.push({0, s});

  while(!q.empty()) {
    auto a = q.top();
    q.pop();
    if (-(a.first) > dist[a.second]) {
      continue;
    }
    for (auto y : graph.adjacentVertices(a.second)) {
      if (dist[y.to] > dist[a.second] + y.cost) {
        dist[y.to] = dist[a.second] + y.cost;
        q.push({-dist[y.to], y.to});
      }
    }
  }

  if (dist[--t] == inf) {
    return -1;
  }
  return dist[t];
}

int main() {
  int n;
  int m; 
  int s;
  int t;
  cin >> n >> m >> s >> t;
  vector<vector<adjacentVertex>> g(n);
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    g[--u].push_back(adjacentVertex(--v, w));
    g[v].push_back(adjacentVertex(u, w));
  }

  WeightedGraph graph(g);

  cout << findDistanceBetweenVertices(graph, s, t) << endl;
}