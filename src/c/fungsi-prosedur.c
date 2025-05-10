#include <stdio.h>
#include <string.h>
#include "..\header\adt-obat.h"
#include "..\header\adt-penyakit.h"
#include "..\header\adt-user.h"
#include "..\header\adt-map.h"
#include "..\header\adt-matrix.h"
#include "..\header\adt-queue.h"
#include "..\header\adt-set.h"
#include "..\header\adt-stack.h"
#include "..\header\file-eksternal.h"
#include "..\header\fungsi-prosedur.h"

void login(User* current_user, ListUser database);

void registerPasien(UsernameSet* username, ListUser* database);

void logout(User* current_user);

void lupaPassword(ListUser* database);

void help(User current_user, MatriksRuangan matriks);

void lihatDenah(User current_user, MatriksRuangan denah) {

    // Validasi login
    if (!isUserValid(current_user)) {
        printf("Login untuk melihat denah!\n");
        return;
    }

    // Display matriks ruangan
    for (int i = 0; i < denah.row; i++) {
        for (int j = 0; j < denah.column; j++) {
            printf("+----");
            if (j == denah.column-1) printf("+\n");
            printf("| %c%d ", (char)(i+65), j+1);
            if (j == denah.column-1) printf("|\n");
            if (i == denah.row - 1 && j < denah.column-1) printf("+----");
            if (i == denah.row - 1 && j == denah.column-1) printf("+\n");
        }
    }
}

void lihatRuangan(User current_user, MatriksRuangan denah) {
    lihatDenah(current_user, denah);
    printf("Kode ruangan: ");
    char kode[4];
    fgets(kode, sizeof(kode), stdin);
    if (strlen(kode) < 2) {
        printf("Kode ruangan salah!\n");
        return;
    }
    if (kode[0] > 'Z') kode[0] = (char)(kode[0]+'A'-'a');
    if ((0 <= (kode[0] - 'A') && (kode[0] - 'A') < denah.row)) {
        int baris = kode[0] - 'A';
        int kolom = 0;
        if ('0' <= kode[1] && kode[1] <= '9') {
            kolom += kode[1] - '0';
            if ('0' <= kode[2] && kode[2] <= '9') {
                kolom = 10*kolom + kode[2] - '0';
            }
        printInfoRuangan(denah, baris, kolom);
        } else {
            printf("Kode ruangan salah!\n");
            return;
        }
    } else {
        printf("Kode ruangan salah!\n");
        return;
    }
}