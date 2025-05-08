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
} Ruangan;

/* Struktur Matriks Ruangan Rumah Sakit*/
typedef struct
{
    
} MatriksRuangan;

void createRuangan(Ruangan* r);

void createMatriksRuangan(MatriksRuangan* m_r);

boolean isUserInMatriks(User user, MatriksRuangan matriks);

#endif