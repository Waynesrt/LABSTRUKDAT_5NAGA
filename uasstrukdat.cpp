#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits>
using namespace std;

struct Produk {
    int id;
    string nama;
    string kategori;
    int harga;
};

struct KeranjangItem {
    int id;
    string nama;
    int jumlah;
    int totalHarga;
};

struct Transaksi {
    int idTransaksi;
    vector<KeranjangItem> items;
    int totalBiaya;
};

vector<Produk> produk = {
    {1, "Smartphone Samsung Galaxy S23", "Elektronik", 12000000},
    {2, "Laptop ASUS ROG Zephyrus G14", "Elektronik", 25000000},
    {3, "TV LED LG 43 Inch", "Elektronik", 6500000},
    {4, "Earbuds Apple AirPods Pro", "Elektronik", 3500000},
    {5, "Kamera DSLR Canon EOS 90D", "Elektronik", 17000000},
    {6, "Sepeda MTB Polygon", "Fitness", 5000000},
    {7, "Dumbbell 5kg", "Fitness", 200000},
    {8, "Matras Yoga", "Fitness", 250000},
    {9, "Mesin Elliptical", "Fitness", 7500000},
    {10, "Resistance Band", "Fitness", 100000},
    {11, "Serum Wajah Vitamin C", "Kecantikan", 150000},
    {12, "Masker Wajah Aloe Vera", "Kecantikan", 75000},
    {13, "Lipstik Matte L'Oréal", "Kecantikan", 120000},
    {14, "Parfum Chanel", "Kecantikan", 2500000},
    {15, "Sabun Cuci Muka Himalaya", "Kecantikan", 35000},
    {16, "Roti Tawar Serba Roti", "Konsumsi", 15000},
    {17, "Kopi Arabica 100g", "Konsumsi", 50000},
    {18, "Mie Instan", "Konsumsi", 5000},
    {19, "Susu UHT Indomilk 1 Liter", "Konsumsi", 18000},
    {20, "Teh Kotak Sosro 500ml", "Konsumsi", 7500}
};

vector<KeranjangItem> keranjang;
vector<Transaksi> riwayat;
int idTransaksiCounter = 1;

// Fungsi untuk menampilkan daftar produk
void tampilkanProduk() {
    cout << "\nDaftar Produk:\n";
    for (const auto& p : produk) {
        cout << "ID: " << p.id << ", Nama: " << p.nama << ", Kategori: " << p.kategori << ", Harga: Rp." << p.harga << endl;
    }
}

// Fungsi untuk menambahkan produk ke keranjang
void tambahKeKeranjang(int idProduk, int jumlah) {
    auto it = find_if(produk.begin(), produk.end(), [idProduk](const Produk& p) {
        return p.id == idProduk;
    });
    if (it != produk.end()) {
        int totalHarga = it->harga * jumlah;
        keranjang.push_back({idProduk, it->nama, jumlah, totalHarga});
        cout << "Produk berhasil ditambahkan ke keranjang.\n";
    } else {
        cout << "Produk dengan ID tersebut tidak ditemukan.\n";
    }
}

// Fungsi untuk melihat isi keranjang
void lihatKeranjang() {
    if (keranjang.empty()) {
        cout << "\nKeranjang Anda kosong.\n";
        return;
    }

    cout << "\nIsi Keranjang:\n";
    for (const auto& item : keranjang) {
        cout << "ID: " << item.id << ", Nama: " << item.nama << ", Jumlah: " << item.jumlah << ", Total Harga: Rp." << item.totalHarga << endl;
    }
}

// Fungsi untuk menghapus produk dari keranjang
void hapusDariKeranjang(int idProduk) {
    auto it = remove_if(keranjang.begin(), keranjang.end(), [idProduk](const KeranjangItem& item) {
        return item.id == idProduk;
    });

    if (it != keranjang.end()) {
        keranjang.erase(it, keranjang.end());
        cout << "Produk berhasil dihapus dari keranjang.\n";
    } else {
        cout << "Produk dengan ID tersebut tidak ditemukan di keranjang.\n";
    }
}

// Fungsi untuk melakukan checkout
void checkout() {
    if (keranjang.empty()) {
        cout << "\nKeranjang kosong, tidak dapat melakukan checkout.\n";
        return;
    }

    int totalBiaya = 0;
    for (const auto& item : keranjang) {
        totalBiaya += item.totalHarga;
    }

    riwayat.push_back({idTransaksiCounter++, keranjang, totalBiaya});
    keranjang.clear();

    cout << "\nCheckout berhasil! Total biaya: Rp." << totalBiaya << endl;
}

// Fungsi untuk melihat riwayat transaksi
void lihatRiwayat() {
    if (riwayat.empty()) {
        cout << "\nTidak ada riwayat transaksi.\n";
        return;
    }

    cout << "\nRiwayat Transaksi:\n";
    for (const auto& transaksi : riwayat) {
        cout << "ID Transaksi: " << transaksi.idTransaksi << ", Total Biaya: Rp." << transaksi.totalBiaya << endl;
    }
}

int main() {
    int pilihan;
    do {
        cout << "\nMenu:\n";
        cout << "1. Tampilkan Produk\n";
        cout << "2. Tambah ke Keranjang\n";
        cout << "3. Lihat Keranjang\n";
        cout << "4. Hapus dari Keranjang\n";
        cout << "5. Checkout\n";
        cout << "6. Lihat Riwayat Transaksi\n";
        cout << "0. Keluar\n";
        cout << "Pilih opsi: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tampilkanProduk();
                break;
            case 2: {
                int idProduk, jumlah;
                cout << "Masukkan ID Produk: ";
                cin >> idProduk;
                cout << "Masukkan Jumlah: ";
                cin >> jumlah;
                tambahKeKeranjang(idProduk, jumlah);
                break;
            }
            case 3:
                lihatKeranjang();
                break;
            case 4: {
                int idProduk;
                cout << "Masukkan ID Produk untuk dihapus: ";
                cin >> idProduk;
                hapusDariKeranjang(idProduk);
                break;
            }
            case 5:
                checkout();
                break;
            case 6:
                lihatRiwayat();
                break;
            case 0:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
    } while (pilihan != 0);

    return 0;
}
