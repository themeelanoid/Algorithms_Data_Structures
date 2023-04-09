/*
ОПИСАНИЕ
Реализуйте двоичную кучу.
Обработайте запросы следующих видов:
insert x — вставить целое число x в кучу;
getMin — вывести значение минимального элемента в куче (гарантируется, что к этому моменту куча не пуста);
extractMin — удалить минимальный элемент из кучи, выводить его не нужно (гарантируется, что к этому моменту куча не пуста);
decreaseKey i Δ — уменьшить число, вставленное на i-м запросе, на целое число Δ≥0. Число i равно номеру запроса среди всех запросов, а не только среди запросов добавления.
В любой момент времени все числа, хранящиеся в куче, попарно различны.
Входные данные
В первой строке содержится число q (1≤q≤10^6), означающее число запросов.
В следующих q строках содержатся запросы в описанном выше формате. Добавляемые числа x и поправки Δ лежат в промежутке [−10^9,10^9], а Δ≥0.
Выходные данные
На каждый запрос вида getMin выведите ответ в отдельной строке.
*/

#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

const long long kInf = numeric_limits<long long>::max();

class BinaryHeap {
 private:
  vector<long long> heap;
  vector<size_t> indexHeap;
  vector<long long> enterTime;
  void exchange(size_t ind1, size_t ind2);
  void siftUp(size_t index);
  void siftDown(size_t index);

 public:
  BinaryHeap();
  void insert(long long number, size_t time);
  long long getMin();
  void extractMin();
  void decreaseKey(long long pointer, long long delta);
};

void BinaryHeap::exchange(size_t ind1, size_t ind2) {
  swap(enterTime[indexHeap[ind1]], enterTime[indexHeap[ind2]]);
  swap(heap[ind1], heap[ind2]);
  swap(indexHeap[ind1], indexHeap[ind2]);
}

void BinaryHeap::siftUp(size_t index) {
  while (index != 1) {
    if (heap[index] < heap[index / 2]) {
      exchange(index, index / 2);
      index /= 2;
    } else {
      break;
    }
  }
}

void BinaryHeap::siftDown(size_t index) {
  while (2 * index < heap.size()) {
    size_t newIndex = 2 * index;
    if (2 * index + 1 < heap.size() && heap[2 * index + 1] < heap[2 * index]) {
      newIndex = index * 2 + 1;
    }
    if (heap[newIndex] < heap[index]) {
      exchange(index, newIndex);
      index = newIndex;
    } else {
      break;
    }
  }
}

BinaryHeap::BinaryHeap() {
  heap = {1};
  indexHeap = {1};
  enterTime = {1};
}

void BinaryHeap::insert(long long number, size_t time) {
  heap.push_back(number);
  indexHeap.push_back(time);
  enterTime.push_back(heap.size() - 1);
  siftUp(heap.size() - 1);
}

long long BinaryHeap::getMin() {
  enterTime.push_back(kInf);
  return (heap[1]);
}

void BinaryHeap::extractMin() {
  enterTime.push_back(kInf);
  exchange(heap.size() - 1, 1);
  heap.pop_back();
  indexHeap.pop_back();
  siftDown(1);
}

void BinaryHeap::decreaseKey(long long pointer, long long delta) {
  enterTime.push_back(kInf);
  heap[enterTime[pointer]] -= delta;
  siftUp(enterTime[pointer]);
}

int main() {
  BinaryHeap BinaryHeap;
  long long q;
  cin >> q;
  for (size_t i = 1; i <= q; ++i) {
    string query;
    cin >> query;

    if (query == "insert") {
      long long number;
      cin >> number;
      BinaryHeap.insert(number, i);
    } else if (query == "getMin") {
      cout << BinaryHeap.getMin() << endl;
    } else if (query == "extractMin") {
      BinaryHeap.extractMin();
    } else if (query == "decreaseKey") {
      long long pointer;
      long long delta;
      cin >> pointer >> delta;
      BinaryHeap.decreaseKey(pointer, delta);
    }
  }
}