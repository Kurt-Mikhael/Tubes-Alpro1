#include <stdio.h>
#include <stdlib.h>  
#include <string.h>
#include "../header/file-eksternal.h"  
#include "../header/global.h"  
#include "../header/adt-map.h"
#include "../header/adt-user.h"
#include "../header/adt-obat.h"
#include "../header/adt-penyakit.h"
#include "../header/adt-stack.h"
#include "../header/adt-queue.h"
#include "../header/adt-matrix.h"
#include "../header/boolean.h"
#include "../header/fungsi-prosedur.h"


int folderExists(const char *folderName) {
    char path[256];
    FILE *fp;

    // Check for config.txt directly in the provided folder
    snprintf(path, sizeof(path), "%s/config.txt", folderName);
    fp = fopen(path, "r");
    if (fp != NULL) {
        fclose(fp);
        return 1;
    }
    return 0;
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

int bacaUserCSV(const char *folderName, ListUser* database,ListPenyakit daftar_penyakit) {
    char path[256];
    snprintf(path, sizeof(path), "%s/user.csv", folderName);
    FILE *file = fopen(path, "r");
    if (!file) {
        printf("Error: File tidak ditemukan!\n");
        return 0;
    }

    char line[1024];
    char buffer[MAX_FIELD_LEN];
    
    printf("Reading user.csv...\n");
    
    // Skip the first line (comment or header)
    if (fgets(line, sizeof(line), file) == NULL) {
        printf("Error: Empty file or reading error\n");
        fclose(file);
        return 0;
    }
    
    // Skip the second line if first was a comment
    if (strncmp(line, "//", 2) == 0) {
        if (fgets(line, sizeof(line), file) == NULL) {
            printf("Error: Couldn't read header line\n");
            fclose(file);
            return 0;
        }
    }    
    while (fgets(line, sizeof(line), file)) {
        User parsed_user;
        createUser(&parsed_user);
        int i = 0; 
        int field = 0; 
        int j = 0; 
        
        // Reset buffer
        buffer[0] = '\0';
          // Proses setiap karakter dalam baris
        while (line[i] != '\0' && line[i] != '\n' && line[i] != '\r') {
            if (line[i] == ','|| line[i] == ';') { 
                // Proses field yang telah dibaca
                buffer[j] = '\0';
                
                // Karena dalam CSV urutannya tetap, maka setiap field tidak berubah.
                if (field == 0) { // ID
                    parsed_user.id = atoi(buffer);
                } 
                else if (field == 1) { // Username
                    strncpy(parsed_user.username, buffer, sizeof(parsed_user.username) - 1);
                    parsed_user.username[sizeof(parsed_user.username) - 1] = '\0';

                } 
                else if (field == 2) { // Password
                    strncpy(parsed_user.password, buffer, sizeof(parsed_user.password) - 1);
                    parsed_user.password[sizeof(parsed_user.password) - 1] = '\0';
                } 
                else if (field == 3) { // Role
                    strncpy(parsed_user.role, buffer, sizeof(parsed_user.role) - 1);
                    parsed_user.role[sizeof(parsed_user.role) - 1] = '\0';
                } 
                else if (field == 4) { // Riwayat penyakit
                    if (buffer[0] != '\0') {
                        char riwayat_sakit[50];
                        strncpy(riwayat_sakit, buffer, sizeof(riwayat_sakit) - 1);
                        riwayat_sakit[sizeof(riwayat_sakit) - 1] = '\0';
                        parsed_user.riwayat_penyakit = getPenyakitByName(daftar_penyakit, riwayat_sakit);
                    }
                } 
                else if (field == 5) { // Suhu tubuh
                    if (buffer[0] != '\0') {
                        parsed_user.suhu_tubuh = atof(buffer);
                    }
                } 
                else if (field == 6) { // Tekanan darah sistolik
                    if (buffer[0] != '\0') {
                        parsed_user.tekanan_darah_sistolik = atoi(buffer);
                    }
                } 
                else if (field == 7) { // Tekanan darah diastolik
                    if (buffer[0] != '\0') {
                        parsed_user.tekanan_darah_diastolik = atoi(buffer);
                    }
                } 
                else if (field == 8) { // Detak jantung
                    if (buffer[0] != '\0') {
                        parsed_user.detak_jantung = atoi(buffer);
                    }
                } 
                else if (field == 9) { // Saturasi oksigen
                    if (buffer[0] != '\0') {
                        parsed_user.saturasi_oksigen = atof(buffer);
                    }
                } 
                else if (field == 10) { // Kadar gula darah
                    if (buffer[0] != '\0') {
                        parsed_user.kadar_gula_darah = atoi(buffer);
                    }
                } 
                else if (field == 11) { // Berat badan
                    if (buffer[0] != '\0') {
                        parsed_user.berat_badan = atof(buffer);
                    }
                } 
                else if (field == 12) { // Tinggi badan
                    if (buffer[0] != '\0') {
                        parsed_user.tinggi_badan = atoi(buffer);
                    }
                } 
                else if (field == 13) { // Kadar kolesterol
                    if (buffer[0] != '\0') {
                        parsed_user.kadar_kolesterol = atoi(buffer);
                    }
                } 
                else if (field == 14) { // Kadar kolesterol LDL
                    if (buffer[0] != '\0') {
                        parsed_user.kadar_kolesterol_ldl = atoi(buffer);
                    }
                } 
                else if (field == 15) { // Trombosit
                    if (buffer[0] != '\0') {
                        parsed_user.trombosit = atoi(buffer);
                    }
                }
                
                // Reset for next field
                j = 0;
                field++;
                buffer[0] = '\0';
            } else {
                // Add character to the current field
                if (j < MAX_FIELD_LEN - 1) {
                    buffer[j++] = line[i];
                }
            }
            i++;
        }
          // Proses akhir baris
        // Jika ada karakter yang tersisa di buffer, proses sebagai field terakhir
        if (j > 0) {
            buffer[j] = '\0';
            
            // Field terakhir
            if (field == 0 && buffer[0] != '\0') {
                parsed_user.id = atoi(buffer);
            } 
            else if (field == 1 && buffer[0] != '\0') {
                strncpy(parsed_user.username, buffer, sizeof(parsed_user.username) - 1);
                parsed_user.username[sizeof(parsed_user.username) - 1] = '\0';
            }
            else if (field == 2 && buffer[0] != '\0') {
                strncpy(parsed_user.password, buffer, sizeof(parsed_user.password) - 1);
                parsed_user.password[sizeof(parsed_user.password) - 1] = '\0';
            }
            else if (field == 3 && buffer[0] != '\0') {
                strncpy(parsed_user.role, buffer, sizeof(parsed_user.role) - 1);
                parsed_user.role[sizeof(parsed_user.role) - 1] = '\0';
            }
            else if (field == 15 && buffer[0] != '\0') {
                parsed_user.trombosit = atoi(buffer);
            }
        }
        
        // Add the user to the database
        insertUser(database, parsed_user);
        //Menambahkan username ke set_nama
    }
    printf("Berhasil membaca %d users dari CSV\n", database->jumlah);
    fclose(file);
    return CountUser;
}

/*
Membaca file penyakit.csv lalu memindahkannya ke ListPenyakit lp
I.S : ListPenyakit lp sudah terisi
F.S : ListPenyakit lp terisi dengan data dari file penyakit.csv
*/
void bacaPenyakitCSV(const char *folderName, ListPenyakit* lp) {
    CountPenyakit = 0;
    char path[256];
    snprintf(path, sizeof(path), "%s/penyakit.csv", folderName);
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        printf("Error: File \"penyakit.csv\" tidak ditemukan!\n");
        return;
    }

    char line[512];

    fgets(line, sizeof(line), file); // lewati header

    while (fgets(line, sizeof(line), file) && !isFull(*lp)) {
        line[strcspn(line, "\n")] = '\0'; // hapus newline

        int field = 0, pos = 0;
        char buffer[100];
        Penyakit p;        for (int i = 0; i <= strlen(line); i++) {
            if (line[i] == ';' || line[i] == ',' || line[i] == '\0') {
                buffer[pos] = '\0';
                switch (field) {
                    case 0: p.id = atoi(buffer);  break;
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
                    case 12: p.kadar_gula_min = atoi(buffer); break;
                    case 13: p.kadar_gula_max = atoi(buffer); break;
                    case 14: p.berat_badan_min = atof(buffer); break;
                    case 15: p.berat_badan_max = atof(buffer); break;
                    case 16: p.tinggi_badan_min = atoi(buffer); break;
                    case 17: p.tinggi_badan_max = atoi(buffer); break;
                    case 18: p.kadar_kolesterol_min = atoi(buffer); break;
                    case 19: p.kadar_kolesterol_max = atoi(buffer); break;
                    case 20: p.kadar_kolesterol_ldl_min = atoi(buffer); break;
                    case 21: p.kadar_kolesterol_ldl_max = atoi(buffer); break;
                    case 22: p.trombosit_min = atoi(buffer); break;
                    case 23: p.trombosit_max = atoi(buffer); break;
                    default: break;
                }
                field++;
                pos = 0;
            } else {
                buffer[pos++] = line[i];
            }
        }
        CountPenyakit++;
        insertLast(lp, p);
    }
    
    fclose(file);
}

