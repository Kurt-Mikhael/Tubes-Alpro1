#include "../header/adt-matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/global.h"

//Membuat matriks ruangan
void createRuangan(Ruangan* ruang) {
    ruang->kapasitas = 0;
    createUser(&(ruang->dokter));
    ruang->antrean = createQueue(); 
}

// Menghapus matriks ruangan
void destroyRuangan(Ruangan* ruang) {
    ruang->kapasitas = 0;
    destroyQueue(ruang->antrean);
    createUser(&(ruang->dokter));
}

// Mengembalikan true jika ruangan kosong
boolean isRuanganEmpty(Ruangan ruang) {
    return !isUserValid(ruang.dokter);
}

// Mengembalikan true jika ruangan penuh
void printInfoRuangan(MatriksRuangan denah, int baris, int kolom){
    printf("--- Informasi Ruangan %c%d ---\n", baris+'A', kolom+1);
    printf("Kapasitas\t: 3\n");
    User* doc = &denah.ruang[baris][kolom].dokter;
    if (isUserValid(*doc)) {
        printf("Dokter\t\t: %s\n", doc->username);
    } else printf("Dokter\t: -\n");
    printf("Pasien di dalam ruangan:\n");
    Queue* antrean = denah.ruang[baris][kolom].antrean;
    if (isQueueEmpty(*antrean)) {
        printf("Tidak ada pasien di dalam ruangan saat ini.\n");
    } else {
        int i = 1;
        while (antrean != NULL && i <= denah.ruang[baris][kolom].kapasitas) {
            printf ("%d. %s\n", i, antrean->pasien.username);
            antrean = antrean->next;
            i++;
        }
        printf("Antrean pasien:\n");
        if (antrean == NULL) {
            printf("Tidak ada pasien dalam antrean saat ini.\n");
        }
        while (antrean != NULL && i <= max_queue) {
            printf ("%d. %s\n", i-denah.ruang[baris][kolom].kapasitas, antrean->pasien.username);
            antrean = antrean->next;
            i++;
        }
    }
    printf("\n---------------------------------------------\n");
}

//Membuat matriks ruangan (denah)
void createMatriksRuangan(MatriksRuangan* denah) {
    denah->row = 0;
    denah->column = 0;
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            createRuangan(&(denah->ruang[i][j]));
        }
    }
}

//Menambah row matriks ruangan
void expandRow(MatriksRuangan* denah) {
    denah->row++;
}

//Menambah column matriks ruangan
void expandCol(MatriksRuangan* denah) {
    denah->column++;
}

/* Mengurangi 1 baris ruangan untuk matriks ruangan dinamis */
void shrinkRow(MatriksRuangan* denah) {
    denah->row--;
}

/* Mengurangi 1 kolom ruangan untuk matriks ruangan dinamis */
void shrinkCol(MatriksRuangan* denah) {
    denah->column--;
}


//Set dokter ID ke dalam matriks ruangan
void setDokterID(MatriksRuangan* denah, int index, int id_dokter, ListUser database) {
    User* dokter = getUserByID(&database, id_dokter);
    int target_row = index / denah->column;
    int target_col = index % denah->column;
    if (strcmp(dokter->role, "dokter") == 0) {
        denah->ruang[target_row][target_col].dokter = *dokter;
    } else printf("Error: getUserByID(%d) returns an empty user\n", id_dokter);
}


//Menambahkan pasien ke dalam matriks ruangan
void addPasienToRuangan(MatriksRuangan* denah, int index, int id_pasien, ListUser database) {
    User* pasien = getUserByID(&database, id_pasien);
    int target_row = index / denah->column;
    int target_col = index % denah->column;
    if (strcmp(pasien->role, "pasien") == 0) {
        enqueue(denah->ruang[target_row][target_col].antrean, *pasien);
    }
}


//Memeriksa apakah user ada dalam matriks ruangan
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

/* Destruktor Matriks Ruangan */
void destroyMatriksRuangan(MatriksRuangan* denah) {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            destroyRuangan(&(denah->ruang[i][j]));
        }
    }
    denah->row = 0;
    denah->column = 0;
}