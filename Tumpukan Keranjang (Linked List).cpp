// Nizar Izzuddin Y.F
// 211054003

#include <iostream>
#include <iomanip>

#include <ios> // Digunakan untuk stream size
#include <limits> // Digunakan mendapatkan numeric limits

// Membuat MENTOK dengan value 100 digunakan pada array record
#define MENTOK 100

using namespace std;

// Mendeklarasikan record barang
struct Barang {
  string kode, nama;
  int stock;
  double harga;
};

// Membuat record barang menjadi array dengan batas MENTOK yang sudah dibuat
Barang barang[MENTOK];
// Mendeklarasikan n_barang untuk menghitung jumlah barang yang sudah dimasukkan pada array record
int n_barang = 0;

// Membuat linked list keranjang untuk menampung barang yang sudah dimasukkan ke troli atau keranjang
struct Keranjang {
  string kode;
  int jumlah;
  Keranjang *next;
};

// Mendeklarasikan first dan last keranjang alamat record linked list
Keranjang *f_keranjang;
Keranjang *l_keranjang;

// Membuat linked list checkout untuk menampung barang yang jadi dibeli
struct Checkout {
  string nama;
  int jumlah;
  double harga, subtotal;
  Checkout *next;
};

// Mendeklarasikan first dan last checkout alamat record linked list
Checkout *f_checkout;
Checkout *l_checkout;

// Mendeklarasikan total untuk menampung hitungan total harga yang dibayar
double total = 0;

// Procedure tambahan system hapus dan pause
void clear();
void pause();

// Function tambahan untuk array record barang untuk mengetahui barang apakah penuh dan barang apakah kosong
bool barang_penuh();
bool barang_kosong();

// Procedure untuk array record tambah, edit, hapus, print data barang
void tambah_barang();
void edit_barang();
void hapus_barang();
void menu_barang();

// Procedure untuk masuk ke menu keranjang
void menu_user();

