/*
УСЛОВИЕ
Вам требуется написать программу, которая по заданной последовательности находит
максимальную невозрастающую её подпоследовательность Входные данные В первой
строке задано число n — количество элементов последовательности (1≤n≤239017). В
последующих строках идут сами числа последовательности ai, отделенные друг от
друга произвольным количеством пробелов и переводов строки (все числа не
превосходят по модулю 2^31−2). Выходные данные Вам необходимо выдать в первой
строке выходного файла число k — длину максимальной невозрастающей
подпоследовательности. В последующих строках должны быть выведены (по одному
числу в каждой строке) все номера элементов исходной последовательности ij,
образующих искомую подпоследовательность. Номера выводятся в порядке
возрастания. Если оптимальных решений несколько, разрешается выводить любое.
*/

#include <iostream>
#include <limits>
#include <vector>

using namespace std;

size_t binSearch(const vector<int>& array, int x) {
  size_t l = 0;
  size_t r = array.size() - 1;
  while (r - l > 1) {
    size_t m = (r + l) / 2;
    if (array[m] < x)
      r = m;
    else
      l = m;
  }
  return r;
}

vector<int> calculateLongestNotRisingSubseq(const vector<int>& arr) {
  size_t n = arr.size();

  // dp[i] is the number which is the end of not rising subsequence with length.
  // dp[i] is the smallest possible
  vector<int> dp(n + 1, numeric_limits<int>::min());
  dp[0] = numeric_limits<int>::max();
  // pos[i] is the index of the element which is the end of optimal subsequence
  // with length i
  vector<int> pos(n + 1);
  pos[0] = -1;
  // prev[i] is the position of the previous element for a[i]
  vector<int> prev(n, -1);
  size_t length = 0;

  for (int i = 0; i < n; ++i) {
    size_t j = binSearch(dp, arr[i]);
    if (dp[j - 1] >= arr[i] && arr[i] >= dp[j]) {
      dp[j] = arr[i];
      pos[j] = i;
      prev[i] = pos[j - 1];
      length = max(length, j);
    }
  }

  vector<int> subseq;
  int p = pos[length];
  while (p != -1) {
    subseq.push_back(p + 1);
    p = prev[p];
  }
  for (int i = 0; i < subseq.size() / 2; ++i) {
    swap(subseq[i], subseq[subseq.size() - i - 1]);
  }
  return subseq;
}

int main() {
  int n;
  cin >> n;
  vector<int> arr(n);
  for (int i = 0; i < n; ++i) {
    cin >> arr[i];
  }

  vector<int> subsequence = calculateLongestNotRisingSubseq(arr);
  cout << subsequence.size() << endl;
  for (int i : subsequence) {
    cout << i << ' ';
  }
  cout << endl;
}