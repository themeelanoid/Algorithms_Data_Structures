/*
ОПИСАНИЕ
Реализуйте AVL-дерево.
Входные данные
Входной файл содержит описание операций с деревом. Операций не больше 10^5.
В каждой строке находится одна из следующих операций:
insert x — добавить в дерево ключ x. Если ключ x есть в дереве, то ничего делать
не надо. delete x — удалить из дерева ключ x. Если ключа x в дереве нет, то
ничего делать не надо. exists x — если ключ x есть в дереве, вывести «true»,
иначе «false» next x — минимальный элемент в дереве, больший x, или «none», если
такого нет. prev x — максимальный элемент в дереве, меньший x, или «none», если
такого нет. Все числа во входном файле целые и по модулю не превышают 10^9.
Выходные данные
Выведите последовательно результат выполнения всех операций exists, next, prev.
*/

#include <iostream>
#include <limits>
#include <string>

using namespace std;

const int kInf = numeric_limits<int>::max();

struct Node {
  int key;
  int height;
  Node* left;
  Node* right;
  Node(int k, int h, Node* l = nullptr, Node* r = nullptr)
      : key(k), height(h), left(l), right(r) {}
};

class AVL_tree {
 public:
  void insert(int key);
  AVL_tree();
  ~AVL_tree();
  AVL_tree(const AVL_tree& other);
  AVL_tree& operator=(const AVL_tree& other);
  bool find(int key) const;
  void remove(int key);
  int find_next(int x);
  int find_prev(int x);

 private:
  Node* top;
  void del(Node* node);
  Node* build(const Node* node);
  static int balance_factor(Node* node);
  static void update_height(Node* node);
  static Node* rotate_right(Node* node);
  static Node* rotate_left(Node* node);
  static Node* big_rotate_right(Node* node);
  static Node* big_rotate_left(Node* node);
  static Node* balance(Node* node);
  Node* insert(Node* node, int key);
  bool find(const Node* node, int key) const;
  Node* find_left(Node* node);
  const Node* find_right(const Node* node) const;
  Node* remove_left(Node* node);
  Node* remove(Node* node, int key);
  int find_next(const Node* node, int x);
  int find_prev(const Node* node, int x);
};

AVL_tree::AVL_tree() { top = nullptr; }

void AVL_tree::del(Node* node) {
  if (node) {
    del(node->left);
    del(node->right);
  }
  delete node;
}

AVL_tree::~AVL_tree() {
  del(top);
  top = nullptr;
}

Node* AVL_tree::build(const Node* node) {
  if (node) {
    Node* newNode = new Node(node->key, node->height);
    newNode->left = build(node->left);
    newNode->right = build(node->right);
    return newNode;
  }
  return nullptr;
}

AVL_tree::AVL_tree(const AVL_tree& other) { top = build(other.top); }

AVL_tree& AVL_tree::operator=(const AVL_tree& other) {
  AVL_tree copy = other;
  swap(top, copy.top);
  return *this;
}

int AVL_tree::balance_factor(Node* node) {
  int height_left, height_right;
  height_left = (node->left == nullptr ? 0 : node->left->height);
  height_right = (node->right == nullptr ? 0 : node->right->height);
  return height_left - height_right;
}

void AVL_tree::update_height(Node* node) {
  int height_left, height_right;
  height_left = (node->left == nullptr ? 0 : node->left->height);
  height_right = (node->right == nullptr ? 0 : node->right->height);
  node->height = (height_left > height_right ? height_left : height_right) + 1;
}

Node* AVL_tree::rotate_right(Node* node) {
  Node* new_node = node->left;
  node->left = new_node->right;
  new_node->right = node;
  update_height(node);
  update_height(new_node);
  return new_node;
}

Node* AVL_tree::rotate_left(Node* node) {
  Node* new_node = node->right;
  node->right = new_node->left;
  new_node->left = node;
  update_height(node);
  update_height(new_node);
  return new_node;
}

Node* AVL_tree::big_rotate_right(Node* node) {
  node->left = rotate_left(node->left);
  return rotate_right(node);
}

