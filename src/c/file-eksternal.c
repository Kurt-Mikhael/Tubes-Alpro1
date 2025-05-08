#include "..\header\file-eksternal.h"
#include <stdio.h>


void bacaPenyakitCSV(ListPenyakit* lp, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: File %s tidak ditemukan!\n", filename);
        return;
    }

    char line[512];
    int count = 0;

    fgets(line, sizeof(line), file); // lewati header

    while (fgets(line, sizeof(line), file) && !isFull(*lp)) {
        line[strcspn(line, "\n")] = '\0'; // hapus newline

        int field = 0, pos = 0;
        char buffer[100];
        Penyakit p;

        for (int i = 0; i <= strlen(line); i++) {
            if (line[i] == ',' || line[i] == '\0') {
                buffer[pos] = '\0';
                switch (field) {
                    case 0: p.id = atoi(buffer); break;
                    case 1: strcpy(p.nama, buffer); break;
                    case 2: p.suhu_min = atof(buffer); break;
                    case 3: p.suhu_max = atof(buffer); break;
                    case 4: p.tekanan_sistolik_min = atoi(buffer); break;
                    case 5: p.tekanan_sistolik_max = atoi(buffer); break;
                    case 6: p.tekanan_diastolik_min = atoi(buffer); break;
                    case 7: p.tekanan_diastolik_max = atoi(buffer); break;
                    case 8: p.detak_jantung_min = atoi(buffer); break;
                    case 9: p.detak_jantung_max = atoi(buffer); break;
                    case 10: p.saturasi_oksigen_min = atoi(buffer); break;
                    case 11: p.saturasi_oksigen_max = atoi(buffer); break;
                }
                field++;
                pos = 0;
            } else {
                buffer[pos++] = line[i];
            }
        }
        insertLast(lp, p);
    }

    fclose(file);
}

