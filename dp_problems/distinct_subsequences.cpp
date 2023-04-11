/*
Дана последовательность целых чисел длины n. Нужно найти количество
различных непустых подпоследовательностей.
Входные данные
На первой строке n (n≤3⋅10^5). На второй строке n положительных целых чисел,
каждое из которых не превосходит 10^6.
Выходные данные
Количество различных подпоследовательностей по модулю 10^9+7.
*/
#include <iostream>
#include <vector>

const long long mod = 1e9 + 7;

using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  vector<long long> dp(
      1e6 + 2);  // number of distinct subsequences ending on each number in a
  long long totalNumber = 1;
  for (int i : a) {
    long long endingI;
    if (totalNumber - dp[i] >= 0)
      endingI = totalNumber - dp[i];
    else
      endingI = totalNumber + mod - dp[i];
    dp[i] = totalNumber;
    totalNumber += endingI;

    if (totalNumber >= mod) totalNumber -= mod;
  }

  if (totalNumber == 0) totalNumber = mod;
  cout << totalNumber - 1;
}