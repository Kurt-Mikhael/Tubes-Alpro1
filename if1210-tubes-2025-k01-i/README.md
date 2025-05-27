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

- **Pasien**: Registrasi, login, daftar checkup, minum obat, cek antrian
- **Dokter**: Login, diagnosis pasien, pemberian obat, manajemen ruangan
- **Manager**: Manajemen pengguna, lihat statistik, tambah dokter, assign dokter

### 🏥 **Manajemen Rumah Sakit**

- **Denah Dinamis**: Matrix ruangan yang dapat dikonfigurasi
- **Sistem Antrian**: Queue untuk mengelola antrian pasien
- **Assignment Dokter**: Penempatan dokter ke ruangan tertentu
- **Kapasitas Ruangan**: Kontrol maksimal pasien per ruangan

### 🔬 **Sistem Diagnosis**

- **Database Penyakit**: Ensiklopedia penyakit dengan parameter kesehatan
- **Diagnosis Otomatis**: Berdasarkan data vital pasien
- **Parameter Kesehatan**: Suhu, tekanan darah, detak jantung, dll.

### 💊 **Manajemen Obat**

- **Database Obat**: Katalog obat dengan ID unik
- **Resep Otomatis**: Pemberian obat berdasarkan diagnosis
- **Inventory Pasien**: Tracking obat yang dimiliki pasien
- **Stack Perut**: Simulasi obat yang telah diminum

### 📊 **Persistent Data Storage**

- **Format CSV**: User, obat, penyakit, obat-penyakit mapping
- **Config File**: Konfigurasi denah dan antrian
- **Auto Save**: Penyimpanan otomatis saat exit

## 🔧 Cara Instalasi dan Menjalankan

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
- `EXIT` - Keluar dari aplikasi

#### 👨‍⚕️ **Manager Commands**

- `LIHAT_USER` - Daftar semua pengguna
- `CARI_USER` - Cari pengguna tertentu
- `LIHAT_ANTREAN` - Status semua ruangan
- `TAMBAH_DOKTER` - Tambah dokter baru
- `ASSIGN_DOKTER` - Tempatkan dokter ke ruangan

#### 🩺 **Dokter Commands**

- `DIAGNOSIS` - Diagnosis pasien dalam antrian
- `NGOBATIN` - Berikan obat kepada pasien

#### 🤒 **Pasien Commands**

- `DAFTAR_CHECKUP` - Daftar antrian pemeriksaan
- `ANTREAN_SAYA` - Cek status antrian
- `MINUM_OBAT` - Konsumsi obat dari inventory
- `MINUM_PENAWAR` - Keluarkan obat terakhir
- `STATUS_ANTREAN` - Lihat posisi dalam antrian

## 🗂️ Format Data

### User Data (user.csv)

```csv
id,username,password,role,riwayat_penyakit,suhu_tubuh,tekanan_darah_sistolik,tekanan_darah_diastolik,detak_jantung,saturasi_oksigen,kadar_gula_darah,berat_badan,tinggi_badan,kadar_kolesterol,kadar_kolesterol_ldl,trombosit
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

### Design Patterns

- **Separation of Concerns**: Pemisahan ADT, business logic, dan I/O
- **Data Persistence**: Automatic save/load dengan format CSV
- **Role-Based Access Control**: Pembatasan fitur berdasarkan role user
- **Command Pattern**: Interface berbasis command untuk user interaction

## ⚙️ Konfigurasi

### Config File Format (config.txt)

```
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

### Development Workflow

1. Fork repository
2. Create feature branch
3. Implement changes
4. Test thoroughly
5. Submit pull request

### Coding Standards

- Konsisten dengan naming convention
- Dokumentasi function headers
- Error handling yang proper
- Memory management yang aman

## 📄 Lisensi

Project ini dikembangkan untuk keperluan akademik Tugas Besar IF1210 - Algoritma dan Pemrograman.

## 👥 Tim Pengembang

Tugas Besar Kelompok K01-I
Institut Teknologi Bandung

---

**Catatan**: Pastikan untuk selalu backup data sebelum menjalankan operasi yang mengubah database sistem.
