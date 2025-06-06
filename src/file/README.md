# 📁 Format File Data Sistem Manajemen Rumah Sakit

## 📋 **Deskripsi Umum**

Folder ini berisi semua file data yang digunakan oleh Sistem Manajemen Rumah Sakit. Setiap file memiliki format dan struktur khusus yang diperlukan untuk operasional sistem.

---

## **Daftar File Data**

### **1. config.txt** - Konfigurasi Rumah Sakit

### **2. user.csv** - Data Pengguna

### **3. penyakit.csv** - Database Penyakit

### **4. obat.csv** - Database Obat

### **5. obat_penyakit.csv** - Mapping Obat-Penyakit

---

## **Format File config.txt**

File `config.txt` berisi konfigurasi lengkap rumah sakit termasuk denah, antrian, dan inventori pasien.

### **Struktur Format:**

```
keuangan_rumah_sakit
baris kolom_denah
kapasitas_ruangan maksimal_antrian
id_dokter id_pasien1 id_pasien2 ... (untuk setiap ruangan)
...
jumlah_pasien_dengan_obat
id_pasien id_obat1 id_obat2 ...
...
jumlah_pasien_dengan_obat_di_perut
id_pasien id_obat1 id_obat2 ... (urutan terbalik - stack)
```

### **Penjelasan Detail:**

#### **Baris 1: Keuangan Rumah Sakit**

```
50000
```

- Menunjukkan saldo keuangan rumah sakit dalam mata uang Banarich
- Digunakan untuk sistem ekonomi dan pelacakan pendapatan

#### **Baris 2: Dimensi Denah**

```
2 3
```

- **2** = Jumlah baris (row) denah rumah sakit
- **3** = Jumlah kolom (column) denah rumah sakit
- Contoh: Denah 2x3 memiliki ruangan A1, A2, A3, B1, B2, B3

#### **Baris 3: Kapasitas Sistem**

```
3 4
```

- **3** = Kapasitas maksimal pasien **di dalam ruangan**
- **4** = Kapasitas maksimal pasien **dalam antrian di luar ruangan**
- Total maksimal pasien per ruangan = 3 + 4 = 7 pasien

#### **Baris 4-9: Status Ruangan (Sesuai jumlah ruangan)**

Format untuk setiap ruangan:

```
id_dokter id_pasien_dalam_ruangan... id_pasien_antrian...
```

**Contoh:**

```
10 2 3 1 16 20    # Ruangan A1: Dokter ID=10, Pasien dalam ruangan: 2,3,1, Antrian: 16,20
11 5 6 7 0        # Ruangan A2: Dokter ID=11, Pasien dalam ruangan: 5,6,7, Tidak ada antrian
12 8 9 0          # Ruangan A3: Dokter ID=12, Pasien dalam ruangan: 8,9, Tidak ada antrian
0                 # Ruangan B1: Tidak ada dokter (ID=0), tidak ada pasien
13 14 0           # Ruangan B2: Dokter ID=13, Pasien dalam ruangan: 14, Tidak ada antrian
15 0              # Ruangan B3: Dokter ID=15, Tidak ada pasien
```

**Keterangan:**

- **ID Dokter = 0**: Ruangan kosong, tidak ada dokter yang ditugaskan
- **ID Pasien = 0**: Menandakan tidak ada pasien (pembatas)
- **Urutan Pasien**: Pasien dalam ruangan ditulis dulu, kemudian pasien antrian

#### **Baris 10: Jumlah Pasien dengan Inventori Obat**

```
2
```

- Menunjukkan ada 2 pasien yang memiliki obat di inventori mereka

#### **Baris 11-12: Inventori Obat Pasien**

```
2 3         # Pasien ID=2 memiliki obat ID=3
4 3 2       # Pasien ID=4 memiliki obat ID=3 dan ID=2
```

#### **Baris 13: Jumlah Pasien dengan Obat di Perut**

```
1
```

- Menunjukkan ada 1 pasien yang telah meminum obat (obat ada di perut)

#### **Baris 14: Obat di Perut Pasien (Stack)**

```
4 4 5       # Pasien ID=4 memiliki obat di perut: urutan minum 5 → 4
```

**Penting:** Obat di perut menggunakan struktur **Stack** (Last In, First Out)

- Obat yang diminum terakhir berada di posisi paling kanan
- Untuk contoh `4 4 5`: Pasien minum obat ID=5 dulu, kemudian obat ID=4

---

## **Format File user.csv**

File yang berisi data semua pengguna sistem (pasien, dokter, manajer).

### **Format:**

```csv
id,username,password,role,riwayat_penyakit,suhu_tubuh,tekanan_darah_sistolik,tekanan_darah_diastolik,detak_jantung,saturasi_oksigen,kadar_gula_darah,berat_badan,tinggi_badan,kadar_kolesterol,trombosit,nyawa,banarich,aura
```

### **Penjelasan Kolom:**

