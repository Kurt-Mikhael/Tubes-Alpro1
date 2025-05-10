#ifndef ADTMAP_H
#define ADTMAP_H

#include "adt-penyakit.h"
#include "adt-stack.h"

typedef struct
{ // dummy
    StackObat map[100];
} MapObatPenyakit;

void createMap(MapObatPenyakit* m_o_p);

void destroyMap(MapObatPenyakit* m_o_p);

void printMap();

#endif