#ifndef ADTOBAT_H
#define ADTOBAT_H

#define MAX_OBAT 100 // Maksimal jumlah obat dalam satu penyakit
typedef struct
{
    int obat_id;
    char nama_obat[100];
} Obat;


void createObat(Obat* new_obat);


/*Returnt true jika obat valid*/
int isObatValid(Obat obat);

/* ADT List elemen Obat*/

typedef struct 
{
    Obat data[MAX_OBAT];
    int jumlah;
} ListObat;

/*Mengisi list obat dengan MARK*/
void createListObat(ListObat*  list_obat);

/*Mengembalikan true jika list obat kosong*/
int isEmptyObat(ListObat list_obat);

/*Mengembalikan true jika list obat penuh*/
int isFullObat(ListObat     list_obat);

/*Menambahkan obat ke list obat*/
void insertLastObat(ListObat* list_obat , Obat obat);

void deleteLastObat(ListObat* list_obat, Obat* obat);

int lengthListObat(ListObat list_obat);

Obat getObatByID(ListObat list_obat, int id);

/*Mencetak isi list obat*/
void printListObat(ListObat s);

#endif