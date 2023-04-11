/*
УСЛОВИЕ
В известной игре «цепочка слов» необходимо получить из одного слова другое, 
меняя в нём по одной букве. Например, получить из мухи слона можно за 8 шагов: 
МУХА–МУЛА–КУЛА–КИЛА–КИЛТ–КИОТ–КЛОТ–КЛОН–СЛОН. Все использованные слова 
должны принадлежать словарю. Игра изобретена Льюисом Кэрроллом, будем называть 
минимальное количество шагов, необходимое для получения из одного слова 
другого «расстоянием по Кэрроллу».
По заданному словарю и набору пар слов определите расстояние по Кэрроллу для 
каждой заданной пары слов.
Входные данные
Первая строка входных данных содержит количество слов в словаре n. Следующие n
строк содержат по одному слову, записанному строчными английскими буквами. Все 
слова имеют одинаковую длину. Следующая строка содержит количество запросов m. 
Следующие 2m строк содержат описание m запросов, каждый запрос состоит из двух 
слов, для которых необходимо определить расстояния.
Выходные данные
Программа должна вывести m целых чисел: для каждого запроса необходимо вывести 
расстояние по Кэрроллу для данных слов. Если из одного слова запроса нельзя 
получить другое, программа должна вывести число -1.
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <queue>

using namespace std;

int heuristics(string& pos, string& end) {
  int ans = 0;
  for (int i = 0; i < pos.length(); ++i) {
    if (pos[i] != end[i]) ++ans;
  }
  return ans;
}

int main() {
  unordered_set<char> alph;
  
  int n;
  cin >> n;
  vector<string> ind1(n);
  unordered_map<string, int> ind2;
  
  vector<vector<int>> g(n);
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    ind1[i] = s;
    ind2[ind1[i]] = i;
    for (char j: s) {
      alph.insert(j);
    }
  }
  for (int i = 0; i < n; ++i) {
    string tmp = ind1[i];
    
    for (int j = 0; j < tmp.size(); ++j) {
      for (char k: alph) {
        if (k != ind1[i][j]) {
          tmp[j] = k;
          if (ind2.find(tmp) != ind2.end()) {
            g[i].push_back(ind2[tmp]);
          }
          tmp[j] = ind1[i][j];
        }
      }
    }
  }
  
  int m;
  cin >> m;
  for (int i = 0; i < m; ++i) {
    string st, end;
    cin >> st >> end;
    int s = ind2[st], e = ind2[end];
    bool way = false;
    unordered_map<int, int> dist;
    dist[s] = 0;
    unordered_set<int> visited;
    priority_queue<pair<int, int>> heap;
    heap.push({0, s});
    
    while (!heap.empty()) {
      
      auto v = heap.top();
      heap.pop();
      
      if (v.second == e) {
        way = true;
        break;
      }
      
      if (visited.find(v.second) != visited.end()) continue;
      visited.insert(v.second);
      
      for (int to: g[v.second]) {
        if (dist.find(to) == dist.end() || dist[v.second] + 1 < dist[to]) {
          dist[to] = dist[v.second] + 1;
          heap.push({-(dist[to] + heuristics(ind1[to], end)), to});
        }
      }
    }
    
    if (way) {
      cout << dist[e] << endl;
    } else {
      cout << -1 << endl;
    }
  }
}