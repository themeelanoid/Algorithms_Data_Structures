// Требуется найти в связном графе остовное дерево минимального веса.
// Воспользуйтесь алгоритмом Крускала.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
  int from;
  int to;
  int weight;
  Edge(int f, int t, int w) : from(f), to(t), weight(w) {}
};

bool cmp(const Edge& a, const Edge& b) {
  return a.weight < b.weight;
}

class Graph {
public:
  Graph(const vector<Edge>& g, size_t n) : graph(g), numberOfVertices(n) {}
  size_t getNumberOfVertices() const;
  size_t getNumberOfEdges() const;
  const Edge& getEdge(size_t ind) const;
private:
  size_t numberOfVertices;
  vector<Edge> graph;
};

size_t Graph::getNumberOfEdges() const {
  return graph.size();
}

size_t Graph::getNumberOfVertices() const {
  return numberOfVertices;
}

const Edge& Graph::getEdge(size_t ind) const {
  return graph[ind];
}

class DSU {
public:
  int find(int v);
  void unite(int v, int u);
  explicit DSU(size_t n);
private:
  vector<int> p;
  vector<int> sz;
};

DSU::DSU(size_t n) {
  p.assign(n, -1);
  sz.assign(n, 1);
}

int DSU::find(int v) {
  if (p[v] == -1) return v;
  return find(p[v]);
}

void DSU::unite(int v, int u) {
  v = find(v);
  u = find(u);
  if (u == v) return;
  if (sz[v] < sz[u]) {
    p[v] = u;
    sz[u] += sz[v];
  } else {
    p[u] = v;
    sz[v] += sz[u];
  }
}

int findMSTcost(const Graph& graph) {
  DSU dsu(graph.getNumberOfVertices());
  int MSTcost = 0;

  for (int i = 0; i < graph.getNumberOfEdges(); ++i) {
    if (dsu.find(graph.getEdge(i).to) != dsu.find(graph.getEdge(i).from)) {
      dsu.unite(graph.getEdge(i).from, graph.getEdge(i).to);
      MSTcost += graph.getEdge(i).weight;
    }
  }
  return MSTcost;
}

int main() {
  int n;
  int m;
  cin >> n >> m;
  vector<Edge> g;
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    g.push_back(Edge(--u, --v, w));
  }
  sort(g.begin(), g.end(), cmp);

  Graph graph(g, n);
  
  cout << findMSTcost(graph) << endl;
}