# Cargo Ship & Container Management System

Sistem Manajemen Kapal Kargo dan Kontainer berbasis C++ untuk mengelola, mencari, mengurutkan, serta menyimpan data kargo secara otomatis menggunakan *file handling* (`.txt`).

---

## 🛠️ Fitur Utama

* **Pengelolaan Data (CRUD):** Input data kargo baru, lihat daftar file, *update*, dan *delete* data berdasarkan ID Kapal.
* **Pencarian (Searching):** 
  * **Sequential Search:** Pencarian fleksibel berdasarkan ID, Nama Kapal, Kontainer, atau Jenis.
  * **Binary Search:** Pencarian terurut berbasis algoritma *divide-and-conquer*.
* **Pengurutan (Sorting):**
  * **Bubble Sort:** Mengurutkan data berdasarkan *Nama Kapal* (A-Z).
  * **Selection Sort:** Mengurutkan data berdasarkan *Berat (Ton)*.
* **File Handling:** Penyimpanan data terorganisasi secara *persistent* ke file `.txt` eksternal.

---

🚀 Cara Menjalankan Program
1.  Clone repositori ini:

git clone [https://github.com/rezasyahputra07/Project_Akhir_Praktikum_Alpro_Lanjut.git](https://github.com/rezasyahputra07/Project_Akhir_Praktikum_Alpro_Lanjut.git)

2. Masuk ke direktori proyek:
   cd Project_Akhir_Praktikum_Alpro_Lanjut

3. jalankan program:
   g++ Project_Kelompok-4.cpp -o main
./main 
