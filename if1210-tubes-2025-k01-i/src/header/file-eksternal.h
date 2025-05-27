// Pengganti config.h

#ifndef FILEEKSTERNAL_H
#define FILEEKSTERNAL_H

#include "global.h"  // This includes all ADT headers

#define MAX_FIELD_LEN 100
#define MAX_LINE_LEN 1024

int folderExists(const char *folderName);

/* Membaca file user.csv lalu memindahkannya ke ListUser database */
int bacaUserCSV(const char *folderName, ListUser* database, ListPenyakit daftar_penyakit);

/* Membaca file penyakit.csv lalu memindahkannya ke ListPenyakit daftar_penyakit */
void bacaPenyakitCSV(const char *folderName, ListPenyakit* daftar_penyakit);

/* Membaca obat.csv lalu memindahkannya ke daftar_obat*/
void bacaObatCSV(const char *folderName, ListObat* daftar_obat);

/* Membaca ListPenyakit, memindahkannya ke MapObatPenyakit sebagai key
Membaca obat_penyakit.csv dan obat.csv lalu memindahkannya ke MapObatPenyakit sebagai value (dalam bentuk Stack) */
void bacaObatPenyakit(const char *folderName, ListPenyakit daftar_penyakit, ListObat daftar_obat, MapObatPenyakit* map);

/* Membaca  line dan mengubahnya ke array*/
void parseLineKeArray(const char* line, int* arr, int* len);

/* Membaca config untuk membuat Rumah Sakit dengan ADT Matrix, load queue dalam matriks*/
void bacaConfig(const char *folderName, MatriksRuangan* denah, ListUser* database, ListObat semuaObat,int *max_queue);

/* Menulis ulang config berdasarkan Matrix denah dan database user.*/
void tulisConfig(const char *folderName, MatriksRuangan denah, ListUser database);


//Mengupdate config.txt
/*
I.S : ListUser database, userId, inventory sudah terisi
F.S : inventory pasien terisi dengan obat yang ada di database
*/
void saveConfig(const char *folderName, MatriksRuangan* denah, ListUser* database);

/* Menyimpan data user ke file CSV */
void saveUserCSV(const char *folderName, ListUser database);

/* Menyimpan data penyakit ke file CSV */
void savePenyakitCSV(const char *folderName, ListPenyakit daftar_penyakit);

/* Menyimpan data obat ke file CSV */
void saveObatCSV(const char *folderName, ListObat daftar_obat);

/* Menyimpan data obat penyakit ke file CSV */
void saveObatPenyakitCSV(const char *folderName, MapObatPenyakit map, ListPenyakit daftar_penyakit);

/* Fungsi utama untuk menyimpan semua data - hanya menggunakan stdlib */
void saveData(MatriksRuangan* denah, ListUser* database, ListPenyakit daftar_penyakit, ListObat daftar_obat, MapObatPenyakit map);
#endif