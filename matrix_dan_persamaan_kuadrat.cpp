#include <iostream>
#include <math.h>

using namespace std;

typedef int Matrix[10][10];
Matrix A,B,C;
int pil, bara, kola, barb, kolb, i, j, a, b, c, hasil;
float x1, x2;

void isi_matrix(Matrix &X, int m, int n) {
  for(i=1;i<=m;i++) {
    for(j=1;j<=n;j++) {
      cout << "Isi elemen matrix ke [" << i << "," << j << "] = "; cin >> X[i][j];
    }
  }
  cout << "Pengisian berhasil" << endl;
}

void cetak_matrix(Matrix X, int m, int n) {
  for(i=1;i<=m;i++) {
    for(j=1;j<=n;j++) {
      cout << X[i][j] << " ";
    }
    cout << endl;
  }
}

void tambah_matrix(Matrix &A, Matrix &B, int m, int n) {
  for(i=1; i<=m;i++) {
    for(j=1; j<=n;j++){
      C[i][j] = A[i][j]+B[i][j];
    }
  }
}

int akar_persamaan_kuadrat(int a, int b, int c) {
  return (b*b)-(4*a*c);
}

int main() {
  do{
    system("cls");
    cout << "Operasi Matrix" << endl;
    cout << "1. Isi Matrix A" << endl;
    cout << "2. Isi Matrix B" << endl;
    cout << "3. A+B" << endl;
    cout << "4. Akar persamaan kuadrat" << endl;
    cout << "0. Keluar" << endl;
    cout << "Pilih menu 0-4 > "; cin >> pil;
    switch(pil){
      case 1:
        cout << "Baris A = "; cin >> bara;
        cout << "Kolom A = "; cin >> kola;
        isi_matrix(A, bara, kola);
        cetak_matrix(A, bara, kola);
        break;
      case 2:
        cout << "Baris B = "; cin >> barb;
        cout << "Kolom B = "; cin >> kolb;
        isi_matrix(B, barb, kolb);
        cetak_matrix(B, barb, kolb);
        break;
      case 3:
        if((bara==barb) && (kola == kolb)){
          cout << "Hasil A+B adalah = " << endl;
          tambah_matrix(A, B, bara, kola);
          cetak_matrix(C, bara, kola);
        }else {
          cout << "Orde tidak sama, operasi tidak diijinkan" << endl;
        }
        break;
      case 4:
        cout << "Format persamaan: ax^2 + bx + c = 0 " << endl;
        cout << "Nilai a = "; cin >> a;
        cout << "Nilai b = "; cin >> b;
        cout << "Nilai c = "; cin >> c;
        hasil = akar_persamaan_kuadrat(a, b, c);
        cout << "Diskriminan = " << hasil;
        if(hasil > 0){
          cout << " akar real dan berbeda" <<endl;
          x1 = (-b + sqrt(hasil)) / (2*a);
          x2 = (-b - sqrt(hasil)) / (2*a);

          cout << "x1 = " << x1 <<endl;
          cout << "x2 = " << x2 <<endl;
        }else if(hasil == 0){
          cout << " akar real dan sama" <<endl;
          x1 = x2 = (-b + sqrt(hasil)) / (2*a);

          cout << "x1 = " << x1 <<endl;
          cout << "x2 = " << x2 <<endl;
        }else{
          cout << " akar tidak real / imajiner" <<endl;
        }
        break;
      case 0:
        cout << "Terima kasih" << endl;
      default:
        cout << "Ada salah pilih menu" << endl;
    }
    system("pause");
  } while(pil!=0);
}
