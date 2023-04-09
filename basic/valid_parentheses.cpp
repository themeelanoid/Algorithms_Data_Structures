/*
ОПИСАНИЕ
По заданной строке из круглых/квадратных/фигурных открывающих и закрывающих
скобок определить, является ли она правильной скобочной последовательностью.

Множество правильных скобочных последовательностей (ПСП) определяется как
наименьшее множество с условиями: 
пустая строка является ПСП;
если S — ПСП, то (S), [S], {S} — тоже ПСП;
если S1 и S2 — ПСП, то S1S2 — тоже ПСП.
*/

#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main() {
  stack<char> st;
  string sequence;
  cin >> sequence;
  bool isCorrect = true;
  for (size_t i = 0; i < sequence.length(); ++i) {
    if (sequence[i] == '(' || sequence[i] == '[' || sequence[i] == '{')
      st.push(sequence[i]);
    else {
      if (!st.size() &&
          (sequence[i] == ')' || sequence[i] == ']' || sequence[i] == '}')) {
        isCorrect = false;
        break;
      }
      if ((st.top() == '(' && sequence[i] == ')') ||
          (st.top() == '[' && sequence[i] == ']') ||
          (st.top() == '{' && sequence[i] == '}')) {
        st.pop();
      } else {
        isCorrect = false;
        break;
      };
    }
  }
  if (st.size()) isCorrect = false;
  cout << (isCorrect ? "yes" : "no") << '\n';
}