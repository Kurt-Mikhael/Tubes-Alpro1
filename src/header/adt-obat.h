#ifndef ADTOBAT_H
#define ADTOBAT_H

#define MAX_OBAT 100 // Maksimal jumlah obat dalam satu penyakit
typedef struct
{
    int obat_id;
    char nama_obat[100];
} Obat;

void createObat(Obat* o);

int isObatValid(Obat o);

/* ADT List elemen Obat*/

typedef struct 
{
    Obat data[MAX_OBAT];
    int jumlah;
} ListObat;

/*Mengisi list obat dengan MARK*/
void createListObat(ListObat* l);

int isEmptyObat(ListObat l);

int isFullObat(ListObat l);

void insertLastObat(ListObat* l, Obat o);

void deleteLastObat(ListObat* l, Obat* o);

int lengthObat(ListObat l);




#endif