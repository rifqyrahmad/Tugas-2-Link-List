#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

struct Buku {
    string judul;
    int harga;
    Buku* next;
    Buku* prev;
};

Buku* head = nullptr;
Buku* tail = nullptr;

void header() {
    cout << "\n====================================\n";
    cout << "    Sistem Manajemen Buku Toko\n";
    cout << "      \"Lingkaran Literasi\"\n";
    cout << "====================================\n";
}

/**
 * Menambah buku di belakang list
 */
void tambahBuku(const string& judul, int harga) {
    Buku* bukuBaru = new Buku{judul, harga, nullptr, nullptr};
    if (!head) head = tail = bukuBaru;
    else {
        tail->next = bukuBaru;
        bukuBaru->prev = tail;
        tail = bukuBaru;
    }
    cout << "\nBuku berhasil ditambahkan!\n";
}

// Menampilkan seluruh buku
void tampilkanBuku() {
    if (!head) {
        cout << "\nBelum ada data buku.\n";
        return;
    }

    cout << "\nDaftar Buku Tersimpan:\n";
    cout << left << setw(30) << "Judul Buku" << "Harga\n";
    cout << string(40, '-') << endl;

    Buku* current = head;
    while (current) {
        cout << left << setw(30) << current->judul << current->harga << endl;
        current = current->next;
    }
}

// Mencari buku berdasarkan judul
void cariBuku(const string& keyword) {
    Buku* current = head;
    while (current) {
        if (current->judul == keyword) {
            cout << "\nBuku ditemukan!\n";
            cout << "Judul: " << current->judul << "\nHarga: " << current->harga << endl;
            return;
        }
        current = current->next;
    }
    cout << "\nBuku tidak ditemukan.\n";
}

// Menyisipkan buku di depan
void sisipDepan(const string& judul, int harga) {
    Buku* bukuBaru = new Buku{judul, harga, head, nullptr};
    if (head) head->prev = bukuBaru;
    else tail = bukuBaru;
    head = bukuBaru;
    cout << "\nBuku disisipkan di depan.\n";
}

// Menyisipkan buku di belakang (implementasi langsung)
void sisipBelakang(const string& judul, int harga) {
    Buku* bukuBaru = new Buku{judul, harga, nullptr, tail};
    if (!head) {
        head = tail = bukuBaru;
    } else {
        tail->next = bukuBaru;
        tail = bukuBaru;
    }
    cout << "\nBuku disisipkan di belakang.\n";
}

// Menyisipkan buku di tengah (setelah judul tertentu)
void sisipTengah(const string& judulBaru, int harga, const string& setelahJudul) {
    Buku* current = head;
    while (current && current->judul != setelahJudul) {
        current = current->next;
    }

    if (!current) {
        cout << "\nJudul acuan tidak ditemukan.\n";
        return;
    }

    Buku* bukuBaru = new Buku{judulBaru, harga, current->next, current};
    if (!current->next) tail = bukuBaru;
    else current->next->prev = bukuBaru;
    current->next = bukuBaru;

    cout << "\nBuku disisipkan setelah \"" << setelahJudul << "\".\n";
}

// Menghapus buku berdasarkan judul
void hapusBuku(const string& judul) {
    Buku* current = head;
    while (current && current->judul != judul) {
        current = current->next;
    }

    if (!current) {
        cout << "\nBuku tidak ditemukan.\n";
        return;
    }

    if (current == head) {
        head = current->next;
        if (head) head->prev = nullptr;
    }
    if (current == tail) {
        tail = current->prev;
        if (tail) tail->next = nullptr;
    }
    if (current->prev) current->prev->next = current->next;
    if (current->next) current->next->prev = current->prev;

    delete current;
    cout << "\nBuku berhasil dihapus.\n";
}

void menu() {
    int pilihan;
    do {
        header();
        cout << "1. Tambahkan Buku\n";
        cout << "2. Tampilkan Semua Buku\n";
        cout << "3. Cari Buku\n";
        cout << "4. Sisip Buku (Depan/Tengah/Belakang)\n";
        cout << "5. Hapus Buku\n";
        cout << "6. Keluar\n";
        cout << "------------------------------------\n";
        cout << "Pilih menu [1-6]: ";

        // Validasi input angka
        while (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid! Masukkan angka: ";
        }
        cin.ignore();

        string judul, setelahJudul;
        int harga;

        switch (pilihan) {
            case 1:
                cout << "\nMasukkan Judul Buku: ";
                getline(cin, judul);
                cout << "Masukkan Harga Buku: ";
                while (!(cin >> harga)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Input tidak valid! Masukkan harga: ";
                }
                cin.ignore();
                tambahBuku(judul, harga);
                break;
            case 2:
                tampilkanBuku();
                break;
            case 3:
                cout << "\nMasukkan Judul Buku yang dicari: ";
                getline(cin, judul);
                cariBuku(judul);
                break;
            case 4: {
                int sub;
                cout << "\n1. Depan\n2. Tengah\n3. Belakang\nPilih posisi: ";
                while (!(cin >> sub)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Input tidak valid! Masukkan angka: ";
                }
                cin.ignore();
                cout << "Masukkan Judul Buku: ";
                getline(cin, judul);
                cout << "Masukkan Harga Buku: ";
                while (!(cin >> harga)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Input tidak valid! Masukkan harga: ";
                }
                cin.ignore();
                if (sub == 1) sisipDepan(judul, harga);
                else if (sub == 2) {
                    cout << "Disisipkan setelah judul: ";
                    getline(cin, setelahJudul);
                    sisipTengah(judul, harga, setelahJudul);
                } else if (sub == 3) sisipBelakang(judul, harga);
                else cout << "\nPilihan tidak valid.\n";
                break;
            }
            case 5:
                cout << "\nMasukkan Judul Buku yang ingin dihapus: ";
                getline(cin, judul);
                hapusBuku(judul);
                break;
            case 6:
                cout << "\nTerima kasih telah menggunakan sistem!\n";
                break;
            default:
                cout << "\nPilihan tidak valid.\n";
        }

        cout << "\nTekan ENTER untuk melanjutkan...";
        cin.get();
    } while (pilihan != 6);
}

int main() {
    menu();
    return 0;
}
