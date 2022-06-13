// Nizar Izzuddin Y.F
// 211054003

#include <iostream>
#include <iomanip>

#include <ios> // Digunakan untuk stream size
#include <limits> // Digunakan mendapatkan numeric limits

#define MENTOK 100

using namespace std;

struct Barang {
  string kode, nama;
  int stock;
  double harga;
};

Barang barang[MENTOK];
int n_barang = 0;

struct Keranjang {
  string kode[MENTOK];
  int jumlah[MENTOK];
  int front = -1;
} keranjang;

struct Checkout {
  string nama[MENTOK];
  int jumlah[MENTOK];
  double harga[MENTOK], subtotal[MENTOK], total;
  int front = -1;
} checkout;

// Procedure tambahan
void clear();
void pause();
bool barang_penuh();
bool barang_kosong();

void tambah_barang();
void edit_barang();
void hapus_barang();
void menu_barang();
void menu_user();

int main()
{
  int pilih;
  do {
    clear();
    cout << ".-----------------------------------------------." << endl;
    cout << "|              Program Mini Market              |" << endl;
    cout << "|-----------------------------------------------|" << endl;
    cout << "| [1] Tambah barang                             |" << endl;
    cout << "| [2] Cetak barang                              |" << endl;
    cout << "| [3] Edit barang                               |" << endl;
    cout << "| [4] Hapus barang                              |" << endl;
    cout << "| [5] Menu pembelian                            |" << endl;
    cout << "| [0] Keluar                                    |" << endl;
    cout << "'-----------------------------------------------'" << endl;
    cout << "? Pilih menu(0-5): ";
    cin >> pilih;

    switch(pilih)
    {
      case 1:
        if (!barang_penuh()) tambah_barang();
        else cout << "Jumlah barang sudah penuh" << endl;
        break;
      case 2:
        if (!barang_kosong()) menu_barang();
        else cout << "Barang tidak ada" << endl;
        break;
      case 3:
        if (!barang_kosong()) edit_barang();
        else cout << "Barang tidak ada" << endl;
        break;
      case 4:
        if (!barang_kosong()) hapus_barang();
        else cout << "Barang tidak ada" << endl;
        break;
      case 5:
        menu_user();
        break;
      case 0:
        cout << "Terima kasih telah menggunakan program kami" << endl;
        break;
      default:
        cout << "Inputan yang dimasukkan tidak ada dalam menu" << endl;
        break;
    }
    pause();
  } while(pilih != 0);

  return 0;
}

// Function Tambahan

