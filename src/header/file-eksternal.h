// Pengganti config.h

#ifndef FILEEKSTERNAL_H
#define FILEEKSTERNAL_H

#include "adt-obat.h"
#include "adt-penyakit.h"
#include "adt-user.h"
#include "adt-map.h"
#include "adt-matrix.h"
#include "adt-queue.h"
#include "adt-set.h"
#include "adt-stack.h"

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
void bacaConfig(const char *folderName, MatriksRuangan* denah, ListUser* database, ListObat semuaObat);

/*Mengisi Inventory PAsien dengan obatnya
I.S : ListUser database, userId, inventory sudah terisi
F.S : inventory pasien terisi dengan obat yang ada di database*/
void TambahObatKePasien(ListUser *database, int pasienId, int obatId, ListObat semuaObat);

/* Menulis ulang config berdasarkan Matrix denah dan database user.*/
void saveConfig(const char *folderName, MatriksRuangan* denah, ListUser* database);
#endif