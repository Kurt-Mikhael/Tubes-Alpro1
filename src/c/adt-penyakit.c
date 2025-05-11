#include "..\header\adt-penyakit.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createPenyakit(Penyakit* p) {
    p->id = 0;
    strcpy(p->nama, "");
    p->suhu_min = 0;
    p->suhu_max = 0;
    p->tekanan_sistolik_min = 0;
    p->tekanan_sistolik_max = 0;
    p->tekanan_diastolik_min = 0;
    p->tekanan_diastolik_max = 0;
    p->detak_jantung_min = 0;
    p->detak_jantung_max = 0;
    p->saturasi_oksigen_min = 0;
    p->saturasi_oksigen_max = 0;
}

boolean isPenyakitValid(Penyakit p) {
    return p.id != 0 && strcasecmp(p.nama, "") != 0;
}


void createListPenyakit(ListPenyakit* lp) {
    for (int i = 0; i < MAX_PENYAKIT; i++) {
        createPenyakit(&lp->data[i]);
    }
    lp->jumlah = 0;
}

int lengthPenyakit(ListPenyakit database_penyakit) {
    return database_penyakit.jumlah;
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

Penyakit getPenyakitByName(ListPenyakit daftar_penyakit, char* nama) {
    for (int i = 0; i < daftar_penyakit.jumlah; i++) {
        if (strcasecmp(nama, daftar_penyakit.data[i].nama) == 0) {
            return daftar_penyakit.data[i];
        }
    }
    Penyakit p; createPenyakit(&p);
    return p;
}