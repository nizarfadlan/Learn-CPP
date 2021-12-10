#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

// Deklarasi type data record
struct Barang {
  string kode_brg, nama_brg;
  float harga;
  int stok;
};
vector<Barang> arr_barang;
int pil;

// Function dan Procedur
void clear();
void pause();

// Menu
void tambah_barang();
void cetak_barang();
void edit_barang();
void hapus_barang();

int main() {
  do {
    clear();
    cout << "Pengelola Data Barang" << endl;
    cout << "1. Input barang" << endl;
    cout << "2. Cetak barang" << endl;
    cout << "3. Edit data barang" << endl;
    cout << "4. Hapus barang" << endl;
    cout << "0. Keluar" << endl;
    cout << "Pilih menu > "; cin >> pil;

    switch(pil) {
      case 1:
        tambah_barang();
        break;
      case 2:
        cetak_barang();
        break;
      case 3:
        edit_barang();
        break;
      case 4:
        hapus_barang();
        break;
      case 0:
        cout << endl << "Terima kasih telah menggunakan program" << endl;
        break;
      default:
        cout << endl << "Salah pilih menu" << endl;
        break;
    }
    pause();
  } while(pil != 0);
}

// Function dan Procedur
void clear() {
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

void pause() {
  #ifdef _WIN32
    system("pause");
  #else
    system("read -n 1 -p \"Press any key to continue...\"");
  #endif
}

void tambah_barang() {
  char lanjut;
  int i = arr_barang.size();
  string kode;

  cout << endl << "Tambah barang baru" << endl;
  do{
    arr_barang.push_back(Barang());
    ulang:
      cout << endl << "Masukkan kode barang : "; cin >> kode;
      if(i >= 1){
        auto val_kode = find_if(arr_barang.begin(), arr_barang.end(), [kode](Barang const barang) {
          return barang.kode_brg == kode;
        });
        if(val_kode != arr_barang.end()) {
          cout << endl << "Kode barang " << kode << " yang dimasukkan sudah ada" << endl;
          goto ulang;
        }
      }
    arr_barang[i].kode_brg = kode;
    cout << "Masukkan nama barang : "; cin >> arr_barang[i].nama_brg;
    cout << "Masukkan harga barang : "; cin >> arr_barang[i].harga;
    cout << "Masukkan stok barang : "; cin >> arr_barang[i].stok;
    i++;
    cout << endl << "Mau memasukkan data lagi (y/t) ? "; cin >> lanjut;
  } while(tolower(lanjut) == 'y');
}

void cetak_barang() {
  int n = arr_barang.size();
  if(n > 0){
    cout << endl << "Daftar barang di Gudang saat ini" << endl;
    cout << "|==============================================|" << endl;
    cout << " No" << setw(10) << "Kode" << setw(15) << "Nama" << setw(10) << "Harga" << setw(10) << "Stok " << endl;
    for(int i=0; i<n; i++) {
      cout << " " << i+1 << setw(10) << arr_barang[i].kode_brg << setw(15) << arr_barang[i].nama_brg << setw(10) << arr_barang[i].harga << setw(10) << arr_barang[i].stok << " " << endl;
    }
    cout << "|==============================================|" << endl << endl;
  }else {
    cout << "Data barang belum ada" << endl;
  }
}

void edit_barang() {
  string pilih;
  int pos=0, stok;
  string nama;
  float harga;
  char lanjut, lanjut2;

  do {
    lanjut2 = 'q';
    int n = arr_barang.size();
    if(n > 0){
      ulang:
        bool ada = false;
        cout << endl << "Edit barang di Gudang" << endl;
        cetak_barang();
        cout << "Pilih kode barang yang diedit > "; cin >> pilih;
        auto check = find_if(arr_barang.begin(), arr_barang.end(), [pilih](Barang const barang) {
          return barang.kode_brg == pilih;
        });
        if(check != arr_barang.end()) {
          ada = true;
          pos = distance(arr_barang.begin(), check);
        }

      if(ada) {
        cout << endl << "Detail barang yang diedit" << endl;
        cout << "Kode barang : " << arr_barang[pos].kode_brg << endl;
        cout << "Nama barang : " << arr_barang[pos].nama_brg << endl;
        cout << "Harga : " << arr_barang[pos].harga << endl;
        cout << "Stok : " << arr_barang[pos].stok << endl;

        cout << "Yakin ingin mengedit barang atau ingin keluar (y/t/q) ? "; cin >> lanjut;
        if(tolower(lanjut) == 'y') {
          cout << "Jika nama barang tidak diganti masukkan \"-\"" << endl;
          cout << "Nama barang : "; cin >> nama;
          if(nama != "-") arr_barang[pos].nama_brg = nama;
          
          cout << endl << "Jika harga barang tidak diganti masukkan \"-0\"" << endl;
          cout << "Harga barang : "; cin >> harga;
          if(harga != -0) arr_barang[pos].harga = harga;
          
          cout << endl << "Jika stok barang tidak diganti masukkan \"-0\"" << endl;
          cout << "Stok barang : "; cin >> stok;
          if(stok != -0) arr_barang[pos].stok = stok;
          
          cout << endl << "Data berhasil disimpan" << endl;
          cout << "Apakah ingin lanjut edit (y/q) ? "; cin >> lanjut2;
          if(tolower(lanjut2) == 'q') lanjut = 'q';
          else clear();
        }else if(tolower(lanjut) == 't') {
          clear();
          goto ulang;
        }else {
          lanjut = 'q';
        }
      }else {
        cout << "Data tidak ditemukan, inputan sensitif" << endl;
        cout << "Apakah ingin lanjut atau ingin keluar (y/q) ? "; cin >> lanjut;
        if(tolower(lanjut) == 'y') {
          clear();
          goto ulang;
        }else {
          lanjut = 'q';
        }
        cout << endl;
      }
    }else {
      cout << "Data barang belum ada" << endl;
      lanjut = 'q';
    }
  } while((tolower(lanjut) != 'q') && (tolower(lanjut2) != 'q'));
}

void hapus_barang() {
  string pilih;
  int pos=0;
  char lanjut, lanjut2;

  do {
    lanjut2 = 'q';
    int n = arr_barang.size();
    if(n > 0){
      ulang:
        bool ada = false;
        cout << endl << "Hapus barang di Gudang" << endl;
        cetak_barang();
        cout << "Pilih kode barang yang dihapus > "; cin >> pilih;
        auto check = find_if(arr_barang.begin(), arr_barang.end(), [pilih](Barang const barang) {
          return barang.kode_brg == pilih;
        });
        if(check != arr_barang.end()) {
          ada = true;
          pos = distance(arr_barang.begin(), check);
        }

      if(ada) {
        cout << endl << "Detail barang yang dihapus" << endl;
        cout << "Kode barang : " << arr_barang[pos].kode_brg << endl;
        cout << "Nama barang : " << arr_barang[pos].nama_brg << endl;
        cout << "Harga : " << arr_barang[pos].harga << endl;
        cout << "Stok : " << arr_barang[pos].stok << endl;
        cout << "Yakin ingin menghapus barang atau ingin keluar (y/t/q) ? "; cin >> lanjut;
        if(tolower(lanjut) == 'y') {
          arr_barang.erase(
            remove_if(arr_barang.begin(), arr_barang.end(), [pilih](Barang const &barang) {
              return barang.kode_brg == pilih;
            }),
          arr_barang.end());
          cout << endl << "Data berhasil dihapus" << endl;
          cout << "Apakah ingin lanjut hapus (y/q) ? "; cin >> lanjut2;
          if(tolower(lanjut2) == 'q') lanjut = 'q';
          else clear();
        }else if(tolower(lanjut) == 't') {
          clear();
          goto ulang;
        }
      }else {
        cout << "Data tidak ditemukan, inputan sensitif" << endl;
        cout << "Apakah ingin lanjut atau ingin keluar (y/q) ? "; cin >> lanjut;
        if(tolower(lanjut) == 'y') {
          clear();
          goto ulang;
        }
        cout << endl;
      }
    }else {
      cout << "Data barang belum ada" << endl;
      lanjut = 'q';
    }
  } while((tolower(lanjut) != 'q') && (tolower(lanjut2) != 'q'));
}
