#include <stdio.h>
#include <stdlib.h>
#include "obat.h"

int load_obat(Obat daftar[]) {
    FILE *file = fopen("obat.csv", "r");
    if (file == NULL) {
        printf("Error: File obat.csv tidak ditemukan!\n");
        return -1;
    }

    char line[64];
    int count = 0;

    // Lewati header
    fgets(line, sizeof(line), file);
    while (fgets(line, 64, file)) {
        Obat o;
        int id = 0;
        char nama[64];
        int i = 0, j = 0;
        while (i < 64 && line[i] != ',') {
            id *= 10;
            id += (line[i] - '0');
            i++;
        }
        i++;
        while (i+j < 64 && !(line[i+j] == '\0' || line[i+j] == '\n')) {
            nama[j] = line[i+j];
            j++;
        }
        nama[j] = '\0';
        o.obat_id = id;
        for (int k = 0; k <=j; k++) {
            o.nama_obat[k] = nama[k];
        }
        daftar[count] = o;
        count++;
    }
    fclose(file);
    return count;
}