Node* AVL_tree::big_rotate_left(Node* node) {
  node->right = rotate_right(node->right);
  return rotate_left(node);
}

Node* AVL_tree::balance(Node* node) {
  update_height(node);
  if (balance_factor(node) == -2)
    return balance_factor(node->right) > 0 ? big_rotate_left(node)
                                           : rotate_left(node);
  if (balance_factor(node) == 2)
    return balance_factor(node->left) < 0 ? big_rotate_right(node)
                                          : rotate_right(node);
  return node;
}

void AVL_tree::insert(int key) { top = insert(top, key); }

Node* AVL_tree::insert(Node* node, int key) {
  if (node == nullptr) {
    node = new Node(key, 1, nullptr, nullptr);
    return node;
  } else {
    if (key < node->key)
      node->left = insert(node->left, key);
    else if (key > node->key)
      node->right = insert(node->right, key);
  }
  return balance(node);
}

bool AVL_tree::find(int key) const { return find(top, key); }

bool AVL_tree::find(const Node* node, int key) const {
  if (node == nullptr) return false;
  if (node->key == key) return true;
  if (node->left != nullptr && key < node->key) return find(node->left, key);
  if (node->right != nullptr && key > node->key) return find(node->right, key);
  return false;
}

Node* AVL_tree::find_left(Node* node) {
  if (node->left == nullptr) return node;
  return find_left(node->left);
}

const Node* AVL_tree::find_right(const Node* node) const {
  if (node->right == nullptr) return node;
  return find_right(node->right);
}

Node* AVL_tree::remove_left(Node* node) {
  if (node->left == nullptr) return node->right;
  node->left = remove_left(node->left);
  return balance(node);
}

Node* AVL_tree::remove(Node* node, int key) {
  if (node == nullptr) return nullptr;
  if (key < node->key)
    node->left = remove(node->left, key);
  else if (key > node->key)
    node->right = remove(node->right, key);
  else if (key == node->key) {
    Node* l = node->left;
    Node* r = node->right;
    delete node;
    if (r == nullptr) return l;
    Node* min = find_left(r);
    min->right = remove_left(r);
    min->left = l;
    return balance(min);
  }
  return balance(node);
}

void AVL_tree::remove(int key) { top = remove(top, key); }

int AVL_tree::find_next(int x) { return find_next(top, x); }

int AVL_tree::find_next(const Node* node, int x) {
  if (node == nullptr) return kInf;
  if (node->key > x &&
      (node->left == nullptr || (find_right(node->left))->key <= x))
    return node->key;
  if (node->left != nullptr && (find_right(node->left))->key > x)
    return find_next(node->left, x);
  if (node->right != nullptr && node->key <= x)
    return find_next(node->right, x);
  if (node->right == nullptr && node->key <= x) return kInf;
  return kInf;
}

int AVL_tree::find_prev(int x) { return find_prev(top, x); }

int AVL_tree::find_prev(const Node* node, int x) {
  if (node == nullptr) return kInf;
  if (node->key < x &&
      (node->right == nullptr || (find_left(node->right))->key >= x))
    return node->key;
  if (node->right != nullptr && (find_left(node->right))->key < x)
    return find_prev(node->right, x);
  if (node->left != nullptr && node->key >= x) return find_prev(node->left, x);
  if (node->left == nullptr && node->key >= x) return kInf;
  return kInf;
}

int main() {
  AVL_tree tree;
  string query;
  while (cin >> query) {
    int key;
    cin >> key;
    if (query == "insert")
      tree.insert(key);
    else if (query == "delete")
      tree.remove(key);
    else if (query == "exists")
      cout << (tree.find(key) ? "true" : "false") << endl;
    else if (query == "next") {
      int ans = tree.find_next(key);
      if (ans == kInf)
        cout << "none" << endl;
      else
        cout << ans << endl;
    } else if (query == "prev") {
      int ans = tree.find_prev(key);
      if (ans == kInf)
        cout << "none" << endl;
      else
        cout << ans << endl;
    }
  }
}