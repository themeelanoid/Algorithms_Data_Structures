/*
УСЛОВИЕ
Даны две последовательности. Найдите длину их наибольшей общей
подпоследовательности (подпоследовательность — это то, что можно получить из
данной последовательности вычеркиванием некоторых элементов).

Входные данные
В первой строке входного файла записано число N — длина первой
последовательности (1⩽N⩽1000). Во второй строке записаны члены первой
последовательности (через пробел) — целые числа, не превосходящие 10000 по
модулю. В третьей строке записано число M — длина второй последовательности
(1⩽M⩽1000). В четвертой строке записаны члены второй последовательности (через
пробел) — целые числа, не превосходящие 10000 по модулю.
*/

#include <iostream>
#include <vector>

using namespace std;

int countCommonSubseqLength(const vector<int>& seq1, const vector<int>& seq2) {
  size_t n = seq1.size();
  size_t m = seq2.size();

  // it's enough to keep only 2 lines instead of full matrix dp NxM, dpCur is
  // current line, dpPrev is one line higher
  vector<int> dpCur(m + 1);
  vector<int> dpPrev(m + 1);

  for (size_t i = 1; i < n + 1; ++i) {
    for (size_t j = 1; j < m + 1; ++j) {
      if (seq1[i - 1] == seq2[j - 1]) {
        dpCur[j] = dpPrev[j - 1] + 1;
      } else {
        dpCur[j] = max(dpPrev[j], dpCur[j - 1]);
      }
    }
    dpPrev = dpCur;
  }
  return dpCur[m];
}

int main() {
  int n;
  cin >> n;
  vector<int> seq1(n);
  for (int i = 0; i < n; ++i) cin >> seq1[i];

  int m;
  cin >> m;
  vector<int> seq2(m);
  for (int i = 0; i < m; ++i) cin >> seq2[i];

  cout << countCommonSubseqLength(seq1, seq2) << endl;
}