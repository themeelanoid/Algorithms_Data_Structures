/*
Отсортируйте данную последовательность, используя алгоритм быстрой сортировки
QuickSort. Входные данные В первой строке дается число n (1≤n≤10^5)- количество
элементов в массиве, затем даются n чисел (0≤ai≤10^9). Выходные данные В
единственной строке выходного файла выведите последовательность в неубывающем
порядке.

Мое решение использует разбиение Ломуто
*/

#include <iostream>
#include <vector>

using namespace std;

pair<int, int> partition(vector<int>& array, int left, int right) {
  int pivotInd = rand() % (right - left + 1) + left;
  int pivotVal = array[pivotInd];
  int indexLess = left;
  for (int i = left; i <= right; ++i) {
    if (array[i] < pivotVal) {
      swap(array[i], array[indexLess]);
      ++indexLess;
    }
  }
  int indexGreater = indexLess;
  while (indexGreater < right && array[indexGreater] == pivotVal) {
    ++indexGreater;
  }
  while (indexGreater < right) {
    if (array[right] == pivotVal) {
      swap(array[right], array[indexGreater]);
    }
    --right;
  }
  --indexGreater;
  return {indexLess, indexGreater};
}

void quickSort(vector<int>& array, int left, int right) {
  if (left < right) {
    pair<int, int> p = partition(array, left, right);
    quickSort(array, left, p.first - 1);
    quickSort(array, p.second + 1, right);
  }
}

int main() {
  int n;
  cin >> n;
  vector<int> array(n);
  for (int i = 0; i < n; ++i) {
    cin >> array[i];
  }

  quickSort(array, 0, n - 1);

  for (int i : array) {
    cout << i << ' ';
  }
}