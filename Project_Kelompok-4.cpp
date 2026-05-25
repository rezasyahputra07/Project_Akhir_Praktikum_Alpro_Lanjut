/*
Kelompok 4 : Nadhir Rifqi       (123250019)
             Fahreza Syahputra  (123250006)
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

struct Kapal {
    string id_kapal;
    string nama_kapal;
    string nama_kontainer;
    string jenis_kontainer;
    float berat_ton;
};

Kapal listData[100];
int jumlahData = 0;

string daftarFile[50];
int jumlahFile = 0;

//---------------------------------------------- FILE -------------------------------------------------//
void loadDaftarFile() {
    ifstream f("data_utama.txt");
    if (!f) return;
    jumlahFile = 0;
    string nama;
    while (getline(f, nama) && jumlahFile < 50) {
        if (!nama.empty()) daftarFile[jumlahFile++] = nama;
    }
    f.close();
}

void catatanFile(string namaFile) {
    // cek duplikat agar tidak tercatat 2 kali
    for(int i=0; i<jumlahFile; i++) if(daftarFile[i] == namaFile) return;
    if(jumlahFile < 50) {
        daftarFile[jumlahFile++] = namaFile;
        ofstream f("data_utama.txt", ios::app);
        f << namaFile << endl;
        f.close();
    }
}

void tampilkanDaftarFile() {
    cout << "\n===== DAFTAR FILE TERSEDIA =====\n";
    if (jumlahFile == 0) cout << "Belum ada file yang tersimpan.\n";
    else {
        for (int i = 0; i < jumlahFile; i++) cout << (i + 1) << ". " << daftarFile[i] << "\n";
    }
    cout << "================================\n";
}

bool bacaFile(string nama) {
    ifstream file(nama.c_str());
    if (!file) return false;
    jumlahData = 0;
    while (file >> listData[jumlahData].id_kapal && jumlahData < 100) {
        file.ignore();
        getline(file, listData[jumlahData].nama_kapal);
        getline(file, listData[jumlahData].nama_kontainer);
        getline(file, listData[jumlahData].jenis_kontainer);
        file >> listData[jumlahData].berat_ton;
        file.ignore();
        jumlahData++;
    }
    file.close();
    return true;
}

void tulisFile(string nama) {
    ofstream f(nama.c_str());
    for (int i = 0; i < jumlahData; i++) {
        f << listData[i].id_kapal << endl;
        f << listData[i].nama_kapal << endl;
        f << listData[i].nama_kontainer << endl;
        f << listData[i].jenis_kontainer << endl;
        f << listData[i].berat_ton << endl;
    }
    f.close();
}

bool konfirmasiSimpan() {
    char c;
    cout << "\nSimpan perubahan ke file? (y/t): "; cin >> c;
    return (c == 'y' || c == 'Y');
}

//------------------------------------------------------------------------------------------------------//
void inputData() {
    cout << "\n----- MENU INPUT DATA -----\n";
    int n;
    cout << "Banyak data kargo yang ingin diinput : "; cin >> n;

    // error handling
    if (n <= 0 || n > 100) { 
        cout << "Jumlah tidak valid (1-100)!\n"; 
        return; 
    }

    Kapal temp[100];
    for (int i = 0; i < n; i++) {
        cout << "\nData ke-" << i + 1 << endl;
        cout << "ID Kapal         : "; cin >> temp[i].id_kapal; 
        cin.ignore();
        cout << "Nama Kapal       : "; getline(cin, temp[i].nama_kapal);
        cout << "Nama Kontainer   : "; getline(cin, temp[i].nama_kontainer);
        cout << "Jenis Kontainer  : "; getline(cin, temp[i].jenis_kontainer);
        cout << "Berat (Ton)      : "; cin >> temp[i].berat_ton;
        cin.ignore();
    }

    char simpan;
    cout << "\nApakah data sudah benar? Simpan ke file? (y/t) : "; cin >> simpan;
    if (simpan == 'y' || simpan == 'Y') {
        string namaFile;
        cout << "Masukkan nama file (contoh: kargo.txt) : "; cin >> namaFile;
        
        ofstream k(namaFile.c_str());
        for (int i = 0; i < n; i++) {
            k << temp[i].id_kapal << endl;
            k << temp[i].nama_kapal << endl;
            k << temp[i].nama_kontainer << endl;
            k << temp[i].jenis_kontainer << endl;
            k << temp[i].berat_ton << endl;
        }
        k.close();
        catatanFile(namaFile);
    cout << "Berhasil! Data telah disimpan di " << namaFile << "\n";
    } else {
        cout << "Data tidak disimpan (bisa input ulang).\n";
    }
}

void tampilData() {
    tampilkanDaftarFile();
    if (jumlahFile == 0) return;
    
    cout << "\n----- MENU TAMPIL DATA -----\n";
    string nama;
    cout << "Masukkan nama file yang ingin ditampilkan: "; cin >> nama;
    
    // error handling
    if (!bacaFile(nama)) {
        cout << " File tidak ditemukan atau kosong!\n";
        return;
    }

    cout << "\n===== ISI FILE : " << nama << " =====\n";
    for (int i = 0; i < jumlahData; i++) {
        cout << "ID: " << listData[i].id_kapal << "\nKapal: " << listData[i].nama_kapal
             << "\nKontainer: " << listData[i].nama_kontainer << "\nJenis: " << listData[i].jenis_kontainer
             << "\nBerat: " << listData[i].berat_ton << " Ton\n------------------------\n";
    }
}

//-------------------------------------------- SEARCHING ----------------------------------------------//
void sequentialSearch() {
    string namaFile, cari;
    int pilihan;
    
    tampilkanDaftarFile();
    if (jumlahFile == 0) return;
    cout << "\n----- SEQUENTIAL SEARCH -----\n";
    cout << "Masukkan nama file yang ingin dicari : "; 
    cin >> namaFile;

    // error handling
    ifstream inFile(namaFile.c_str());
    if (!inFile) {
        cout << "File tidak ditemukan!\n";
        return;
    }

    jumlahData = 0;
    while (inFile >> listData[jumlahData].id_kapal) {
        inFile.ignore();

        getline(inFile, listData[jumlahData].nama_kapal);
        getline(inFile, listData[jumlahData].nama_kontainer);
        getline(inFile, listData[jumlahData].jenis_kontainer);
        inFile >> listData[jumlahData].berat_ton;
        inFile.ignore();
        jumlahData++;
    }
    inFile.close();
    
    cout << "Cari berdasarkan:\n1. ID Kapal\n2. Nama Kapal\n3. Nama Kontainer\n4. Jenis Kontainer\nPilihan: ";
    cin >> pilihan;
    cout << "Masukkan kata kunci yang mau dicari: "; 
    cin.ignore(); 

    getline(cin, cari);

    bool ketemu = false;
    cout << "\n----- HASIL PENCARIAN (SEQUENTIAL) -----\n";
    for (int i = 0; i < jumlahData; i++) {
        bool cocok = false;
        if (pilihan == 1 && listData[i].id_kapal == cari) cocok = true;
        else if (pilihan == 2 && listData[i].nama_kapal == cari) cocok = true;
        else if (pilihan == 3 && listData[i].nama_kontainer == cari) cocok = true;
        else if (pilihan == 4 && listData[i].jenis_kontainer == cari) cocok = true;

        if (cocok) {
            cout << "ID         : " << listData[i].id_kapal<<endl;
            cout << "Kapal      : " << listData[i].nama_kapal << endl;
            cout << "Kontainer  : " << listData[i].nama_kontainer << endl;
            cout << "Jenis      : " << listData[i].jenis_kontainer << endl;
            cout << "Berat      : " << listData[i].berat_ton << " Ton" << endl;
            cout << "----------------------------------" << endl;
            ketemu = true;
        }
    }
    if (!ketemu) cout << "Data tidak ditemukan!\n";
}

void binarySearch() {
    string namaFile, cari;
    int pilihan;
    
    tampilkanDaftarFile();
    if (jumlahFile == 0) return;
    cout << "\n----- BINARY SEARCH -----\n";
    cout << "Masukkan nama file yang ingin dicari: "; 
    cin >> namaFile;

    // error handling
    ifstream inFile(namaFile.c_str());
    if (!inFile) {
        cout << "File tidak ditemukan!\n";
        return;
    }

    jumlahData = 0;
    while (inFile >> listData[jumlahData].id_kapal) {
        inFile.ignore();

        getline(inFile, listData[jumlahData].nama_kapal);
        getline(inFile, listData[jumlahData].nama_kontainer);
        getline(inFile, listData[jumlahData].jenis_kontainer);
        inFile >> listData[jumlahData].berat_ton;
        inFile.ignore();
        jumlahData++;
    }
    inFile.close();

    cout << "Cari berdasarkan:\n1. ID Kapal\n2. Nama Kapal\n3. Nama Kontainer\n4. Jenis Kontainer\nPilihan: ";
    cin >> pilihan;
    cout << "Masukkan kata kunci yang mau dicari: "; 
    cin.ignore(); 
    getline(cin, cari);

    for (int i = 0; i < jumlahData - 1; i++) {
        for (int j = 0; j < jumlahData - i - 1; j++) {
            bool swap = false;
            if (pilihan == 1 && listData[j].id_kapal > listData[j+1].id_kapal) swap = true;
            else if (pilihan == 2 && listData[j].nama_kapal > listData[j+1].nama_kapal) swap = true;
            else if (pilihan == 3 && listData[j].nama_kontainer > listData[j+1].nama_kontainer) swap = true;
            else if (pilihan == 4 && listData[j].jenis_kontainer > listData[j+1].jenis_kontainer) swap = true;

            if (swap) {
                Kapal temp = listData[j];
                listData[j] = listData[j+1];
                listData[j+1] = temp;
            }
        }
    }

    int awal = 0;
    int akhir = jumlahData - 1;
    int tengah;
    bool ketemu = false;
    cout << "\n----- HASIL PENCARIAN (BINARY) -----\n";
    while (awal <= akhir && !ketemu) {
        tengah = (awal + akhir) / 2;
        
        string nilaiTengah;
        if (pilihan == 1) nilaiTengah = listData[tengah].id_kapal;
        else if (pilihan == 2) nilaiTengah = listData[tengah].nama_kapal;
        else if (pilihan == 3) nilaiTengah = listData[tengah].nama_kontainer;
        else if (pilihan == 4) nilaiTengah = listData[tengah].jenis_kontainer;

        if (nilaiTengah == cari) {
            ketemu = true;
            cout << "ID         : " << listData[tengah].id_kapal<<endl;
            cout << "Kapal      : " << listData[tengah].nama_kapal << endl;
            cout << "Kontainer  : " << listData[tengah].nama_kontainer << endl;
            cout << "Jenis      : " << listData[tengah].jenis_kontainer << endl;
            cout << "Berat      : " << listData[tengah].berat_ton << " Ton" << endl;
            cout << "----------------------------------" << endl;
        }else if (cari < nilaiTengah) {
            akhir = tengah - 1; 
        }else{
            awal = tengah + 1; 
        }
    }
    if (!ketemu) cout << "Data dengan kata kunci " << cari << " tidak ditemukan.\n";
}

void searching() {
    int pilihSearch;
    char ulangSearch;
        do {
            system("cls");
            cout << "Menu Searching:\n";
            cout << "======================\n";
            cout << "1. Sequential Search\n";
            cout << "2. Binary Search\n";
            cout << "3. Kembali ke menu utama\n";
            cout << "======================\n";
            cout << "Pilih : ";
            cin >> pilihSearch;
            cout << endl;

            switch (pilihSearch) {
                case 1 :    
                        system("cls");
                        sequentialSearch();
                        cout << "\nUlang searching? (y/t) : ";
                        cin >> ulangSearch;
                        break;

                case 2 :   
                        system("cls");
                        binarySearch();
                        cout << "\nUlang searching? (y/t) : ";
                        cin >> ulangSearch;
                        break;

                case 3 :    
                        ulangSearch = 't';
                        break;

                default :   
                        cout << "Pilihan tidak ada, ulang (y/t) : ";
                        cin >> ulangSearch;
                        break;
            }
        } while (ulangSearch == 'y' || ulangSearch == 'Y');
}

//--------------------------------------------- SORTING ----------------------------------------------//
void bubbleSort() {
    tampilkanDaftarFile();
    if (jumlahFile == 0) return;
    
    cout << "\n----- BUBBLE SORT (by Nama Kapal) -----\n";
    string nama;
    cout << "Pilih file untuk sorting : "; cin >> nama;

    // error handling
    if (!bacaFile(nama)) { 
        cout << "File tidak ditemukan!\n"; 
        return; 
    } else if (jumlahData < 2) { 
        cout << "Data terlalu sedikit untuk sorting!\n"; 
        return; 
    }

    cout << "\n Data SEBELUM sorting :\n";
    for (int i = 0; i < jumlahData; i++) cout << (i + 1) << ". " << listData[i].nama_kapal << " | " << listData[i].berat_ton << " Ton" << endl;

    for (int i = 0; i < jumlahData - 1; i++) {
        for (int j = 0; j < jumlahData - i - 1; j++) {
            if (listData[j].nama_kapal > listData[j + 1].nama_kapal) {
                Kapal t = listData[j]; listData[j] = listData[j + 1]; listData[j + 1] = t;
            }
        }
    }

    cout << "\n========== Data SESUDAH sorting : ==========\n";
    for (int i = 0; i < jumlahData; i++) cout << (i + 1) << ". " << listData[i].nama_kapal << " | " << listData[i].berat_ton << " Ton" << endl;

    if (konfirmasiSimpan()) {
        string fBaru; 
        cout << "Nama file baru : "; cin >> fBaru;
        tulisFile(fBaru);
        catatanFile(fBaru);
        cout << "Berhasil! Data disimpan di " << fBaru << "\n";
    }
}

void selectionSort() {
    tampilkanDaftarFile();
    if (jumlahFile == 0) return;
    
    cout << "\n----- SELECTION SORT (by Berat Ton) -----\n";
    string nama;
    cout << "Pilih file untuk sorting: "; cin >> nama;

    // error handling
    if (!bacaFile(nama)) { 
        cout << "File tidak ditemukan!\n"; 
        return; 
    } else if (jumlahData < 2) { 
        cout << "Data terlalu sedikit untuk sorting!\n"; 
        return; 
    }

    cout << "\n Data SEBELUM sorting: \n";
    for (int i = 0; i < jumlahData; i++) cout << (i + 1) << ". " << listData[i].nama_kapal << " | " << listData[i].berat_ton << " Ton\n";

    for (int i = 0; i < jumlahData - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < jumlahData; j++) {
            if (listData[j].berat_ton < listData[minIdx].berat_ton) minIdx = j;
        }
        if (minIdx != i) { Kapal t = listData[i]; listData[i] = listData[minIdx]; listData[minIdx] = t; }
    }

    cout << "\n----- Data SESUDAH sorting : -----\n";
    for (int i = 0; i < jumlahData; i++) cout << (i + 1) << ". " << listData[i].nama_kapal << " | " << listData[i].berat_ton << " Ton\n";

    if (konfirmasiSimpan()) {
        string fBaru; 
        cout << "Nama file baru : "; cin >> fBaru;
        tulisFile(fBaru);
        catatanFile(fBaru);
        cout << "Berhasil! Data disimpan di " << fBaru << "\n";
    }
}

void sorting(){
    int pilihSort;
    char ulangSort;
        do {
            system("cls");
            cout << "Menu Sorting:\n";
            cout << "======================\n";
            cout << "1. Bubble Sort\n";
            cout << "2. Selection Sort\n";
            cout << "3. Kembali ke menu utama\n";
            cout << "======================\n";
            cout << "Pilih : ";
            cin >> pilihSort;
            cout << endl;

                switch (pilihSort) {
                    case 1 :    
                        system("cls");
                        bubbleSort();
                        cout << "\nUlang sorting? (y/t) : ";
                        cin >> ulangSort;
                        break;
                    
                    case 2 :    
                        system("cls");
                        selectionSort();
                        cout << "\nUlang sorting? (y/t) : ";
                        cin >> ulangSort;
                        break;

                    case 3 :   
                        ulangSort = 't';
                        break;

                    default :  
                        cout << "Pilihan tidak ada, ulang (y/t) : ";
                        cin >> ulangSort;
                        break;
                }
        } while (ulangSort == 'y' || ulangSort == 'Y');
}

//--------------------------------------------- OPERASI FILE ----------------------------------------------//
void updateData() {
    tampilkanDaftarFile();
    if (jumlahFile == 0) return;
    
    cout << "\n----- UPDATE DATA -----\n";
    string nama;
    cout << "Pilih file yang ingin diupdate : "; cin >> nama;

    // error handling
    if (!bacaFile(nama)) { 
        cout << "File tidak ditemukan!\n"; 
        return; 
    }

    string idCari;
    cout << "Masukkan ID Kapal yang ingin diupdate : "; cin >> idCari;
    int idx = -1;
    for (int i = 0; i < jumlahData; i++) {
        if (listData[i].id_kapal == idCari) { 
            idx = i; 
            break; 
        }
    }
    if (idx == -1) { 
        cout << "ID Kapal tidak ditemukan!\n"; 
        return; 
    }

    cout << "\n Update data untuk ID : " << listData[idx].id_kapal << "\n";
    cout << "Nama Kapal Baru         : "; cin.ignore(); getline(cin, listData[idx].nama_kapal);
    cout << "Nama Kontainer Baru     : "; getline(cin, listData[idx].nama_kontainer);
    cout << "Jenis Kontainer Baru    : "; getline(cin, listData[idx].jenis_kontainer);
    cout << "Berat Baru              : "; cin >> listData[idx].berat_ton;

    cout << "\n Data berhasil diupdate di memori.\n";
    if (konfirmasiSimpan()) {
        tulisFile(nama);
        cout << "Perubahan disimpan ke " << nama << "\n";
    }
}

void deleteData() {
    tampilkanDaftarFile();
    if (jumlahFile == 0) return;
    
    cout << "\n----- DELETE DATA -----\n";
    string nama;
    cout << "Pilih file yang ingin dihapus datanya : "; cin >> nama;

    // error handling
    if (!bacaFile(nama)) { 
        cout << "File tidak ditemukan!\n"; 
        return; 
    }

    string idHapus;
    cout << "Masukkan ID Kapal yang ingin dihapus : "; cin >> idHapus;
    int idx = -1;
    for (int i = 0; i < jumlahData; i++) {
        if (listData[i].id_kapal == idHapus) { 
            idx = i; 
            break; 
        }
    }
    if (idx == -1) { 
        cout << "ID Kapal tidak ditemukan!\n"; 
        return; 
    }

    cout << "Hapus data : " << listData[idx].id_kapal << " - " << listData[idx].nama_kapal << "? (y/t): ";
    char konf; cin >> konf;
    if (konf == 'y' || konf == 'Y') {
        for (int i = idx; i < jumlahData - 1; i++) listData[i] = listData[i + 1];
        jumlahData--;
        cout << "Data dihapus dari memori.\n";
        if (konfirmasiSimpan()) {
            tulisFile(nama);
            cout << "Perubahan disimpan ke " << nama << "\n";
        }
    }
}

void operasiFile() {
    int pilihOperasi;
    char ulangOperasi;
        do {
            system("cls");
            cout << "Menu Operasi File :\n";
            cout << "======================\n";
            cout << "1. Update Data\n";
            cout << "2. Delete Data\n";
            cout << "3. Kembali ke menu utama\n";
            cout << "======================\n";
            cout << "Pilih : ";
            cin >> pilihOperasi;
            cout << endl;

                switch (pilihOperasi) {
                    case 1 :    
                        system("cls");
                        updateData();
                        cout << "\nUlang Operasi File? (y/t): ";
                        cin >> ulangOperasi;
                        break;
                    
                    case 2 :    
                        system("cls");
                        deleteData();
                        cout << "\nUlang Operasi File? (y/t): ";
                        cin >> ulangOperasi;
                        break;

                    case 3 :   
                        ulangOperasi = 't';
                        break;

                    default :  
                        cout << "Pilihan tidak ada, ulang (y/t) :";
                        cin >> ulangOperasi;
                        break;
                }
        } while (ulangOperasi == 'y' || ulangOperasi == 'Y');
}

//--------------------------------------------- MAIN FUNCTION ----------------------------------------------//
int main() {
    loadDaftarFile();
    int pilihan;
    char balik;

    do {
        system("cls");
        cout << "\n===== MANAGEMENT SYSTEM KAPAL KARGO & CONTAINER =====\n";
        cout << "1. INPUT DATA\n2. TAMPILKAN DATA\n3. DAFTAR FILE\n4. SEARCHING\n5. SORTING\n6. OPERASI FILE\n7. EXIT\n";
        cout << "Pilihan: "; 
        cin >> pilihan;

        switch (pilihan) {
            case 1: 
                system("cls");
                inputData();
                cout << "\nKembali ke menu utama(y/t) : ";
                cin >> balik;
                break;

            case 2:
                system("cls");
                tampilData();
                cout << "\nKembali ke menu utama(y/t) : ";
                cin >> balik;
                break;

            case 3:
                system("cls");
                tampilkanDaftarFile();
                cout << "\nKembali ke menu utama(y/t) : ";
                cin >> balik;
                break;

            case 4:
                system("cls");
                searching();
                cout << "\nKembali ke menu utama(y/t) : ";
                cin >> balik;
                break;

            case 5:
                system("cls");
                sorting();
                cout << "\nKembali ke menu utama(y/t) : ";
                cin >> balik;
                break;

            case 6:
                system("cls");
                operasiFile();
                cout << "\nKembali ke menu utama(y/t) : ";
                cin >> balik;
                break;

            case 7:
                cout << "\n>>>>> Terima kasih telah menggunakan program ini! <<<<<\n";
                return 0;

            default :   
                cout << "Pilihan tidak ada, coba lagi\n";
                cout << "Kembali ke menu utama(y/t) : ";
                cin >> balik;
                break;
         }
    } while (balik == 'y' || balik == 'Y');

    cout << "\n>>>>> Terima kasih telah menggunakan program ini! <<<<<\n";
    return 0;
}