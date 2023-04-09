/*
ОПИСАНИЕ
Нужно отвечать на запросы вида
• + x – добавить в мультимножество число x.
• ? x – посчитать сумму чисел не больших x.
Формат входных данных
В первой строке содержится число запросов 1 6 q 6 105
.
Далее каждая строка содержит один запрос.
Все числа x целые от 0 до 109 − 1.
Формат выходных данных
Ответы на все запросы вида ? x

Мое решение использует структуру дерево отрезков
*/

#include <iostream>

const long long kBorder = 10e9 + 1;

using namespace std;

class Segment_tree {
 private:
  struct Node {
    size_t tl;
    size_t tr;
    long long sum;
    Node* lChild;
    Node* rChild;
    Node(size_t tll, size_t trr, long long summ, Node* l, Node* r)
        : tl(tll), tr(trr), sum(summ), lChild(l), rChild(r) {}
  };

 public:
  Segment_tree();
  Segment_tree(const Segment_tree& segtree);
  Segment_tree& operator=(const Segment_tree& segtree);
  ~Segment_tree();
  Node* peak();
  void update(long long x);
  long long get(size_t index);

 private:
  Node* top_ = nullptr;
  void remove_(Node* node);
  long long get_(Node* node, size_t index);
  void update_(Node* node, long long x, size_t left, size_t right);
};

Segment_tree::Segment_tree()
    : top_(new Node(0, kBorder, 0, nullptr, nullptr)) {}

Segment_tree::Segment_tree(const Segment_tree& segtree) : top_(segtree.top_) {}

Segment_tree& Segment_tree::operator=(const Segment_tree& segtree) {
  Segment_tree copy = segtree;
  swap(top_, copy.top_);
  return *this;
}

Segment_tree::~Segment_tree() { remove_(top_); }

Segment_tree::Node* Segment_tree::peak() { return top_; }

void Segment_tree::update_(Node* node, long long value, size_t left,
                          size_t right) {
  if ((node->tl == left) && (node->tr == right)) {
    node->sum += value;
  } else if ((node->tl + node->tr) / 2 < left) {
    if (node->rChild == nullptr) {
      node->rChild = new Node((node->tl + node->tr) / 2 + 1, node->tr, 0,
                              nullptr, nullptr);
    }
    update_(node->rChild, value, left, right);
  } else if ((node->tl + node->tr) / 2 >= right) {
    if (node->lChild == nullptr) {
      node->lChild =
          new Node(node->tl, (node->tl + node->tr) / 2, 0, nullptr, nullptr);
    }
    update_(node->lChild, value, left, right);
  } else {
    if (node->rChild == nullptr) {
      node->rChild = new Node((node->tl + node->tr) / 2 + 1, node->tr, 0,
                              nullptr, nullptr);
    }
    update_(node->rChild, value, node->rChild->tl, right);
    if (node->lChild == nullptr) {
      node->lChild =
          new Node(node->tl, (node->tl + node->tr) / 2, 0, nullptr, nullptr);
    }
    update_(node->lChild, value, left, node->lChild->tr);
  }
}

void Segment_tree::update(long long x) { return update_(top_, x, x, kBorder); }

long long Segment_tree::get_(Node* node, size_t index) {
  if ((node->lChild != nullptr) && (index <= (node->tl + node->tr) / 2)) {
    return node->sum + get_(node->lChild, index);
  }
  if ((node->rChild != nullptr) && (index > (node->tl + node->tr) / 2)) {
    return node->sum + get_(node->rChild, index);
  }
  return node->sum;
}

long long Segment_tree::get(size_t index) { return get_(top_, index); }

void Segment_tree::remove_(Node* node) {
  if (node->rChild != nullptr) {
    remove_(node->rChild);
  }
  if (node->lChild != nullptr) {
    remove_(node->lChild);
  }
  delete node;
}

int main() {
  Segment_tree tree;
  long long q;
  char request;
  cin >> q;
  for (long long i = 0; i < q; ++i) {
    long long x;
    cin >> request >> x;
    if (request == '+') {
      tree.update(x);
    } else if (request == '?') {
      cout << tree.get(x) << '\n';
    }
  }
}
