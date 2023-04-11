/*
УСЛОВИЕ
Постройте суффиксный массив для заданной строки s.
Входные данные
Первая строка входного файла содержит строку s (1≤|s|≤400000). Строка 
состоит из строчных латинских букв.
Выходные данные
Выведите |s| различных чисел — номера первых символов суффиксов строки s
так, чтобы соответствующие суффиксы были упорядочены в лексикографически 
возрастающем порядке.
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class SufArr {
  static const size_t ALPHABETSIZE = 27;
  static const char LEXICALMINIMUM = '`';

 public:
  SufArr(const string& s);
  void print();

 private:
  size_t n;
  vector<int> array_;
  void sortFirstLayer(const string& s, int& classes,
                      vector<int>& eqClasses, vector<int>& cnt);
  void sortNthLayer(const string& s, int& classes,
                    vector<int>& eqClasses, vector<int>& cnt);
  void constructSortedArray(const string& s);
};

SufArr::SufArr(const string& s) : n(s.size() + 1) {
  string modified = s + LEXICALMINIMUM;
  constructSortedArray(modified);
}

void SufArr::sortFirstLayer(const string& s, int& classes,
                            vector<int>& eqClasses,
                            vector<int>& cnt) {
  for (int i = 0; i < n; ++i) {
    ++cnt[s[i] - LEXICALMINIMUM];
  }
  for (int i = 1; i < ALPHABETSIZE; ++i) {
    cnt[i] += cnt[i - 1];
  }
  for (int i = n - 1; i >= 0; --i) {
    array_[--cnt[s[i] - LEXICALMINIMUM]] = i;
  }
  eqClasses[array_[0]] = 0;
  for (int i = 1; i < n; ++i) {
    if (s[array_[i]] - s[array_[i - 1]] == 0) {
      eqClasses[array_[i]] = classes - 1;
    } else {
      ++classes;
      eqClasses[array_[i]] = classes - 1;
    }
  }
}

void SufArr::sortNthLayer(const string& s, int& classes,
                          vector<int>& eqClasses, vector<int>& cnt) {
  vector<int> layerN(n);
  vector<int> eqClassesN(n);

  for (int h = 0; (1 << h) < n; ++h) {
    for (int i = 0; i < n; ++i) {
      if (array_[i] - (1 << h) < 0) {
        layerN[i] = n + array_[i] - (1 << h);
      } else {
        layerN[i] = array_[i] - (1 << h);
      }
    }
    cnt.assign(classes, 0);
    for (int i = 0; i < n; ++i) {
      ++cnt[eqClasses[layerN[i]]];
    }
    for (int i = 1; i < classes; ++i) {
      cnt[i] += cnt[i - 1];
    }
    for (int i = n - 1; i >= 0; --i) {
      array_[--cnt[eqClasses[layerN[i]]]] = layerN[i];
    }
    eqClassesN[array_[0]] = 0;
    classes = 1;
    for (int i = 1; i < n; ++i) {
      if (eqClasses[array_[i]] != eqClasses[array_[i - 1]] ||
          eqClasses[(array_[i] + (1 << h)) % n] !=
              eqClasses[(array_[i - 1] + (1 << h)) % n]) {
        ++classes;
      }
      eqClassesN[array_[i]] = classes - 1;
    }
    eqClasses = eqClassesN;
  }
}

void SufArr::constructSortedArray(const string& s) {
  int classes = 1;
  array_.resize(n);
  vector<int> eqClasses(n);
  vector<int> cnt(ALPHABETSIZE);

  sortFirstLayer(s, classes, eqClasses, cnt);

  vector<int> layerN(n);
  vector<int> eqClassesN(n);

  sortNthLayer(s, classes, eqClasses, cnt);
}

void SufArr::print() {
  for (int i = 1; i < array_.size(); ++i) {
    cout << array_[i] + 1 << ' ';
  }
  cout << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  string s;
  cin >> s;

  SufArr sa(s);
  sa.print();
}