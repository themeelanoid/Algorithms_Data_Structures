/*
УСЛОВИЕ
Вам задан неориентированный граф с N вершинами и M ребрами.
В графе отсутствуют петли и кратные ребра.
Определите компоненты связности заданного графа.
Входные данные
Граф задан во входном файле следующим образом: первая строка содержит числа
N и M (1≤N≤20000,1≤M≤200000). Каждая из следующих M строк содержит описание
ребра — два целых числа из диапазона от 1 до N — номера концов ребра.
Выходные данные
На первой строке выходного файла выведите число L — количество компонент
связности заданного графа. На следующей строке выведите N чисел из диапазона
от 1 до L — номера компонент связности, которым принадлежат соответствующие
вершины. Компоненты связности следует
занумеровать от 1 до L произвольным образом.
*/

#include <iostream>
#include <vector>

using namespace std;

void dfs(int v, const vector<vector<int>>& graph, vector<bool>& used,
         vector<int>& numberOfComponent, int OGBuda) {
  used[v] = true;
  numberOfComponent[v] = OGBuda;
  for (size_t i = 0; i < graph[v].size(); ++i) {
    int to = graph[v][i];
    if (!used[to]) {
      numberOfComponent[to] = OGBuda;
      dfs(to, graph, used, numberOfComponent, OGBuda);
    }
  }
}

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> graph(n + 1);
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  vector<bool> used(n + 1);
  vector<int> numberOfComponent(n + 1);

  int OGBuda = 1;
  for (int i = 1; i < n + 1; ++i) {
    if (!used[i]) {
      dfs(i, graph, used, numberOfComponent, OGBuda);
      ++OGBuda;
    }
  }
  cout << OGBuda - 1 << endl;
  for (int i = 1; i < numberOfComponent.size(); ++i) {
    cout << numberOfComponent[i] << ' ';
  }
}