/*
УСЛОВИЕ
Дан ориентированный невзвешенный граф. Необходимо его топологически
отсортировать.
Входные данные
В первой строке входного файла даны два натуральных числа N и M
(1≤N≤100000,M≤100000) — количество вершин и рёбер в графе соответственно.
Далее в M строках перечислены рёбра графа. Каждое ребро задаётся парой чисел —
номерами начальной и конечной вершин соответственно.
Выходные данные
Вывести любую топологическую сортировку графа в виде последовательности номеров
вершин. Если граф невозможно топологически отсортировать, вывести -1.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int cycleSt = -1;

bool cycleSearch(int v, const vector<vector<int>>& graph, vector<int>& color) {
  color[v] = 1;
  for (size_t i = 0; i < graph[v].size(); ++i) {
    int to = graph[v][i];
    if (color[to] == 0) {
      if (cycleSearch(to, graph, color)) return true;
    } else if (color[to] == 1) {
      cycleSt = to;
      return true;
    }
  }
  color[v] = 2;
  return false;
}

void dfs(int v, vector<bool>& used, vector<int>& ans,
         const vector<vector<int>>& graph) {
  used[v] = true;
  for (size_t i = 0; i < graph[v].size(); ++i) {
    int to = graph[v][i];
    if (!used[to]) dfs(to, used, ans, graph);
  }
  ans.push_back(v);
}

void topological_sort(int n, vector<bool>& used, vector<int>& ans,
                      const vector<vector<int>>& graph) {
  for (int i = 1; i < n + 1; ++i) {
    used[i] = false;
  }
  ans.clear();
  for (int i = 1; i < n + 1; ++i) {
    if (!used[i]) {
      dfs(i, used, ans, graph);
    }
  }
  reverse(ans.begin(), ans.end());
}

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> graph(n + 1);
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
  }
  vector<int> color(n + 1);

  for (int i = 1; i < n + 1; ++i) {
    if (cycleSearch(i, graph, color)) {
      break;
    }
  }

  if (cycleSt == -1) {
    vector<bool> used(n + 1);
    vector<int> ans;
    topological_sort(n, used, ans, graph);
    for (int i = 0; i < ans.size(); ++i) {
      cout << ans[i] << ' ';
    }
    cout << endl;
  } else {
    cout << -1 << endl;
  }
}