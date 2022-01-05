#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

// barang
typedef struct{
	string kode_brg, nama_brg;
	float harga_brg;
  int stok_brg;
} Barang;

typedef Barang arr_barang[20];
arr_barang barang;

// pengiriman outlet
typedef struct{
	string kode_pengiriman, nama_outlet, kode_brg_pengiriman;
  int jumlah_brg;
} Pengiriman;

typedef Pengiriman arr_pengiriman[20];
arr_pengiriman pengiriman;
int n, z, i, pil;

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
    cout << endl << "Press <Enter> to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin.get();
  #endif
}

void tambah_barang(arr_barang &X){
	string barang_baru;
	cout << "Tambah barang gudang" << endl;
	ulang:
    cout << "Masukan kode barang > "; cin >> barang_baru;
    for(i=1;i<=n;i++){
      if(X[i].kode_brg == barang_baru){
        cout << "Kode sudah digunakan ulangi mengisi!" << endl;
        goto ulang;
      }
    }
  n++;
  X[n].kode_brg = barang_baru;
  cout << "Masukan nama barang  : ";cin >> X[n].nama_brg;
  cout << "Masukan harga barang : ";cin >> X[n].harga_brg;
  cout << "Masukan stok barang  : ";cin >> X[n].stok_brg;
  cout << "Tambah data berhasil" << endl;
}

void cetak_barang(arr_barang X){
	cout << "Daftar Barang di gudang saat ini" << endl;
	cout << "-------------------------------------------" << endl;
	cout << "No	Kode	Nama	Harga	Stok" << endl;
	cout << "-------------------------------------------" << endl;
	for(i=1;i<=n;i++){
    cout << setw(2) << i
        << setw(8) << X[i].kode_brg
        << setw(10) << X[i].nama_brg
        << setw(8) << X[i].harga_brg
        << setw(6) << X[i].stok_brg << endl;
  }
  cout << "-------------------------------------------" << endl;
}

void edit_barang(arr_barang&X){
	string edit, nama;
  int pos, stok;
  float harga;
  bool ada=false;
  char lanjut;

  cout << "Mengedit barang gudang";
	cetak_barang(X);
	cout << "Masukan kode barang yang akan di edit > "; cin >> edit;

	for(i=1;i<=n;i++){
		if(X[i].kode_brg==edit){
      pos=i;
      ada=true;
    }
	}

	if(ada){
		cout << "Detail barang yang diedit " << endl;
    cout << "Kode buku : " << edit << endl;
		cout << "Nama barang :" << X[pos].nama_brg << endl;
		cout << "Harga barang : " << X[pos].harga_brg << endl;
		cout << "Stok saat ini : " << X[pos].stok_brg << endl;
		cout << "Yakin ingin mengedit barang (y/t) > "; cin >> lanjut;
		if (tolower(lanjut) == 'y'){
      cout << "Jika nama barang tidak diganti masukkan \"-\"" << endl;
      cout << "Nama barang baru > "; cin >> nama;
      if(nama != "-") X[pos].nama_brg = nama;

      cout << endl << "Jika harga barang tidak diganti masukkan \"-0\"" << endl;
      cout << "Harga barang baru > "; cin >> harga;
      if(harga != -0) X[pos].harga_brg = harga;

      cout << endl << "Jika jumlah stok tidak diganti masukkan \"-0\"" << endl;
      cout << "Jumlah stok baru > "; cin >> stok;
      if(stok != -0) X[pos].stok_brg = stok;
			cout << "Edit barang berhasil" << endl;
		}
  }else {
    cout << "Kode barang " << edit << " tidak ditemukan, editing gagal" << endl;
  }
}

