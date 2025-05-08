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

/* Membaca file user.csv lalu memindahkannya ke ListUser database */
void bacaUserCSV(ListUser* database);

/* Membaca file penyakit.csv lalu memindahkannya ke ListPenyakit daftar_penyakit */
void bacaPenyakitCSV(ListPenyakit* daftar_penyakit, const char* filename);

/* Membaca ListPenyakit, memindahkannya ke MapObatPenyakit sebagai key
Membaca obat_penyakit.csv dan obat.csv lalu memindahkannya ke MapObatPenyakit sebagai value (dalam bentuk Stack) */
void bacaObatPenyakit(ListPenyakit daftar_penyakit, MapObatPenyakit* map);

/* Membaca config untuk membuat Rumah Sakit dengan ADT Matrix, load queue dalam matriks,*/
void bacaConfig(MatriksRuangan* denah, ListUser* database, MapObatPenyakit map);

/* Menulis ulang config berdasarkan Matrix denah dan database user.*/
void tulisConfig(MatriksRuangan denah, ListUser database);

#endif