- **id**: ID unik pengguna (integer)
- **username**: Nama pengguna (string)
- **password**: Kata sandi (string)
- **role**: Peran (pasien/dokter/manager)
- **riwayat_penyakit**: Nama penyakit terakhir (string, "-" jika tidak ada)
- **suhu_tubuh**: Suhu dalam Celsius (float)
- **tekanan_darah_sistolik/diastolik**: Tekanan darah (integer)
- **detak_jantung**: Detak jantung per menit (integer)
- **saturasi_oksigen**: Saturasi oksigen % (float)
- **kadar_gula_darah**: Gula darah mg/dL (integer)
- **berat_badan**: Berat badan kg (float)
- **tinggi_badan**: Tinggi badan cm (integer)
- **kadar_kolesterol**: Kolesterol mg/dL (integer)
- **trombosit**: Trombosit ribu/uL (integer)
- **nyawa**: Status hidup (1=hidup, 0=mati)
- **banarich**: Saldo mata uang virtual (integer)
- **aura**: Rating dokter/reputasi (integer)

---

## **Format File penyakit.csv**

Database penyakit dengan parameter kesehatan untuk diagnosis.

### **Format:**

```csv
id;nama_penyakit;suhu_tubuh_min;suhu_tubuh_max;tekanan_darah_sistolik_min;tekanan_darah_sistolik_max;tekanan_darah_diastolik_min;tekanan_darah_diastolik_max;detak_jantung_min;detak_jantung_max;saturasi_oksigen_min;saturasi_oksigen_max;kadar_gula_darah_min;kadar_gula_darah_max;berat_badan_min;berat_badan_max;tinggi_badan_min;tinggi_badan_max;kadar_kolesterol_min;kadar_kolesterol_max;trombosit_min;trombosit_max
```

### **Penjelasan:**

- Setiap penyakit memiliki rentang normal untuk setiap parameter kesehatan
- Sistem diagnosis akan mencocokkan data vital pasien dengan rentang penyakit
- Format semicolon (;) digunakan sebagai delimiter

---

## **Format File obat.csv**

Database obat yang tersedia di rumah sakit.

### **Format:**

```csv
obat_id;nama_obat
```

### **Contoh:**

```csv
1;Paracetamol
2;Amoxicillin
3;Ibuprofen
4;Vitamin C
5;Aspirin
```

---

## **Format File obat_penyakit.csv**

Mapping antara obat dan penyakit dengan urutan konsumsi.

### **Format:**

```csv
obat_id;penyakit_id;urutan_minum
```

### **Penjelasan:**

- **obat_id**: ID obat yang diresepkan
- **penyakit_id**: ID penyakit yang memerlukan obat tersebut
- **urutan_minum**: Urutan konsumsi obat (1=pertama, 2=kedua, dst.)

### **Contoh:**

```csv
1;1;1    # Obat ID=1 untuk penyakit ID=1, diminum pertama
2;1;2    # Obat ID=2 untuk penyakit ID=1, diminum kedua
3;2;1    # Obat ID=3 untuk penyakit ID=2, diminum pertama
```

---

## **Panduan Modifikasi File**

### **Peringatan Penting:**

1. **Backup Data**: Selalu backup file sebelum melakukan modifikasi
2. **Format Konsistensi**: Jaga format yang konsisten untuk menghindari error parsing
3. **ID Unik**: Pastikan semua ID bersifat unik dan tidak duplikat
4. **Delimiter**: Gunakan delimiter yang benar (koma untuk .csv, spasi untuk config.txt)

### **Tips Modifikasi:**

#### **Menambah Ruangan:**

1. Ubah dimensi denah di baris 2 config.txt
2. Tambahkan baris status ruangan baru
3. Pastikan jumlah baris sesuai dengan (baris × kolom)

#### **Menambah Pengguna:**

1. Tambah baris baru di user.csv
2. Pastikan ID unik dan tidak konflik
3. Isi semua field sesuai format

#### **Menambah Penyakit/Obat:**

1. Tambah entry baru di file terkait
2. Update mapping di obat_penyakit.csv jika diperlukan
3. Pastikan rentang parameter penyakit logis

---

## 🧪 **Contoh Konfigurasi Lengkap**

### **config.txt:**

```
25000
2 3
3 4
10 2 3 1 16 20
11 5 6 7 0
12 8 9 0
0
13 14 0
15 0
2
2 3
4 3 2
1
4 4 5
```

### **Interpretasi:**

- Rumah sakit memiliki 25000 Banarich
- Denah 2×3 (6 ruangan: A1-A3, B1-B3)
- Kapasitas: 3 pasien per ruangan, 4 antrian
- Ruangan A1: Dokter 10, pasien 2,3,1 di dalam, 16,20 antrian
- Ruangan B1: Kosong (tidak ada dokter)
- Pasien 2 punya obat ID=3
- Pasien 4 punya obat ID=3,2 dan sudah minum obat 5→4

---

## **Dukungan**

Jika mengalami masalah dengan format file:

1. Periksa delimiter yang digunakan
2. Pastikan tidak ada karakter khusus
3. Verifikasi ID tidak duplikat
4. Konsultasikan dengan dokumentasi sistem

---

*Dokumentasi ini dibuat untuk Tugas Besar IF1210 - Kelompok K01-I*
