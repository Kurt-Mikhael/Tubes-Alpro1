#include "..\header\file-eksternal.h"
#include <stdio.h>

/*Mengisi Inventory PAsien dengan obatnya
I.S : ListUser database, userId, inventory sudah terisi
F.S : inventory pasien terisi dengan obat yang ada di database*/

void TambahObatKePasien(ListUser *database, int pasienId, int obatId, ListObat *semuaObat) {
    for (int i = 0; i < database->jumlah; i++) {
        if (database->data[i].id == pasienId) {
            if (database->data[i].inventory.jumlah < MAX_OBAT) {
                for (int j = 0; j < semuaObat->jumlah; j++) {
                    if (semuaObat->data[j].obat_id == obatId) {
                        database->data[i].inventory.data[database->data[i].inventory.jumlah] = semuaObat->data[j];
                        database->data[i].inventory.jumlah++;
                        return;
                    }
                }
            }
        }
    }
}


/*
Membaca file penyakit.csv lalu memindahkannya ke ListPenyakit lp
I.S : ListPenyakit lp sudah terisi
F.S : ListPenyakit lp terisi dengan data dari file penyakit.csv
*/
void bacaPenyakitCSV(ListPenyakit* lp, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: File %s tidak ditemukan!\n", filename);
        return;
    }

    char line[512];
    int count = 0;

    fgets(line, sizeof(line), file); // lewati header

    while (fgets(line, sizeof(line), file) && !isFull(*lp)) {
        line[strcspn(line, "\n")] = '\0'; // hapus newline

        int field = 0, pos = 0;
        char buffer[100];
        Penyakit p;

        for (int i = 0; i <= strlen(line); i++) {
            if (line[i] == ',' || line[i] == '\0') {
                buffer[pos] = '\0';
                switch (field) {
                    case 0: p.id = atoi(buffer); break;
                    case 1: strcpy(p.nama, buffer); break;
                    case 2: p.suhu_min = atof(buffer); break;
                    case 3: p.suhu_max = atof(buffer); break;
                    case 4: p.tekanan_sistolik_min = atoi(buffer); break;
                    case 5: p.tekanan_sistolik_max = atoi(buffer); break;
                    case 6: p.tekanan_diastolik_min = atoi(buffer); break;
                    case 7: p.tekanan_diastolik_max = atoi(buffer); break;
                    case 8: p.detak_jantung_min = atoi(buffer); break;
                    case 9: p.detak_jantung_max = atoi(buffer); break;
                    case 10: p.saturasi_oksigen_min = atoi(buffer); break;
                    case 11: p.saturasi_oksigen_max = atoi(buffer); break;
                }
                field++;
                pos = 0;
            } else {
                buffer[pos++] = line[i];
            }
        }
        insertLast(lp, p);
    }

    fclose(file);
}

void bacaObatPenyakit(ListPenyakit daftar_penyakit, MapObatPenyakit* map){
    FILE* file = fopen("obat_penyakit.csv", "r");
    if(!file){
        printf("file tidak dapat dibuka");
        return NULL;

    }
    int count = 0;
    char buffer[64];
    fgets(buffer, sizeof(buffer), file);

    while (fgets(buffer, sizeof(buffer), file))
    {
        (count)++;
    }
    rewind (file);
    obatpenyakit* data =  (obatpenyakit*)malloc((count) * sizeof(obatpenyakit));

    fgets(buffer, sizeof(buffer), file);

    int idx = 0;
    while (fgets(buffer, sizeof(buffer), file))
    {
        int nilai = 0;
        int cols = 0;
        int i = 0;
        while (buffer[i] != '\0')
        {
            if(buffer[i] >= '0' && buffer[i] <= '9'){
                nilai = nilai * 10 + (buffer[i] - '0');
                i++;
            }
            else if(buffer[i] == ',' || buffer[i] == '\n'){
                
                if(cols == 0){
                    data[idx].obat_id = nilai;
                }
                else if(cols == 1){
                    data[idx].penyakit_id = nilai;
                }
                else if(cols == 2){
                    data[idx].urutan_minum = nilai;
                }
                i++;
                nilai = 0;
                cols++;
            }
        }
        idx++;

    }
    // data obat untuk penyakit di simpan di obatpenyakit* data

    fclose(file);
    
}
/*
Membaca file config.txt lalu memindahkan datanya ke variabel-variabel yang sesuai
*/
void parseLineKeArray(const char* line, int* arr, int* len) {
    int i = 0, val = 0, idx = 0;
    *len = 0;
    while (line[i] != '\0' && line[i] != '\n') {
        if (line[i] >= '0' && line[i] <= '9') {
            val = val * 10 + (line[i] - '0');
        } else if (line[i] == ' ') {
            arr[idx++] = val;
            val = 0;
        }
        i++;
    }
    if (i > 0 && line[i-1] != ' ') {
        arr[idx++] = val;
    }
    *len = idx;
}

