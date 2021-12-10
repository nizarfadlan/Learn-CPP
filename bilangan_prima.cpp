// Nama : Nizar Izzuddin Y.F
// NIM  : 211054003
// Soal 1

#include <iostream>

using namespace std;

// FUnction mnentukan apakah prima atau bukan
bool prima(int x){
  if(x==2){
    return true;
  }

  // Membuat perulangan
  for(int i=2;i<x;i++) {
		if(x%i==0) return false;
	}	
	return true;
}

int main() {
  int n, p, s, u=0;
  bool h = false;

  cout << "Mencari bilangan prima" << endl;
  // Input berapa data yang di inginkan
  cout << "Masukkan jumlah prima > "; cin >> n;
  // Mendeklarasikan array sesuai jumlah n
  int a[n-1];
  int i = 2;
  while(i<=n){
    // Jika prima true akan dimasukkan ke array dan n untuk cout jumlah data array
    if(prima(i)){
      a[u] = i;
      u++;
    }
    i++;
  }

  // Input bilangan yg dicari
  cout << "Masukkan bilangan yang dicari > "; cin >> s;

  // Perulangan untuk menampilkan matrik dan untuk mencari bilangan yg dicari
  for(int j=0; j<u; j++){
    cout << a[j];
    if(j<u-1){
      cout << ", ";
    }else{
      cout << "." << endl;
    }
    
    // Untuk mencari bilangan yg dicari
    if(a[j] == s){
      p = j+1;
      h = true;
    }
  }
  
  // hasil
  if(h){
    cout << s << " adalah bilangan prima dengan urutan ke " << p << endl;
  }else{
    cout << s << " bukan bilangan prima" << endl;
  }

}