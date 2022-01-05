// Nama : Nizar Izzuddin Y.F
// NIM  : 211054003
// Informatika Akprind

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

// Deklarasi type data record buku
struct Buku {
  string kode_buku, nama_buku;
  int jumlah_buku;
};
vector<Buku> arr_buku;

// Deklarasi type data record pinjaman
struct Pinjaman {
  string kode_pinjam, kode_buku_pinjam, nama_pinjaman;
  time_t hari_pinjam, tempo_hari_pengembalikan, hari_pengembalikan;
  bool denda, pengembalikan;
  double harga_denda;
};
vector<Pinjaman> arr_pinjaman;

int pil, uang_denda = 1000;

// Function dan Procedur
void clear();
void pause();

// Menu
void tambah_buku();
void cetak_buku();
void edit_buku();
void delete_buku();

// Menu pinjaman
void pinjam_buku();
void cetak_peminjam();
void delete_peminjam();
void pengembalian_pinjaman();

int main() {
  do {
    clear();
    cout << "Program Perpustakaan" << endl;
    cout << "1. Input buku baru" << endl;
    cout << "2. Cetak daftar buku" << endl;
    cout << "3. Edit buku" << endl;
    cout << "4. Delete buku" << endl;
    cout << "5. Pinjam buku" << endl;
    cout << "6. Cetak peminjam" << endl;
    cout << "7. Delete peminjam" << endl;
    cout << "8. Pengembalian peminjaman" << endl;
    cout << "0. Keluar" << endl;
    cout << "Pilih menu > "; cin >> pil;

    switch(pil) {
      case 1:
        tambah_buku();
        break;
      case 2:
        cetak_buku();
        break;
      case 3:
        edit_buku();
        break;
      case 4:
        delete_buku();
        break;
      case 5:
        pinjam_buku();
        break;
      case 6:
        cetak_peminjam();
        break;
      case 7:
        delete_peminjam();
        break;
      case 8:
        pengembalian_pinjaman();
        break;
      case 0:
        cout << endl << "Terima kasih telah menggunakan program perpus" << endl;
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

double denda(time_t hari_pinjam, time_t tempo_hari_pengembalian, bool &denda) {
  int detik_perhari = 86400;
  double harga_denda = 0;
  long int seconds;
  seconds = difftime(tempo_hari_pengembalian, hari_pinjam);
  if(seconds < 0) {
    denda = true;
    seconds -= seconds*2;
    harga_denda += seconds/detik_perhari;
    harga_denda *= uang_denda;
  }else {
    denda = false;
  }
  return harga_denda;
}

void convertTime(time_t hari, char *salin) {
  time_t salin_hari;
  tm * conday_hari;

  salin_hari = hari;
  conday_hari = localtime(&salin_hari);
  strftime(salin, 100, "%d %A, %Y", conday_hari);
}

void tambah_buku() {
  char lanjut;
  int i = arr_buku.size();
  string kode;
  bool ada;

  cout << endl << "Tambah buku baru" << endl;
  do{
    cout << endl << "Masukkan kode buku : "; cin >> kode;
    if(i >= 1){
      auto val_kode = find_if(arr_buku.begin(), arr_buku.end(), [kode](Buku const buku) {
        return buku.kode_buku == kode;
      });
      if(val_kode != arr_buku.end()) {
        cout << endl << "Kode buku " << kode << " yang dimasukkan sudah ada, silahkan edit data buku" << endl;
        lanjut = 't';
        ada = true;
      }
    }
    if(!ada) {
      arr_buku.push_back(Buku());
      arr_buku[i].kode_buku = kode;
      cout << "Masukkan nama buku : "; cin >> arr_buku[i].nama_buku;
      cout << "Masukkan jumlah buku : "; cin >> arr_buku[i].jumlah_buku;
      i++;
      cout << endl << "Mau memasukkan data lagi (y/t) ? "; cin >> lanjut;
    }
  } while(tolower(lanjut) == 'y');
}

void cetak_buku() {
  int n = arr_buku.size();
  if(n > 0){
    cout << endl << "Daftar buku di Perpustakaan saat ini" << endl;
    cout << "|==============================|" << endl;
    cout << " Kode" << setw(12) << "Judul" << setw(13) << "Jumlah " << endl;
    for(int i=0; i<n; i++) {
      cout << " " << arr_buku[i].kode_buku
          << setw(14) << arr_buku[i].nama_buku
          << setw(12) << arr_buku[i].jumlah_buku
          << " " << endl;
    }
    cout << "|==============================|" << endl << endl;
  }else {
    cout << endl << "Data buku belum ada" << endl;
  }
}

void edit_buku() {
  string pilih;
  int pos=0, jumlah;
  string nama;
  char lanjut;

  do {
    int n = arr_buku.size();
    if(n > 0){
      ulang:
        bool ada = false;
        cout << endl << "Edit buku di Perpustakaan" << endl;
        cetak_buku();
        cout << "Pilih kode buku yang diedit > "; cin >> pilih;
        auto check_val = find_if(arr_buku.begin(), arr_buku.end(), [pilih](Buku const buku) {
          return buku.kode_buku == pilih;
        });
        if(check_val != arr_buku.end()) {
          ada = true;
          pos = distance(arr_buku.begin(), check_val);
        }

      if(ada) {
        cout << endl << "Detail buku yang diedit" << endl;
        cout << "Kode buku : " << arr_buku[pos].kode_buku << endl;
        cout << "Nama buku : " << arr_buku[pos].nama_buku << endl;
        cout << "Jumlah buku : " << arr_buku[pos].jumlah_buku << endl;

        cout << "Yakin ingin mengedit buku atau ingin keluar (y/t/q) ? "; cin >> lanjut;
        if(tolower(lanjut) == 'y') {
          cout << "Jika nama buku tidak diganti masukkan \"-\"" << endl;
          cout << "Nama buku : "; cin >> nama;
          if(nama != "-") arr_buku[pos].nama_buku = nama;

          cout << endl << "Jika jumlah buku tidak diganti masukkan \"-0\"" << endl;
          cout << "Jumlah buku : "; cin >> jumlah;
          if(jumlah != -0) arr_buku[pos].jumlah_buku = jumlah;

          cout << endl << "Data berhasil diganti" << endl;
          cout << "Apakah ingin lanjut edit (y/q) ? "; cin >> lanjut;
          if(tolower(lanjut) == 'y') clear();
        }else if(tolower(lanjut) == 't') {
          clear();
          goto ulang;
        }
      }else {
        cout << "Data buku tidak ditemukan, inputan sensitif" << endl;
        cout << "Apakah ingin lanjut atau ingin keluar (y/q) ? "; cin >> lanjut;
        if(tolower(lanjut) == 'y') {
          clear();
          goto ulang;
        }
        cout << endl;
      }
    }else {
      cout << endl << "Data buku belum ada" << endl;
      lanjut = 'q';
    }
  } while(tolower(lanjut) != 'q');
}

void delete_buku() {
  string pilih;
  int pos=0;
  char lanjut;

  do {
    int n = arr_buku.size();
    if(n > 0){
      ulang:
        bool ada = false;
        cout << endl << "Hapus buku di Perpustakaan" << endl;
        cetak_buku();
        cout << "Pilih kode buku yang dihapus > "; cin >> pilih;
        auto check_val = find_if(arr_buku.begin(), arr_buku.end(), [pilih](Buku const buku) {
          return buku.kode_buku == pilih;
        });
        if(check_val != arr_buku.end()) {
          ada = true;
          pos = distance(arr_buku.begin(), check_val);
        }

      if(ada) {
        cout << endl << "Detail buku yang ingin dihapus" << endl;
        cout << "Kode buku : " << arr_buku[pos].kode_buku << endl;
        cout << "Nama buku : " << arr_buku[pos].nama_buku << endl;
        cout << "Jumlah buku : " << arr_buku[pos].jumlah_buku << endl;

        cout << "Yakin ingin menghapus buku atau ingin keluar (y/t/q) ? "; cin >> lanjut;
        if(tolower(lanjut) == 'y') {
          arr_buku.erase(
            remove_if(arr_buku.begin(), arr_buku.end(), [pilih](Buku const &buku) {
              return buku.kode_buku == pilih;
            }),
          arr_buku.end());
          cout << endl << "Data berhasil dihapus" << endl;
          cout << "Apakah ingin lanjut menghapus (y/q) ? "; cin >> lanjut;
          if(tolower(lanjut) == 'y') clear();
        }else if(tolower(lanjut) == 't') {
          clear();
          goto ulang;
        }
      }else {
        cout << "Data buku tidak ditemukan, inputan sensitif" << endl;
        cout << "Apakah ingin lanjut atau ingin keluar (y/q) ? "; cin >> lanjut;
        if(tolower(lanjut) == 'y') {
          clear();
          goto ulang;
        }
        cout << endl;
      }
    }else {
      cout << endl << "Data buku belum ada" << endl;
      lanjut = 'q';
    }
  } while(tolower(lanjut) != 'q');
}

void pinjam_buku() {
  string nama, kode;
  int pos, i = arr_pinjaman.size();
  char lanjut;

  do {
    pos=0;
    int n = arr_buku.size();
    if(n > 0){
      ulang:
        bool ada = false;
        cout << endl << "Pinjam buku di Perpustakaan" << endl;
        cetak_buku();
        cout << "Pilih kode buku yang dipinjam > "; cin >> kode;
        auto check_val = find_if(arr_buku.begin(), arr_buku.end(), [kode](Buku const buku) {
          return buku.kode_buku == kode;
        });
        if(check_val != arr_buku.end()) {
          ada = true;
          pos = distance(arr_buku.begin(), check_val);
        }

      if(ada) {
        cout << "Buku yang akan dipinjam " << arr_buku[pos].nama_buku << endl;
        cout << "Nama peminjam > "; cin >> nama;
        if(arr_buku[pos].jumlah_buku > 0) {
          arr_buku[pos].jumlah_buku -= 1;
          arr_pinjaman.push_back(Pinjaman());
          arr_pinjaman[i].kode_pinjam = nama.substr(0, 2) + arr_buku[pos].kode_buku;
          arr_pinjaman[i].kode_buku_pinjam = kode;
          arr_pinjaman[i].nama_pinjaman = nama;
          arr_pinjaman[i].hari_pinjam = time(0);
          arr_pinjaman[i].tempo_hari_pengembalikan = time(0)+86400*7;
          arr_pinjaman[i].hari_pengembalikan = time(0);
          arr_pinjaman[i].denda = false;
          arr_pinjaman[i].pengembalikan = false;
          cout << "Berhasil meminjam" << endl;
        }else {
          cout << "Meminjam buku dibatalkan karena jumlah buku yang dipinjam sudah maksimal" << endl;
        }

        cout << "Yakin ingin meminjam lagi (y/t) ? "; cin >> lanjut;
        if(tolower(lanjut) == 'y') i++;
      }else {
        cout << "Data buku tidak ditemukan, inputan sensitif" << endl;
        cout << "Apakah ingin lanjut pinjam (y/t) ? "; cin >> lanjut;
        if(tolower(lanjut) == 'y') {
          clear();
          goto ulang;
        }
        cout << endl;
      }
    }else {
      cout << endl << "Data buku belum ada" << endl;
      lanjut = 't';
    }
  } while(tolower(lanjut) != 't');
}

void cetak_peminjam() {
  int n = arr_pinjaman.size(), pos=0;
  char hari_pinjaman[100], tempo_hari_pengembalian[100], hari_pengembalian[100];

  if(n > 0){
    cout << endl << "Daftar peminjam buku di Perpustakaan saat ini" << endl;
    cout << "|==========================================================================================================================================|" << endl;
    cout << " Kode pinjam"
        << setw(20) << "Kode buku/Judul"
        << setw(20) << "Nama peminjam"
        << setw(18) << "Hari Peminjaman"
        << setw(23) << "Tempo Pengembalian"
        << setw(21) << "Hari Pengembalian"
        << setw(14) << "Status " << endl;
    for(int i=0; i<n; i++) {
      auto check_val = find_if(arr_buku.begin(), arr_buku.end(), [&](Buku const buku) {
        return buku.kode_buku == arr_pinjaman[i].kode_buku_pinjam;
      });
      pos = distance(arr_buku.begin(), check_val);

      // date pinjam
      convertTime(arr_pinjaman[i].hari_pinjam, hari_pinjaman);
      // date tempo pengembalikan
      convertTime(arr_pinjaman[i].tempo_hari_pengembalikan, tempo_hari_pengembalian);
      // date pengembalikan
      convertTime(arr_pinjaman[i].hari_pengembalikan, hari_pengembalian);

      arr_pinjaman[i].harga_denda = denda(arr_pinjaman[i].hari_pinjam,
                                          arr_pinjaman[i].tempo_hari_pengembalikan,
                                          arr_pinjaman[i].denda);

      cout << " " << arr_pinjaman[i].kode_pinjam
          << setw(15) << arr_pinjaman[i].kode_buku_pinjam
          << "/" << arr_buku[pos].nama_buku
          << setw(20) << arr_pinjaman[i].nama_pinjaman
          << setw(25) << hari_pinjaman
          << setw(23) << tempo_hari_pengembalian
          << setw(21) << (arr_pinjaman[i].pengembalikan ? hari_pengembalian : "Belum dikembalikan")
          << setw(35) << (arr_pinjaman[i].denda
                          ? (arr_pinjaman[i].pengembalikan
                              ? "Denda/Sudah dikembalikan"
                              : "Denda/Belum dikembalikan")
                          : (arr_pinjaman[i].pengembalikan
                              ? "Tidak denda/Sudah dikembalikan"
                              : "Tidak denda/Belum dikembalikan"))
          << " " << endl;
    }
    cout << "|==========================================================================================================================================|" << endl << endl;
  }else {
    cout << endl << "Data pinjaman belum ada" << endl;
  }
}

void delete_peminjam() {
  string pilih;
  int pos=0, pos_buku=0;
  char lanjut;
  char hari_pinjaman[100], tempo_hari_pengembalian[100];

  do {
    int n = arr_pinjaman.size();
    if(n > 0){
      ulang:
        bool ada = false;
        cout << endl << "Hapus peminjaman di Perpustakaan" << endl;
        cetak_peminjam();
        cout << "Pilih kode peminjaman yang dihapus > "; cin >> pilih;
        auto check_val = find_if(arr_pinjaman.begin(), arr_pinjaman.end(), [pilih](Pinjaman const pinjam) {
          return pinjam.kode_pinjam == pilih;
        });
        if(check_val != arr_pinjaman.end()) {
          ada = true;
          pos = distance(arr_pinjaman.begin(), check_val);
        }

      if(ada) {
        auto buku_pos = find_if(arr_buku.begin(), arr_buku.end(), [&](Buku const buku) {
          return buku.kode_buku == arr_pinjaman[pos].kode_buku_pinjam;
        });
        pos_buku = distance(arr_buku.begin(), buku_pos);

        // date pinjam
        convertTime(arr_pinjaman[pos].hari_pinjam, hari_pinjaman);
        // date tempo pengembalikan
        convertTime(arr_pinjaman[pos].tempo_hari_pengembalikan, tempo_hari_pengembalian);
        arr_pinjaman[pos].harga_denda = denda(arr_pinjaman[pos].hari_pinjam,
                                              arr_pinjaman[pos].tempo_hari_pengembalikan,
                                              arr_pinjaman[pos].denda);

        cout << endl << "Detail peminjaman yang ingin dihapus" << endl;
        cout << "Kode pinjaman : " << arr_pinjaman[pos].kode_pinjam << endl;
        cout << "Kode/Nama buku : " << arr_pinjaman[pos].kode_buku_pinjam
                                    << "/" << arr_buku[pos_buku].nama_buku << endl;
        cout << "Nama peminjam : " << arr_pinjaman[pos].nama_pinjaman << endl;
        cout << "Tanggal peminjaman : " << hari_pinjaman << endl;
        cout << "Tempo tanggal pengembalian : " << tempo_hari_pengembalian << endl;
        cout << "Status : " << (arr_pinjaman[pos].denda
                                ? (arr_pinjaman[pos].pengembalikan
                                    ? "Denda/Sudah dikembalikan"
                                    : "Denda/Belum dikembalikan")
                                : (arr_pinjaman[pos].pengembalikan
                                    ? "Tidak denda/Sudah dikembalikan"
                                    : "Tidak denda/Belum dikembalikan"))
                            << endl;
        cout << "Total tanggungan denda : " << arr_pinjaman[pos].harga_denda << endl;

        cout << "Yakin ingin menghapus pinjaman atau ingin keluar (y/t/q) ? "; cin >> lanjut;
        if(tolower(lanjut) == 'y') {
          if(!arr_pinjaman[pos].denda || arr_pinjaman[pos].pengembalikan) {
            arr_pinjaman.erase(
              remove_if(arr_pinjaman.begin(), arr_pinjaman.end(), [pilih](Pinjaman const &pinjam) {
                return pinjam.kode_pinjam == pilih;
              }),
            arr_pinjaman.end());
            arr_buku[pos_buku].jumlah_buku += 1;
            cout << endl << "Data berhasil dihapus" << endl;
          }else {
            cout << endl << "Data gagal dihapus karena status pinjaman adalah denda atau belum dikembalikan" << endl;
          }
          cout << "Apakah ingin lanjut menghapus (y/q) ? "; cin >> lanjut;
          if(tolower(lanjut) == 'y') clear();
        }else if(tolower(lanjut) == 't') {
          clear();
          goto ulang;
        }
      }else {
        cout << "Data pinjaman tidak ditemukan, inputan sensitif" << endl;
        cout << "Apakah ingin lanjut atau ingin keluar (y/q) ? "; cin >> lanjut;
        if(tolower(lanjut) == 'y') {
          clear();
          goto ulang;
        }
        cout << endl;
      }
    }else {
      cout << endl << "Data pinjaman belum ada" << endl;
      lanjut = 'q';
    }
  } while(tolower(lanjut) != 'q');
}

void pengembalian_pinjaman() {
  string pilih;
  int pos=0, pos_buku=0;
  char lanjut;
  char hari_pinjaman[100];

  do {
    int n = arr_pinjaman.size();
    if(n > 0){
      ulang:
        bool ada = false;
        cout << endl << "Pengembalian pinjaman" << endl;
        cetak_peminjam();
        cout << "Pilih kode peminjaman yang dikembalikan > "; cin >> pilih;
        auto check_val = find_if(arr_pinjaman.begin(), arr_pinjaman.end(), [pilih](Pinjaman const pinjam) {
          return pinjam.kode_pinjam == pilih;
        });
        if(check_val != arr_pinjaman.end()) {
          ada = true;
          pos = distance(arr_pinjaman.begin(), check_val);
        }

      if(ada) {
        if(arr_pinjaman[pos].pengembalikan) {
          cout << "Pinjaman buku sudah dikembalikan" << endl;
        }else{
          auto buku_pos = find_if(arr_buku.begin(), arr_buku.end(), [&](Buku const buku) {
            return buku.kode_buku == arr_pinjaman[pos].kode_buku_pinjam;
          });
          pos_buku = distance(arr_buku.begin(), buku_pos);

          // date pinjam
          convertTime(arr_pinjaman[pos].hari_pinjam, hari_pinjaman);

          arr_pinjaman[pos].harga_denda = denda(arr_pinjaman[pos].hari_pinjam,
                                                arr_pinjaman[pos].tempo_hari_pengembalikan,
                                                arr_pinjaman[pos].denda);

          cout << endl << "Detail pinjaman yang dikembalikan" << endl;
          cout << "Kode pinjaman : " << arr_pinjaman[pos].kode_pinjam << endl;
          cout << "Kode/Nama buku : " << arr_pinjaman[pos].kode_buku_pinjam << "/" << arr_buku[pos_buku].nama_buku << endl;
          cout << "Nama peminjam : " << arr_pinjaman[pos].nama_pinjaman << endl;
          cout << "Tanggal peminjaman : " << hari_pinjaman << endl;
          cout << "Status denda : " << (arr_pinjaman[pos].denda ? "Denda" : "Tidak denda") << endl;
          cout << "Total tanggungan denda : Rp." << arr_pinjaman[pos].harga_denda << endl;

          cout << "Yakin data pinjaman yang ingin dikembalikan sudah benar atau ingin keluar (y/t/q) ? "; cin >> lanjut;
          if(tolower(lanjut) == 'y') {
            arr_pinjaman[pos].pengembalikan = true;
            arr_pinjaman[pos].hari_pengembalikan = time(0);
            arr_buku[pos_buku].jumlah_buku += 1;
            cout << endl << "Pengembalian pinjaman berhasil" << endl;
            cout << "Apakah ingin lanjut mengembalikan pinjaman lagi (y/q) ? "; cin >> lanjut;
            if(tolower(lanjut) == 'y') clear();
          }else if(tolower(lanjut) == 't') {
            clear();
            goto ulang;
          }
        }
      }else {
        cout << "Data pinjaman tidak ditemukan, inputan sensitif" << endl;
        cout << "Apakah ingin lanjut atau ingin keluar (y/q) ? "; cin >> lanjut;
        if(tolower(lanjut) == 'y') {
          clear();
          goto ulang;
        }
        cout << endl;
      }
    }else {
      cout << endl << "Data pinjaman belum ada" << endl;
      lanjut = 'q';
    }
  } while(tolower(lanjut) != 'q');
}
