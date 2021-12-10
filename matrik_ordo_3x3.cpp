// Nama : Nizar Izzuddin Y.F
// NIM  : 211054003
// Soal 2

#include <iostream>

using namespace std;

// deklarasi array
int* m1 = new int[3*3];
int* m2 = new int[3*1];

int main() {
  cout << "Perhitungan perkalian matrik ordo 3x3 dengan ordo 3x1" << endl;
  cout << "Masukkan data matrik ordo 3x3" << endl;

  // Input array ke dalam variable array untuk matrik ordo 3x3
  for(int i=1; i<=3; i++){
    for(int j=1; j<=3; j++){
      cout << "Masukkan angka matrik ke [" << i << "," << j << "] = ";
      cin >> m1[j+i * 3];
    }
  }

  // Input array ke dalam variable array untuk matrik ordo 3x1
  cout << endl << "Masukkan data matrik ordo 3x1" << endl;

  for(int i=1; i<=3; i++){
    cout << "Masukkan angka matrik ke [" << i << ",1] = ";
    cin >> m2[1+i * 1];
  }

  // Perulangan untuk menampilkan matrik
  cout << endl << "Perkalian :" << endl;
  for(int i=1; i<=3; i++){
    for(int j=1; j<=3; j++){
      cout << m1[j+i * 3];
      if(j==3){
        if(i==2 && j==3){
          cout << "  x  ";
        }else{
          cout << "     ";
        }
        cout << m2[1+i * 1];
      }else{
        cout << " ";
      }
    }
    cout << endl;
  }

  // Hasil perkalian dan untuk menampilkan, hanya sebatas untuk menampilkan tidak menampung perkalian
  cout << endl << "Hasil perkalian matrik : " << endl;
  for(int i=1; i<=3; i++){
    for(int j=1; j<=3; j++){
      cout << m1[j+i * 3] * m2[1+j * 1] << "\t";
    }
    cout << endl;
  }

  cout << endl << "Hasil akhir :" << endl;
  int jumlah = 0;

  // Perulangan untuk menampilkan hasil akhir
  for(int i=1; i<=3; i++){
    for(int j=1; j<=3; j++){
      // Menambah jumlah setiap 1 row dan kolom dengan mengalikan dan menambah
      jumlah += m1[j+i * 3] * m2[1+j * 1];
      if(j==3){
        cout << jumlah;
      }
    }
    // mereset jumlah ke 0 untuk row baru
    jumlah = 0;
    cout << endl;
  }
}