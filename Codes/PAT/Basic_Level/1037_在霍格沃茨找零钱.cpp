#include <iostream>

using namespace std;

typedef long long llong;

llong toKnut(llong Galleon, llong Sickle, llong Knut);
void printFormat(llong Knut);

int main() {
  llong g1, s1, k1, g2, s2, k2;
  llong k;
  scanf("%lld.%lld.%lld %lld.%lld.%lld", &g1, &s1, &k1, &g2, &s2, &k2);
  k = toKnut(g2, s2, k2) - toKnut(g1, s1, k1);
  printFormat(k);
  return 0;
}


llong toKnut(llong Galleon, llong Sickle, llong Knut) {
  return Galleon * 17 * 29 + Sickle * 29 + Knut;
}

void printFormat(llong Knut) {
  if (Knut < 0) {
    cout << '-';
    Knut = -Knut;
  }
  llong Sickle = Knut / 29;
  llong Galleon = Sickle / 17;
  Knut %= 29;
  Sickle %= 17;
  cout << Galleon << '.' << Sickle << '.' << Knut;
}
