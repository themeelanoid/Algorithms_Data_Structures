/*
Даны два многочлена
A(x)=anx^n+an−1x^n−1+⋯+a0
B(x)=bmx^m+bm−1x^m−1+⋯+b0
Вычислите C(x)=A(x)⋅B(x)
Входные данные
n,an,an−1,…,a0
m,bm,bm−1,…,b0
0≤n,m<216, |ai|,|bj|≤9, an≠0,bm≠0
Выходные данные
Выведите коэффициенты C в том же формате
*/

#include <complex>
#include <iostream>
#include <vector>

using namespace std;

const double kPi = 3.14159265358979323846;

template <typename Type>
class Polynom;

template <typename Type>
ostream& operator<<(ostream&, const Polynom<Type>&);

template <typename Type>
class Polynom {
  friend ostream& operator<< <>(ostream& os, const Polynom& a);
  friend class Polynom<complex<double>>;

 public:
  Polynom(const vector<Type>& coeff);
  Polynom& operator*=(const Polynom& other);
  int get_deg() { return deg_; }

 private:
  int deg_;
  vector<Type> coeff_;
};

template <>
class Polynom<complex<double>> {
 public:
  template <typename Type>
  Polynom(const Polynom<Type>& other)
      : deg_(other.deg_), coeff_(other.coeff_.begin(), other.coeff_.end()) {}
  int get_deg() { return deg_; }
  Polynom& operator*=(const Polynom& other);
  template <typename Type>
  vector<Type> get_type_coeff();

 private:
  int deg_;
  vector<complex<double>> coeff_;
  int FindLog(int x);
  int FindReversed(int x, int log);
  int FindDeg2(int x);
  void AddPowerOf2Coeff(int number);  
  template <bool is_inverse>
  void FastFourierTransform();

};

template <typename Type>
Polynom<Type>::Polynom(const vector<Type>& coeff)
    : coeff_(coeff), deg_(coeff.size() - 1) {}

int Polynom<complex<double>>::FindLog(int x) {
  int log = 0;
  while ((1 << log) < x) {
    ++log;
  }
  return log;
}

int Polynom<complex<double>>::FindReversed(int x, int log) {
  int reversed = 0;
  for (int j = 0; j < log; ++j) {
    if (x & (1 << j)) {
      reversed |= 1 << (log - 1 - j);
    }
  }
  return reversed;
}

int Polynom<complex<double>>::FindDeg2(int x) {
  int deg2 = 1;
  while (deg2 < x) {
    deg2 <<= 1;
  }
  return deg2 << 1;
}

void Polynom<complex<double>>::AddPowerOf2Coeff(int number) {
  coeff_.resize(number);
}

template <bool is_inverse>
void Polynom<complex<double>>::FastFourierTransform() {
  int log = FindLog(coeff_.size());
  for (int i = 0; i < coeff_.size(); ++i) {
    int reversed = FindReversed(i, log);
    if (i < reversed) {
      swap(coeff_[i], coeff_[reversed]);
    }
  }
  for (int len = 2; len <= coeff_.size(); len <<= 1) {
    double angle = 2 * kPi / len;
    if (is_inverse) {
      angle *= -1;
    }
    complex<double> wlen(cos(angle), sin(angle));
    for (int i = 0; i < coeff_.size(); i += len) {
      complex<double> w(1);
      for (int j = 0; j < len / 2; ++j) {
        complex<double> u = coeff_[i + j];
        complex<double> v = coeff_[i + j + len / 2] * w;
        coeff_[i + j] = u + v;
        coeff_[i + j + len / 2] = u - v;
        w *= wlen;
      }
    }
  }
  if (is_inverse) {
    for (auto& i : coeff_) {
      i /= coeff_.size();
    }
  }
}

template <typename Type>
Polynom<Type>& Polynom<Type>::operator*=(const Polynom<Type>& other) {
  Polynom<complex<double>> fa(*this);
  Polynom<complex<double>> fb(other);
  fa *= fb;
  *this = Polynom<Type>(fa.get_type_coeff<int>());
  return *this;
}

Polynom<complex<double>>& Polynom<complex<double>>::operator*=(
    const Polynom<complex<double>>& other) {
  deg_ += other.deg_;
  int deg2 = FindDeg2(max(coeff_.size(), other.coeff_.size()));
  auto copy = other;
  this->AddPowerOf2Coeff(deg2);
  copy.AddPowerOf2Coeff(deg2);
  this->FastFourierTransform<false>();
  copy.FastFourierTransform<false>();
  for (int i = 0; i < deg2; ++i) {
    this->coeff_[i] *= copy.coeff_[i];
  }
  this->FastFourierTransform<true>();
  return *this;
}

template <typename Type>
vector<Type> Polynom<complex<double>>::get_type_coeff() {
  vector<Type> coeff(deg_ + 1);
  for (int i = 0; i < deg_ + 1; ++i) {
    coeff[i] = round(coeff_[i].real());
  }
  return coeff;
}

template <typename Type>
Polynom<Type> operator*(const Polynom<Type>& a, const Polynom<Type>& b) {
  Polynom<Type> copy = a;
  copy *= b;
  return copy;
}

template <typename Type>
ostream& operator<<(ostream& os, const Polynom<Type>& a) {
  for (int i = 0; i <= a.deg_; ++i) {
    os << a.coeff_[i] << ' ';
  }
  return os;
}

int main() {
  int n;
  cin >> n;
  vector<int> a(n + 1);
  for (int i = 0; i < n + 1; ++i) {
    cin >> a[i];
  }
  Polynom<int> first(a);
  int m;
  cin >> m;
  vector<int> b(m + 1);
  for (int j = 0; j < m + 1; ++j) {
    cin >> b[j];
  }
  Polynom<int> second(b);

  auto result = first * second;
  cout << result.get_deg() << ' ' << result << endl;
}