#ifndef ADTMATRIX_H
#define ADTMATRIX_H

#include "boolean.h"
#include "adt-user.h"
#include "adt-queue.h"


/* Struktur Ruangan Rumah Sakit*/
typedef struct {
    User dokter;
    QueuePasien antrean;
    int kapasitas; 
    int pasienIds[100]; // array of pasienId
    int jumlahPasien; // jumlah pasien dalam matriks
} Ruangan;

/* Struktur Matriks Ruangan Rumah Sakit*/
typedef struct
{
    int baris; // jumlah baris
    int kolom; // jumlah kolom
    int kapasitas; // kapasitas total

    Ruangan ruangan[100]; // array of Ruangan
} MatriksRuangan;

void createRuangan(Ruangan* r);

void createMatriksRuangan(MatriksRuangan* m_r);

boolean isUserInMatriks(User user, MatriksRuangan matriks);

#endif