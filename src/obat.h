#ifndef OBAT_H
#define OBAT_H
#define MAX_OBAT 100

typedef struct
{
    int obat_id;
    char nama_obat[64];
} Obat;

int load_obat(Obat daftar[]);

#endif