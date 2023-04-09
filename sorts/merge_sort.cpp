/*
ОПИСАНИЕ
Реализация алгоритма сортировки Merge sort с помощью рекурсии
*/

#include <iostream>
#include <vector>

using namespace std;

vector<int>& merge(vector<int>& array, vector<int>& toMerge1,
                   vector<int>& toMerge2) {
  int ind1 = 0;
  int ind2 = 0;
  int a = 0;
  while (ind1 < toMerge1.size() && ind2 < toMerge2.size()) {
    if (toMerge1[ind1] <= toMerge2[ind2]) {
      array[a++] = toMerge1[ind1++];
    } else {
      array[a++] = toMerge2[ind2++];
    }
  }

  while (ind1 < toMerge1.size()) {
    array[a++] = toMerge1[ind1++];
  }
  while (ind2 < toMerge2.size()) {
    array[a++] = toMerge2[ind2++];
  }

  return array;
}

void mergeSort(vector<int>& array) {
  if (array.size() <= 1) {
    return;
  }

  int middle = array.size() / 2;
  vector<int> firstHalf(array.begin(), array.begin() + middle);
  vector<int> secondHalf(array.begin() + middle, array.end());
  mergeSort(firstHalf);
  mergeSort(secondHalf);

  array = merge(array, firstHalf, secondHalf);
}

int main() {
  // vector<int> array = {13, 9, 7, 6, 9, 6, 0, 100900};
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n;
  cin >> n;
  vector<int> array(n);
  for (int i = 0; i < n; ++i) {
    cin >> array[i];
  }
  mergeSort(array);
  for (int i : array) {
    cout << i << ' ';
  }
}