#include <iostream>

using namespace std;

void passByValue(int x, int y) {
  cout << "Hasil perkalian dari " << x << "x" << y << " = " << x*y << endl;
}

void passByPreference(int &x, int &y) {
  int i = x;
  x = y;
  y = i;
}

int main() {
  int x = 21;
  int y = 20;

  passByValue(x,y);

  cout << "Sebelum Swap Preference: " << endl;
  cout << x << y << endl;

  passByPreference(x,y);

  cout << "Sesudah Swap Preference: " << endl;
  cout << x << y << endl;
}