void clear()
{
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

void pause()
{
  #ifdef _WIN32
    system("pause");
  #else
    //system("read -n 1 -p \"Press any key to continue...\"");
    cout << "Press any key to continue...";
    cin.ignore().get();
  #endif
}

// Function pembantu pada menu barang

bool barang_penuh()
{
  return n_barang > MENTOK;
}

bool barang_kosong()
{
  return n_barang == 0;
}

int position_barang(string kode)
{
  for (int i=0; i < n_barang; i++) if (kode == barang[i].kode) return i;

  return -1;
}

bool validation_barang(string kode)
{
  for (int i=0; i < n_barang; i++) if (kode == barang[i].kode) return true;

  return false;
}

// Function utama barang

void tambah_barang()
{
  string kode;

  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  ulang:
    bool ada = false;
    cout << "? Masukkan kode barang: ";
    getline(cin, kode);
    ada = validation_barang(kode);

  if (ada) {
    clear();
    cout << "Kode barang sudah ada" << endl;
    goto ulang;
  }

  barang[n_barang].kode = kode;
  cout << "? Masukkan nama barang: ";
  getline(cin, barang[n_barang].nama);
  cout << "? Masukkan stock barang: ";
  cin >> barang[n_barang].stock;
  cout << "? Masukkan harga barang: ";
  cin >> barang[n_barang].harga;
  n_barang++;
}

void edit_barang()
{
  int position, stock;
  string kode, nama;
  double harga;
  char lanjut;

  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  ulang:
    bool ada = false;
    menu_barang();
    cout << "? Masukkan kode barang: ";
    getline(cin, kode);
    position = position_barang(kode);
    ada = (position == -1 ? false : true);

  if (!ada) {
    clear();
    cout << "Kode barang tidak ada" << endl;
    goto ulang;
  }

  cout << "Detail barang" << endl;
  cout << "Kode barang  : " << barang[position].kode << endl;
  cout << "Nama barang  : " << barang[position].nama << endl;
  cout << "Stock barang : " << barang[position].stock << endl;
  cout << "Harga barang : " << barang[position].harga << endl;
  cout << "? Apakah ingin mengedit data ini (y/t): ";
  cin >> lanjut;

  if (tolower(lanjut) == 'y') {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << endl << "! Jika tidak ingin mengganti masukkan \"-\"" << endl;
    cout << "? Masukkan nama barang: ";
    getline(cin, nama);
    if (nama != "-") barang[position].nama = nama;

    cout << endl << "! Jika tidak ingin mengganti masukkan \"-0\"" << endl;
    cout << "? Masukkan stock barang: ";
    cin >> stock;
    if (stock != -0) barang[position].stock = stock;

    cout << endl << "! Jika tidak ingin mengganti masukkan \"-0\"" << endl;
    cout << "? Masukkan harga barang: ";
    cin >> harga;
    if (harga != -0) barang[position].harga = harga;

    cout << "Berhasil mengedit barang" << endl;
  }
}

void hapus_barang()
{
  int position;
  string kode;
  char lanjut;

  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  ulang:
    bool ada = false;
    menu_barang();
    cout << "? Masukkan kode barang: ";
    getline(cin, kode);
    position = position_barang(kode);
    ada = (position == -1 ? false : true);

  if (!ada) {
    clear();
    cout << "Kode barang tidak ada" << endl;
    goto ulang;
  }

  cout << endl << "Detail barang" << endl;
  cout << "Kode barang  : " << barang[position].kode << endl;
  cout << "Nama barang  : " << barang[position].nama << endl;
  cout << "Stock barang : " << barang[position].stock << endl;
  cout << "Harga barang : " << barang[position].harga << endl;
  cout << "? Apakah ingin menghapus data ini (y/t): ";
  cin >> lanjut;

  if (tolower(lanjut) == 'y') {
    for (int i = position; i < n_barang; i++) barang[i] = barang[i+1];

    n_barang--;
    cout << "Berhasil menghapus data" << endl;
  }
}

void menu_barang()
{
  cout << ".-----------------------------------------------." << endl;
  cout << "|                   List Barang                 |" << endl;
  cout << "|-----------------------------------------------|" << endl;
  cout << "|   Kode    Nama barang           Harga   Stock |" << endl;
  for (int i=0; i < n_barang; i++)
    cout << "| " << setw(6) << barang[i].kode
        << setw(15) << barang[i].nama
        << setw(16) << barang[i].harga
        << setw(8) << barang[i].stock
        << " |" << endl;
  cout << "'-----------------------------------------------'" << endl;
}

// Function pembantu keranjang

double hitung_harga_barang(double harga, int jumlah)
{
  return harga*jumlah;
}

bool keranjang_penuh()
{
  return keranjang.front == MENTOK-1;
}

bool keranjang_kosong()
{
  return keranjang.front == -1;
}

string ambil_nama_barang(string kode)
{
  for (int i=0; i < n_barang; i++) if (kode == barang[i].kode) return barang[i].nama;

  return "";
}

double ambil_harga_barang(string kode)
{
  for (int i=0; i < n_barang; i++) if (kode == barang[i].kode) return barang[i].harga;

  return 0;
}

bool hapus_keranjang_barang(string kode, int pos_barang)
{
  for (int i=keranjang.front; i >= 0; i--)
  {
    if (kode == keranjang.kode[i])
    {
      barang[pos_barang].stock += keranjang.jumlah[i];
      for (int j=i; j > 0; j--)
      {
        keranjang.kode[i] = keranjang.kode[i+1];
        keranjang.jumlah[i] = keranjang.jumlah[i+1];
      }
      keranjang.front--;
      return true;
    }
  }

  return false;
}

bool cek_barang_keranjang(string kode)
{
  for (int i=keranjang.front; i >= 0; i--) if (kode == keranjang.kode[i]) return true;

  return false;
}

int cek_index_barang_keranjang(string kode)
{
  for (int i=keranjang.front; i >= 0; i--) if (kode == keranjang.kode[i]) return i;

  return -1;
}

// Function utama keranjang

void tambah_keranjang()
{
  string pilih;
  int jumlah, position;
  char lanjut;

  ulang:
    bool ada = false;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    menu_barang();
    cout << "? Pilih barang: ";
    getline(cin, pilih);
    cout << "? Jumlah barang: ";
    cin >> jumlah;
    position = position_barang(pilih);
    ada = (position == -1 ? false : true);

  if (!ada)
  {
    clear();
    cout << "Barang tidak ada" << endl;
    goto ulang;
  }

  if (jumlah > barang[position].stock)
  {
    clear();
    cout << "Jumlah barang melebihi stock" << endl;
    goto ulang;
  }

  cout << "Detail barang: " << endl;
  cout << "Kode barang  : " << pilih << endl;
  cout << "Nama barang  : " << barang[position].nama << endl;
  cout << "Harga barang : " << barang[position].harga
                            << " X " << jumlah
                            << " = " << hitung_harga_barang(barang[position].harga, jumlah)
                            << endl;
  cout << "? Apakah jadi membeli barang(y/t): ";
  cin >> lanjut;

  if (tolower(lanjut) == 'y')
  {
    if (cek_barang_keranjang(pilih)) {
      int index_keranjang = cek_index_barang_keranjang(pilih);
      keranjang.jumlah[index_keranjang] += jumlah;
    } else {
      keranjang.front++;
      keranjang.kode[keranjang.front] = pilih;
      keranjang.jumlah[keranjang.front] = jumlah;
    }
    barang[position].stock = barang[position].stock - jumlah;
    cout << "Barang berhasil dimasukkan ke keranjang" << endl;
  } else {
    cout << "Barang tidak jadi dibeli" << endl;
  }

  cout << endl << "? Apakah ingin membeli yang lain(y/t): ";
  cin >> lanjut;

  if (tolower(lanjut) == 'y') goto ulang;
}

void cetak_keranjang()
{
  cout << ".----------------------------." << endl;
  cout << "|       Keranjang Barang     |" << endl;
  cout << "|----------------------------|" << endl;
  cout << "| No   Nama barang    Jumlah |" << endl;
  for (int i=0; i <= keranjang.front; i++)
    cout << "| " << i+1
        << setw(15) << ambil_nama_barang(keranjang.kode[i])
        << setw(10) << keranjang.jumlah[i]
        << " |" << endl;
  cout << "'----------------------------'" << endl;
}

void edit_keranjang()
{
  int jumlah, pos_barang, pilih;
  char lanjut;

  ulang:
    bool ada = false;
    cetak_keranjang();
    cout << "? Pilih no barang: ";
    cin >> pilih;
    ada = ((pilih-1 < 0 || pilih-1 > keranjang.front) ? false : true);

  if (!ada)
  {
    clear();
    cout << "Barang tidak ada" << endl;
    goto ulang;
  }

  string kode = keranjang.kode[pilih-1];
  pos_barang = position_barang(kode);
  cout << endl << "Detail barang" << endl;
  cout << "Kode barang   : " << kode << endl;
  cout << "Nama barang   : " << ambil_nama_barang(kode) << endl;
  cout << "Jumlah barang : " << keranjang.jumlah[pilih-1] << endl;
  cout << "? Apakah ingin mengedit data ini (y/t): ";
  cin >> lanjut;

  if (tolower(lanjut) == 'y') {
    cout << endl << "! Jika tidak ingin mengganti masukkan \"-0\"" << endl;
    cout << "? Masukkan jumlah barang: ";
    cin >> jumlah;
    if (jumlah != -0) {
      barang[pos_barang].stock += keranjang.jumlah[pilih-1] - jumlah;
      keranjang.jumlah[pilih-1] = jumlah;
    }
    else if (jumlah == 0) hapus_keranjang_barang(kode, pos_barang);

    cout << "Berhasil mengedit keranjang" << endl;
  }
}

void hapus_keranjang()
{
  int pos_barang, pilih;
  char lanjut;

  ulang:
    bool ada = false;
    cetak_keranjang();
    cout << "? Pilih no barang: ";
    cin >> pilih;
    ada = ((pilih-1 < 0 || pilih-1 > keranjang.front) ? false : true);

  if (!ada)
  {
    clear();
    cout << "Barang tidak ada" << endl;
    goto ulang;
  }

  string kode = keranjang.kode[pilih-1];
  pos_barang = position_barang(kode);
  cout << endl << "Detail barang" << endl;
  cout << "Kode barang   : " << pilih << endl;
  cout << "Nama barang   : " << ambil_nama_barang(kode) << endl;
  cout << "Jumlah barang : " << keranjang.jumlah[pilih-1] << endl;
  cout << "? Apakah ingin menghapus data ini (y/t): ";
  cin >> lanjut;

  if (tolower(lanjut) == 'y') {
    hapus_keranjang_barang(kode, pos_barang);
    cout << "Berhasil menghapus keranjang" << endl;
  }
}

void cari_keranjang()
{
  string pilih;
  int position;
  char lanjut;

  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  ulang:
    bool ada = false;
    cout << "? Kode barang: ";
    getline(cin, pilih);
    ada = validation_barang(pilih);
    position = position_barang(pilih);

  if (!ada)
  {
    clear();
    cout << "Barang tidak ada" << endl;
    goto ulang;
  }

  cout << endl << "Detail barang" << endl;
  cout << "Kode barang   : " << pilih << endl;
  cout << "Nama barang   : " << barang[position].nama << endl;
  cout << "Jumlah barang : " << barang[position].stock << endl;
  cout << "Harga barang  : " << barang[position].harga << endl;
}

void total_belanja()
{
  double total=0, subtotal, harga;
  char lanjut;
  // Push semua barang sudah di inputkan untuk checkout
  if (keranjang.front >= 0) {
    checkout.front = -1;
    for (int i=keranjang.front; i >= 0; i--)
    {
      checkout.front++;
      harga = ambil_harga_barang(keranjang.kode[i]);
      subtotal = hitung_harga_barang(harga, keranjang.jumlah[i]);
      checkout.nama[checkout.front] = ambil_nama_barang(keranjang.kode[i]);
      checkout.jumlah[checkout.front] = keranjang.jumlah[i];
      checkout.subtotal[checkout.front] = subtotal;
      checkout.harga[checkout.front] = harga;
      total += subtotal;
    }
    checkout.total = total;
  }

  cout << ".-------------------------------------------------------------." << endl;
  cout << "|                        Invoice Belanja                      |" << endl;
  cout << "|-------------------------------------------------------------|" << endl;
  cout << "| No      Nama barang     Jumlah       Harga   |     Total    |" << endl;
  for (int i=0; i <= checkout.front; i++)
  {
    cout << "| " << i+1
        << setw(18) << checkout.nama[i]
        << setw(11) << checkout.jumlah[i]
        << setw(14) << checkout.harga[i]
        << setw(2) << "|"
        << setw(13) << checkout.subtotal[i]
        << " |" << endl;
  }
  cout << "|-------------------------------------------------------------|" << endl;
  cout << "|                   Total                      | " << setw(12) << checkout.total << " |" << endl;
  cout << "'-------------------------------------------------------------'" << endl;

  cout << endl << "? Apakah ingin mengchekout semua keranjang (y/t): ";
  cin >> lanjut;

  // Belanja dianggap selesai keluarkan semua dari keranjang
  if (tolower(lanjut) == 'y') keranjang.front = -1;
}

void menu_user()
{
  int pilih;
  do {
    clear();
    cout << ".-----------------------------------------------." << endl;
    cout << "|            User Program Mini Maket            |" << endl;
    cout << "|-----------------------------------------------|" << endl;
    cout << "| [1] Tambah keranjang                          |" << endl;
    cout << "| [2] Cetak keranjang                           |" << endl;
    cout << "| [3] Edit keranjang                            |" << endl;
    cout << "| [4] Hapus keranjang                           |" << endl;
    cout << "| [5] Cari detail barang                        |" << endl;
    cout << "| [6] Total belanja                             |" << endl;
    cout << "| [0] Keluar pembelian                          |" << endl;
    cout << "'-----------------------------------------------'" << endl;
    cout << "? Pilih menu(0-6): ";
    cin >> pilih;

    switch(pilih)
    {
      case 1:
        if (n_barang >= 1) tambah_keranjang();
        else cout << "Barang sekarang tidak tersedia" << endl;
        break;
      case 2:
        if (keranjang.front >= 0) cetak_keranjang();
        else cout << "Anda belum berbelanja" << endl;
        break;
      case 3:
        if (keranjang.front >= 0) edit_keranjang();
        else cout << "Anda belum berbelanja" << endl;
        break;
      case 4:
        if (keranjang.front >= 0) hapus_keranjang();
        else cout << "Anda belum berbelanja" << endl;
        break;
      case 5:
        if (keranjang.front >= 0) cari_keranjang();
        else cout << "Anda belum berbelanja" << endl;
        break;
      case 6:
        if (keranjang.front >= 0) total_belanja();
        else cout << "Anda belum berbelanja" << endl;
        break;
      case 0:
        checkout.front = -1;
        cout << "Terima kasih telah menggunakan program kami" << endl;
        break;
      default:
        cout << "Inputan yang dimasukkan tidak ada dalam menu" << endl;
        break;
    }
    pause();
  } while(pilih != 0);
}
