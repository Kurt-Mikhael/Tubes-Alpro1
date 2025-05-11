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
    createUser(&current_user); // done

    // load data penyakit dari csv
    ListPenyakit database_penyakit;
    createListPenyakit(&database_penyakit); // done
    bacaPenyakitCSV(folderName, &database_penyakit); // done

    // load data obat dari csv
    ListObat daftar_obat;
    createListObat(&daftar_obat); // done
    bacaObatCSV(folderName, &daftar_obat); // done

    // load data akun dari csv
    ListUser database_user;
    createListUser(&database_user); // done
    bacaUserCSV(folderName, &database_user, database_penyakit); // done
    
    // copy semua username di database ke set
    UsernameSet daftar_username;
    createUsernameSet(&daftar_username); // done
    copyListToSet(database_user, &daftar_username); // done

    // load urutan obat untuk penyakit (tunda dulu)
    // MapObatPenyakit resep_obat;
    // createMap(&resep_obat);
    // bacaObatPenyakit(folderName, database_penyakit, daftar_obat, &resep_obat);

    // load matriks ruangan
    MatriksRuangan rumah_sakit;
    createMatriksRuangan(&rumah_sakit);
    bacaConfig(folderName, &rumah_sakit, &database_user, daftar_obat);

    char command[32] = "";
    while (strcasecmp(command, "EXIT") != 0) {
        strcpy(command, "");
        scanf("%d", command);
        if (strcasecmp(command, "LOGIN") == 0) {
            login(&current_user, database_user);
        } else if (strcasecmp(command, "REGISTER") == 0) {
            registerPasien(&daftar_username, &database_user);
        } else if (strcasecmp(command, "LOGOUT") == 0) {
            logout(&current_user);
        } else if (strcasecmp(command, "LUPA_PASSWORD") == 0) {
            lupaPassword(&database_user);
        } else if (strcasecmp(command, "HELP") == 0) {
            help(current_user, rumah_sakit);
        } else if (strcasecmp(command, "LIHAT_DENAH") == 0) {
            lihatDenah(current_user, rumah_sakit);
        } else if (strcasecmp(command, "LIHAT_RUANGAN") == 0) {
            lihatRuangan(current_user, rumah_sakit);
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
    if (opt == 'Y') saveConfig(folderName, &rumah_sakit, &database_user);
    destroyUser(&current_user);
    destroyListUser(&database_user);
    // destroyMap(&resep_obat);
    destroyMatriksRuangan(&rumah_sakit);
}