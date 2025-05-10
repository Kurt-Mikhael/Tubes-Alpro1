#ifndef PENYAKIT_H
#define PENYAKIT_H

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
} Penyakit;

void createPenyakit(Penyakit* p);

/* ADT List elemen Penyakit*/

typedef struct
{
    /* data */
} ListPenyakit;

int lengthPenyakit(ListPenyakit daftar_penyakit);

Penyakit getPenyakitByID(ListPenyakit l, int id);

#endif
