#include "../header/adt-stack.h"
#include <stdio.h>
#include "../header/global.h"  // Diasumsikan berisi definisi Obat, createObat, dll

/* Konstruktor Stack */
void createStackObat(StackObat* s_o) {
    s_o->top = -1;
}

/* Destruktor Stack */
void destroyStackObat(StackObat* s_o) {
    // Bisa dikosongkan manual jika ingin clear data (opsional)
    for (int i = 0; i <= s_o->top; i++) {
        createObat(&s_o->data[i]);  // Reset ke default
    }
    s_o->top = -1;
}

/* Memeriksa apakah stack kosong */
boolean isStackEmpty(StackObat s_o) {
    return s_o.top == -1;
}

/* Memeriksa apakah stack penuh */
boolean isStackFull(StackObat s_o) {
    return s_o.top >= STACK_MAX_CAPACITY - 1;
}

/* Menghitung jumlah elemen dalam stack */
int stackLength(StackObat s_o) {
    return s_o.top + 1;
}

/* Mendapatkan elemen teratas tanpa menghapusnya */
Obat getTopStack(StackObat s_o) {
    if (isStackEmpty(s_o)) {
        Obat emptyObat;
        createObat(&emptyObat);  // Isi default
        return emptyObat;
    }
    return s_o.data[s_o.top];
}

/* Menambahkan elemen ke tumpukan */
void pushStack(StackObat* s_o, Obat o) {
    if (!isStackFull(*s_o)) {
        s_o->data[++(s_o->top)] = o;
    } else {
        printf("Stack penuh! Tidak bisa menambahkan obat.\n");
    }
}

/* Mengeluarkan elemen teratas dari tumpukan */
Obat popStack(StackObat* s_o) {
    if (!isStackEmpty(*s_o)) {
        return s_o->data[(s_o->top)--];
    } else {
        Obat emptyObat;
        createObat(&emptyObat);
        return emptyObat;
    }
}

/* Menampilkan isi stack */
void printStackObat(StackObat s) {
    if (isStackEmpty(s)) {
        printf("Stack kosong!\n");
        return;
    }
    
    printf("Isi Stack (atas -> bawah):\n");
    for (int i = s.top; i >= 0; i--) {
        printf(" (ID: %d) %s\n", s.data[i].obat_id, s.data[i].nama_obat);
    }
}

