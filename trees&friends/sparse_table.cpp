/*
ОПИСАНИЕ
Дано число N и последовательность из N целых чисел. Найти вторую порядковую
статистику на заданных диапазонах.
Для решения задачи используйте структуру данных Sparse Table. Требуемое время
обработки каждого диапазона O(1). Время подготовки структуры данных O(nlogn).
Входные данные
В первой строке заданы 2 числа: размер последовательности N и количество
диапазонов M.
Следующие N целых чисел задают последовательность. Далее вводятся M пар чисел -
границ диапазонов.
*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class SparceTable {
 public:
  explicit SparceTable(const vector<int> &array);
  int getSecondMin(int left, int right) const;

 private:
  vector<vector<pair<int, int>>> table;
  vector<int> log;
  static const int kInf;
  void logPrecount();
  void firstLayerPrecount();
  void wholeTablePrecount();
  vector<int> array;
};

const int SparceTable::kInf = numeric_limits<int>::max();

SparceTable::SparceTable(const vector<int> &arr) {
  array = arr;
  logPrecount();
  firstLayerPrecount();
  wholeTablePrecount();
}

void SparceTable::logPrecount() {
  int n = array.size();
  log.assign(n + 1, 0);
  log[1] = 0;
  for (int i = 2; i <= n; ++i) {
    log[i] = log[i / 2] + 1;
  }
}

void SparceTable::firstLayerPrecount() {
  int n = array.size();
  table.assign(log[n] + 1, vector<pair<int, int>>(n));
  for (int i = 0; i < n; ++i) {
    table[0][i] = {i, kInf};
  }
}

void SparceTable::wholeTablePrecount() {
  int n = array.size();
  for (int level = 0; level < log[n]; ++level) {
    for (int i = 0; i + (2 << level) <= n; ++i) {
      int ind1_1 = table[level][i].first,
             ind2_1 = table[level][i + (1 << level)].first;
      if (table[level][i].second == kInf) {
        if (array[ind1_1] < array[ind2_1]) {
          table[level + 1][i] = {ind1_1, ind2_1};
        } else {
          table[level + 1][i] = {ind2_1, ind1_1};
        }
      } else {
        int ind1_2 = table[level][i].second,
               ind2_2 = table[level][i + (1 << level)].second;
        vector<pair<int, int>> sorted = {{array[ind1_1], ind1_1},
                                                      {array[ind1_2], ind1_2},
                                                      {array[ind2_1], ind2_1},
                                                      {array[ind2_2], ind2_2}};
        sort(sorted.begin(), sorted.end());
        if (sorted[1].second == sorted[2].second ||
            sorted[0].second == sorted[1].second) {
          table[level + 1][i] = {sorted[0].second, sorted[2].second};
        } else {
          table[level + 1][i] = {sorted[0].second, sorted[1].second};
        }
      }
    }
  }
}

int SparceTable::getSecondMin(int left, int right) const {
  int k = log[right - left + 1];
  int ind1_1 = table[k][left].first, ind1_2 = table[k][left].second,
         ind2_1 = table[k][right - (1 << k) + 1].first,
         ind2_2 = table[k][right - (1 << k) + 1].second;
  vector<pair<int, int>> sorted = {{array[ind1_1], ind1_1},
                                                {array[ind1_2], ind1_2},
                                                {array[ind2_1], ind2_1},
                                                {array[ind2_2], ind2_2}};
  sort(sorted.begin(), sorted.end());
  if (sorted[1].second == sorted[2].second ||
      sorted[0].second == sorted[1].second) {
    return sorted[2].first;
  }
  return sorted[1].first;
}

int main() {
  int n;
  int m;
  cin >> n >> m;
  vector<int> array(n);
  for (int i = 0; i < n; ++i) {
    cin >> array[i];
  }
  SparceTable st(array);
  int left, right;
  for (int i = 0; i < m; ++i) {
    cin >> left >> right;
    cout << st.getSecondMin(left - 1, right - 1) << endl;
  }
}