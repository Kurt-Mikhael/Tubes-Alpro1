#ifndef ADTMATRIX_H
#define ADTMATRIX_H

#include "adt-user.h"
#include "adt-queue.h"

typedef struct {
    User dokter;
    QueuePasien antrean;
    int jumlahPasien;
} Ruangan;

typedef struct
{
    /* data */
} MatriksRuangan;

void createRuangan(Ruangan* r);

void createMatriksRuangan(MatriksRuangan* m_r);

#endif