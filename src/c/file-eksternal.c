#include <stdio.h>
#include <stdlib.h>
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

int folderExists(const char *folderName) {
    char path[256];
    FILE *fp;

    snprintf(path, sizeof(path), "%s/config.txt", folderName);
    fp = fopen(path, "r");
    if (fp != NULL) {
        fclose(fp);
        return 1;
    }
    return 0;
}

/*Mengisi Inventory PAsien dengan obatnya
I.S : ListUser database, userId, inventory sudah terisi
F.S : inventory pasien terisi dengan obat yang ada di database*/

void TambahObatKePasien(ListUser *database, int pasienId, int obatId, ListObat semuaObat) {
    for (int i = 0; i < database->jumlah; i++) {
        if (database->data[i].id == pasienId) {
            if (database->data[i].inventory.jumlah < MAX_OBAT) {
                for (int j = 0; j < semuaObat.jumlah; j++) {
                    if (semuaObat.data[j].obat_id == obatId) {
                        database->data[i].inventory.data[database->data[i].inventory.jumlah] = semuaObat.data[j];
                        database->data[i].inventory.jumlah++;
                        return;
                    }
                }
            }
        }
    }
}

int parse_field(FILE* file, char* buffer, int max_len) {
    int i = 0, c;

    while ((c = fgetc(file)) != EOF) {
        if (c == ',' || c == '\n' || c == '\r') {  // Ganti ; dengan ,
            break;
        }
        if (i < max_len - 1) { 
            buffer[i++] = (char)c;
        }
    }
    buffer[i] = '\0';

    if (c == EOF && i == 0) {
        buffer[0] = '\0';
        return EOF;
    }

    // Skip \r if present (for Windows-style \r\n)
    if (c == '\r') {
        int next_c = fgetc(file);
        if (next_c != '\n' && next_c != EOF) {
            ungetc(next_c, file);
        }
    }

    return c;
}

int bacaUserCSV(const char *folderName, ListUser* database, ListPenyakit daftar_penyakit) {
    char path[256];
    snprintf(path, sizeof(path), "%s/data/user.csv", folderName);
    FILE *file = fopen(path, "r");
    if (!file) {
        printf("Error: File tidak ditemukan!\n");
        return 0;
    }

    char buffer[MAX_FIELD_LEN];
    int count = 0, delimiter;

    // Skip header line
    while ((delimiter = fgetc(file)) != '\n' && delimiter != EOF);

    while (count < MAX_USER) {
        User parsed_user;
        createUser(&parsed_user);
        // Parse ID
        delimiter = parse_field(file, buffer, MAX_FIELD_LEN);
        if (delimiter == EOF || buffer[0] == '\0') break;
        parsed_user.id = atoi(buffer);

        // Parse username
        delimiter = parse_field(file, buffer, MAX_FIELD_LEN);
        strncpy(parsed_user.username, buffer, sizeof(parsed_user.username) - 1);
        parsed_user.username[sizeof(parsed_user.username) - 1] = '\0';

        // Parse password
        delimiter = parse_field(file, buffer, MAX_FIELD_LEN);
        strncpy(parsed_user.password, buffer, sizeof(parsed_user.password) - 1);
        parsed_user.password[sizeof(parsed_user.password) - 1] = '\0';

        // Parse role
        delimiter = parse_field(file, buffer, MAX_FIELD_LEN);
        strncpy(parsed_user.role, buffer, sizeof(parsed_user.role) - 1);
        parsed_user.role[sizeof(parsed_user.role) - 1] = '\0';

        // Parse remaining fields
        delimiter = parse_field(file, buffer, MAX_FIELD_LEN);
        char riwayat_sakit[50];
        strncpy(riwayat_sakit, buffer, sizeof(riwayat_sakit) -1);
        riwayat_sakit[sizeof(riwayat_sakit) -1] = '\0';
        parsed_user.riwayat_penyakit = getPenyakitByName(daftar_penyakit, riwayat_sakit);

        delimiter = parse_field(file, buffer, MAX_FIELD_LEN);
        parsed_user.suhu_tubuh = (buffer[0]) ? atof(buffer) : 0.0f;

        delimiter = parse_field(file, buffer, MAX_FIELD_LEN);
        parsed_user.tekanan_darah_sistolik = (buffer[0]) ? atoi(buffer) : 0;

        delimiter = parse_field(file, buffer, MAX_FIELD_LEN);
        parsed_user.tekanan_darah_diastolik = (buffer[0]) ? atoi(buffer) : 0;

        delimiter = parse_field(file, buffer, MAX_FIELD_LEN);
        parsed_user.detak_jantung = (buffer[0]) ? atoi(buffer) : 0;

        delimiter = parse_field(file, buffer, MAX_FIELD_LEN);
        parsed_user.saturasi_oksigen = (buffer[0]) ? atof(buffer) : 0.0f;

        delimiter = parse_field(file, buffer, MAX_FIELD_LEN);
        parsed_user.kadar_gula_darah = (buffer[0]) ? atoi(buffer) : 0;

        delimiter = parse_field(file, buffer, MAX_FIELD_LEN);
        parsed_user.berat_badan = (buffer[0]) ? atof(buffer) : 0.0f;

        delimiter = parse_field(file, buffer, MAX_FIELD_LEN);
        parsed_user.tinggi_badan = (buffer[0]) ? atoi(buffer) : 0;

        delimiter = parse_field(file, buffer, MAX_FIELD_LEN);
        parsed_user.kadar_kolesterol = (buffer[0]) ? atoi(buffer) : 0;

        delimiter = parse_field(file, buffer, MAX_FIELD_LEN);
        parsed_user.kadar_kolesterol_ldl = (buffer[0]) ? atoi(buffer) : 0;

        delimiter = parse_field(file, buffer, MAX_FIELD_LEN);
        parsed_user.trombosit = (buffer[0]) ? atoi(buffer) : 0;

        insertUserLast(database, parsed_user);
        destroyUser(&parsed_user);

        count++;
    }
}

