#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header\adt-obat.h"
#include "header\adt-penyakit.h"
#include "header\adt-user.h"
#include "header\adt-map.h"
#include "header\adt-matrix.h"
#include "header\adt-queue.h"
#include "header\adt-set.h"
#include "header\adt-stack.h"
#include "header\file-eksternal.h"
#include "header\fungsi-prosedur.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Tidak ada nama folder yang diberikan!\n");
        printf("Usage : ./main <<nama_folder>>\n");
        return EXIT_FAILURE;
    }

    const char *folderName = argv[1];
    if (!folderExists(folderName)) {
        printf("Folder \"%s\" tidak ditemukan.\n", folderName);
        return EXIT_FAILURE;
    }

    printf("Loading...\n");

    // inisialisasi pengguna
    User current_user;
    createUser(&current_user);

    // load data akun dari csv
    ListUser database_user;
    createListUser(&database_user);
    bacaUserCSV(&database_user);
    
    // copy semua username di database ke set
    UsernameSet daftar_username;
    createUsernameSet(&daftar_username);
    copyListToSet(database_user, &daftar_username);

    // load data penyakit dari csv
    ListPenyakit database_penyakit;
    createListPenyakit(&database_penyakit);
    bacaPenyakitCSV(&database_penyakit);

    // load data obat dari csv
    ListObat daftar_obat;
    createListObat(&daftar_obat);
    bacaObatCSV(&daftar_obat);

    // load urutan obat untuk penyakit
    MapObatPenyakit resep_obat;
    createMap(&resep_obat);
    bacaObatPenyakit(database_penyakit, daftar_obat, &resep_obat);

    // load matriks ruangan
    MatriksRuangan rumah_sakit;
    createMatriksRuangan(&rumah_sakit);
    bacaConfig(&rumah_sakit, &database_user, resep_obat, &daftar_obat);

    Load("if1210-tubes-2025-k01-i" /*nama folder*/);
    char command[32] = "";
    while (strcmp(command, "EXIT") != 0) {
        scanf("%d", command);
        if (strcmp(command, "LOGIN") == 0) {
            login(&current_user, database_user);
        } else if (strcmp(command, "REGISTER") == 0) {
            registerPasien(&daftar_username, &database_user);
        } else if (strcmp(command, "LOGOUT") == 0) {
            logout(&current_user);
        } else if (strcmp(command, "LUPA_PASSWORD") == 0) {
            lupaPassword(&database_user);
        } else if (strcmp(command, "HELP") == 0) {
            help(current_user, rumah_sakit);
        } else if (strcmp(command, "LIHAT_DENAH") == 0) {
            lihatDenah(rumah_sakit);
        } else {
            printf("Command invalid!\n");
            printf("Masukkan \"HELP\" jika anda tidak tahu harus apa:)\n");
        }
    }
    char opt = ' ';
    do {
        printf("Mau save perubahan? (Y/N)\n");
        scanf("%c", &opt);
    } while (opt != 'Y' && opt != 'N');
    if (opt == 'Y') tulisConfig(rumah_sakit, database_user);
    destroyUser(&current_user);
    destroyListUser(&database_user);
    destroyMap(&resep_obat);
    destroyMatriksRuangan(&rumah_sakit);
}