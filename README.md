# Sistem Manajemen Rumah Sakit

**IF1210 - Tugas Besar Algoritma dan Pemrograman**

## 📋 Deskripsi Proyek

Sistem Manajemen Rumah Sakit adalah aplikasi berbasis konsol yang dikembangkan menggunakan bahasa C untuk mengelola operasional rumah sakit. Sistem ini menyediakan fitur lengkap untuk manajemen pasien, dokter, diagnosis penyakit, pemberian obat, dan administrasi rumah sakit.

## 🏗️ Struktur Proyek

```
if1210-tubes-2025-k01-i/
├── README.md                          # Dokumentasi utama
├── doc/                               # Dokumentasi
│   ├── Laporan Tugas Besar ALPRO.pdf
│   └── README.md
└── src/                              # Source code utama
    ├── main.c                        # Entry point aplikasi
    ├── makefile                      # Build configuration
    ├── build/                        # File hasil kompilasi
    │   ├── main                      # Executable utama
    │   ├── main.o                    # Object file main
    │   └── c/                        # Object files ADT
    ├── c/                            # Implementasi ADT dan fungsi
    │   ├── adt-map.c                 # Map untuk obat-penyakit
    │   ├── adt-matrix.c              # Matrix ruangan rumah sakit
    │   ├── adt-obat.c                # ADT obat
    │   ├── adt-penyakit.c            # ADT penyakit
    │   ├── adt-queue.c               # Queue untuk antrian
    │   ├── adt-stack.c               # Stack untuk perut pasien
    │   ├── adt-user.c                # ADT user (pasien, dokter, manager)
    │   ├── file-eksternal.c          # File I/O operations
    │   ├── fungsi-prosedur.c         # Fungsi utama aplikasi
    │   ├── global.c                  # Global variables
    │   ├── interface.c               # Interface pengguna
    │   └── loader.c                  # Data loader
    ├── file/                         # File data sistem
    │   ├── config.txt                # Konfigurasi rumah sakit
    │   ├── obat_penyakit.csv         # Mapping obat-penyakit
    │   ├── obat.csv                  # Data obat
    │   ├── penyakit.csv              # Data penyakit
    │   └── user.csv                  # Data pengguna
    └── header/                       # Header files
        ├── adt-map.h                 # Header ADT map
        ├── adt-matrix.h              # Header ADT matrix
        ├── adt-obat.h                # Header ADT obat
        ├── adt-penyakit.h            # Header ADT penyakit
        ├── adt-queue.h               # Header ADT queue
        ├── adt-stack.h               # Header ADT stack
        ├── adt-user.h                # Header ADT user
        ├── boolean.h                 # Boolean type definition
        ├── file-eksternal.h          # Header file operations
        ├── fungsi-prosedur.h         # Header fungsi utama
        ├── global.h                  # Global declarations
        ├── interface.h               # Header interface
        └── loader.h                  # Header loader
```

## 🚀 Fitur Utama

### 👤 **Sistem Pengguna Multi-Role**

- **Pasien**: Registrasi, login, daftar checkup, minum obat, cek antrian, dompet pasien, gacha gaming
- **Dokter**: Login, diagnosis pasien, pemberian obat, manajemen ruangan, dompet dokter
- **Manager**: Manajemen pengguna, lihat statistik, tambah dokter, assign dan unassign dokter, keuangan rumah sakit

### 🏥 **Manajemen Rumah Sakit**

- **Denah Dinamis**: Matrix ruangan yang dapat dikonfigurasi
- **Sistem Antrian**: Queue untuk mengelola antrian pasien
- **Assignment Dokter**: Penempatan dokter ke ruangan tertentu
- **Kapasitas Ruangan**: Kontrol maksimal pasien per ruangan
- **Sistem Aura**: Pemantauan reputasi dokter

### 🔬 **Sistem Diagnosis**

- **Database Penyakit**: Ensiklopedia penyakit dengan parameter kesehatan
- **Diagnosis Otomatis**: Berdasarkan data vital pasien
- **Parameter Kesehatan**: Suhu, tekanan darah, detak jantung, dll.

### 💊 **Manajemen Obat**

- **Database Obat**: Katalog obat dengan ID unik
- **Resep Otomatis**: Pemberian obat berdasarkan diagnosis
- **Inventory Pasien**: Tracking obat yang dimiliki pasien
- **Stack Perut**: Simulasi obat yang telah diminum

### 💰 **Sistem Ekonomi dan Gaming**

- **Dompet Digital**: Setiap user memiliki saldo virtual (Banarich)
- **Sistem Keuangan RS**: Manager dapat memantau kondisi keuangan rumah sakit
- **Gacha Gaming**: Pasien dapat bermain gacha untuk mendapatkan hadiah random
- **Economic Balance**: Integrasi sistem ekonomi dengan gameplay

### 🎨 **User Interface**

- **Display Terminal**: Terminal berwarna untuk experience yang lebih baik
- **Emoji Icons**: Simbol emoji pada setiap perintah.
- **Role-specific Help**: Menu bantuan yang disesuaikan dengan role pengguna
- **Clear Navigation**: Membersihkan layar setiap ada perintah "CLEAR"

### 📊 **Data Storage**

- **Format CSV**: User, obat, penyakit, obat-penyakit mapping
- **Config File**: Konfigurasi denah dan antrian
- **Auto Save**: Penyimpanan otomatis saat exit

### 🔧 Cara Instalasi dan Menjalankan

### Prasyarat

