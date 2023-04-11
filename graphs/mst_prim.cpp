// Требуется найти в связном графе остовное дерево минимального веса.
// Воспользуйтесь алгоритмом Прима.
 
#include <iostream>
#include <vector>
#include <limits>
 
const int inf = numeric_limits<int>::max();
using namespace std;

class Graph {
public:
  Graph(const vector<vector<int>>& g) : graph(g) {}
   const vector<int>& adjacentVertices(size_t vertex) const;
  size_t numberOfVertices() const;
private:
  vector<vector<int>> graph;
};
 
const vector<int>& Graph::adjacentVertices(size_t vertex) const {
  return graph[vertex];
}
 
size_t Graph::numberOfVertices() const {
  return graph.size();
}
 
int findMSTcost(const Graph& graph) {
  vector<bool> used(graph.numberOfVertices());
  vector<int> dist(graph.numberOfVertices(), inf);
  dist[0] = 0;
 
  int MSTcost = 0;
  for (int i = 0; i < graph.numberOfVertices(); ++i) {
    int v = -1;
    for (int j = 0; j < graph.numberOfVertices(); ++j) {
      if (!used[j] && (v == -1 || dist[j] < dist[v])) {
        v = j;
      }
    }
    MSTcost += dist[v];
    used[v] = true;
    for (int to = 0; to < graph.numberOfVertices(); ++to) {
      if (graph.adjacentVertices(v)[to] < dist[to]) {
        dist[to] = graph.adjacentVertices(v)[to];
      }
    }
  }
  return MSTcost;
}
 
int main() {
  int n;
  int m;
  cin >> n >> m;
  vector<vector<int>> g(n, vector<int>(n, inf));
  for (int i = 0; i < m; ++i) {
    int u;
    int v;
    int w;
    cin >> u >> v >> w;
    g[--u][--v] = w;
    g[v][u] = w;
  }
 
  Graph graph(g);
 
  cout << findMSTcost(graph) << endl;
}