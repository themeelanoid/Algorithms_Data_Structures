/*
Найти все вхождения строки T в строку S.
Входные данные
Первые две строки входных данных содержат строки S и T, соответственно. 
Длины строк больше 0 и меньше 50000, строки содержат только строчные 
латинские буквы.
Выходные данные
Выведите номера символов, начиная с которых строка T входит в строку S, в 
порядке возрастания.
*/

#include <iostream>
#include <string>
#include <vector>
 
using namespace std;
 
int main() {
  string s;
  string t;
  cin >> s >> t;
  
  string pr = t + 'A' + s;
  vector<int> prefFunc(pr.size());
  for (int i = 1; i < pr.size(); ++i) {
    int j = prefFunc[i - 1];
    while (j >= 1 && pr[i] != pr[j]) {
      j = prefFunc[j - 1];
    }
    if (pr[i] == pr[j]) ++j;
    prefFunc[i] = j;
    if (j == t.size()) cout << i - 2 * t.size() << ' ';
  }
  cout << endl;
}