- **Compiler**: GCC (GNU Compiler Collection)
- **OS**: Windows/Linux/MacOS
- **Make**: GNU Make (opsional, untuk kemudahan build)

### Langkah Instalasi

1. **Clone Repository**

   ```bash
   git clone <repository-url>
   cd if1210-tubes-2025-k01-i
   ```
2. **Navigate ke Source Directory**

   ```bash
   cd src
   ```
3. **Compile menggunakan Makefile**

   ```bash
   make all
   ```

   Atau compile manual:

   ```bash
   gcc -g -Wall -o build/main *.c c/*.c
   ```
4. **Jalankan Aplikasi**

   ```bash
   # Menggunakan makefile
   make run folder=file

   # Atau manual
   ./build/main file
   ```

### Menjalankan dengan Data Custom

```bash
./build/main nama_folder_data
```

## 📖 Panduan Penggunaan

### Alur Kerja Umum

1. **Startup**: Aplikasi memuat data dari folder yang ditentukan
2. **Authentication**: Login sebagai pasien, dokter, atau manager
3. **Operasi**: Gunakan command sesuai role
4. **Exit**: Simpan perubahan saat keluar

### Command Utama

#### 🔐 **Authentication Commands**

- `LOGIN` - Masuk ke sistem
- `REGISTER` - Daftar sebagai pasien baru
- `LOGOUT` - Keluar dari akun
- `LUPA_PASSWORD` - Reset password

#### 🏥 **General Commands**

- `HELP` - Tampilkan panduan sesuai role
- `LIHAT_DENAH` - Lihat denah rumah sakit
- `LIHAT_RUANGAN` - Detail ruangan tertentu
- `CLEAR` - Bersihkan layar terminal
- `EXIT` - Keluar dari aplikasi

#### 👨‍⚕️ **Manager Commands**

- `LIHAT_USER` - Daftar semua pengguna
- `CARI_USER` - Cari pengguna tertentu
- `LIHAT_ANTREAN` - Status semua ruangan
- `TAMBAH_DOKTER` - Tambah dokter baru
- `ASSIGN_DOKTER` - Tempatkan dokter ke ruangan
- `LIHAT_KEUANGAN` - Lihat kondisi keuangan rumah sakit

#### 🩺 **Dokter Commands**

- `DIAGNOSIS` - Diagnosis pasien dalam antrian
- `NGOBATIN` - Berikan obat kepada pasien
- `LIHAT_DOMPET` - Lihat isi dompet dokter

#### 🤒 **Pasien Commands**

- `DAFTAR_CHECKUP` - Daftar antrian pemeriksaan
- `ANTREAN_SAYA` - Cek status antrian
- `MINUM_OBAT` - Konsumsi obat dari inventory
- `MINUM_PENAWAR` - Keluarkan obat terakhir
- `STATUS_ANTREAN` - Lihat posisi dalam antrian
- `LIHAT_DOMPET` - Lihat isi dompet pasien
- `GACHA_GAMING` - Bermain gacha untuk mendapatkan hadiah

## 🗂️ Format Data

### User Data (user.csv)

```csv
id,username,password,role,riwayat_penyakit,suhu_tubuh,tekanan_darah_sistolik,tekanan_darah_diastolik,detak_jantung,saturasi_oksigen,kadar_gula_darah,berat_badan,tinggi_badan,kadar_kolesterol,trombosit,nyawa,banarich,aura
```

### Penyakit Data (penyakit.csv)

```csv
id;nama_penyakit;suhu_tubuh_min;suhu_tubuh_max;tekanan_darah_sistolik_min;tekanan_darah_sistolik_max;...
```

### Obat Data (obat.csv)

```csv
obat_id;nama_obat
```

### Obat-Penyakit Mapping (obat_penyakit.csv)

```csv
obat_id;penyakit_id;urutan_minum
```

## 🏛️ Arsitektur Sistem

### Abstract Data Types (ADT)

1. **ADT User**: Manajemen data pengguna dengan role-based access
2. **ADT Matrix**: Representasi denah rumah sakit 2D
3. **ADT Queue**: Antrian pasien per ruangan
4. **ADT Stack**: Simulasi perut pasien untuk tracking obat
5. **ADT Map**: Mapping obat ke penyakit
6. **ADT List**: Collections untuk obat dan penyakit

## ⚙️ Konfigurasi

### Config File Format (config.txt)

```
keuangan_RS
baris kolom_denah
ruangan_dengan_dokter jumlah_pasien_dalam_ruangan
id_dokter id_pasien1 id_pasien2 ...
id_dokter id_pasien1 id_pasien2
...
jumlah_user_dengan_obat
id_user1 id_obat1 id_obat2 ...
id_user2 id_obat1 id_obat2 ...
```

## 🧪 Testing

### Manual Testing

1. Jalankan aplikasi dengan data test
2. Test semua role dan fitur
3. Verifikasi persistence data
4. Check edge cases dan error handling

## 🤝 Kontribusi

* Ahmad Zaky Robbani (13524045)
* Kurt Mikhael Purba (13524065)
* Angelina Andra Alanna (13524079)
* Fauzan Mohamad Abdul Ghani (13524113)
* Amanda Aurellia Salsabilla (13524131)

### Standard Penulisan Kode

- Konsisten dengan naming convention
- Dokumentasi function headers
- Error handling yang proper
- Memory management yang aman

## 📄 Lisensi

Project ini dikembangkan untuk keperluan akademik Tugas Besar IF1210 - Algoritma dan Pemrograman.
