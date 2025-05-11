#ifndef FUNGSIPROSEDUR_H
#define FUNGSIPROSEDUR_H

#include "adt-obat.h"
#include "adt-penyakit.h"
#include "adt-user.h"
#include "adt-map.h"
#include "adt-matrix.h"
#include "adt-queue.h"
#include "adt-set.h"
#include "adt-stack.h"
#include "file-eksternal.h"

/*Akses: Sebelum Login

Mengubah current_user menjadi suatu user jika masukan username dan password sesuai database.*/
void login(User* current_user, ListUser database);

/*Akses: Sebelum Login

Meminta masukan username dan password User baru.
Memeriksa set of username lalu menambahkan User (role pasien) ke database jika username unik.*/
void registerPasien(UsernameSet* username, ListUser* database);

/*Akses: Manajer, Dokter, Pasien

Mengubah current_user menjadi NO_USER.*/
void logout(User* current_user);

/*Akses: Sebelum Login

Mengubah password seorang user jika username ada dan kode unik sesuai ketentuan.*/
int validasiKodeUnik(char* username, char *kodeUnik); //validasi kode unik apakah sesuai ketentuan
void gantiPasswordDiList(char *baris, const char *passwordBaru, char *outputBaris); //memperbarui data password di ADT List
void lupaPassword(ListUser* database);

/* Akses: Manager, Dokter, Pasien

Menampilkan panduan prosedur yang tersedia untuk current_user.*/
void help(User* current_user);

/*Akses: Manajer

Menampilkan bentuk denah ruangan beserta kodenya.*/
void lihatDenah(User current_user, MatriksRuangan denah);

/*Akses: Manajer, Dokter, Pasien

Menampilkan informasi kapasitas, nama dokter, daftar pasien dalam ruangan, dan antrean pasien suatu ruangan berdasarkan kodenya.*/
void lihatRuangan(User current_user, MatriksRuangan denah, char* kode_ruangan);

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
void tambahDokter(User current_user, UsernameSet* username, ListUser* database);

/*Akses: Manajer

Meminta username dokter dan kode ruangan lalu meng-assign dokter (jika ditemukan dan belum di-assign) ke ruangan yang sesuai.*/
void assignDokter(User current_user, User dokter, MatriksRuangan* denah);


void diagnosis(User current_user, User* pasien, ListPenyakit ensiklopedia);

void ngobatin(User current_user, User pasien, MapObatPenyakit obat_penyakit);

void bolehPulang();

void daftarCheckUp();

void antreanSaya();

void minumObat();

void minumPenawar();

void exitRumahSakit(ListUser database);

//tambahan
int username_exists(User users[], int user_count, const char *username);


#endif