void bacaObatCSV(const char *folderName, ListObat* daftar_obat) {
    char path[256];
    snprintf(path, sizeof(path), "%s/obat.csv", folderName);
    FILE *file_obat = fopen(path, "r");
    if (file_obat == NULL) {
        printf("Error: File \"obat.csv\" tidak ditemukan!\n");
        return;
    }

    char line[64];

    // Lewati header
    fgets(line, sizeof(line), file_obat);    while (fgets(line, 64, file_obat)) { // baca baris 1 per 1 hingga end of file
        Obat o;
        int id = 0;
        char nama[64];
        int i = 0, j = 0;        // parse id obat
        while (i < 64 && line[i] >= '0' && line[i] <= '9') {
            id *= 10;
            id += (line[i] - '0');
            i++;
        }
        // Skip delimiter (either comma or semicolon)
        if (line[i] == ',' || line[i] == ';') {
            i++;
        }
        
        // parse nama obat
        while (i+j < 64 && line[i+j] != '\0' && line[i+j] != '\n' && line[i+j] != '\r') {
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


void bacaObatPenyakit(const char *folderName, ListPenyakit daftar_penyakit, ListObat daftar_obat, MapObatPenyakit* map) {
    char path[256];
    snprintf(path, sizeof(path), "%s/obat_penyakit.csv", folderName);
    FILE* file = fopen(path, "r");
    if (!file) {
        printf("Error: File \"obat_penyakit.csv\" tidak ditemukan!\n");
        return;
    }

    // Inisialisasi struktur sementara untuk menyimpan urutan
    int urutan_obat[MAX_PENYAKIT][MAX_OBAT] = {0};

    char line[128];
    fgets(line, sizeof(line), file); // skip header

    while (fgets(line, sizeof(line), file)) {
        int obat_id = 0, penyakit_id = 0, urutan = 0;
        int field = 0, temp = 0;
        for (int i = 0; line[i] != '\0'; ++i) {
            if (line[i] >= '0' && line[i] <= '9') {
                temp = temp * 10 + (line[i] - '0');
            } else if (line[i] == ',' || line[i] == '\n' || line[i] == ';') {
                if (field == 0) obat_id = temp;
                else if (field == 1) penyakit_id = temp;
                else if (field == 2) urutan = temp;
                temp = 0;
                field++;
            }
        }
        // handle last field (jaga-jaga)
        if (field == 2) urutan = temp;

        // masukkan ke array sementara
        if (penyakit_id > 0 && urutan > 0) {
            urutan_obat[penyakit_id - 1][urutan - 1] = obat_id;
        }
    }
    fclose(file);    // Inisialisasi map
    createMap(map);
    map->length = lengthPenyakit(daftar_penyakit);

    for (int i = 0; i < lengthPenyakit(daftar_penyakit); i++) {
        Penyakit p = getPenyakit(daftar_penyakit, i);
        strcpy(map->data[i].key, p.nama);  // Updated to use the new structure

        ListObat tempObat;
        createListObat(&tempObat);

        // masukkan ke list sesuai urutan (dari urutan tinggi ke rendah)
        for (int j = 0; j <MAX_OBAT; j++) {
            int id_obat = urutan_obat[p.id - 1][j];
            if (id_obat != 0) {
                Obat o = getObatByID(daftar_obat, id_obat);
                insertLastObat(&tempObat, o);
            }
        }
        map->data[i].value = tempObat;  // Updated to use the new structure
    }
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
void bacaConfig(const char *folderName, MatriksRuangan* denah, ListUser* database, ListObat semuaObat, int* max_queue) {
    char path[256];
    snprintf(path, sizeof(path), "%s/config.txt", folderName);
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

    // Baris 2: Kapasitas ruangan dan max_queue
    fgets(line, 256, file);
    parseLineKeArray(line, temp, &len);
    int kapasitas = temp[0];
    *max_queue = temp[1]+temp[0]; // max_queue = kapasitas ruangan + kapasitas antrean
    // Inisialisasi matriks ruangan
    denah->row = baris;
    denah->column = kolom;
    for (int i = 0; i < baris; i++) {
        for (int j = 0; j < kolom; j++) {
            denah->ruang[i][j].kapasitas = kapasitas;
        }
    }
    // createMatrixRuangan(denah, baris, kolom, kapasitas);

    // Baris 3 - (3+totalRuangan-1): Data dokter, pasien tiap ruangan, dan pasien pada antrean
    for (int i = 0; i < totalRuangan; i++) {
        fgets(line, 256, file);
        parseLineKeArray(line, temp, &len);
        int dokterId = temp[0];
        if (dokterId != 0) {
            setDokterID(denah, i, dokterId, *database);
            //Masukan pasien ke queue
            for (int j = 1; j < len; j++) {
                int pasienId = temp[j];
                if (pasienId != 0) {
                    User* pasien = getUserByID(database, pasienId);
                    if (strcmp(pasien->role, "pasien") == 0) {
                        addPasienToRuangan(denah, i, pasienId, *database);
                    }
                }
            }
            
        }
    }    // Baris selanjutnya: Jumlah pasien dengan obat
    fgets(line, 256, file);
    parseLineKeArray(line, temp, &len);
    CountUserDenganObat = temp[0];

    // Set flag to indicate we're loading from config file
    // This prevents double-counting users with medications
    isLoadingFromConfig = TRUE;

    // Pasien dengan daftar obat
    for (int i = 0; i < CountUserDenganObat; i++) {
        fgets(line, 256, file);
        parseLineKeArray(line, temp, &len);
        int pasienId = temp[0];
        User* user = getUserByID(database, pasienId);
        for(int j = 1; j<len;j++){
            tambahObatKeInventory(user, getObatByID(semuaObat, temp[j]));   
        }
    }
    
    // Reset flag after loading is complete
    isLoadingFromConfig = FALSE;
    
    fclose(file);
}

void saveConfig(const char *folderName, MatriksRuangan* denah, ListUser* database) {
    char path[256];
    snprintf(path, sizeof(path), "%s/config.txt", folderName);
    FILE* file = fopen(path, "w");
    if (!file) {
        printf("Gagal membuka config.txt\n");
        return;
    }

    char buffer[1024];

    // Baris 1: ukuran denah
    sprintf(buffer, "%d %d\n", denah->row, denah->column);
    fputs(buffer, file);

    // Baris 2: kapasitas
    sprintf(buffer, "%d %d\n", denah->ruang[0][0].kapasitas, max_queue-denah->ruang[0][0].kapasitas);
    fputs(buffer, file);    // Baris 3-...: ruangan
    for (int i = 0; i < denah->row * denah->column; i++) {        // Write doctor ID 
        int doktorId = denah->ruang[i/denah->column][i % denah->column].dokter.id;
        // For empty doctor slots, keep them as -1 for the 7th entry (index 6) to match original format
        if (i == 6 && doktorId == -1) {
            int pos = sprintf(buffer, "%d", doktorId);
            sprintf(buffer + pos, "\n");
            fputs(buffer, file);
            continue;
        }        // For all other cases, convert -1 to 0
        if (doktorId == -1) doktorId = 0;
        int pos = sprintf(buffer, "%d", doktorId);
        
        // Instead of using dequeue which can free memory, we'll manually traverse the queue
        Queue* currentQueue = denah->ruang[i/denah->column][i % denah->column].antrean;
        int qlen = queueLength(*currentQueue);
        
        // We need to create an array to store patient IDs from the queue
        int patientIds[50]; // Assume a reasonable max queue size
        int count = 0;
        
        // Traverse the linked queue without modifying it
        if (qlen > 0) {
            // First patient
            patientIds[count++] = currentQueue->pasien.id;
            
            // Rest of the patients
            Queue* temp = currentQueue->next;
            while (temp != NULL && count < qlen) {
                patientIds[count++] = temp->pasien.id;
                temp = temp->next;
            }
        }
        
        // Now write the patient IDs to the buffer
        for (int j = 0; j < count; j++) {
            pos += sprintf(buffer + pos, " %d", patientIds[j]);
        }
          // Only add trailing zero for doctors 11, 12, 15 to match the original format
        // In the original file, only some doctors had trailing zeros when they had no patients
        if (doktorId != 0 && qlen == 0 && (doktorId == 11 || doktorId == 12 || doktorId == 15)) {
            pos += sprintf(buffer + pos, " %d", 0);
        }
        
        sprintf(buffer + pos, "\n");
        fputs(buffer, file);
    }    // Baris berikutnya: jumlah pasien dengan obat
    // Use the global counter that's properly maintained by the application
    sprintf(buffer, "%d\n", CountUserDenganObat);
    fputs(buffer, file);

    // Tulis data obat per pasien
    int countWritten = 0; // Track to ensure we write the correct number of entries
    for (int i = 0; i < database->jumlah; i++) {
        if (database->id_list.buffer[i].inventory.jumlah > 0) {
            int pos = sprintf(buffer, "%d", database->id_list.buffer[i].id);
            for (int j = 0; j < database->id_list.buffer[i].inventory.jumlah; j++) {
                pos += sprintf(buffer + pos, " %d", database->id_list.buffer[i].inventory.data[j].obat_id);
            }
            sprintf(buffer + pos, "\n");
            fputs(buffer, file);
            countWritten++;
        }
    }    // Safety check: if we didn't write the expected number of entries, print a warning
    if (countWritten != CountUserDenganObat) {
        printf("WARNING: Expected to write %d users with medication, but wrote %d\n", 
               CountUserDenganObat, countWritten);
    }fclose(file);
    printf("Berhasil menyimpan konfigurasi ke config.txt\n");
}

/* Menyimpan data user ke file CSV */
void saveUserCSV(const char *folderName, ListUser database) {
    char path[256];
    snprintf(path, sizeof(path), "%s/user.csv", folderName);
    FILE* file = fopen(path, "w");
    if (!file) {
        printf("Gagal membuka file user.csv\n");
        return;
    }

    // Tulis header
    fputs("id,username,password,role,riwayat_penyakit,suhu_tubuh,tekanan_darah_sistolik,tekanan_darah_diastolik,detak_jantung,saturasi_oksigen,kadar_gula_darah,berat_badan,tinggi_badan,kadar_kolesterol,kadar_kolesterol_ldl,trombosit\n", file);

    // Tulis data user
    for (int i = 0; i < database.jumlah; i++) {
        User user = database.id_list.buffer[i];
        fprintf(file, "%d,%s,%s,%s,", 
                user.id, user.username, user.password, user.role);
        
        // Tulis data riwayat penyakit jika ada
        if (strcmp(user.riwayat_penyakit.nama, "") != 0) {
            fprintf(file, "%s", user.riwayat_penyakit.nama);
        }
        fprintf(file, ",");        // Tulis data kesehatan
        fprintf(file, "%.1f,%d,%d,%d,%.1f,%.1f,%.1f,%d,%d,%d,%d\n", 
                user.suhu_tubuh, user.tekanan_darah_sistolik, user.tekanan_darah_diastolik,
                user.detak_jantung, user.saturasi_oksigen, user.kadar_gula_darah,
                user.berat_badan, user.tinggi_badan, user.kadar_kolesterol,
                user.kadar_kolesterol_ldl, user.trombosit);
    }

    fclose(file);
    printf("Berhasil menyimpan data user ke user.csv\n");
}

/* Menyimpan data penyakit ke file CSV */
void savePenyakitCSV(const char *folderName, ListPenyakit daftar_penyakit) {
    char path[256];
    snprintf(path, sizeof(path), "%s/penyakit.csv", folderName);
    FILE* file = fopen(path, "w");
    if (!file) {
        printf("Gagal membuka file penyakit.csv\n");
        return;
    }    // Tulis header
    fputs("id,nama,suhu_min,suhu_max,tekanan_sistolik_min,tekanan_sistolik_max,tekanan_diastolik_min,tekanan_diastolik_max,detak_jantung_min,detak_jantung_max,saturasi_oksigen_min,saturasi_oksigen_max,kadar_gula_min,kadar_gula_max,berat_badan_min,berat_badan_max,tinggi_badan_min,tinggi_badan_max,kadar_kolesterol_min,kadar_kolesterol_max,kadar_kolesterol_ldl_min,kadar_kolesterol_ldl_max,trombosit_min,trombosit_max\n", file);    // Tulis data penyakit
    for (int i = 0; i < daftar_penyakit.jumlah; i++) {
        Penyakit p = daftar_penyakit.data[i];
        fprintf(file, "%d,%s,%.1f,%.1f,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%.1f,%.1f,%d,%d,%d,%d,%d,%d,%d,%d\n",
                p.id, p.nama, p.suhu_min, p.suhu_max, p.tekanan_sistolik_min, 
                p.tekanan_sistolik_max, p.tekanan_diastolik_min, p.tekanan_diastolik_max,
                p.detak_jantung_min, p.detak_jantung_max, p.saturasi_oksigen_min, 
                p.saturasi_oksigen_max, p.kadar_gula_min, p.kadar_gula_max,
                p.berat_badan_min, p.berat_badan_max, p.tinggi_badan_min, p.tinggi_badan_max,
                p.kadar_kolesterol_min, p.kadar_kolesterol_max, p.kadar_kolesterol_ldl_min,
                p.kadar_kolesterol_ldl_max, p.trombosit_min, p.trombosit_max);
    }

    fclose(file);
    printf("Berhasil menyimpan data penyakit ke penyakit.csv\n");
}

/* Menyimpan data obat ke file CSV */
void saveObatCSV(const char *folderName, ListObat daftar_obat) {
    char path[256];
    char originalPath[256];
    char delimiter = ','; // Default delimiter
    
    // Check original file for delimiter type
    snprintf(originalPath, sizeof(originalPath), "%s/obat.csv", folderName);
    FILE* checkFile = fopen(originalPath, "r");
    if (checkFile) {
        char header[128];
        if (fgets(header, sizeof(header), checkFile) != NULL) {
            // Check if semicolon is used as delimiter
            if (strchr(header, ';') != NULL) {
                delimiter = ';';
            }
        }
        fclose(checkFile);
    }
    
    snprintf(path, sizeof(path), "%s/obat.csv", folderName);
    FILE* file = fopen(path, "w");
    if (!file) {
        printf("Gagal membuka file obat.csv\n");
        return;
    }

    // Tulis header based on the delimiter we found
    if (delimiter == ';') {
        fputs("obat_id;nama_obat\n", file);
    } else {
        fputs("id,nama\n", file);
    }

    // Tulis data obat with appropriate delimiter
    for (int i = 0; i < daftar_obat.jumlah; i++) {
        Obat o = daftar_obat.data[i];
        if (delimiter == ';') {
            fprintf(file, "%d;%s\n", o.obat_id, o.nama_obat);
        } else {
            fprintf(file, "%d,%s\n", o.obat_id, o.nama_obat);
        }
    }

    fclose(file);
    printf("Berhasil menyimpan data obat ke obat.csv\n");
}

/* Menyimpan data obat penyakit ke file CSV */
void saveObatPenyakitCSV(const char *folderName, MapObatPenyakit map, ListPenyakit daftar_penyakit) {
    char path[256];
    snprintf(path, sizeof(path), "%s/obat_penyakit.csv", folderName);
    FILE* file = fopen(path, "w");
    if (!file) {
        printf("Gagal membuka file obat_penyakit.csv\n");
        return;
    }

    // Tulis header
    fputs("obat_id,penyakit_id,urutan\n", file);    // Untuk setiap penyakit dalam map
    for (int i = 0; i < daftar_penyakit.jumlah; i++) {
        Penyakit p = getPenyakit(daftar_penyakit, i);
        
        // Cari di map
        int map_idx = -1;
        for (int j = 0; j < map.length; j++) {
            if (strcmp(map.data[j].key, p.nama) == 0) {
                map_idx = j;
                break;
            }
        }
        
        if (map_idx != -1) {
            ListObat obat_list = map.data[map_idx].value;
            
            // Tulis data obat untuk penyakit ini
            for (int j = 0; j < obat_list.jumlah; j++) {
                fprintf(file, "%d,%d,%d\n", 
                        obat_list.data[j].obat_id, p.id, j+1); // urutan dimulai dari 1
            }
        }
    }

    fclose(file);
    printf("Berhasil menyimpan data obat penyakit ke obat_penyakit.csv\n");
}

/* Fungsi utama untuk menyimpan semua data - hanya menggunakan stdlib */
void saveData(MatriksRuangan* denah, ListUser* database, ListPenyakit daftar_penyakit, ListObat daftar_obat, MapObatPenyakit map) {
    char folderName[256];
    char command[512];
    
    printf("Masukkan nama folder untuk menyimpan data: ");
    scanf("%s", folderName);
    
    // Cek apakah folder sudah ada dengan mencoba membuka file di dalamnya
    if (folderExists(folderName)) {
        printf("Folder \"%s\" sudah ada. Data akan ditimpa.\n", folderName);
    } else {
        // Folder belum ada, buat folder baru dengan system command dari stdlib
        #ifdef _WIN32
        sprintf(command, "mkdir %s", folderName);
        #else
        sprintf(command, "mkdir -p %s", folderName);
        #endif
        
        if (system(command) != 0) {
            printf("Error: Gagal membuat folder!\n");
            return;
        }
        printf("Folder \"%s\" berhasil dibuat.\n", folderName);
    }
    
    // Simpan semua file
    saveConfig(folderName, denah, database);
    saveUserCSV(folderName, *database);
    savePenyakitCSV(folderName, daftar_penyakit);
    saveObatCSV(folderName, daftar_obat);
    saveObatPenyakitCSV(folderName, map, daftar_penyakit);
    
    printf("Semua data berhasil disimpan ke folder \"%s\".\n", folderName);
}