/*
Membaca file penyakit.csv lalu memindahkannya ke ListPenyakit lp
I.S : ListPenyakit lp sudah terisi
F.S : ListPenyakit lp terisi dengan data dari file penyakit.csv
*/
void bacaPenyakitCSV(const char *folderName, ListPenyakit* lp) {
    char path[256];
    snprintf(path, sizeof(path), "%s/data/penyakit.csv", folderName);
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        printf("Error: File \"penyakit.csv\" tidak ditemukan!\n");
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

void bacaObatCSV(const char *folderName, ListObat* daftar_obat) {
    char path[256];
    snprintf(path, sizeof(path), "%s/data/obat.csv", folderName);
    FILE *file_obat = fopen(path, "r");
    if (file_obat == NULL) {
        printf("Error: File \"obat.csv\" tidak ditemukan!\n");
        return;
    }

    char line[64];

    // Lewati header
    fgets(line, sizeof(line), file_obat);

    while (fgets(line, 64, file_obat)) { // baca baris 1 per 1 hingga end of file
        Obat o;
        int id = 0;
        char nama[64];
        int i = 0, j = 0;

        // parse id obat
        while (i < 64 && line[i] != ',') {
            id *= 10;
            id += (line[i] - '0');
            i++;
        }
        i++;

        // parse nama obat
        while (i+j < 64 && !(line[i+j] == '\0' || line[i+j] == '\n')) {
            nama[j] = line[i+j];
            j++;
        }
        nama[j] = '\0';

        // tambahkan obat ke daftar obat
        o.obat_id = id;
        for (int k = 0; k <= j; k++) {
            o.nama_obat[k] = nama[k];
        }
        insertLastObat(daftar_obat, o);
    }
    fclose(file_obat);
}


void bacaObatPenyakit(const char *folderName, ListPenyakit daftar_penyakit, ListObat daftar_obat, MapObatPenyakit* map){

    // array yang menyatakan urutan obat tiap penyakit
    int urutan_obat[lengthPenyakit(daftar_penyakit)][MAX_OBAT];
    for (int i = 0; i < lengthPenyakit(daftar_penyakit); i++) {
        for (int j = 0; i < MAX_OBAT; i++) {
            // i menyatakan id penyakit - 1
            // j menyatakan urutan - 1
            urutan_obat[i][j] = 0;
        }
    }

    // Mulai parsing obat_penyakit.csv
    char path[256];
    snprintf(path, sizeof(path), "%s/data/obat_penyakit.csv", folderName);
    FILE* file = fopen(path, "r");
    if(!file){
        printf("Error: File \"obat_penyakit.csv\" tidak ditemukan!\n");
        return;

    }
    int count = 0;
    char buffer[64];

    // skip header
    fgets(buffer, sizeof(buffer), file);

    int idx = 0;
    while (fgets(buffer, sizeof(buffer), file))
    {
        int read[3]; // {obat_id, penyakit_id, urutan_minum}
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
                read[cols] = nilai;
                i++;
                nilai = 0;
                cols++;
            }
        }
        urutan_obat[read[1]-1][read[2]-1] = read[0];
        idx++;
    }
    fclose(file);

    for (int i = 0; i < lengthPenyakit(daftar_penyakit); i++) {
        int j = 0;
        while (urutan_obat[i][j] != 0) {
            pushStack(&map->map[i], getObatByID(daftar_obat, urutan_obat[i][j]));
            j++;
        }
    }

    
    // Buat getPenyakitByID() sebagai key dan buat StackObat sebagai value Map
    
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
I.S : MatriksRuangan denah tidak terdefinisi, ListUser database dan semuaObat terisi dari file CSV
F.S : MatriksRuangan denah terisi, Queue dan inventory terisi dengan data dari file config.txt
*/
void bacaConfig(const char *folderName, MatriksRuangan* denah, ListUser* database, ListObat semuaObat) {
    char path[256];
    snprintf(path, sizeof(path), "%s/data/config.txt", folderName);
    FILE* file = fopen(path, "r");
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
    denah->row = baris;
    denah->column = kolom;
    for (int i = 0; i < baris; i++) {
        for (int j = 0; j < kolom; j++) {
            denah->ruang[i][j].kapasitas = kapasitas;
        }
    }
    // createMatrixRuangan(denah, baris, kolom, kapasitas);

    // Baris 3 - (3+totalRuangan-1): Data dokter dan pasien tiap ruangan
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

void saveConfig(const char *folderName, MatriksRuangan* denah, ListUser* database) {
    char path[256];
    snprintf(path, sizeof(path), "%s/data/config.txt", folderName);
    FILE* file = fopen(path, "w");
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