int main()
{
  // Definisikan first dan last checkout menjadi nullptr untuk membuat data kosong
  f_checkout = nullptr;
  l_checkout = nullptr;

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

// Procedure Tambahan

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

//// Untuk mengecek barang apakah penuh
bool barang_penuh()
{
  /*
  apakah jumlah barang lebih sama dengan 100-1 = 99 jika iya maka akan dikembalikan true,
  jika tidak maka akan dikembalikan false
  */
  return n_barang >= MENTOK-1;
}

//// Untuk mengecek apakah barang kosong
bool barang_kosong()
{
  /*
  apakah jumlah barang sama dengan 0 jika iya maka akan dikembalikan true,
  jika tidak maka akan dikembalikan false
  */
  return n_barang == 0;
}

//// Untuk mencari tau posisi index barang dari kode barang
int position_barang(string kode)
{
  /*
  Membuat perulangan dari 0 sampai kurang dari jumlah barang dengan variabel i di increament
  Didalam perulangan ada kondisi jika kode dari parameter sama dengan lopping barang maka akan mengembalikan nilai i
  Jika tidak ditemukan maka akan mengembalikan -1
  */
  for (int i=0; i < n_barang; i++) if (kode == barang[i].kode) return i;

  return -1;
}

//// Untuk validasi kode barang apakah ada pada record barang
bool validation_barang(string kode)
{
  /*
  Membuat perulangan dari 0 sampai kurang dari jumlah barang dengan variabel i di increament
  Didalam perulangan ada kondisi jika kode dari parameter sama dengan lopping barang maka akan mengembalikan true
  Jika tidak ditemukan maka akan mengembalikan false
  */
  for (int i=0; i < n_barang; i++) if (kode == barang[i].kode) return true;

  return false;
}

// Procedure utama barang

//// Procedure untuk menambah barang
void tambah_barang()
{
  // Mendeklarasikan kode untuk menyimpan sementara kode barang yang akan dimasukkan
  string kode;
  bool ada;

  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  ulang:
    ada = false;
    // Menginput kode barang yang akan dimasukkan
    cout << "? Masukkan kode barang: ";
    getline(cin, kode);
    /*
    Memvalidasi kode barang yg diinput tadi dengan algoritma function validation_barang yang sudah dijelaskan tadi
    Nilai yg dikembalikan dari function validation_barang akan ditampung pada variabel ada
    */
    ada = validation_barang(kode);

  // Jika ada true maka akan kembali ke label ulang
  if (ada) {
    clear();
    cout << "Kode barang sudah ada" << endl;
    goto ulang;
  }

  /*
  Jika ada false maka akan dilanjutkan kode dibawah
  Kode yang tadi dimasukkan di variabel kode dimasukkan ke record barang sesuai n_barang yaitu dari index 0
  Dan seterusnya memasukkan nama, stock, harga barang
  */
  barang[n_barang].kode = kode;
  cout << "? Masukkan nama barang: ";
  getline(cin, barang[n_barang].nama);
  cout << "? Masukkan stock barang: ";
  cin >> barang[n_barang].stock;
  cout << "? Masukkan harga barang: ";
  cin >> barang[n_barang].harga;

  // Setelah memasukkan data tadi maka n_barang akan di increment dan menambah 1 dari nilainya
  n_barang++;
}

//// Procedure edit barang yang ada
void edit_barang()
{
  int position, stock;
  string kode, nama;
  double harga;
  char lanjut;
  bool ada;

  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  ulang:
    ada = false;
    // Menampilkan data barang
    menu_barang();
    // Memasukkan kode barang yang ingin diedit
    cout << "? Masukkan kode barang: ";
    getline(cin, kode);
    // Mencari posisi index barang dengan kode barang yang dimasukkan
    position = position_barang(kode);
    /*
    Membuat validasi dari kembalian nilai index barang jika nilai position -1 maka barang tidak ada
    Jika tidak -1 maka barang dianggap ada
    */
    ada = (position == -1 ? false : true);

  /*
  Jika ada false akan berubah menjadi true dan akan kembali ke label ulang
  Jika ada true akan menjadi false maka akan lanjut ke kode setelahnya
  */
  if (!ada) {
    clear();
    cout << "Kode barang tidak ada" << endl;
    goto ulang;
  }

  // Menampilkan detail barang yang ingin diedit dengan memanggil index barang
  cout << "Detail barang" << endl;
  cout << "Kode barang  : " << barang[position].kode << endl;
  cout << "Nama barang  : " << barang[position].nama << endl;
  cout << "Stock barang : " << barang[position].stock << endl;
  cout << "Harga barang : " << barang[position].harga << endl;
  cout << "? Apakah ingin mengedit data ini (y/t): ";
  cin >> lanjut;

  // Jika dijawab y maka akan lanjut mengedit jika tidak maka akan kembali ke menu utama
  if (tolower(lanjut) == 'y') {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << endl << "! Jika tidak ingin mengganti masukkan \"-\"" << endl;
    // Mengganti nama barang jika tidak sama dengan - maka akan dimasukkan ke record
    cout << "? Masukkan nama barang: ";
    getline(cin, nama);
    if (nama != "-") barang[position].nama = nama;

    cout << endl << "! Jika tidak ingin mengganti masukkan \"-1\"" << endl;
    // Mengganti stock barang jika tidak sama dengan -1 maka akan dimasukkan ke record
    cout << "? Masukkan stock barang: ";
    cin >> stock;
    if (stock != -1) barang[position].stock = stock;

    cout << endl << "! Jika tidak ingin mengganti masukkan \"-1\"" << endl;
    // Mengganti harga barang jika tidak sama dengan -1 maka akan dimasukkan ke record
    cout << "? Masukkan harga barang: ";
    cin >> harga;
    if (harga != -1) barang[position].harga = harga;

    cout << "Berhasil mengedit barang" << endl;
  }
}

//// Procedure hapus barang
void hapus_barang()
{
  int position;
  string kode;
  char lanjut;
  bool ada;

  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  ulang:
    ada = false;
    // Menampilkan data barang
    menu_barang();
    // Memasukkan kode barang yang ingin dihapus
    cout << "? Masukkan kode barang: ";
    getline(cin, kode);
    // Mencari posisi index barang dengan kode barang yang dimasukkan
    position = position_barang(kode);
    /*
    Membuat validasi dari kembalian nilai index barang jika nilai position -1 maka barang tidak ada
    Jika tidak -1 maka barang dianggap ada
    */
    ada = (position == -1 ? false : true);

  /*
  Jika ada false akan berubah menjadi true dan akan kembali ke label ulang
  Jika ada true akan menjadi false maka akan lanjut ke kode setelahnya
  */
  if (!ada) {
    clear();
    cout << "Kode barang tidak ada" << endl;
    goto ulang;
  }

  // Menampilkan detail barang yang ingin diedit dengan memanggil index barang
  cout << endl << "Detail barang" << endl;
  cout << "Kode barang  : " << barang[position].kode << endl;
  cout << "Nama barang  : " << barang[position].nama << endl;
  cout << "Stock barang : " << barang[position].stock << endl;
  cout << "Harga barang : " << barang[position].harga << endl;
  cout << "? Apakah ingin menghapus data ini (y/t): ";
  cin >> lanjut;

  // Jika dijawab y maka akan lanjut mengedit jika tidak maka akan kembali ke menu utama
  if (tolower(lanjut) == 'y') {
    /*
    Membuat perulangan dari posisi index barang yang tadi sampai jumlah barang yang ada
    Setelah itu dari index posisi barang tadi data direplace dengan data setelahnya
    */
    for (int i = position; i < n_barang; i++) barang[i] = barang[i+1];

    // Setelah berhasil menimpan data maka akan mengurangi n_barang dengan decrement yg akan mengurangi 1 dari value
    n_barang--;
    cout << "Berhasil menghapus data" << endl;
  }
}

//// Procedure cetak data barang
void menu_barang()
{
  cout << ".-----------------------------------------------." << endl;
  cout << "|                   List Barang                 |" << endl;
  cout << "|-----------------------------------------------|" << endl;
  cout << "|   Kode    Nama barang           Harga   Stock |" << endl;
  // Perulangan dari 0 sampai jumlah data
  for (int i=0; i < n_barang; i++)
    cout << "| " << setw(6) << barang[i].kode
        << setw(15) << barang[i].nama
        << setw(16) << barang[i].harga
        << setw(8) << barang[i].stock
        << " |" << endl;
  cout << "'-----------------------------------------------'" << endl;
}

// Function pembantu keranjang
//// Function menghitung dari harga * jumlah barang yang dimasukkan ke keranjang
double hitung_harga_barang(double harga, int jumlah)
{
  // Akan mengembalikan hasil perkalian parameter harga dan jumlah
  return harga*jumlah;
}

//// Function mengambil nama barang yang dimasukkan keranjang atau yg dipilih, dicari dengan menggunakan kode
string ambil_nama_barang(string kode)
{
  /*
  Membuat perulangan dari index 0 sampai jumlah barang
  Didalam perulangan ada kondisi jika kode pada parameter sama dengan record barang yang sudah dibuat perulangan
  Maka akan mengembalikkan nama
  Jika tidak maka akan dikembalikan value kosong
  */
  for (int i=0; i < n_barang; i++) if (kode == barang[i].kode) return barang[i].nama;

  return "";
}

//// Function mengambil harga barang dari kode yang dimasukkan
double ambil_harga_barang(string kode)
{
  /*
  Membuat perulangan dari index 0 sampai jumlah barang
  Didalam perulangan ada kondisi jika kode pada parameter sama dengan record barang yang sudah dibuat perulangan
  Maka akan mengembalikkan harga
  Jika tidak maka akan dikembalikan 0
  */
  for (int i=0; i < n_barang; i++) if (kode == barang[i].kode) return barang[i].harga;

  return 0;
}

//// Function hapus keranjang memasukkan parameter kode barang pada keranjang
/*
posisi barang yang sudah ditemukan tadi yang sama dengan kode barang keranjang
Parameter f dan l dari linked list keranjang yang berbentuk pointer dan menggunakan reference untuk mengembalikan value
*/
bool hapus_keranjang_barang(string kode, int pos_barang, Keranjang *&f, Keranjang *&l)
{
  // Deklarasi remove dan temp dari linked list keranjang
  Keranjang *remove, *temp;
  remove = new Keranjang;
  temp = new Keranjang;

  // temp diisi f
  temp = f;

  // Jika parameter kode sama dengan first maka akan melakukan kode didalam nya dan melakukkan kembalian true
  if (f->kode == kode) {
    // variabel remove akan diisi data alamat first
    remove = f;
    // f akan direplace atau ditimpa alamat dari first next yang berarti alamat kedua
    f = f->next;
    // Stok barang akan ditambah dari nilai jumlah barang keranjang yang ingin dihapus
    barang[pos_barang].stock += remove->jumlah;
    // Menghapus data remove
    delete remove;

    return true;
  // Jika parameter kode sama dengan last maka akan melakukan kode didalam nya dan melakukkan kembalian true
  } else if (l->kode == kode) {
    // Melakukkan perulangan trs sampai menemukan alamat NULL atau kosong
    // yang berarti data sebelum alamat akhir
    while((temp->next)->next != NULL)
    {
      // temp akan direplace dengan alamat selanjutnya
      temp = temp->next;
    }
    // remove akan diisi alamat temp setelahnya
    remove = temp->next;
    // Stok barang akan ditambah dari nilai jumlah barang keranjang yang ingin dihapus
    barang[pos_barang].stock += remove->jumlah;
    // Mengganti alamat last dengan temp yang berarti data sebelum alamat terakhir
    l = temp;
    // mengganti alamat selanjutnya menjadi NULL
    l->next = NULL;
    // Menghapus data remove
    delete remove;

    return true;
  // Jika parameter kode tidak sama dengan diatas maka akan menjalankan kode didalamnya
  } else {
    // Membuat perulangan sampai data terakhir
    while (temp->next != NULL)
    {
      // Jika kode dari parameter sama dengan perulangan temp alamat selanjutnya yg menunjukkan kode maka akan melakukan kode dibawah
      if (temp->next->kode == kode) {
        // remove akan diisi alamat temp setelahnya
        remove = temp->next;
        // Stok barang akan ditambah dari nilai jumlah barang keranjang yang ingin dihapus
        barang[pos_barang].stock += remove->jumlah;
        // Alamat temp setelahnya akan diisi alamat remove setelahnya
        temp->next = remove->next;
        // Akan menghapus data remove
        delete remove;
        // Akan mengembalikan nilai true dan berhenti melakukkan perulangan
        return true;
      }
      // jika kondisi false maka temp akan direplace dengan alamat temp setelahnya
      temp = temp->next;
    }
  }

  // jika semua kondisi tidak ada maka akan dikembalikan false yang berarti gagal menghapus
  return false;
}

//// Function cek barang apakah kode barang keranjang yg dicari ada atau tidak
bool cek_barang_keranjang(string kode, Keranjang *f, Keranjang *l)
{
  // Jika first atau last kode sama dengan parameter kode yang dicari maka akan dikembalikan true
  if (f->kode == kode || l->kode == kode) return true;
  // Jika tidak ada maka akan menjalankan kode didalam else
  else {
    // Membuat perulangan sampai data terakhir
    while (f->next != NULL)
    {
      // Jika kode dari parameter sama dengan perulangan f alamat selanjutnya yg menunjukkan kode maka akan mengembalikan true dan selesai perulangan
      if (f->next->kode == kode) return true;
      // Jika kondisi tidak terpenuhi maka f akan direplace dengan alamat f setelahnya
      f = f->next;
    }
  }

  // Jika kondisi diatas tidak dikembalikan maka akan dikembalikan nilai false
  return false;
}

//// Function untuk menambah jumlah barang atau mengganti jumlah barang
/*
parameter baru itu untuk kondisi jika jumlah barang tidak baru maka hanya akan mengganti jumlah dengan isi jumlah
parameter kode keranjang barang yang ingin diganti jumlah barang
parameter jumlah untuk value jumlah
*/
bool tambah_jumlah_barang_keranjang(bool baru, string kode, int jumlah, Keranjang *f, Keranjang *l)
{
  // membuat deklarasi variabel total dengan isi jumlah
  int total = jumlah;

  // jika kode yang ingin diganti sama dengan kode first maka akan melakukkan kode yg didalamnya dan dikembalikan nilai true
  if (f->kode == kode) {
    // jika baru tidak baru menambah total dengan jumlah barang pada keranjang yg dicari
    if (!baru) total += f->jumlah;
    // mengganti nilai jumlah pada keranjang dengan total
    f->jumlah = total;

    return true;
  // jika kode yang ingin diganti sama dengan kode last maka akan melakukkan kode yg didalamnya dan dikembalikan nilai true
  } else if (l->kode == kode) {
    // jika baru tidak baru menambah total dengan jumlah barang pada keranjang yg dicari
    if (!baru) total += l->jumlah;
    // mengganti nilai jumlah pada keranjang dengan total
    l->jumlah = total;

    return true;
  // jika kondisi diatas tidak memenuhi maka akan menjalankan kode didalam else
  } else {
    // Membuat perulangan dari first sampai data linked list terakhir
    while (f != nullptr)
    {
      // jika f kode sama dengan kode yg dicari maka akan melakukan kode didalamnya dan mengembalikan nilai true
      if (f->kode == kode) {
        // jika baru tidak baru menambah total dengan jumlah barang pada keranjang yg dicari
        if (!baru) total += f->jumlah;
        // mengganti nilai jumlah pada keranjang dengan total
        f->jumlah = total;

        return true;
      }
      // jika kondisi diatas tidak terpenuhi maka f akan ditimpa dengan alamat selanjutnya dari f
      f = f->next;
    }
  }

  // Jika kondisi diatas tidak terpenuhi semua akan mengembalikan nilai false
  return false;
}

//// Function mengambil jumlah barang pada keranjang
int ambil_jumlah_barang_keranjang(string kode, Keranjang *f, Keranjang *l)
{
  // jika f kode sama dengan kode yang dicari maka akan mengembalikan value f jumlah
  if (f->kode == kode) return f->jumlah;
  // jika l kode sama dengan kode yang dicari maka akan mengembalikan value l jumlah
  else if (l->kode == kode) return l->jumlah;
  // jika kondisi diatas tidak terpenuhi maka akan menjalankan kode dibawah
  else {
    // Membuat perulangan dari first sampai data linked list terakhir
    while (f != nullptr)
    {
      // jika f kode sama dengan kode yg dicari maka akan melakukan kode didalamnya dan mengembalikan value f jumlah
      if (f->kode == kode) return f->jumlah;
      // jika kondisi diatas tidak terpenuhi maka f akan ditimpa dengan alamat selanjutnya dari f
      f = f->next;
    }
  }

  // Jika kondisi diatas tidak terpenuhi semua akan mengembalikan nilai 0
  return 0;
}

//// Membantu checkout barang
bool checkout_barang(Keranjang *&f, Keranjang *&l)
{
  // Deklarasi remove dan temp dari linked list keranjang
  Keranjang *remove, *temp;
  remove = new Keranjang;
  temp = new Keranjang;

  // temp diisi f
  temp = f;
  if (f == l) {
    // remove diberi alamat f untuk dihapus
    remove = f;
    // alamat pada last dikosongkan karena f->next berisi null
    f = f->next;
    // alamat pada last dikosongkan
    l = nullptr;
  } else {
    // Melakukkan perulangan trs sampai menemukan alamat NULL atau kosong
    // yang berarti data sebelum alamat akhir
    while((temp->next)->next != NULL)
    {
      // temp akan direplace dengan alamat selanjutnya
      temp = temp->next;
    }
    // remove akan diisi alamat temp setelahnya
    remove = temp->next;
    // Mengganti alamat last dengan temp yang berarti data sebelum alamat terakhir
    l = temp;
    // mengganti alamat selanjutnya menjadi NULL
    l->next = NULL;
    // Menghapus data remove
  }

  // delete alamat remove
  delete remove;

  return true;
}

// Function utama keranjang
//// Procedure menambah barang pada keranjang
void tambah_keranjang(Keranjang *&f, Keranjang *&l)
{
  Keranjang *barang_baru;
  string pilih;
  int jumlah, position;
  char lanjut;
  bool cek, berhasil = false, ada;

  ulang:
    barang_baru = new Keranjang;
    ada = false;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // Menampilkan menu barang atau barang yg ada
    menu_barang();
    // Memasukkan kode barang yg ada dan memasukkan ke variabel pilih
    cout << "? Pilih kode barang: ";
    getline(cin, pilih);
    // Memasukkan jumlah barang yang ingin dimasukka ke keranjang
    cout << "? Jumlah barang: ";
    cin >> jumlah;
    // Menjadi posisi index barang dari kode yang dimasukkan
    position = position_barang(pilih);
    /*
    Validasi barang apakah ada dari posisi barang jika sama dengan -1 maka barang tidak ada
    jika tidak sama dengan -1 maka barang ada
    */
    ada = (position == -1 ? false : true);

  // kebalikan value variabel ada jika menjadi true maka akan dikembalikan ke label ulang
  if (!ada)
  {
    clear();
    cout << "Barang tidak ada" << endl;
    goto ulang;
  }

  // jika jumlah yang dimasukkan lebih dari stok barang maka akan kembali ke label ulang
  if (jumlah > barang[position].stock)
  {
    clear();
    cout << "Jumlah barang melebihi stock" << endl;
    goto ulang;
  }

  // Menampilkan detail barang yang dimasukkan ke keranjang
  cout << "Detail barang: " << endl;
  cout << "Kode barang  : " << pilih << endl;
  cout << "Nama barang  : " << barang[position].nama << endl;
  cout << "Harga barang : " << barang[position].harga
                            << " X " << jumlah
                            // Menghitung harga barang dari harga dikali jumlah yang ingin dimasukkan
                            << " = " << hitung_harga_barang(barang[position].harga, jumlah)
                            << endl;
  cout << "? Apakah jadi membeli barang(y/t): ";
  cin >> lanjut;

  // jika y maka akan memasukkan barang ke keranjang
  if (tolower(lanjut) == 'y')
  {
    // memasukkan inputan tadi ke linked list
    barang_baru->kode = pilih;
    barang_baru->jumlah = jumlah;
    barang_baru->next = NULL;
    // jika f berisi null akan menambahkan f dan l dengan alamat barang baru dan variabel berhasil menjadi true
    if (f == nullptr) {
      f = barang_baru;
      l = barang_baru;
      berhasil = true;
    // jika kondisi diatas tidak terpenuhi maka akan menjalankan kode dibawahnya
    } else {
      // akan mengecek kode barang yg dimasukkan tadi apakah ada pada keranjang atau tidak
      cek = cek_barang_keranjang(pilih, f, l);
      // jika cek true maka hanya menambah jumlah barang pada keranjang
      if (cek) {
        // berhasil akan menerima nilai kembali dari function, disini set baru false maka jumlah hanya akan ditambah dari jumlah aslinya
        berhasil = tambah_jumlah_barang_keranjang(false, pilih, jumlah, f, l);
      /*
      jika kondisi diatas tidak terpenuhi maka akan last next menjadi alamat barang baru dan
      memasukkan alamat barang baru tadi ke last yang berarti data terakhir dan set berhasil menjadi true
      */
      } else {
        l->next = barang_baru;
        l = barang_baru;
        berhasil = true;
      }
    }

    // jika berhasil true maka stok akan mengurangi sesuai jumlah yang dimasukkan ke keranjang
    if (berhasil) {
      barang[position].stock -= jumlah;
      cout << "Barang berhasil dimasukkan ke keranjang" << endl;
    } else cout << "Barang gagal dimasukkan ke keranjang" << endl;
  } else {
    cout << "Barang tidak jadi dibeli" << endl;
  }

  cout << endl << "? Apakah ingin membeli yang lain(y/t): ";
  cin >> lanjut;

  // jika ingin memasukkan barang ke keranjang lagi maka barang baru akan diset null dan akan kembali ke label ulang
  if (tolower(lanjut) == 'y') {
    barang_baru = nullptr;
    goto ulang;
  }
}

//// Procedure cetak data keranjang dari data first
void cetak_keranjang(Keranjang *f)
{
  cout << ".-------------------------------." << endl;
  cout << "|        Keranjang Barang       |" << endl;
  cout << "|-------------------------------|" << endl;
  cout << "|   Kode    Nama barang  Jumlah |" << endl;
  while (f != NULL)
  {
    cout << "| " << setw(6) << f->kode
        // Mengambil nama barang dari kode barang yang dikeranjang
        << setw(15) << ambil_nama_barang(f->kode)
        << setw(8) << f->jumlah
        << " |" << endl;
    f = f->next;
  }
  cout << "'-------------------------------'" << endl;
}

//// Procedure edit data keranjang
void edit_keranjang(Keranjang *&f, Keranjang *&l)
{
  int jumlah, pos_barang, jumlah_barang_keranjang;
  char lanjut;
  bool berhasil, ada;
  string pilih;

  ulang:
    ada = false;
    // Mencetak data keranjang yang ada
    cetak_keranjang(f);
    // Menginput kode barang
    cout << "? Pilih kode barang: ";
    cin >> pilih;
    // validasi kode barang dengan function cek_barang_keranjang yg dijelaskan diatas
    ada = cek_barang_keranjang(pilih, f, l);

  // kebalikan dari nilai variabel ada jika dari kebalikan itu menghasilkan true maka barang dianggap tidak ada dan kembali ke label ulang
  if (!ada)
  {
    clear();
    cout << "Barang tidak ada" << endl;
    goto ulang;
  }

  // Mencari posisi barang dari kode barang keranjang dengan function yg sudah dijelaskan diatas
  pos_barang = position_barang(pilih);
  // Mengambil jumlah barang pada keranjang dengan function yg sudah dijelaskan diatas
  jumlah_barang_keranjang = ambil_jumlah_barang_keranjang(pilih, f, l);
  cout << endl << "Detail barang" << endl;
  cout << "Kode barang   : " << pilih << endl;
  cout << "Nama barang   : " << ambil_nama_barang(pilih) << endl;
  cout << "Jumlah barang : " << jumlah_barang_keranjang << endl;
  cout << "? Apakah ingin mengedit data ini (y/t): ";
  cin >> lanjut;

  // Jika y maka akan menjalankan kode didalamnya jika tidak maka akan kembali ke menu utama
  if (tolower(lanjut) == 'y') {
    cout << endl << "! Jika tidak ingin mengganti masukkan \"-1\"" << endl;
    // Memasukkan jumlah barang pada keranjang yg akan diganti
    cout << "? Masukkan jumlah barang: ";
    cin >> jumlah;
    // jika jumlah tidak sama dengan -1 dan 0 maka akan melanjutkan kode didalamnya
    if (jumlah != -1 && jumlah != 0) {
      /*
      Akan menjalankan function tambah_jumlah_barang_keranjang dan set parameter baru dengan true maka jumlah akan direplace dengan jumlah baru
      jika berhasil true maka stok barang yg pada array record akan ditambah jumlah barang sebelumnya dikurangi dari jumlah barang baru
      */
      berhasil = tambah_jumlah_barang_keranjang(true, pilih, jumlah, f, l);
      if (berhasil) barang[pos_barang].stock += jumlah_barang_keranjang - jumlah;
    // jika jumlah sama dengan 0 maka akan menjalankan function hapus_keranjang_barang
    } else if (jumlah == 0) berhasil = hapus_keranjang_barang(pilih, pos_barang, f, l);

    if (berhasil) cout << "Berhasil mengedit keranjang" << endl;
    else cout << "Gagal mengedit keranjang" << endl;
  }
}

//// Procedure menghapus barang dari keranjang
void hapus_keranjang(Keranjang *&f, Keranjang *&l)
{
  int pos_barang, jumlah_barang_keranjang;
  char lanjut;
  bool berhasil, ada;
  string pilih;

  ulang:
    ada = false;
    // Mencetak barang yg ada pada keranjang
    cetak_keranjang(f);
    // Memasukkan kode barang yg ada pada keranjang
    cout << "? Pilih kode barang: ";
    cin >> pilih;
    // Validasi dengan function cek_barang_keranjang dan nilai yg dikembalikan akan diterima ada
    ada = cek_barang_keranjang(pilih, f, l);

  // kebalikan value variabel ada jika menjadi true maka akan dikembalikan ke label ulang
  if (!ada)
  {
    clear();
    cout << "Barang tidak ada" << endl;
    goto ulang;
  }

  // Mencari posisi barang dari kode barang keranjang dengan function yg sudah dijelaskan diatas
  pos_barang = position_barang(pilih);
  // Mengambil jumlah barang pada keranjang dengan function yg sudah dijelaskan diatas
  jumlah_barang_keranjang = ambil_jumlah_barang_keranjang(pilih, f, l);
  cout << endl << "Detail barang" << endl;
  cout << "Kode barang   : " << pilih << endl;
  cout << "Nama barang   : " << ambil_nama_barang(pilih) << endl;
  cout << "Jumlah barang : " << jumlah_barang_keranjang << endl;
  cout << "? Apakah ingin menghapus data ini (y/t): ";
  cin >> lanjut;

  // jika y maka menjalankan kode didalamnya
  if (tolower(lanjut) == 'y') {
    // akan menggunakan function hapus_keranjang_barang yang sudah dijelaskan diatas dan nilai kembali akan diterima ke variabel berhasil
    berhasil = hapus_keranjang_barang(pilih, pos_barang, f, l);
    if (berhasil) cout << "Berhasil menghapus keranjang" << endl;
    else cout << "Gagal menghapus keranjang" << endl;
  }
}

//// Procedure cari detail barang dari array record
void cari_barang()
{
  string pilih;
  int position;
  bool ada;

  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  ulang:
    ada = false;
    // Memasukkan kode barang yg ingin dicari
    cout << "? Kode barang: ";
    getline(cin, pilih);
    // validasi barang dengan function validation_barang
    ada = validation_barang(pilih);
    // mencari posisi barang dengan function position_barang
    position = position_barang(pilih);

  // kebalikan value variabel ada jika menjadi true maka akan dikembalikan ke label ulang
  if (!ada)
  {
    clear();
    cout << "Barang tidak ada" << endl;
    goto ulang;
  }

  // Menampilkan detail barang dari index yg didapat digunakan pada array record barang
  cout << endl << "Detail barang" << endl;
  cout << "Kode barang   : " << pilih << endl;
  cout << "Nama barang   : " << barang[position].nama << endl;
  cout << "Jumlah barang : " << barang[position].stock << endl;
  cout << "Harga barang  : " << barang[position].harga << endl;
}

//// Procedure cetak invoice dari linkedlist checkout
void print_invoice(Checkout *f)
{
  int  n=0;
  cout << ".-------------------------------------------------------------." << endl;
  cout << "|                        Invoice Belanja                      |" << endl;
  cout << "|-------------------------------------------------------------|" << endl;
  cout << "| No      Nama barang     Jumlah       Harga   |     Total    |" << endl;
  while (f != NULL)
  {
    n++;
    cout << "| " << n
        << setw(18) << f->nama
        << setw(11) << f->jumlah
        << setw(14) << f->harga
        << setw(2) << "|"
        << setw(13) << f->subtotal
        << " |" << endl;
    f = f->next;
  }
  cout << "|-------------------------------------------------------------|" << endl;
  cout << "|                   Total                      | " << setw(12) << total << " |" << endl;
  cout << "'-------------------------------------------------------------'" << endl;
}

//// Procedure checkout atau total belanja dari barang yg dimasukkan
void total_belanja(Keranjang *&fk, Keranjang *&lk, Checkout *&fc, Checkout *&lc)
{
  Checkout *barang_checkout;
  double subtotal, harga;
  char lanjut;
  string nama;
  int n=0;

  // jika keranjang kosong tidak maka tidak menjalankan kode didalamnya
  if (lk != nullptr) {
    // Reset total checkout atau belanja
    total = 0;

    // Reset first dan last checkout untuk memulai data pertama lagi
    delete fc;
    delete lc;
    fc = nullptr;
    lc = nullptr;

    // Membuat perulangan first keranjang pada stack keranjang sampai keranjang habis atau null
    while (lk != nullptr)
    {
      // barang_checkout meminta memori yg dibuat checkout lagi karena diakhir while barang_checkout dihapus
      barang_checkout = new Checkout;
      // n hanya untuk memberi tau barang keberapa pada keranjang
      n++;
      // mengambil nama barang pada kode barang keranjang
      nama = ambil_nama_barang(lk->kode);
      // mengambil harga barang pada kode barang keranjang
      harga = ambil_harga_barang(lk->kode);
      // menghitung subtotal dari harga barang dan jumlah barang
      subtotal = hitung_harga_barang(harga, lk->jumlah);
      // menampilkan detail barang
      cout << endl << "Detail barang" << endl;
      cout << "Nama barang            : " << nama << endl;
      cout << "Jumlah barang          : " << lk->jumlah << endl;
      cout << "Harga barang           : " << harga << endl;
      cout << "Subtotal harga barang  : " << subtotal << endl;

      cout << endl << "? Apakah ingin mengchekout barang diatas (y/t): ";
      cin >> lanjut;

      // jika iya maka akan dimasukkan ke checkout atau ke invoice
      if (tolower(lanjut) == 'y') {
        // Memasukkan data tadi ke linkedlist barang_checkout
        barang_checkout->nama = nama;
        barang_checkout->jumlah = lk->jumlah;
        barang_checkout->harga = harga;
        barang_checkout->subtotal = subtotal;
        barang_checkout->next = NULL;
        // Menambah total dengan subtotal yg tadi dihitung
        total += subtotal;

        // jika data first checkout null maka data barang_checkout tadi dimasukkan pada first dan last checkout
        if (fc == nullptr) {
          fc = barang_checkout;
          lc = barang_checkout;
        /*
        jika kondisi diatas tidak terpenuhi maka akan last next menjadi alamat barang_checkout dan
        memasukkan alamat barang_checkout tadi ke last yang berarti data terakhir
        */
        } else {
          lc->next = barang_checkout;
          lc = barang_checkout;
        }
      }

      // mereplace alamat lk menjadi alamat sebelumnya lk dan menghapus alamat setelahnya
      checkout_barang(fk, lk);

      // menghapus isi data linkedlist barang_checkout
      barang_checkout = nullptr;
    }
  }

  // Mencetak isi data linkedlist checkout
  cout << endl;
  print_invoice(fc);

  // Hapus linked list first dan last keranjang karena dianggap selesai belanja maka keranjang kosong
  delete fk;
  delete lk;
  fk = nullptr;
  lk = nullptr;
}

//// Procedure menu user atau fitur user
void menu_user()
{
  f_keranjang = nullptr;
  l_keranjang = nullptr;
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
        if (n_barang >= 1) tambah_keranjang(f_keranjang, l_keranjang);
        else cout << "Barang sekarang tidak tersedia" << endl;
        break;
      case 2:
        if (f_keranjang != nullptr) cetak_keranjang(f_keranjang);
        else cout << "Anda belum berbelanja" << endl;
        break;
      case 3:
        if (f_keranjang != nullptr) edit_keranjang(f_keranjang, l_keranjang);
        else cout << "Anda belum berbelanja" << endl;
        break;
      case 4:
        if (f_keranjang != nullptr) hapus_keranjang(f_keranjang, l_keranjang);
        else cout << "Anda belum berbelanja" << endl;
        break;
      case 5:
        cari_barang();
        break;
      case 6:
        if (f_keranjang != nullptr || f_checkout != nullptr) total_belanja(f_keranjang, l_keranjang, f_checkout, l_checkout);
        else cout << "Anda belum berbelanja" << endl;
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
}
