#ifndef PENYAKIT_H
#define PENYAKIT_H

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

#endif
