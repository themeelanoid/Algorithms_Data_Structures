/*
УСЛОВИЕ
Дан неориентированный граф. Требуется найти все мосты в нем.
Входные данные
Первая строка входного файла содержит два натуральных числа n и m — количество
вершин и ребер графа соответственно (n≤20000,m≤200000). Следующие m строк
содержат описание ребер по одному на строке. Ребро номер i описывается двумя
натуральными числами bi,ei — номерами концов ребра (1≤bi,ei≤n).
Выходные данные
Первая строка выходного файла должна содержать одно натуральное число k —
количество мостов в заданном графе. На следующей строке выведите k целых чисел
— номера ребер, которые являются мостами, в возрастающем порядке.
Ребра нумеруются с единицы в том порядке, в котором они заданы во входном файле.
*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <vector>

using namespace std;
int timer = 0;

void dfs(int v, vector<bool>& vertex_used, vector<int>& tin,
         vector<int>& minimum_time_of_connected,
         map<pair<int, int>, int>& number_of_edge, vector<int>& bridges,
         const vector<vector<int>>& adjacent, int& number_of_bridges,
         int parent = -1) {
  vertex_used[v] = true;
  tin[v] = minimum_time_of_connected[v] = timer++;

  for (int son : adjacent[v]) {
    if (son != parent) {
      if (vertex_used[son] == true) {
        if (tin[son] < minimum_time_of_connected[v]) {
          minimum_time_of_connected[v] = tin[son];
        }
      } else {
        dfs(son, vertex_used, tin, minimum_time_of_connected, number_of_edge,
            bridges, adjacent, number_of_bridges, v);
        if (minimum_time_of_connected[son] < minimum_time_of_connected[v]) {
          minimum_time_of_connected[v] = minimum_time_of_connected[son];
        }
        if (minimum_time_of_connected[son] > tin[v]) {
          if (number_of_edge[make_pair(v, son)] != 0) {
            bridges.push_back(number_of_edge[{v, son}]);
          } else {
            bridges.push_back(number_of_edge[{son, v}]);
          }
        }
      }
    }
  }
}

signed main() {
  int V, E;
  cin >> V >> E;

  vector<vector<int>> adjacent(V);
  vector<bool> vertex_used(V, false);

  map<pair<int, int>, int> number_of_edge;
  int parent_input, son_input;
  for (int e = 0; e < E; ++e) {
    cin >> parent_input >> son_input;
    adjacent[--parent_input].push_back(--son_input);
    adjacent[son_input].push_back(parent_input);
    number_of_edge[{parent_input, son_input}] = e + 1;
  }
  vector<int> tin(V, numeric_limits<int>::max());
  vector<int> minimum_time_of_connected(V, numeric_limits<int>::max());
  int number_of_bridges = 0;
  vector<int> bridges;
  for (int v = 0; v < V; ++v) {
    if (vertex_used[v]) {
      continue;
    } else {
      dfs(v, vertex_used, tin, minimum_time_of_connected, number_of_edge,
          bridges, adjacent, number_of_bridges);
    }
  }
  sort(bridges.begin(), bridges.end());
  cout << bridges.size() << "\n";
  for (auto e : bridges) cout << e << " ";
}