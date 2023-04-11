/*
УСЛОВИЕ
У нас есть несколько предметов и рюкзак, который выдерживает вес C.
Предмет с номером i имеет вес xi. Определите число различных наборов предметов,
которые можно унести в рюкзаке. Два набора считаются различными, если
существует хотя бы один предмет, который включён в один из
наборов и не включён в другой.
Входные данные
В первой строке ввода записано целое число n — количество предметов (1≤n≤30).
Во второй строке записано n целых чисел xi (1≤xi≤10^9).
В третьей строке записано целое число C — вместимость рюкзака (0≤C≤10^9).
Выходные данные
Выведите единственное целое число — искомое число способов.
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
  long long n;
  cin >> n;

  long long k = n % 2 == 0 ? n / 2 : n / 2 + 1;

  vector<long long> arr(n);
  for (long long i = 0; i < n; ++i) cin >> arr[i];

  long long sum = 0;
  for (long long i = 0; i < n; ++i) sum += arr[i];

  long long c;
  cin >> c;

  if (sum < c + 1) {
    cout << (1 << n);
    return 0;
  }

  long long pow1 = 1 << (n / 2);
  long long pow2 = 1 << k;

  vector<long long> dp1(pow1);
  vector<long long> dp2(pow2);

  long long q = -1;
  long long ans = 0;
  for (long long i = 1; i < pow1; ++i) {
    if ((i & (i - 1)) == 0) ++q;
    dp1[i] = dp1[((1 << q) - 1) & i] + arr[q];
    if (dp1[i] < c + 1) ++ans;
  }

  q = -1;
  for (long long i = 1; i < pow2; ++i) {
    if ((i & (i - 1)) == 0) ++q;
    dp2[i] = dp2[((1 << q) - 1) & i] + arr[q + n / 2];
    if (dp2[i] < c + 1) ++ans;
  }

  for (long long i = 1; i < pow1; ++i) {
    for (long long j = 1; j < pow2; ++j) {
      if (dp1[i] + dp2[j] < c + 1) ++ans;
    }
  }

  cout << ans + 1;
}