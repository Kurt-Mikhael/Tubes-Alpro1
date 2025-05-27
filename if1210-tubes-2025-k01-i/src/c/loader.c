#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/global.h"
#include "../header/loader.h"

void loadData(const char *folderName, ListUser *database_user, ListPenyakit *database_penyakit, ListObat *daftar_obat, MapObatPenyakit *map, MatriksRuangan *denah_ruang, int *max_queue) {
    // Load penyakit dari CSV
    createListPenyakit(database_penyakit);
    bacaPenyakitCSV(folderName, database_penyakit);
    printf("Data penyakit berhasil dimuat.\n");
    
    // Load obat dari CSV
    createListObat(daftar_obat);
    bacaObatCSV(folderName, daftar_obat);
    printf("Data penyakit dan obat berhasil dimuat.\n");
    
    // Load user dari CSV
    createListUser(database_user, BASE_CAP);
    bacaUserCSV(folderName, database_user, *database_penyakit);
    printf("Data user berhasil dimuat.\n");
    
    // Load obat penyakit dari CSV
    createMap(map);
    bacaObatPenyakit(folderName, *database_penyakit, *daftar_obat, map);    
    printf("Data penyakit, obat, dan obat penyakit berhasil dimuat.\n");

    // Load konfigurasi dari config.txt
    createMatriksRuangan(denah_ruang);
    bacaConfig(folderName, denah_ruang, database_user, *daftar_obat, max_queue);
    printf("Konfigurasi berhasil dimuat.\n");
    printf("Seluruh data berhasil dimuat dari folder: %s\n\n", folderName);
}

