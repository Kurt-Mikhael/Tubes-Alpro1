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
