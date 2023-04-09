/*
ОПИСАНИЕ
Отсортировать массив 64-битных чисел методом поразрядной сортировки LSD по байтам.
Входные данные
В первой строке вводится количество чисел в массиве N. На следующей строке через
пробел вводятся N неотрицательных чисел.
Выходные данные
Выведите этот массив, отсортированный в порядке возрастания, в одну строчку
через пробел.
*/

#include <iostream>
#include <vector>

using namespace std;

const int byteContains = 256;

long long getByte(long long number, int byteNumber) {
  number = number >> (byteNumber * 8);
  return number & (byteContains - 1);
}

void lsdSortByBytes(vector<long long>& array) {
  vector<int> counts(byteContains);
  for (int byteNumber = 0; byteNumber < 8; ++byteNumber) {
    for (int i = 0; i < byteContains; ++i) {
      counts[i] = 0;
    }
    for (int i = 0; i < array.size(); ++i) {
      ++counts[getByte(array[i], byteNumber)];
    }
    for (int i = 1; i < byteContains; ++i) {
      counts[i] += counts[i - 1];
    }
    vector<long long> sorted(array.size());
    for (int i = array.size() - 1; i >= 0; --i) {
      long long byte = getByte(array[i], byteNumber);
      sorted[--counts[byte]] = array[i];
    }
    for (int i = 0; i < array.size(); ++i) {
      array[i] = sorted[i];
    }
  }
}

int main() {
  int n;
  cin >> n;
  vector<long long> array(n);
  for (int i = 0; i < n; ++i) {
    cin >> array[i];
  }
  lsdSortByBytes(array);
  for (int i = 0; i < n; ++i) {
    cout << array[i] << ' ';
  }
}