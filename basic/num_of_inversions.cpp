/*
ОПИСАНИЕ 
Напишите программу, которая для заданного массива A = ⟨a1, a2, …, an⟩ находит
количество пар (i, j) таких, что i < j и ai > aj.
*/

#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

vector<long long> merge(const vector<long long>& merging1,
                        const vector<long long>& merging2) {
  vector<long long> merged;
  int i = 0;
  int j = 0;
  while (i < merging1.size() && j < merging2.size()) {
    if (merging1[i] > merging2[j]) {
      merged.push_back(merging2[j]);
      ++j;
    } else {
      merged.push_back(merging1[i]);
      ++i;
    }
  }
  while (i < merging1.size()) {
    merged.push_back(merging1[i]);
    ++i;
  }
  while (j < merging2.size()) {
    merged.push_back(merging2[j]);
    ++j;
  }
  return merged;
}

void count_inversions(const vector<long long>& merging1,
                      const vector<long long>& merging2,
                      long long& inversions) {
  int a = 0, b = 0;
  while (a < merging1.size() && b < merging2.size()) {
    if (merging1[a] > merging2[b]) {
      inversions += merging1.size() - a;
      ++b;
    } else {
      ++a;
    }
  }
}

int main() {
  freopen("inverse.in", "r", stdin);
  freopen("inverse.out", "w", stdout);
  int n;
  cin >> n;
  queue<vector<long long>> que;
  long long k;
  for (int i = 0; i < n; ++i) {
    cin >> k;
    que.push({k});
  }
  int power_of2 = 1;
  while (n > power_of2) {
    power_of2 *= 2;
  }
  for (int i = 0; i < power_of2 - n; ++i) {
    que.push({numeric_limits<long long>::max()});
  }

  long long inversions = 0;
  vector<long long> merging1;
  vector<long long> merging2;
  while (que.size() > 1) {
    merging1 = que.front();
    que.pop();
    merging2 = que.front();
    que.pop();
    count_inversions(merging1, merging2, inversions);
    que.push(merge(merging1, merging2));
  }
  cout << inversions << '\n';
}
