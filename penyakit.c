#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "penyakit.h"

int load_penyakit(const char *filename, Penyakit daftar[], int max_penyakit) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: File %s tidak ditemukan!\n", filename);
        return 0;
    }

    char line[512];
    int count = 0;

    // Lewati header
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file) && count < max_penyakit) {
        line[strcspn(line, "\n")] = '\0'; // hapus newline

        int field = 0, pos = 0;
        char buffer[100];

        for (int i = 0; i <= strlen(line); i++) {
            if (line[i] == ',' || line[i] == '\0') {
                buffer[pos] = '\0';
                switch (field) {
                    case 0: daftar[count].id = atoi(buffer); break;
                    case 1: strcpy(daftar[count].nama, buffer); break;
                    case 2: daftar[count].suhu_min = atof(buffer); break;
                    case 3: daftar[count].suhu_max = atof(buffer); break;
                    case 4: daftar[count].tekanan_sistolik_min = atoi(buffer); break;
                    case 5: daftar[count].tekanan_sistolik_max = atoi(buffer); break;
                    case 6: daftar[count].tekanan_diastolik_min = atoi(buffer); break;
                    case 7: daftar[count].tekanan_diastolik_max = atoi(buffer); break;
                    case 8: daftar[count].detak_jantung_min = atoi(buffer); break;
                    case 9: daftar[count].detak_jantung_max = atoi(buffer); break;
                    case 10: daftar[count].saturasi_oksigen_min = atoi(buffer); break;
                    case 11: daftar[count].saturasi_oksigen_max = atoi(buffer); break;
                }
                field++;
                pos = 0;
            } else {
                buffer[pos++] = line[i];
            }
        }
        count++;
    }

    fclose(file);
    return count;
}
