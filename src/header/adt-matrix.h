#ifndef ADTMATRIX_H
#define ADTMATRIX_H

#include "boolean.h"
#include "adt-user.h"
#include "adt-queue.h"

#define MAX_ROWS 26
#define MAX_COLS 10

/* Struktur Ruangan Rumah Sakit*/
typedef struct {
    int kapasitas;
    User dokter;
    Queue* antrean;
} Ruangan;

/* Struktur Matriks Ruangan Rumah Sakit*/
typedef struct {
    Ruangan ruang[MAX_ROWS][MAX_COLS];
    int row;
    int column;
} MatriksRuangan;

/* Konstruktor Ruangan */
void createRuangan(Ruangan* ruang);

/* Destruktor Ruangan */
void destroyRuangan(Ruangan* ruang);

/* Memeriksa apakah ruangan kosong */
boolean isRuanganEmpty(Ruangan ruang);

/* Konstruktor Matriks Ruangan */
void createMatriksRuangan(MatriksRuangan* denah);

/* Destruktor Matriks Ruangan */
void destroyMatriksRuangan(MatriksRuangan* denah);

/* Mencetak informasi dokter dan pasien ruangan */
void printInfoRuangan(MatriksRuangan denah, int baris, int kolom);

/* Set dokter dalam suatu ruangan dalam matriks menjadi dokter dengan id id_dokter.*/
void setDokterID(MatriksRuangan* denah, int index, int id_dokter, ListUser database);

/* Menambahkan pasien dengan id id_pasien ke antrean suatu ruangan dalam matriks*/
void addPasienToRuangan(MatriksRuangan* denah, int index, int id_pasien, ListUser database);

/* Menambah 1 baris ruangan untuk matriks ruangan dinamis */
void expandRow(MatriksRuangan* denah);

/* Menambah 1 kolom ruangan untuk matriks ruangan dinamis */
void expandCol(MatriksRuangan* denah);

/* Mengurangi 1 baris ruangan untuk matriks ruangan dinamis */
void shrinkRow(MatriksRuangan* denah);

/* Mengurangi 1 kolom ruangan untuk matriks ruangan dinamis */
void shrinkCol(MatriksRuangan* denah);

/* Memeriksa apakah user sudah ada di dalam matriks ruangan */
boolean isUserInMatriks(User user, MatriksRuangan denah);

#endif