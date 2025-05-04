#include <stdio.h>
#include <stdlib.h>
#include "obat.h"

int main() {
    Obat daftarObat[25];
    if (load_obat(daftarObat) == -1) {
        printf("Gagal memuat daftar obat.\n");
    } else {
        printf("ID\tNAMA\n");
        for (int i = 0; i < 25; i++) {
            printf("%d\t%s\n", daftarObat[i].obat_id, daftarObat[i].nama_obat);
        }
    }
    printf("Terminating...");
}