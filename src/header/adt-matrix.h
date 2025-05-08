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
    ListUser pasien;
    Queue* antrean;
} Ruangan;

/* Struktur Matriks Ruangan Rumah Sakit*/
typedef struct {
    int row;
    int column;
    Ruangan ruang[MAX_ROWS][MAX_COLS];
} MatriksRuangan;

void createRuangan(Ruangan* r);

void createMatriksRuangan(MatriksRuangan* m_r);

void expandRow(MatriksRuangan* m_r);

void expandCol(MatriksRuangan* m_r);

boolean isUserInMatriks(User user, MatriksRuangan matriks);

#endif