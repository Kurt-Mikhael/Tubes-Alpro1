#ifndef OBAT_H
#define OBAT_H

typedef struct
{
    int obat_id;
    char nama_obat[64];
} Obat;

int load_obat(Obat daftar[]);

#endif