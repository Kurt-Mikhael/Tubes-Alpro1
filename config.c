#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256
#define MAX_CAP 100

// Struktur ruangan rumah sakit
typedef struct {
    int dokterId;
    int *pasienIds;
    int jumlahPasien;
} Ruangan;

// Struktur utama konfigurasi
typedef struct {
    int baris, kolom;
    int kapasitas;
    Ruangan *ruangan;
    int jumlahRuangan;

    int jumlahPasienObat;
    int *pasienObatId;
    int **obatPasien;
    int *jumlahObat;
} Config;

// Fungsi untuk menginisialisasi konfigurasi
void initConfig(Config *cfg) {
    cfg->baris = 0;
    cfg->kolom = 0;
    cfg->kapasitas = 0;
    cfg->ruangan = NULL;
    cfg->jumlahRuangan = 0;
    cfg->jumlahPasienObat = 0;
    cfg->pasienObatId = NULL;
    cfg->obatPasien = NULL;
    cfg->jumlahObat = NULL;
}

// Fungsi untuk membebaskan memori yang dialokasikan untuk konfigurasi
void freeConfig(Config *cfg) {
    for (int i = 0; i < cfg->jumlahRuangan; i++) {
        free(cfg->ruangan[i].pasienIds);
    }
    free(cfg->ruangan);
    for (int i = 0; i < cfg->jumlahPasienObat; i++) {
        free(cfg->obatPasien[i]);
    }
    free(cfg->pasienObatId);
    free(cfg->obatPasien);
    free(cfg->jumlahObat);
}

void parseLineKeArray(char *line, int *arr, int *lengthLine) {
    *lengthLine = 0;
    int i = 0, val = 0;
    int isNumber = 0;

    while (line[i] != '\0') {
        if (line[i] >= '0' && line[i] <= '9') {
            val = val * 10 + (line[i] - '0');
            isNumber = 1;
        } 
        else if (isNumber) {
            arr[(*lengthLine)++] = val;
            val = 0;
            isNumber = 0;
        }
        i++;
    }
    if (isNumber) {
        arr[(*lengthLine)++] = val;
    }
}

int bacaConfigFile(const char *fileName, Config *cfg) {
    FILE *file = fopen(fileName, "r");
    if (!file) {
        return 0;
    }

    char line[MAX_LINE];
    int temp[MAX_CAP], len = 0;

    // Baris 1, Ukuran denah
    fgets(line, MAX_LINE, file);
    parseLineKeArray(line, temp, &len);
    cfg->baris = temp[0];
    cfg->kolom = temp[1];
    cfg->jumlahRuangan = cfg->baris * cfg->kolom;

    // Baris 2, Kapasitas ruangan
    fgets(line, MAX_LINE, file);
    parseLineKeArray(line, temp, &len);
    cfg->kapasitas = temp[0];

    // Alokasi array ruangan
    cfg->ruangan = (Ruangan*) malloc(sizeof(Ruangan) * cfg->jumlahRuangan);

    // Baris 3 hingga baris ke-(2+jumlahRuangan): isi ruangan
    for (int i = 0; i < cfg->jumlahRuangan; i++) {
        if (!fgets(line, MAX_LINE, file)) break;
        parseLineKeArray(line, temp, &len);
        cfg->ruangan[i].dokterId = (len > 0) ? temp[0] : 0;
        cfg->ruangan[i].jumlahPasien = len - 1;
        cfg->ruangan[i].pasienIds = malloc(sizeof(int) * (len > 1 ? len - 1 : 1));
        for (int j = 1; j < len; j++) {
            cfg->ruangan[i].pasienIds[j - 1] = temp[j];
        }
    }

    // Baris berikutnya, jumlah pasien dengan obat
    fgets(line, MAX_LINE, file);
    parseLineKeArray(line, temp, &len);
    cfg->jumlahPasienObat = temp[0];

    // Alokasi untuk data obat pasien
    cfg->pasienObatId = (int*)malloc(sizeof(int) * cfg->jumlahPasienObat);
    cfg->obatPasien = (int**)malloc(sizeof(int*) * cfg->jumlahPasienObat);
    cfg->jumlahObat = (int*)malloc(sizeof(int) * cfg->jumlahPasienObat);

    // Baris berikutnya, isi pasien dengan obat
    for (int i = 0; i < cfg->jumlahPasienObat; i++) {
        if (!fgets(line, MAX_LINE, file)) break;
        parseLineKeArray(line, temp, &len);
        cfg->pasienObatId[i] = temp[0];
        cfg->jumlahObat[i] = len - 1;
        cfg->obatPasien[i] = (int*)malloc(sizeof(int) * (len > 1 ? len - 1 : 1));
        for (int j = 1; j < len; j++) {
            cfg->obatPasien[i][j - 1] = temp[j];
        }
    }

    fclose(file);
    return 1;
}

//Debugging 
int main() {
    Config cfg;
    initConfig(&cfg);

    if (bacaConfigFile("config.txt", &cfg)) {
        printf("Denah: %dx%d, Kapasitas: %d\n", cfg.baris, cfg.kolom, cfg.kapasitas);
        for (int i = 0; i < cfg.jumlahRuangan; i++) {
            printf("Ruangan %d: Dokter ID %d, Pasien %d\n", i, cfg.ruangan[i].dokterId, cfg.ruangan[i].jumlahPasien);
        }
    }
    else {
        printf("Gagal membaca file konfigurasi.\n");
    }
    freeConfig(&cfg);
    return 0;
}
