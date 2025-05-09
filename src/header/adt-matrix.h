#ifndef ADTMATRIX_H
#define ADTMATRIX_H

#include "boolean.h"
#include "adt-user.h"
#include "adt-queue.h"

#define MAX_ROWS 10
#define MAX_COLS 10

/* Struktur Ruangan Rumah Sakit*/
typedef struct {
    int kapasitas;
    User dokter;
    ListUser pasienMasuk;
    Queue* antrean;
} Ruangan;

/* Struktur Matriks Ruangan Rumah Sakit*/
typedef struct {
    int row;
    int column;
    Ruangan ruang[MAX_ROWS][MAX_COLS];
} MatriksRuangan;

void createRuangan(Ruangan* ruang);

void destroyRuangan(Ruangan* ruang);

void createMatriksRuangan(MatriksRuangan* denah);

void destroyMatriksRuangan(MatriksRuangan* denah);

void expandRow(MatriksRuangan* denah);

void expandCol(MatriksRuangan* denah);

boolean isUserInMatriks(User user, MatriksRuangan denah);

#endif