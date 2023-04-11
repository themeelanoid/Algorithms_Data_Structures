/*
УСЛОВИЕ
Дан ориентированный невзвешенный граф без петель и кратных рёбер. Необходимо
определить есть ли в нём циклы, и если есть, то вывести любой из них.

Входные данные
В первой строке входного файла находятся два натуральных числа N и M
(1⩽N⩽100000, M⩽100000) — количество вершин и рёбер в графе соответственно. Далее
в M строках перечислены рёбра графа. Каждое ребро задаётся парой чисел  —
номерами начальной и конечной вершин соответственно.

Выходные данные
Если в графе нет цикла, то вывести «NO», иначе  — «YES» и затем перечислить все
вершины в порядке обхода цикла.
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Graph {
 public:
  Graph(const vector<vector<int>>& g) : graph(g) {}
  const vector<int>& adjacentVertexes(size_t vertex) const;
  size_t size() const;

 private:
  vector<vector<int>> graph;
};

const vector<int>& Graph::adjacentVertexes(size_t vertex) const {
  return graph[vertex];
}

size_t Graph::size() const { return graph.size(); }

bool checkForCycle(int v, const Graph& graph, vector<int>& color,
                   vector<int>& parent, int& cycleStart, int& cycleEnd) {
  color[v] = 1;
  for (size_t i = 0; i < graph.adjacentVertexes(v).size(); ++i) {
    int to = graph.adjacentVertexes(v)[i];
    if (color[to] == 0) {
      parent[to] = v;
      if (checkForCycle(to, graph, color, parent, cycleStart, cycleEnd)) {
        return true;
      }
    } else if (color[to] == 1) {
      cycleEnd = v;
      cycleStart = to;
      return true;
    }
  }
  color[v] = 2;
  return false;
}

string checkForCycleInGraph(const Graph& graph, vector<int>& color,
                                 vector<int>& parent, int& cycleStart,
                                 int& cycleEnd) {
  for (int v = 1; v < graph.size(); ++v) {
    if (checkForCycle(v, graph, color, parent, cycleStart, cycleEnd)) {
      return "YES";
    }
  }
  return "NO";
}

vector<int> reconstructCycle(int cycleStart, int cycleEnd,
                                  const vector<int>& parent) {
  vector<int> cycle;
  for (int v = cycleEnd; v != cycleStart; v = parent[v]) {
    cycle.push_back(v);
  }
  cycle.push_back(cycleStart);
  reverse(cycle.begin(), cycle.end());
  return cycle;
}

int main() {
  int n;
  int m;
  cin >> n >> m;
  vector<vector<int>> g(n + 1);
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
  }
  Graph graph(g);

  vector<int> color(n + 1);
  vector<int> parent(n + 1, -1);
  int cycleStart = -1;
  int cycleEnd = -1;

  string s =
      checkForCycleInGraph(graph, color, parent, cycleStart, cycleEnd);

  cout << s << endl;
  if (s == "YES") {
    vector<int> cycle = reconstructCycle(cycleStart, cycleEnd, parent);
    for (int i : cycle) {
      cout << i << ' ';
    }
  }
  cout << endl;
}