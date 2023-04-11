/*
Компания BrokenTiles планирует заняться выкладыванием во дворах у состоятельных
клиентов узор из черных и белых плиток, каждая из которых имеет размер 1×1 метр.
Известно, что дворы всех состоятельных людей имеют наиболее модную на сегодня
форму прямоугольника M×N метров.
Однако при составлении финансового плана у директора этой организации появилось
целых две серьезных проблемы: во первых, каждый новый клиент очевидно захочет,
чтобы узор, выложенный у него во дворе, отличался от узоров всех остальных
клиентов этой фирмы, а во вторых, этот узор должен быть симпатичным.
Как показало исследование, узор является симпатичным, если в нем нигде не
встречается квадрата 2×2 метра, полностью покрытого плитками одного цвета. Для
составления финансового плана директору необходимо узнать, сколько клиентов он
сможет обслужить, прежде чем симпатичные узоры данного размера закончатся.
Помогите ему!
Входные данные
На первой строке входного файла находятся два
положительных целых числа, разделенные пробелом — M и N (1⩽M×N⩽30).
Выходные данные
Выведите в выходной файл единственное число — количество различных
симпатичных узоров, которые можно выложить во дворе размера M×N. Узоры,
получающиеся друг из друга сдвигом, поворотом или отражением считаются
различными.
*/

#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> multiplyMatrix(const vector<vector<int>>& a,
                                   const vector<vector<int>>& b) {
  vector<vector<int>> multiplied(a.size(), vector<int>(a.size()));
  for (size_t i = 0; i < a.size(); ++i) {
    for (size_t j = 0; j < b[0].size(); ++j) {
      for (size_t k = 0; k < b.size(); ++k) {
        multiplied[i][j] += a[i][k] * b[k][j];
      }
    }
  }
  return multiplied;
}

vector<vector<int>> createUnitMatrix(size_t n) {
  vector<vector<int>> unitMatrix(n, vector<int>(n));
  for (size_t i = 0; i < n; ++i) {
    unitMatrix[i][i] = 1;
  }
  return unitMatrix;
}

vector<vector<int>> raiseMatrixToPower(const vector<vector<int>>& a, int n) {
  vector<vector<int>> powered = createUnitMatrix(a.size());
  if (n == 0) {
    return powered;
  }
  if (n % 2 == 1) {
    powered = raiseMatrixToPower(a, n - 1);
    return multiplyMatrix(a, powered);
  }
  powered = raiseMatrixToPower(a, n / 2);
  return multiplyMatrix(powered, powered);
}

bool isNicePattern(int mask1, int mask2, int m) {
  for (size_t i = 0; i < m - 1; ++i) {
    if (((mask1 >> i) & 1) == ((mask2 >> i) & 1) &&
        ((mask2 >> i) & 1) == ((mask2 >> (i + 1)) & 1) &&
        ((mask1 >> (i + 1)) & 1) == ((mask2 >> (i + 1)) & 1)) {
      return false;
    }
  }
  return true;
}

// динамика пересчитывается по столбцам - при очередном умножении матриц я
// считаю число симпатичных узоров на прямоугольнике Nxi
int countNicePatterns(int n, int m) {
  vector<vector<int>> patternsOnFirstTiles(1 << m, vector<int>(1 << m));
  for (size_t i = 0; i < (1 << m); ++i) {
    for (size_t j = 0; j < (1 << m); ++j) {
      if (isNicePattern(i, j, m)) {
        patternsOnFirstTiles[i][j] = 1;
      }
    }
  }
  vector<vector<int>> patternsOnAllTiles =
      raiseMatrixToPower(patternsOnFirstTiles, n - 1);
  int numberOfNicePatterns = 0;
  for (size_t i = 0; i < (1 << m); ++i) {
    for (size_t j = 0; j < (1 << m); ++j) {
      numberOfNicePatterns += patternsOnAllTiles[i][j];
    }
  }
  return numberOfNicePatterns;
}

int main() {
  int n;
  int m;
  cin >> n >> m;
  if (m > n) {
    swap(m, n);
  }

  cout << countNicePatterns(n, m) << endl;
}