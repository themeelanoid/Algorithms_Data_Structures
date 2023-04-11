/*
УСЛОВИЕ
Задан ориентированный граф, каждое ребро которого обладает пропускной 
способностью и стоимостью. Найдите максимальный поток минимальной стоимости из 
вершины с номером 1 в вершину с номером n.
Входные данные
Первая строка входного файла содержит n и m — количество вершин и количество 
ребер графа (2≤n≤100, 0≤m≤1000). Следующие m строк содержат по четыре целых 
числа числа: номера вершин, которые соединяет соответствующее ребро графа, его 
пропускную способность и его стоимость. Пропускные способности и стоимости не 
превосходят 10^5.
Выходные данные
В выходной файл выведите одно число — цену максимального потока минимальной 
стоимости из вершины с номером 1 в вершину с номером n. 
Ответ не превышает 2^63−1. Гарантируется, что в графе нет циклов 
отрицательной стоимости.
*/

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <limits>
#include <queue>

using namespace std;

const long long inf = numeric_limits<long long>::max();

int n;
map<long long, set<long long>> graph;
map<vector<int>, pair<long long, long long>> cost_capacity;

void dijkstra(long long s, vector<pair<int, int>>& parent, 
                                                vector<long long>& dist) {
  vector<bool> busy(n, false);
  queue<int> q;
  parent.assign(n, {-1, 0});
  dist.assign(n, inf);

  dist[s] = 0;
  q.push(s);

  while (!q.empty()) {
    int v = q.front();
    q.pop();
    busy[v] = false;

    for (int u: graph[v]) {
      int j = 0;
      while (cost_capacity.find({v, u, j}) != cost_capacity.end()) {
        if (dist[v] + cost_capacity[{v, u, j}].first < dist[u] 
                                    && cost_capacity[{v, u, j}].second > 0 ) {
          long long delta =  dist[v] + cost_capacity[{v, u, j}].first;
          dist[u] = delta;
          parent[u] = {v, j};
          if (!busy[u]) {
            busy[u] = !busy[u];
            q.push(u);
          }
        }
        ++j;
      }
    }
  }
}

long long MCMF(long long s, long long t) {
  long long cost = 0;
  vector<long long> dist;
  vector<pair<int, int>> parent;
  while (true) {
    dijkstra(s, parent, dist);
    if (dist[t] == inf) break;

    long long delta = inf;

    for (int v = t; v != s; v = parent[v].first) {
      delta = min(delta, 
                  cost_capacity[{parent[v].first, v, parent[v].second}].second);
    }

    for (int v = t; v != s; v = parent[v].first) {
      long long mult = 
        cost_capacity[{parent[v].first, v, parent[v].second}].first;
      cost += delta * mult;
      cost_capacity[{parent[v].first, v, parent[v].second}].second = 
        cost_capacity[{parent[v].first, v, parent[v].second}].second  - delta;
      cost_capacity[{v, parent[v].first, parent[v].second}].second =
        cost_capacity[{v, parent[v].first, parent[v].second}].second + delta;
    }
  }
  return cost;
}

int main() {
  int m;
  cin >> n >> m;

  int s = 0;
  int t = n - 1;

  for (long long i = 0; i < m; ++i) {
    int v;
    int to;
    long long cap; 
    long long cost;
    cin >> v >> to >> cap >> cost;
    --v;
    --to;
    int j = 0;
    while (cost_capacity.find({v, to, j}) != cost_capacity.end()) {
      ++j;
    }
    graph[v].insert(to);
    cost_capacity[{v, to, j}] = make_pair(cost, cap);
    graph[to].insert(v);
    cost_capacity[{to, v, j}] = make_pair(-cost, 0);
  }

  cout << MCMF(s, t) << endl;
}