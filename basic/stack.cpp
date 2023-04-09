/*
ОПИСАНИЕ
Реализуйте свой стек.
Гарантируется, что количество элементов в стеке ни в какой момент времени не превышает 10000.

Обработайте следующие запросы:
push n: добавить число n в конец стека и вывести «ok»;
pop: удалить из стека последний элемент и вывести его значение, либо вывести «error», если стек был пуст;
back: сообщить значение последнего элемента стека, либо вывести «error», если стек пуст;
size: вывести количество элементов в стеке;
clear: опустошить стек и вывести «ok»;
exit: вывести «bye» и завершить работу.
*/

#include <iostream>
#include <string>

using namespace std;

class Stack {
 public:
  void push(int n);
  int pop();
  int back();
  size_t size();
  void clear();

 private:
  struct Node;
  Node* top_ = nullptr;
  size_t sz_ = 0;
};

struct Stack::Node {
  int val;
  Node* prev;
  Node(int v, Node* p) : val(v), prev(p) {}
};

void Stack::push(int v) {
  Node* node = new Node(v, top_);
  std::swap(top_, node);
  ++sz_;
}

int Stack::pop() {
  Node* x = top_->prev;
  int y = top_->val;
  delete top_;
  top_ = x;
  --sz_;
  return y;
}

int Stack::back() { return top_->val; }

size_t Stack::size() { return sz_; }

void Stack::clear() {
  while (sz_ > 0) {
    pop();
  }
}

int main() {
  Stack stack;
  string inpt;
  cin >> inpt;
  while (inpt != "exit") {
    if (inpt == "push") {
      int n;
      cin >> n;
      stack.push(n);
      cout << "ok" << '\n';
    } else if (inpt == "pop") {
      if (stack.size() > 0)
        cout << stack.pop() << '\n';
      else
        cout << "error" << '\n';
    } else if (inpt == "back") {
      if (stack.size() > 0)
        cout << stack.back() << '\n';
      else
        cout << "error" << '\n';
    } else if (inpt == "size")
      cout << stack.size() << '\n';
    else if (inpt == "clear") {
      stack.clear();
      cout << "ok" << '\n';
    }
    cin >> inpt;
  }
  stack.clear();
  cout << "bye" << '\n';
}