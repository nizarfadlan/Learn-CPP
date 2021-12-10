#include <iostream>
using namespace std;

string nama, st1, st2, st3;
int td, kgd;
char lanjut;

int main(){
	ulang:
		cout << "-----------------------------------" << endl;
		cout << "Program mendeteksi status kesehatan" << endl;
		cout << "-----------------------------------" << endl;
		cout << endl;
		cout << "Masukkan nama > "; cin >> nama;
		
		ulang1:
			cout << "Masukkan tekanan darah > "; cin >> td;
			if(td<60 || td>600) {
				cout << "Inputan tekanan darah tidak valid" << endl;
				cout << endl;
				goto ulang1;
			}
			
		ulang2:
			cout << "Masukkan kadar gula darah > "; cin >> kgd;
			if(kgd<60 || kgd>600) {
				cout << "Inputan kadar gula darah tidak valid" << endl;
				cout << endl;
				goto ulang2;
			}
		
		if(td>300) {
			st1 = "hipertensi akut";
		}else if(td>=150 && td<=300) {
			st1 = "hipertensi ringan";
		}else if(td>=100 && td<150) {
			st1 = "normal";
		}else{
			st1 = "hipotensi";
		}
		
		st2 = ((kgd>300) ? "diabet" : ((kgd>=120 && kgd<=300) ? "waspada diabet" : "normal"));
		st3 = ((st1=="normal" && st2=="normal") ? "sehat" : "kurang sehat");
		
		cout << endl;
		cout << "Saudara " << nama << " keadaan anda sekarang sedang " << st3 << ",\ntekanan darah anda dinyatakan " << st1 << " dan kadar gula darah anda dinyatakan " << st2 << endl;
		
	cout << endl;
	cout << "Apakah mau dilanjut (y/t) ? "; cin >> lanjut;
	cout << endl;
	if(tolower(lanjut)=='y'){goto ulang;}
}
