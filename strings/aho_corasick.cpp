/*
УСЛОВИЕ
Входные данные
В стандартном потоке ввода ваша программа найдёт строчку из маленьких латинских 
букв, которую мы назовём исходной. На следующей строчке программа найдёт число N
(1≤N≤1000000), а в следующих N строчках — по слову из тех же маленьких 
латинских букв; эти слова мы назовём словарём. Суммарная сумма длин слов 
из словаря не превосходит 1000000.
Выходные данные
Ваша программа должна вывести на стандартный поток вывода N строк. В i-ой 
строке программа должна вывести несколько чисел: первое число — количество 
(сколько штук) вхождений строчки i из словаря в исходную строку, затем через 
пробел для каждого вхождения выведите индексы начал всех вхождений этой строки 
в исходную в отсортированном порядке. Индексы всех строк начинаются с единицы. 
Вам гарантируют, что количество вхождений не превосходит 1000000.
*/

#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>
 
using namespace std;

const int ALPHABETSIZE = 26;
 
int charToAlphabet(char c) { return c - 'a'; }
 
class Trie {
 private:
  struct Node_;
  vector<Node_> trie_;
 
 public:
  void add(const string& str, int number);
  Node_& getNode(size_t ind) { return trie_[ind]; }
  const Node_& getNode(size_t ind) const { return trie_[ind]; }
};
 
struct Trie::Node_ {
  bool term;
  int link;
  int stringSize;
  vector<int> endingNumbers;
  vector<int> to;
  Node_();
};
 
Trie::Node_::Node_() : term(false), link(-1), stringSize(0) {
  to.assign(ALPHABETSIZE, -1);
}
 
void Trie::add(const string& str, int number) {
  if (trie_.empty()) {
    trie_.push_back(Node_());
  }
  int v = 0;
  for (int i = 0; i < str.size(); ++i) {
    if (trie_[v].to[charToAlphabet(str[i])] == -1) {
      trie_[v].to[charToAlphabet(str[i])] = trie_.size();
      trie_.push_back(Node_());
    }
    v = trie_[v].to[charToAlphabet(str[i])];
  }
  trie_[v].term = true;
  trie_[v].endingNumbers.push_back(number);
  trie_[v].stringSize = str.size();
}
 
void ahoCorasick(Trie& trie_) {
  trie_.getNode(0).link = 0;
  for (int c = 0; c < ALPHABETSIZE; ++c) {
    if (trie_.getNode(0).to[c] == -1) {
      trie_.getNode(0).to[c] = 0;
    }
  }
  queue<int> q;
  q.push(0);
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (int c = 0; c < ALPHABETSIZE; ++c) {
      int u = trie_.getNode(v).to[c];
      if (trie_.getNode(u).link != -1) {
        continue;
      }
      trie_.getNode(u).link =
          (v ? trie_.getNode(trie_.getNode(v).link).to[c] : 0);
      for (int d = 0; d < ALPHABETSIZE; ++d) {
        if (trie_.getNode(u).to[d] != -1) {
          continue;
        }
        trie_.getNode(u).to[d] = trie_.getNode(trie_.getNode(u).link).to[d];
      }
      q.push(u);
    }
  }
}
 
vector<pair<int, set<int>>> findStringsOccurances(
    const string& text, int n, const Trie& trie_) {
  vector<pair<int, set<int>>> occur(n, {0, {}});
  int v = 0;
  for (int i = 0; i < text.size(); ++i) {
    v = trie_.getNode(v).to[charToAlphabet(text[i])];
    int linkJump = v;
    while (linkJump != 0) {
      if (trie_.getNode(linkJump).term) {
        for (int j : trie_.getNode(linkJump).endingNumbers) {
          ++occur[j].first;
          occur[j].second.insert(i - trie_.getNode(linkJump).stringSize + 2);
        }
      }
      linkJump = trie_.getNode(linkJump).link;
    }
  }
  return occur;
}
 
int main() {
  Trie trie;
 
  string text;
  cin >> text;
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    string si;
    cin >> si;
    trie.add(si, i);
  }
 
  ahoCorasick(trie);
 
  auto occur = findStringsOccurances(text, n, trie);
 
  for (int i = 0; i < n; ++i) {
    cout << occur[i].first << ' ';
    for (int j : occur[i].second) {
      cout << j << ' ';
    }
    cout << endl;
  }
}