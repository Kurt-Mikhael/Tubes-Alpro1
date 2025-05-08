#include "..\header\adt-penyakit.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createListPenyakit(ListPenyakit* lp) {
    lp->jumlah = 0;
}

int isEmpty(ListPenyakit lp) {
    return lp.jumlah == 0;
}

int isFull(ListPenyakit lp) {
    return lp.jumlah == MAX_PENYAKIT;
}

void insertLast(ListPenyakit* lp, Penyakit p) {
    if (!isFull(*lp)) {
        lp->data[lp->jumlah] = p;
        lp->jumlah++;
    } else {
        printf("ListPenyakit penuh! Tidak bisa menambahkan.\n");
    }
}

void deleteLast(ListPenyakit* lp, Penyakit* p) {
    if (!isEmpty(*lp)) {
        *p = lp->data[lp->jumlah - 1];
        lp->jumlah--;
    } else {
        printf("ListPenyakit kosong! Tidak ada yang dihapus.\n");
    }
}

Penyakit getPenyakit(ListPenyakit lp, int index) {
    if (index >= 0 && index < lp.jumlah) {
        return lp.data[index];
    } else {
        printf("Index %d tidak valid! Mengembalikan elemen kosong.\n", index);
        Penyakit kosong = {0}; // semua field 0
        return kosong;
    }
}

