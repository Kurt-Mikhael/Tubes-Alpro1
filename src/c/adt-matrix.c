#include "..\header\adt-matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createRuangan(Ruangan* ruang) {
    ruang->kapasitas = 0;
    createUser(&(ruang->dokter));
    ruang->antrean = createQueue();
}

void destroyRuangan(Ruangan* ruang) {
    ruang->kapasitas = 0;
    destroyQueue(ruang->antrean);
    createUser(&(ruang->dokter));
}

void printInfoRuangan(MatriksRuangan denah, int baris, int kolom){
    printf("--- Informasi Ruangan %c%d ---\n", baris+'A', kolom);
    printf("Kapasitas\t: 3\n");
    User* doc = &denah.ruang[baris][kolom].dokter;
    if (isUserValid(*doc)) {
        printf("Dokter\t: %s\n", doc->username);
    } else printf("Dokter\t: -\n");
    printf("Pasien di dalam ruangan:\n");
    Queue* antrean = denah.ruang[baris][kolom].antrean;
    if (isEmpty(*antrean)) {
        printf("Tidak ada pasien di dalam ruangan saat ini.\n");
    } else {
        for (int i = 1; i <= queueLength(*antrean); i++) {
            printf ("%d.\t%s\n", i, *antrean->pasien.username);
            antrean = antrean->next;
        }
    }
    printf("---------------------------------------------\n");
}

void createMatriksRuangan(MatriksRuangan* denah) {
    denah->row = 0;
    denah->column = 0;
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            createRuangan(&(denah->ruang[i][j]));
        }
    }
}

void expandRow(MatriksRuangan* denah) {
    denah->row++;
}

void expandCol(MatriksRuangan* denah) {
    denah->column++;
}

void setDokterID(MatriksRuangan* denah, int index, int id_dokter, ListUser database) {
    User dokter = getUserByID(database, id_dokter);
    int target_row = index / denah->column;
    int target_col = index % denah->column;
    if (strcmp(dokter.role, "dokter") == 0) {
        denah->ruang[target_row][target_col].dokter = dokter;
    }
}

void addPasienToRuangan(MatriksRuangan* denah, int index, int id_pasien, ListUser database) {
    User pasien = getUserByID(database, id_pasien);
    int target_row = index / denah->column;
    int target_col = index % denah->column;
    if (strcmp(pasien.role, "pasien") == 0) {
        enqueue(denah->ruang[target_row][target_col].antrean, pasien);
    }
}

boolean isUserInMatriks(User user, MatriksRuangan denah) {
    if (strcmp(user.role, "dokter") == 0) {
        // Mencari dokter dalam denah
        for (int i = 0; i < denah.row; i++) {
            for (int j = 0; j < denah.column; j++) {
                if (isSameUser((denah.ruang[i][j]).dokter, user)) {
                    return TRUE;
                }
            }
        }
    } else if (strcmp(user.role, "pasien") == 0) {
        // Mencari pasien dalam denah
        for (int i = 0; i < denah.row; i++) {
            for (int j = 0; j < denah.column; j++) {
                if (findInQueue(*(denah.ruang[i][j]).antrean, user) != -1) {
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}