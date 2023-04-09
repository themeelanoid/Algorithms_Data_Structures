/*
ОПИСАНИЕ
Даны неотрицательные целые числа N, K и массив целых чисел из диапазона [0,10^9]
размера N. Требуется найти K-ю порядковую статистику, т.е. напечатать число,
которое бы стояло на позиции с индексом K ∈[0,N−1] в отсортированном массиве.
Реализуйте алгоритм QuickSelect (среднее время работы O(N)).
Входные данные
В первой строке записаны N и K.
В N последующих строках записаны числа последовательности.
Выходные данные
K-я порядковая статистика.
*/

#include <iostream>
#include <vector>

using namespace std;

int partition(vector<int>& array, int left, int right) {
  int pivotInd = rand() % (right - left + 1) + left;
  int pivotVal = array[pivotInd];
  swap(array[pivotInd], array[right]);
  int indexLess = left;
  for (int i = left; i < right; ++i) {
    if (array[i] < pivotVal) {
      swap(array[i], array[indexLess++]);
    }
  }
  swap(array[right], array[indexLess]);
  return indexLess;
}

int quickSelect(vector<int>& array, int k) {
  int left = 0;
  int right = array.size() - 1;
  while (left != right) {
    int indexLess = partition(array, left, right);
    if (indexLess == k) {
      return array[indexLess];
      if (indexLess < k) {
        left = indexLess + 1;
      } else {
        right = indexLess;
      }
    }
  }
  return array[right];
}

int main() {
  int n;
  int k;
  cin >> n >> k;
  vector<int> array(n);
  for (int i = 0; i < n; ++i) {
    cin >> array[i];
  }
  cout << quickSelect(array, k) << endl;
}