/*
Membaca file config.txt lalu memindahkan datanya ke variabel-variabel yang sesuai
I.S : MatriksRuangan denah, ListUser database, MapObatPenyakit map belum terisi, semuatObat terisi dengan obat-obat dari file obat.csv
F.S : MatriksRuangan denah, ListUser database, MapObatPenyakit map terisi dengan data dari file config.txt
*/
void bacaConfig(MatriksRuangan* denah, ListUser* database, MapObatPenyakit* map, ListObat* semuaObat) {
    FILE* file = fopen("config.txt", "r");
    if (!file) return;

    char line[256];
    int temp[128], len;

    // Baris 1: Ukuran denah
    fgets(line, 256, file);
    parseLineKeArray(line, temp, &len);
    int baris = temp[0];
    int kolom = temp[1];
    int totalRuangan = baris * kolom;

    // Baris 2: Kapasitas ruangan
    fgets(line, 256, file);
    parseLineKeArray(line, temp, &len);
    int kapasitas = temp[0];

    // Inisialisasi matriks ruangan
    createMatrixRuangan(denah, baris, kolom, kapasitas);

    // Baris 3 - (3+totalRuangan-1): Data ruangan
    for (int i = 0; i < totalRuangan; i++) {
        fgets(line, 256, file);
        parseLineKeArray(line, temp, &len);
        int dokterId = temp[0];
        setDokterID(denah, i, dokterId, *database);
        for (int j = 1; j < len; j++) {
            addPasienToRuangan(denah, i, temp[j], *database);
        }
    }

    // Baris selanjutnya: Jumlah pasien dengan obat
    fgets(line, 256, file);
    parseLineKeArray(line, temp, &len);
    int jumlahPasienObat = temp[0];

    // Pasien dengan daftar obat
    for (int i = 0; i < jumlahPasienObat; i++) {
        fgets(line, 256, file);
        parseLineKeArray(line, temp, &len);
        int pasienId = temp[0];
        for (int j = 1; j < len; j++) {
            TambahObatKePasien(database, pasienId, temp[j], semuaObat);
        }
    }
    fclose(file);
}

void saveConfig(MatriksRuangan* denah, ListUser* database, MapObatPenyakit map) {
    FILE* file = fopen("config.txt", "w");
    if (!file) {
        printf("Gagal membuka config.txt\n");
        return;
    }

    char buffer[256];

    // Baris 1: ukuran denah
    sprintf(buffer, "%d %d\n", denah->row, denah->column);
    fputs(buffer, file);

    // Baris 2: kapasitas
    sprintf(buffer, "%d\n", denah->ruang[0][0].kapasitas);
    fputs(buffer, file);

    // Baris 3-...: ruangan
    for (int i = 0; i < denah->row * denah->column; i++) {
        int pos = sprintf(buffer, "%d", denah->ruang[i/denah->column][i % denah->column].dokter.id);
        for (int j = 0; j < queueLength(*(denah->ruang[i/denah->column][i % denah->column].antrean))
        ; j++) {
            pos += sprintf(buffer + pos, " %d",dequeue(&(denah->ruang[i/denah->column][i % denah->column].antrean)).id);
        }
        sprintf(buffer + pos, "\n");
        fputs(buffer, file);
    }

    // Baris berikutnya: jumlah pasien dengan obat
    int countObat = 0;
    for (int i = 0; i < database->jumlah; i++) {
        if (database->data[i].inventory.jumlah > 0) {
            countObat++;
        }
    }
    sprintf(buffer, "%d\n", countObat);
    fputs(buffer, file);

    // Tulis data obat per pasien
    for (int i = 0; i < database->jumlah; i++) {
        if (database->data[i].inventory.jumlah > 0) {
            int pos = sprintf(buffer, "%d", database->data[i].id);
            for (int j = 0; j < database->data[i].inventory.jumlah; j++) {
                pos += sprintf(buffer + pos, " %d", database->data[i].inventory.data[j].obat_id);
            }
            sprintf(buffer + pos, "\n");
            fputs(buffer, file);
        }
    }

    fclose(file);
    printf("Berhasil menyimpan konfigurasi ke config.txt\n");
}
