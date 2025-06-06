#ifndef FUNGSIPROSEDUR_H
#define FUNGSIPROSEDUR_H

#include "global.h"  // This includes all ADT headers
#include "file-eksternal.h"

/*Akses: Sebelum Login

Mengubah current_user menjadi suatu user jika masukan username dan password sesuai database.*/
void login(User* current_user, ListUser database);

/*Akses: Sebelum Login

Meminta masukan username dan password User baru.
Memeriksa set of username lalu menambahkan User (role pasien) ke database jika username unik.*/
void registerPasien(User current_user, ListUser* database);

/*Akses: Manajer, Dokter, Pasien

Mengubah current_user menjadi NO_USER.*/
void logout(User* current_user);

/*Akses: Sebelum Login

Mengubah password seorang user jika username ada dan kode unik sesuai ketentuan.*/
int validasiKodeUnik(char* username, char *kodeUnik); //validasi kode unik apakah sesuai ketentuan
void gantiPasswordDiList(User *user, const char *passwordBaru); //memperbarui data password di ADT List
void lupaPassword(User current_user, ListUser* database);

/* Akses: Semua

Menampilkan panduan prosedur yang tersedia untuk current_user.*/
void help(User current_user);

/*Akses: Manajer, Dokter, Pasien

Menampilkan bentuk denah ruangan beserta kodenya.*/
void lihatDenah(User current_user, MatriksRuangan denah);

/*Akses: Manajer, Dokter, Pasien

Menampilkan informasi kapasitas, nama dokter, daftar pasien dalam ruangan, dan antrean pasien suatu ruangan berdasarkan kodenya.*/
void lihatRuangan(User current_user, MatriksRuangan denah_rumah_sakit);

/*Akses: Manajer

Menampilkan daftar ID, Nama, Role, dan Penyakit semua User secara urut.
Pengurutan bisa berdasarkan ID (numerik) atau Nama (Leksikografis, Case-Insensitive).
Pengurutan bisa bisa menaik / ascending atau menurun / descending.*/
void lihatUser(User current_user, ListUser database);

/*Akses: Manajer

Menampilkan daftar ID, Nama, dan Penyakit semua User dengan role pasien secara urut.
Pengurutan bisa berdasarkan ID (numerik) atau Nama (Leksikografis, Case-Insensitive).
Pengurutan bisa menaik / ascending atau menurun / descending.*/
void lihatPasien(User current_user, ListUser database);

/*Akses: Manajer

Menampilkan daftar ID dan Nama semua User dengan role dokter secara urut.
Pengurutan bisa berdasarkan ID (numerik) atau Nama (Leksikografis, Case-Insensitive).
Pengurutan bisa menaik / ascending atau menurun / descending.*/
void lihatDokter(User current_user, ListUser database);

/*Akses: Manajer

Mencari User berdasarkan ID atau Nama (Leksikografis, Case-Insensitive).
Menampilkan (jika ada) ID, Nama, Role, dan Penyakit (jika Role Pasien) User yang sesuai.*/
void cariUser(User current_user, ListUser database);

/*Akses: Manajer

Mencari User dengan Role Pasien berdasarkan ID, Nama (Leksikografis, Case-Insensitive), atau Penyakit.
Menampilkan (jika ada) ID, Nama, dan Penyakit User yang sesuai.*/
void cariPasien(User current_user, ListUser database);

/*Akses: Manajer

Mencari User dengan Role Dokter berdasarkan ID atau Nama (Leksikografis, Case-Insensitive).
Menampilkan (jika ada) ID dan Nama User yang sesuai.*/
void cariDokter(User current_user, ListUser database);

/*Akses: Manajer

Menampilkan bentuk denah ruangan beserta kodenya.
Menampilkan informasi kapasitas, nama dokter, daftar pasien dalam ruangan, dan antrean pasien tiap ruangan yang tidak kosong.*/
void lihatAntrean(User current_user, MatriksRuangan denah);

/*Akses: Manajer

Meminta masukan username dan password User baru.
Memeriksa set of username lalu menambahkan User (role dokter) ke database jika username unik.*/
void tambahDokter(User current_user, ListUser* database);

/*Akses: Manajer

Meminta username dokter dan kode ruangan lalu meng-assign dokter (jika ditemukan dan belum di-assign) ke ruangan yang sesuai.*/
void assignDokter(User current_user, ListUser database, MatriksRuangan* denah);

/*Akses: Manajer

Meminta username dokter lalu meng-unassign dokter (jika ditemukan dan sudah di-assign) dari ruangannya.*/
void unassignDokter(User current_user, ListUser database, MatriksRuangan* denah);

/*Akses: Manajer

Menambah jumlah baris ruangan sebanyak 1 jika belum mencapai MAX_ROWS lalu menampilkan denah setelahnya.*/
void tambahBaris(User current_user, MatriksRuangan* denah);

/*Akses: Manajer

Menambah jumlah baris ruangan sebanyak 1 jika belum mencapai MAX_COLS lalu menampilkan denah setelahnya.*/
void tambahKolom(User current_user, MatriksRuangan* denah);

