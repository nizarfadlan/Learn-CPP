#include <iostream>
using namespace std;

float c, k, f, r;

int main() {
	cout << "---------------------------------------" << endl;
	cout << "              Convert Suhu             " << endl;
	cout << "---------------------------------------" << endl << endl;
	
	cout << "Masukkan suhu (dalam bentuk Celcius) > "; cin >> c;
	
	k = c+273;
	f = 1.8*c+32;
	r = 0.8*c;
	
	cout << "\nHasil dari konversi suhu" << endl;
	cout << "Kelvin      :" << k << endl;
	cout << "Fahrenheit  :" << f << endl;
	cout << "Reamur      :" << r << endl;
	
	return 0;
}
