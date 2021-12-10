// Nama : Nizar Izzuddin Y.F
// NIM  : 211054003

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

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

int pil_menu;

void tampil_menu() {
  cout << endl << "|========================|" << endl;
  cout << "       Rental Halal       " << endl;
  cout << "|========================|" << endl;
  cout << "  1. Input Data Mobil" << endl;
  cout << "  2. Lihat Data Mobil" << endl;
  cout << "  3. Layanan" << endl;
  cout << "  4. Cetak Penyewaan" << endl;
  cout << "  0. Keluar" << endl;
}

// Data Mobil
struct Car {
  string plat;
  string nama_mobil;
  long tarif;
  int stok;
};

vector<Car> cars;

// Validasi PLat
bool val_plat(string x) {
  for(int y=0; y<cars.size(); y++){
    if(cars[y].plat == x){
      return true;
    }
  }
  return false;
}

// Menu

void input_mobil() {
  char lanjut;
  string plat_no;
  int i = cars.size();

  do{
    cars.push_back(Car());
    ulang:
      cout << "Masukkan no plat : "; cin >> plat_no;
      if(cars.size() > 1){
        if(val_plat(plat_no)) {
          cout << endl << "Plat nomer " << plat_no << " yang dimasukkan sudah ada" << endl;
          goto ulang;
        }
      }
    cars[i].plat = plat_no;
    cout << "Masukkan nama mobil : "; cin >> cars[i].nama_mobil;
    cout << "Masukkan tarif mobil : "; cin >> cars[i].tarif;
    cout << "Masukkan stok mobil : "; cin >> cars[i].stok;
    i++;
    cout << endl << "Mau memasukkan data lagi (y/t) ? "; cin >> lanjut;
  } while(tolower(lanjut) == 'y');
}

void cetak_mobil() {
  cout << "|==============================================|" << endl;
  cout << " No" << setw(10) << "No PLat" << setw(15) << "Nama Mobil" << setw(10) << "Tarif" << setw(10) << "Stok " << endl;
  for(int i=0; i<cars.size(); i++) {
    cout << " " << i << setw(10) << cars[i].plat << setw(15) << cars[i].nama_mobil << setw(10) << cars[i].tarif << setw(10) << cars[i].stok << " " << endl;
  }
  cout << "|==============================================|" << endl << endl;
}

// Data Penyewa
struct Rental {
  string nama_penyewa;
  string mobil_sewa;
  int jumlah_mobil;
  int lama_sewa;
  long tarif_perjam;
  long total_perhari;
  long total_harga;
};

vector<Rental> rentals;

// Hitung harga
long hitung_total_harga(int x, int y, long z) {
  int jumlah_jam_total = ((y*24)/12);
  return x*jumlah_jam_total*z;
}

long hitung_total_perhari(int x, int y, long z) {
  int jumlah_jam_perhari = ((y*24)/24);
  return x*jumlah_jam_perhari*z;
}

// Validasi Mobil
bool val_mobil(string x) {
  for(int y=0; y<cars.size(); y++) {
    if(cars[y].nama_mobil == x) {
      return false;
    }
  }
  return true;
}

void rental_mobil() {
  if(cars.size() > 0){
    string nama_mobil_input, nama;
    long harga;
    int mobil_stok, sisa_stok, hari_sewa, posisi_data, hitung_stok, i=rentals.size();
    char lanjut;

    do{
      cetak_mobil();

      cout << "Rental Mobil" << endl;
      rentals.push_back(Rental());
      cout << "Masukkan nama penyewa: "; cin >> rentals[i].nama_penyewa;
      ulang1:
        cout << "Masukkan nama mobil: "; cin >> nama_mobil_input;
        if(val_mobil(nama_mobil_input)) {
          cout << endl << "Mobil " << nama_mobil_input << " tidak ada dalam list rental mobil" << endl;
          cout << "Penulisan sesitif pastikan sama dengan yang ada dilist" << endl;
          goto ulang1;
        }

      for(int z=0; z<cars.size(); z++) {
        if(cars[z].nama_mobil == nama_mobil_input){
          nama = cars[z].nama_mobil;
          harga = cars[z].tarif;
          sisa_stok = cars[z].stok;
          posisi_data = z;
        }
      }

      rentals[i].mobil_sewa = nama;
      rentals[i].tarif_perjam = harga;
      ulang2:
        cout << "Masukkan jumlah mobil yang disewa: "; cin >> mobil_stok;
        hitung_stok = sisa_stok - mobil_stok;
        if(hitung_stok < 0) {
          cout << endl << "Mobil " << nama << " stok kurang" << endl;
          goto ulang2;
        }

      cars[posisi_data].stok = hitung_stok;
      rentals[i].jumlah_mobil = mobil_stok;
      cout << "Masukkan lama sewa (hari): "; cin >> hari_sewa;
      rentals[i].lama_sewa = hari_sewa;
      rentals[i].total_perhari = hitung_total_perhari(mobil_stok, hari_sewa, harga);
      rentals[i].total_harga = hitung_total_harga(mobil_stok, hari_sewa, harga);
      i++;
      cout << endl << "Mau menyewa lagi (y/t) ? "; cin >> lanjut;
    } while(tolower(lanjut) == 'y');
  }else {
    cout << endl << "Tidak ada mobil yang tersedia" << endl;
  }
}

void cetak_penyewa() {
  if(rentals.size() > 0){
    for(int i=0; i<rentals.size(); i++) {
      cout << "|==============================================|" << endl << endl;
      cout << "Nama penyewa : " << rentals[i].nama_penyewa << endl;
      cout << "Nama mobil : " << rentals[i].mobil_sewa << endl;
      cout << "Tarif per 12 jam : " << rentals[i].tarif_perjam << endl;
      cout << endl << "Jumlah mobil : " << rentals[i].jumlah_mobil << endl;
      cout << "Lama penyewaan : " << rentals[i].lama_sewa << endl;
      cout << endl << "Jumlah tagihan perhari : " << rentals[i].total_perhari << endl;
      cout << "Jumlah semua tagihan : " << rentals[i].total_harga << endl;
    }
    cout << endl;
  }else {
    cout << endl << "Tidak ada penyewaan" << endl;
  }
}

int main() {
  do{
    clear();
    tampil_menu();
    cout << endl << "Masukkan pilihan anda > "; cin >> pil_menu;

    cout << endl;
    switch(pil_menu){
      case 1:
        input_mobil();
        break;
      case 2:
        cetak_mobil();
        break;
      case 3:
        rental_mobil();
        break;
      case 4:
        cetak_penyewa();
        break;
      case 0:
        cout << "Terima kasih telah menggunakan jasa kami!!" << endl;
        break;
      default:
        cout << "Menu yang dipilih tidak ada" << endl;
        break;
    }
    pause();
  } while(pil_menu != 0);
  return 0;
}
