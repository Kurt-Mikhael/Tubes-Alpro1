#include "..\header\adt-matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createRuangan(Ruangan* ruang) {
    ruang->kapasitas = 0;
    createUser(&(ruang->dokter));
    createListUser(&(ruang->pasienMasuk));
    ruang->antrean = createQueue();
}

void destroyRuangan(Ruangan* ruang) {
    ruang->kapasitas = 0;
    
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