/*Akses: Manajer

Memeriksa kondisi antrean pasien di ruangan-ruangan baris terakhir. Jika kosong, otomatis UNASSIGN DOKTER dari denah. tampilkan denah*/
void kurangiBaris(User current_user, MatriksRuangan* denah);

/*Akses: Manajer

Memeriksa kondisi antrean pasien di ruangan-ruangan kolom terakhir. Jika kosong, otomatis UNASSIGN DOKTER dari denah. tampilkan denah*/
void kurangiKolom(User current_user, MatriksRuangan* denah);

/* 
Akses: Dokter
Memberikan informasi terkait penyakit yang diderita pasien
I.S : Antrean mungkin kosong
F.S : Menampilkan informasi terkait penyakit yang diderita pasien
*/
void diagnosis(User current_user, ListPenyakit ensiklopedia, MatriksRuangan* denah_ruang, ListUser* database);

/*
Akses: Dokter
Memberikan informasi terkait penyakit yang diderita pasien
I.S : Antrian mungkin kosong
F.S : Menampilkan informasi terkait obatan yang harus diberikan kepada pasien
*/
void ngobatin(User current_user, MatriksRuangan* denah_ruang, MapObatPenyakit obat_penyakit, ListUser* database);

/*
Akses: Pasien
Menanyakan kepada dokter apakah pasien sudah bisa pulang
I.S : Pasien sudah terdiagnosis, pasien mungkin salah minum obat
F.S : Jika pasien sudah minum obat sesuai resep, pasien bisa pulang, 
        jika tidak, pasien tidak bisa pulang
*/
void bolehPulang(User* current_user, MapObatPenyakit peta_obat_penyakit, ListUser* database_pengguna, MatriksRuangan* rumah_sakit);

/*
Akses: Pasien
Memasukan data kesehatan pasien untuk pemeriksaan kesehatan
*/
void daftarCheckUp(User* current_user,  ListUser* database, MatriksRuangan* rumah_sakit);

/*
Akses: Pasien
Menampilkan antrean pasien yang sedang menunggu pemeriksaan kesehatan.
I.S : Pasien sudah terdaftar dalam antrean
F.S : Menampilkan antrean pasien yang sedang menunggu pemeriksaan kesehatan.
*/
void antreanSaya(User current_user, MatriksRuangan rumah_sakit);

/*
Akses: Pasien
Meminta masukan nama obat yang akan diminum.
I.S : Pasien sudah terdaftar dalam antrean
F.S : Jika obat ditemukan, obat akan diminum, jika tidak, akan menampilkan pesan error.
Jika obat yang diminum tidak sesuai dengan resep dokter, akan menampilkan pesan error.
*/
void minumObat(User* current_user, ListUser* database);

/*
Akses: Pasien
Meminta masukan nama obat penawar yang akan diminum.
I.S : Pasien sudah terdaftar dalam antrean
F.S : Jika obat penawar ditemukan, obat penawar akan diminum
*/
void minumPenawar(User* pasien, MapObatPenyakit map_obat_penyakit, ListUser* database_pengguna, MatriksRuangan* rumah_sakit);

/*
Akses: Semua
Keluar dari program dengan menyimpan data ke file eksternal.
I.S : Program akan menyimpan data ke file eksternal
F.S : Program akan keluar dengan mengembalikan nilai TRUE jika berhasil, FALSE jika gagal.
*/
boolean exitRumahSakit(User* current_user, MatriksRuangan* denah, ListUser* database, ListPenyakit daftar_penyakit, ListObat daftar_obat, MapObatPenyakit map);


/* Akses: Pasien
Memindahkan pasien ke antrean terdepan 
I.S : Pasien sudah terdaftar dalam antrean
F.S : Pasien akan dipindahkan ke antrean terdepan, jika antrean tidak kosong.
*/
void skipAntrean(User* current_user, MatriksRuangan* rumah_sakit);

/* Akses: Pasien
Menghapus pasien dari antrean
I.S : Pasien sudah terdaftar dalam antrean
F.S : Pasien akan dihapus dari antrean, jika antrean tidak kosong.
*/
void cancelAntrean(User* current_user, MatriksRuangan* rumah_sakit);

/* Akses: Pasien
Mengundi banarich untuk ditambahkan ke dompet
I.S : Pasien terdaftar di database
F.S : Dompet pasien bertambah sejumlah hasil undian*/
void gachaGaming(User* current_user, ListUser* database_user, unsigned* prev_rng);

/* Akses: Pasien, Dokter
Melihat jumlah uang dalam dompet
I.S : User terdaftar di database
F.S : Ditampilkan banyaknya banarich dalam dompet*/
void lihatDompet(User current_user);

/* Akses: Manager
Melihat jumlah uang milik Rumah Sakit
I.S : User terdaftar di database
F.S : Ditampilkan banyaknya banarich milik Rumah Sakit*/
void lihatKeuangan(User current_user);

#endif