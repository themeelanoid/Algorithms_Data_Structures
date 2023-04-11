/*
УСЛОВИЕ
Требуется найти количество ребер в конденсации ориентированного графа. 
Входные данные
Первая строка входного файла содержит два натуральных числа n и m — количество 
вершин и рёбер графа соответственно (n≤10000, m≤100000). Следующие m
строк содержат описание ребер, по одному на строке. Ребро номер i
описывается двумя натуральными числами bi,ei — началом и концом ребра 
соответственно (1≤bi,ei≤n). В графе могут присутствовать кратные ребра и петли.
Выходные данные
Первая строка выходного файла должна содержать одно число — количество ребер в 
конденсации графа.
*/

#include <iostream>
#include <set>
#include <vector>

using namespace std;

void dfs(int v, vector<bool>& used, const vector<vector<int>>& graph,
         vector<int>& order) {
  used[v] = true;
  for (size_t i = 0; i < graph[v].size(); ++i) {
    if (!used[graph[v][i]]) {
      dfs(graph[v][i], used, graph, order);
    }
  }
  order.push_back(v);
}

void dfstransposed(int v, vector<bool>& used,
                   const vector<vector<int>>& transposed,
                   vector<int>& component) {
  used[v] = true;
  component.push_back(v);
  for (size_t i = 0; i < transposed[v].size(); ++i) {
    if (!used[transposed[v][i]]) {
      dfstransposed(transposed[v][i], used, transposed, component);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m;
  cin >> n >> m;
  vector<vector<int>> graph(n + 1), transposed(n + 1);
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    transposed[v].push_back(u);
  }

  vector<bool> used(n + 1, false);
  vector<int> order, component;
  vector<int> firstVertexOfComponent(n + 1);
  for (int i = 1; i < n + 1; ++i) {
    if (!used[i]) {
      dfs(i, used, graph, order);
    }
  }
  used.assign(n + 1, false);
  for (int i = 1; i < n + 1; ++i) {
    int v = order[n - i];
    if (!used[v]) {
      dfstransposed(v, used, transposed, component);
      for (int j : component) {
        firstVertexOfComponent[j] = component[0];
      }
      component.clear();
    }
  }
  vector<set<int>> edgesToAnotherComponent(n + 1);
  int cnt = 0;
  for (int v = 1; v < n + 1; ++v) {
    for (int j : graph[v]) {
      if (firstVertexOfComponent[v] != firstVertexOfComponent[j]) {
        if (edgesToAnotherComponent[firstVertexOfComponent[v]].find(
                firstVertexOfComponent[j]) ==
            edgesToAnotherComponent[firstVertexOfComponent[v]].end()) {
          ++cnt;
          edgesToAnotherComponent[firstVertexOfComponent[v]].insert(
              firstVertexOfComponent[j]);
        }
      }
    }
  }
  cout << cnt;
}