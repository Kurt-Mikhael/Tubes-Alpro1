#ifndef OBAT_PENYAKIT_H
#define OBAT_PENYAKIT_H

typedef struct 
{
    int obat_id;
    int penyakit_id;
    int urutan_minum;
} obatpenyakit;

obatpenyakit* load_obat_penyakit(const char* namafile, int* count);

void freeObatPenyakit(obatpenyakit* data);

#endif
