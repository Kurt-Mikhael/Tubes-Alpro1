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
void logout(User* current_user, ListUser* database);

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
void lihatRuangan(User current_user, MatriksRuangan denah);

/*Akses: Manajer

Menampilkan daftar ID, Nama, Role, dan Penyakit semua User secara urut.
Pengurutan bisa berdasarkan ID (numerik) atau Nama (Leksikografis, Case-Insensitive).
Pengurutan bisa menaik / ascending atau menurun / descending.*/
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
void bolehPulang();


void daftarCheckUp(User* current_user,  ListUser* database, MatriksRuangan* rumah_sakit);

void antreanSaya(User current_user, MatriksRuangan rumah_sakit);

void minumObat(User* current_user, ListUser* database_user);

void minumPenawar(User* current_user, ListUser* database_user);

boolean exitRumahSakit(User* current_user, MatriksRuangan* denah, ListUser* database, ListPenyakit daftar_penyakit, ListObat daftar_obat, MapObatPenyakit map);

//tambahan
int username_exists(User users[], int user_count, const char *username);


#endif