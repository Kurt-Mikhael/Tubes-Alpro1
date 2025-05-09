#include <stdio.h>
#include <stdlib.h>
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

    User* current_user;
    createUser(current_user);

    ListUser database_user;
    createListUser(&database_user);
    bacaUserCSV(&database_user);
    
    UsernameSet daftar_username;
    createUsernameSet(&daftar_username);

    Load("if1210-tubes-2025-k01-i" /*nama folder*/);
    char command[32];
    /*
    pokoknya while command bukan exit, minta command, jalanin command pake if else if else ds
    */
    exitRumahSakit(database_user);
}