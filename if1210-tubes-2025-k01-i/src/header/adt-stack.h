#ifndef ADTSTACK_H
#define ADTSTACK_H

#include "adt-obat.h"
#include "boolean.h"

#define STACK_MAX_CAPACITY 50

typedef struct {
    Obat data[STACK_MAX_CAPACITY];
    int top;
} StackObat;

/* Konstruktor Stack */
void createStackObat(StackObat* s_o);

/* Destruktor Stack */
void destroyStackObat(StackObat* s_o);

/* Memeriksa apakah stack kosong */
boolean isStackEmpty(StackObat s_o);

/* Memeriksa apakah stack penuh */
boolean isStackFull(StackObat s_o);

/* Menghitung jumlah elemen dalam stack */
int stackLength(StackObat s_o);

/* Mendapatkan elemen teratas tanpa menghapusnya */
Obat getTopStack(StackObat s_o);

/* Menambahkan elemen ke tumpukan */
void pushStack(StackObat* s_o, Obat o);

/* Mengeluarkan elemen teratas dari tumpukan */
Obat popStack(StackObat* s_o);

/* Menampilkan isi stack */
void printStackObat(StackObat s); //Deklarasi
#endif