#ifndef PENYAKIT_H
#define PENYAKIT_H

#include "boolean.h"

#define MAX_PENYAKIT 100 // Maksimal jumlah penyakit
#define MAX_OBAT 100 // Maksimal jumlah obat dalam satu penyakit
typedef struct {    int id;
    char nama[50];
    float suhu_min;
    float suhu_max;
    float tekanan_sistolik_min;
    float tekanan_sistolik_max;
    float tekanan_diastolik_min;
    float tekanan_diastolik_max;
    float detak_jantung_min;
    float detak_jantung_max;
    float saturasi_oksigen_min;
    float saturasi_oksigen_max;
    float kadar_gula_min;
    float kadar_gula_max;
    float berat_badan_min;
    float berat_badan_max;
    float tinggi_badan_min;
    float tinggi_badan_max;    
    float kadar_kolesterol_min;
    float kadar_kolesterol_max;
    float trombosit_min;
    float trombosit_max;
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

int isPenyakitEmpty(ListPenyakit lp);

int isPenyakitFull(ListPenyakit lp);

void insertPenyakitLast(ListPenyakit* lp, Penyakit p);

void deletePenyakitLast(ListPenyakit* lp, Penyakit* p);

Penyakit getPenyakit(ListPenyakit lp, int index);

Penyakit getPenyakitByName(ListPenyakit daftar_penyakit, char* nama);

#endif