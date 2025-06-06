#include "../header/adt-map.h"
#include "../header/global.h"
#include <stdio.h>
#include <string.h>

// Prosedur untuk membuat MapObatPenyakit
void createMap(MapObatPenyakit* m_o_p) {
    m_o_p->length = 0;
    for (int i = 0; i < MAX_PENYAKIT; i++) {
        strcpy(m_o_p->data[i].key, "");
        createListObat(&m_o_p->data[i].value);
    }
}

// Prosedur untuk menghapus entri pada MapObatPenyakit
void destroyMap(MapObatPenyakit* m_o_p) {    
    for (int i = 0; i < m_o_p->length; i++) {
        createListObat(&m_o_p->data[i].value);
    }
    m_o_p->length = 0;
}


// Prosedur untuk print MapObatPenyakit
void printMapObatPenyakit(MapObatPenyakit map, int length) {
    printf("== Daftar Obat untuk Penyakit ==\n");
    for (int i = 0; i < map.length; i++) {
        if (strcmp(map.data[i].key, "") != 0) {
            printf("Penyakit: %s\n", map.data[i].key);
            printf("Obat yang harus diminum (urutan dari yang pertama):\n");
            
            // Buat salinan list untuk tampilan
            ListObat tempObat = map.data[i].value;
              if (isEmptyObat(tempObat)) {
                printf("  Tidak ada obat yang terdaftar\n");
            } else {
                printListObat(tempObat);
                printf("\n");
            }
        }
    }
    printf("===============================\n");
}