void hapus_barang(arr_barang &X){
	int hapus;
  char lanjut;

	cout << "Menghapus data barang" << endl;
  cetak_barang(X);
	ulang:
    cout<<"masukan nomor record barang yang di hapus > ";cin >> hapus;

    if((hapus<1)||(hapus>n)) {
      cout << "Nomor record tidak valid,ulangi!" << endl;
      goto ulang;
    }

  cout << "Yakin akan di hapus (y/t) > "; cin >> lanjut;
  if(tolower(lanjut) == 'y'){
    cout << "data sudah di hapus" << endl;
    for(i=hapus;i<n;i++) X[i]=X[i+1];
    n--;
  }else{
    cout << "Data tidak jadi dihapus" << endl;
  }
}

void cetak_pengiriman(arr_pengiriman &X){
  cout << "Daftar pengiriman barang saat ini" << endl;
	cout << "-------------------------------------------" << endl;
	cout << "No	Kode	Nama	Barang	Jumlah" << endl;
	cout << "-------------------------------------------" << endl;
	for(i=1;i<=z;i++){
    cout << setw(2) << i
        << setw(8) << X[i].kode_pengiriman
        << setw(10) << X[i].nama_outlet
        << setw(8) << X[i].kode_brg_pengiriman
        << setw(6) << X[i].jumlah_brg << endl;
  }
  cout << "-------------------------------------------" << endl;
}

void pengiriman_barang(arr_pengiriman &X, arr_barang &Y){
  string kirim, nama, kode;
  int jum, pos;
  bool ada=false;

  cout << "Pengiriman barang" << endl;
  cetak_barang(Y);
  cout << "Masukan kode barang yang akan dikirim > "; cin >> kirim;
  for(i=1;i<=n;i++){
    if(Y[i].kode_brg == kirim) {
      ada=true;
      pos=i;
    }
  }

  if(ada){
    cout << "Nama outlet > "; cin >> nama;
    cout << "Jumlah pengiriman barang > "; cin >> jum;
    if(Y[pos].stok_brg >= jum) {
      kode = nama.substr(0, 2) + kirim;
      z++;
      X[z].kode_pengiriman = kode;
      X[z].nama_outlet = nama;
      X[z].kode_brg_pengiriman = kirim;
      X[z].jumlah_brg = jum;

      cout << "Pengiriman barang berhasil" << endl;
      cout << "Total pembayaran barang yang dikirim : " << jum*Y[pos].harga_brg << endl;
    }else {
      cout << "Stok tidak cukup silahkan transaksi ulang" << endl;
    }
  }else {
    cout << "Barang yang dibeli tidak ada" << endl;
  }
}

int main(){
	do{
		clear();
		cout << "1. Tambah barang" << endl;
		cout << "2. Cetak barang" << endl;
		cout << "3. Edit barang" << endl;
		cout << "4. Hapus barang" << endl;
		cout << "5. Pengiriman barang" << endl;
		cout << "6. Cetak pengiriman" << endl;
		cout << "0. Keluar" << endl;
		cout << "Pilih menu > ";cin >> pil;

		switch(pil){
			case 1:
        if(n>20) cout << "Barang gudang sudah penuh" << endl;
        else tambah_barang(barang);
        break;
			case 2:
        if(n==0) cout << "Barang gudang masih kosong" << endl;
        else cetak_barang(barang);
        break;
			case 3:
        if(n==0) cout << "Barang gudang masih kosong" << endl;
        else edit_barang(barang);
        break;
			case 4:
        if(n==0) cout << "Barang gudang masih kosong" << endl;
        else hapus_barang(barang);
        break;
			case 5:
        if(n==0 && z>20) cout << "Barang gudang masih kosong atau pengiriman sudah penuh" << endl;
        else pengiriman_barang(pengiriman, barang);
        break;
			case 6:
        if(z==0) cout << "Pengiriman masih kosong" << endl;
        else cetak_pengiriman(pengiriman);
        break;
			case 0:
        cout << "Terima kasih sudah menggunakan program" << endl;
        break;
			default:
        cout << "Menu pilihan anda tidak ada" << endl;
        break;
		}
		pause();
	}while(pil!=0);
}
