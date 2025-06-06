#include "../header/adt-penyakit.h"
#include "../header/global.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fungsi untuk membuat penyakit baru
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

// Fungsi untuk memeriksa apakah penyakit valid
boolean isPenyakitValid(Penyakit p) {
    return p.id != 0 && strcasecmp(p.nama, "") != 0;
}


// Fungsi untuk membuat list penyakit
void createListPenyakit(ListPenyakit* lp) {
    for (int i = 0; i < MAX_PENYAKIT; i++) {
        createPenyakit(&lp->data[i]);
    }
    lp->jumlah = 0;
}

// Fungsi untuk menampilkan semua penyakit dalam list
int lengthPenyakit(ListPenyakit database_penyakit) {
    return database_penyakit.jumlah;
}


int isPenyakitEmpty(ListPenyakit lp) {
    return lp.jumlah == 0;
}

// Fungsi untuk memeriksa apakah list penyakit sudah penuh
int isPenyakitFull(ListPenyakit lp) {
    return lp.jumlah == MAX_PENYAKIT;
}


// Fungsi untuk menambahkan penyakit ke list
void insertPenyakitLast(ListPenyakit* lp, Penyakit p) {
    if (!isPenyakitFull(*lp)) {
        lp->data[lp->jumlah] = p;
        lp->jumlah++;
    } else {
        printf("ListPenyakit penuh! Tidak bisa menambahkan.\n");
    }
}

// Fungsi untuk menghapus penyakit terakhir dari list
void deletePenyakitLast(ListPenyakit* lp, Penyakit* p) {
    if (!isPenyakitEmpty(*lp)) {
        *p = lp->data[lp->jumlah - 1];
        lp->jumlah--;
    } else {
        printf("ListPenyakit kosong! Tidak ada yang dihapus.\n");
    }
}

// Fungsi untuk menghapus penyakit berdasarkan ID
Penyakit getPenyakit(ListPenyakit lp, int index) {
    if (index >= 0 && index < lp.jumlah) {
        return lp.data[index];
    } else {
        printf("Index %d tidak valid! Mengembalikan elemen kosong.\n", index);
        Penyakit kosong = {0}; // semua field 0
        return kosong;
    }
}

// Fungsi untuk mendapatkan penyakit berdasarkan nama
Penyakit getPenyakitByName(ListPenyakit daftar_penyakit, char* nama) {
    for (int i = 0; i < daftar_penyakit.jumlah; i++) {
        if (strcasecmp(nama, daftar_penyakit.data[i].nama) == 0) {
            return daftar_penyakit.data[i];
        }
    }
    Penyakit p; createPenyakit(&p);
    return p;
}