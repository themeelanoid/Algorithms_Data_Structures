/*
До конца света осталось не так много дней, но Третий всадник Апокалипсиса Голод
так и не смог понять, какие города стоит наказывать за прегрешения, а какие нет.
Тогда он решил потренироваться на одной небольшой стране. Эта страна
представляет собой клетчатый прямоугольник размера n×m, в котором каждая клетка
— отдельный город. Голод может либо наслать голод на город, либо пощадить его.
При этоместь города, в которых еды хватит и до следующего конца света, и Голод
не в силах заставить их голодать, а есть те, в которых еды никогда и не было, и
им в любом случае придется голодать. Страшный Суд Голода должен быть ещё и
справедлив, а это значит, что в любом квадрате размера 2×2 должно быть поровну
голодающих и сытых городов. Теперь Голод хочет узнать количество различных
вариантов распределения городов этой страны на голодающие и сытые.
Входные данные
В первой строке входного файла задано два целых числа n и m (1≤n≤15 и
1≤m≤100) — размер страны. Далее следует n строк по m символов в каждой, где
символ '+' означает, что соответствующий город не может голодать, символ '—' —
соответствующий город будет голодать в любом случае и символ '.' — Голод может
решить, что ему делать с этим городом.
Выходные данные
Выведите количество различных вариантов наслать голод на эту страну по модулю
10^9+7
*/

#include <bits/stdc++.h>

using namespace std;
const size_t mod = 1e9 + 7;

size_t bit(size_t mask, size_t i) { return (mask >> i) & 1; }

bool maskSuits(size_t index, size_t mask, const vector<size_t>& fed,
               const vector<size_t>& hungry) {
  if ((mask + fed[index] == (mask ^ fed[index])) &&
      (mask - hungry[index] == (mask ^ hungry[index]))) {
    return true;
  }
  return false;
}

bool sameMaskSuits(size_t mask, size_t n) {
  bool fits = true;
  for (size_t i = 0; i < n - 1; ++i) {
    if (bit(mask, i) == bit(mask, i + 1)) {
      fits = false;
      break;
    }
  }
  return fits;
}

size_t calculateReversedMask(size_t mask, size_t n) {
  size_t reversedMask = 0;
  for (size_t i = 0; i < n; ++i) {
    if ((mask >> i) % 2 == 0) {
      reversedMask += (1 << i);
    }
  }
  return reversedMask;
}

// для фиксированной предыдущей маски всегда подходит обратная маска,
// но может подходить и такая же маска, если в ней нет двух идущих подряд + или
// -
vector<set<size_t>> countAppropriateMasks(size_t n) {
  vector<set<size_t>> appropriateMasks(1 << n);
  for (size_t mask = 0; mask < 1 << n; ++mask) {
    size_t reversedMask = calculateReversedMask(mask, n);
    appropriateMasks[mask].insert(reversedMask);
    if (sameMaskSuits(mask, n)) {
      appropriateMasks[mask].insert(mask);
    }
  }
  return appropriateMasks;
}

// насчет массива масок с 1 на местах 100% сытых городов
vector<size_t> countFed(const vector<vector<char>>& citiesMap) {
  vector<size_t> fed(citiesMap[0].size());
  size_t makeMaskFed;
  for (int i = 0; i < citiesMap[0].size(); ++i) {
    makeMaskFed = 0;
    for (int j = 0; j < citiesMap.size(); ++j) {
      if (citiesMap[j][i] == '+') {
        makeMaskFed += (1 << j);
      }
    }
    fed[i] = makeMaskFed;
  }
  return fed;
}

// насчет массива масок с 1 на местах 100% голодающих городов
vector<size_t> countHungry(const vector<vector<char>>& citiesMap) {
  vector<size_t> hungry(citiesMap[0].size());
  size_t makeMaskHungry;
  for (int i = 0; i < citiesMap[0].size(); ++i) {
    makeMaskHungry = 0;
    for (int j = 0; j < citiesMap.size(); ++j) {
      if (citiesMap[j][i] == '-') {
        makeMaskHungry += (1 << j);
      }
    }
    hungry[i] = makeMaskHungry;
  }
  return hungry;
}

// изначально мне казалось, что рекурсивная реализация выглядит изящней((
vector<size_t> countJudgementVariantsByMask(
    size_t m, size_t n, vector<size_t>& judgementVariantsForMask,
    vector<size_t>& totalJudgementVariants,
    const vector<set<size_t>>& appropriateMasks, const vector<size_t>& fed,
    const vector<size_t>& hungry) {
  if (m == 1) {
    for (size_t i = 0; i < 1 << n; ++i) {
      totalJudgementVariants[i] = maskSuits(0, i, fed, hungry) ? 1 : 0;
    }
    return totalJudgementVariants;
  }

  judgementVariantsForMask = countJudgementVariantsByMask(
      m - 1, n, judgementVariantsForMask, totalJudgementVariants,
      appropriateMasks, fed, hungry);
  for (size_t i = 0; i < 1 << n; ++i) {
    totalJudgementVariants[i] = 0;
  }
  for (size_t maskLeft = 0; maskLeft < 1 << n; ++maskLeft) {
    if (maskSuits(m - 2, maskLeft, fed, hungry)) {
      for (auto rightMask : appropriateMasks[maskLeft]) {
        if (maskSuits(m - 1, rightMask, fed, hungry)) {
          totalJudgementVariants[rightMask] +=
              judgementVariantsForMask[maskLeft];
          totalJudgementVariants[rightMask] %= mod;
        }
      }
    }
  }
  return totalJudgementVariants;
}

size_t countJudgementVariants(const vector<vector<char>>& citiesMap) {
  size_t n = citiesMap.size();
  size_t m = citiesMap[0].size();

  vector<size_t> fed = countFed(citiesMap);  // маски с 1 на местах городов,
                                             // которые 100% не будут голодать
  vector<size_t> hungry = countHungry(
      citiesMap);  // маски с 1 на местах городов, которые 100% будут голодать
  vector<set<size_t>> appropriateMasks = countAppropriateMasks(
      n);  // для каждого столбца содержит подходящие маски
  // при которых в каждом квадрате 2x2 будет поровну голодающих и сытых городов
  vector<size_t> judgementVariantsForMask(1 << n, 0);
  vector<size_t> totalJudgementVariants(
      1 << n, 0);  // массивы для рекурсивного подсчета вариантов "наказания"
  totalJudgementVariants = countJudgementVariantsByMask(
      m, n, judgementVariantsForMask, totalJudgementVariants, appropriateMasks,
      fed, hungry);

  size_t numberOfJudgementVariants = 0;
  for (size_t i : totalJudgementVariants) {
    numberOfJudgementVariants += i;
    numberOfJudgementVariants %= mod;
  }
  return numberOfJudgementVariants;
}

int main() {
  size_t n;
  size_t m;
  cin >> n >> m;
  vector<vector<char>> citiesMap(n, vector<char>(m, '.'));
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      cin >> citiesMap[i][j];
    }
  }
  cout << countJudgementVariants(citiesMap) << endl;
}