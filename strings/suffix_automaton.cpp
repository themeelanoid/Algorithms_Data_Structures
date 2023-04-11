/*
УСЛОВИЕ
Дано K не обязательно различных строк из маленьких латинских букв, с суммарной 
длиной N. Li определяется как максимальная длина строки, которая встречается 
как подстрока хотя бы у i строк из начального набора. 
Требуется для каждого 2≤i≤K посчитать Li.
Входные данные
В первой строке входных данных дано одно число L (1≤L≤200000) — число строк.
В следующих L строках даны сами строки из начального набора, по одной в строке. 
Гарантируется, что N — суммарная длина всех строк не превышает 200000.
Выходные данные
В k−1 строке выведите по одному числу – L2,L3,…,LK.
*/

#include <bits/stdc++.h>

using namespace std;

struct Node {
  int len;
  int link;
  map<int, int> to;
  set<int> seps;
  Node();
  Node(int len_, int link_, map<int, int>& to_);
};

Node::Node() : len(0), link(-1) {}

Node::Node(int len_, int link_, map<int, int>& to_)
    : len(len_), link(link_), to(to_) {}

vector<Node> aut;
vector<bool> visited;
int last = 0;

void dfs(int v) {
  if (visited[v]) return;
  visited[v] = true;
  for (auto next : aut[v].to) {
    if (next.first >= 26) {
      aut[v].seps.insert(next.first);
    } else {
      dfs(next.second);
      for (auto sep : aut[next.second].seps) {
        aut[v].seps.insert(sep);
      }
    }
  }
}

void saExtend(int c) {
  aut.push_back(Node());
  aut[aut.size() - 1].len = aut[last].len + 1;
  int code = c - 'a';
  int p = last;
  last = code >= 26 ? 0 : aut.size() - 1;

  while (p != -1 && aut[p].to.find(code) == aut[p].to.end()) {
    aut[p].to[code] = aut.size() - 1;
    p = aut[p].link;
  }

  if (p == -1) {
    aut[aut.size() - 1].link = 0;
  }
   else {
    int q = aut[p].to[code];

    if (aut[q].len == aut[p].len + 1) {
      aut[aut.size() - 1].link = q;
    }
     else {
      aut.push_back(Node(aut[p].len + 1, aut[q].link, aut[q].to));
      aut[q].link = aut[aut.size() - 2].link = aut.size() - 1;

      while (p != -1 && aut[p].to[code] == q) {
        aut[p].to[code] = aut.size() - 1;
        p = aut[p].link;
      }
    }
  }
}

int main() {
  aut.push_back(Node());

  int k;
  cin >> k;
  for (int i = 0; i < k; ++i) {
    string s;
    cin >> s;
    for (int j = 0; j < s.size(); ++j) {
      saExtend(s[j]);
    }
    saExtend((int)'a' + 26 + i);
  }
  visited.resize(aut.size());
  dfs(0);

  vector<int> ans(k + 1);
  for (int i = 0; i < aut.size(); ++i) {
    ans[aut[i].seps.size()] = max(aut[i].len, ans[aut[i].seps.size()]);
  }
  
  int j = k;
  for (int i = k; i >= 2; --i) {
    if (ans[i] == 0 || ans[i] < ans[j]) {
      ans[i] = ans[j];
    } else {
      j = i;
    }
  }

  for (int i = 2; i <= k; ++i) {
    cout << ans[i] << endl;
  }
}