#ifndef ADTOBAT_H
#define ADTOBAT_H

typedef struct
{
    int obat_id;
    char* nama_obat;
} Obat;

void createObat(Obat* o);

int isObatValid(Obat o);

/* ADT List elemen Obat*/

typedef struct 
{
    /* data */
} ListObat;

#endif