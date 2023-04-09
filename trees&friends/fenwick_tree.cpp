/*
ОПИСАНИЕ
Реализация дерева Фенвика на массиве array с операциями
getSum(left, right) - узнать сумму элементов массива на отрезке с left по right включительно 
update(pos, value) - обновить элемент в массиве в позиции pos,задав значение value
*/

#include <iostream>
#include <vector>

using namespace std;

class FenwickTree {
 public:
  explicit FenwickTree(const vector<int>& array);
  int getSum(int left, int right);
  void update(int pos, int value);
  vector<int> getTree() { return tree_; };
  vector<int> getArray() { return array_; };

 private:
  int n_;
  vector<int> tree_;
  vector<int> array_;
  int down(int x) { return x & (x + 1); };
  int up(int x) { return x | (x + 1); };
  int prefSum(int right);
  void addValue(int pos, int value);
};

FenwickTree::FenwickTree(const vector<int>& array)
    : n_(array.size()), array_(array) {
  tree_.assign(n_, 0);
  for (int i = 0; i < n_; ++i) {
    addValue(i, array[i]);
  }
}

int FenwickTree::prefSum(int right) {
  int ans = 0;
  for (int i = right; i >= 0; i = down(i) - 1) {
    ans += tree_[i];
  }
  return ans;
}

void FenwickTree::addValue(int pos, int value) {
  for (int i = pos; i < n_; i = up(i)) {
    tree_[i] += value;
  }
}

int FenwickTree::getSum(int left, int right) {
  return prefSum(right) - prefSum(left - 1);
}

void FenwickTree::update(int pos, int value) {
  addValue(pos, value - array_[pos]);
  array_[pos] = value;
}

int main() {
  FenwickTree ft({1, 5, 2, 10, 14, 6, 3, 0, 0, 2});
  for (int i : ft.getArray()) {
    cout << i << ' ';
  }
  cout << endl;
  cout << ft.getSum(2, 4) << endl;
  ft.update(3, 0);
  for (int i : ft.getArray()) {
    cout << i << ' ';
  }
  cout << endl;
  cout << ft.getSum(2, 4) << endl;
}