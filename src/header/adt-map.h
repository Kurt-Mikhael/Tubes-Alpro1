#ifndef ADTMAP_H
#define ADTMAP_H

#include "adt-penyakit.h"
#include "adt-obat.h"
#include "adt-stack.h"

typedef struct {
    char key[50];        // nama penyakit
    ListObat value;      // list obat untuk penyakit itu
} MapEntry;

typedef struct {
    MapEntry data[MAX_PENYAKIT];
    int length;          // jumlah entry aktif
} MapObatPenyakit;

/*Konstruktor Map*/
void createMap(MapObatPenyakit* m_o_p);

/*Destruktor Map*/
void destroyMap(MapObatPenyakit* m_o_p);


/*Memprint obat yang digunakan untuk menyembuhkan suatu penyakit*/
void printMapObatPenyakit(MapObatPenyakit map, int length);
#endif