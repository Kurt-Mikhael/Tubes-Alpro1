#ifndef PENYAKIT_H
#define PENYAKIT_H

#include "boolean.h"

#define MAX_PENYAKIT 100 // Maksimal jumlah penyakit
#define MAX_OBAT 100 // Maksimal jumlah obat dalam satu penyakit
typedef struct {
    int id;
    char nama[50];
    float suhu_min;
    float suhu_max;
    int tekanan_sistolik_min;
    int tekanan_sistolik_max;
    int tekanan_diastolik_min;
    int tekanan_diastolik_max;
    int detak_jantung_min;
    int detak_jantung_max;
    int saturasi_oksigen_min;
    int saturasi_oksigen_max;
    int kadar_gula_min;
    int kadar_gula_max;
    float berat_badan_min;
    float berat_badan_max;
    int tinggi_badan_min;
    int tinggi_badan_max;
    int kadar_kolesterol_min;
    int kadar_kolesterol_max;
    int kadar_kolesterol_ldl_min;
    int kadar_kolesterol_ldl_max;
    int trombosit_min;
    int trombosit_max;
} Penyakit;

void createPenyakit(Penyakit* p);

boolean isPenyakitValid(Penyakit p);

/* ADT List elemen Penyakit*/

typedef struct
{
    Penyakit data[MAX_PENYAKIT];
    int jumlah;
} ListPenyakit;

void createListPenyakit(ListPenyakit* database_penyakit);

int lengthPenyakit(ListPenyakit database_penyakit);

int isEmpty(ListPenyakit lp);

int isFull(ListPenyakit lp);

void insertLast(ListPenyakit* lp, Penyakit p);

void deleteLast(ListPenyakit* lp, Penyakit* p);

Penyakit getPenyakit(ListPenyakit lp, int index);

Penyakit getPenyakitByName(ListPenyakit daftar_penyakit, char* nama);

#endif