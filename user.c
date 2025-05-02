#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "user.h"

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

int load_users(const char *filename, User users[], int max_users) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: File tidak ditemukan!\n");
        return 0;
    }

    char buffer[MAX_FIELD_LEN];
    int count = 0, delimiter;

    // Skip header line
    while ((delimiter = fgetc(file)) != '\n' && delimiter != EOF);

    while (count < max_users) {

        // Parse ID
        delimiter = parse_field(file, buffer, MAX_FIELD_LEN);
        if (delimiter == EOF || buffer[0] == '\0') break;
        users[count].id = atoi(buffer);

        // Parse username
        delimiter = parse_field(file, buffer, MAX_FIELD_LEN);
        strncpy(users[count].username, buffer, sizeof(users[count].username) - 1);
        users[count].username[sizeof(users[count].username) - 1] = '\0';

        // Parse password
        delimiter = parse_field(file, buffer, MAX_FIELD_LEN);
        strncpy(users[count].password, buffer, sizeof(users[count].password) - 1);
        users[count].password[sizeof(users[count].password) - 1] = '\0';

        // Parse role
        delimiter = parse_field(file, buffer, MAX_FIELD_LEN);
        strncpy(users[count].role, buffer, sizeof(users[count].role) - 1);
        users[count].role[sizeof(users[count].role) - 1] = '\0';

        // Parse remaining fields
        delimiter = parse_field(file, buffer, MAX_FIELD_LEN);
        strncpy(users[count].riwayat_penyakit, buffer, sizeof(users[count].riwayat_penyakit) -1);
        users[count].riwayat_penyakit[sizeof(users[count].riwayat_penyakit) -1] = '\0';

        delimiter = parse_field(file, buffer, MAX_FIELD_LEN);
        users[count].suhu_tubuh = (buffer[0]) ? atof(buffer) : 0.0f;

        delimiter = parse_field(file, buffer, MAX_FIELD_LEN);
        users[count].tekanan_darah_sistolik = (buffer[0]) ? atoi(buffer) : 0;

        delimiter = parse_field(file, buffer, MAX_FIELD_LEN);
        users[count].tekanan_darah_diastolik = (buffer[0]) ? atoi(buffer) : 0;

        delimiter = parse_field(file, buffer, MAX_FIELD_LEN);
        users[count].detak_jantung = (buffer[0]) ? atoi(buffer) : 0;

        delimiter = parse_field(file, buffer, MAX_FIELD_LEN);
        users[count].saturasi_oksigen = (buffer[0]) ? atof(buffer) : 0.0f;

        delimiter = parse_field(file, buffer, MAX_FIELD_LEN);
        users[count].kadar_gula_darah = (buffer[0]) ? atoi(buffer) : 0;

        delimiter = parse_field(file, buffer, MAX_FIELD_LEN);
        users[count].berat_badan = (buffer[0]) ? atof(buffer) : 0.0f;

        delimiter = parse_field(file, buffer, MAX_FIELD_LEN);
        users[count].tinggi_badan = (buffer[0]) ? atoi(buffer) : 0;

        delimiter = parse_field(file, buffer, MAX_FIELD_LEN);
        users[count].kadar_kolesterol = (buffer[0]) ? atoi(buffer) : 0;

        delimiter = parse_field(file, buffer, MAX_FIELD_LEN);
        users[count].kadar_kolesterol_ldl = (buffer[0]) ? atoi(buffer) : 0;

        delimiter = parse_field(file, buffer, MAX_FIELD_LEN);
        users[count].trombosit = (buffer[0]) ? atoi(buffer) : 0;

        count++;
    }

    fclose(file);
    printf("Berhasil memuat %d pengguna!\n", count);
    return count;
}

int username_exists(User users[], int user_count, const char *username) {
    for (int i = 0; i < user_count; i++) {
        if (strcasecmp(users[i].username, username) == 0) {
            return 1; // Sudah ada
        }
    }
    return 0; // Belum ada
}
void register_pasien(User users[], int *user_count, int max_users) {
    if (*user_count >= max_users) {
        printf("Maaf, kapasitas penuh! Tidak bisa menambah pasien baru.\n");
        return;
    }

    char username[50], password[50];

    printf(">>> REGISTER\n");

    while (1) { // Loop sampai registrasi berhasil
        printf("Username: ");
        if (fgets(username, sizeof(username), stdin) == NULL) return;
        username[strcspn(username, "\n")] = '\0';

        // Validasi hanya huruf dan angka
        int valid = 1;
        for (int i = 0; i < strlen(username); i++) {
            if (!isalpha(username[i])) {
                valid = 0;
                break;
            }
        }
        if (!valid) {
            printf("Registrasi gagal! Username hanya boleh berisi huruf (tanpa angka).\n");
            continue; // ulangi
        }

        if (username_exists(users, *user_count, username)) {
            printf("Registrasi gagal! Pasien dengan nama %s sudah terdaftar.\n", username);
            continue; // ulangi
        }

        break; // lolos validasi, keluar loop
    }

    printf("Password: ");
    if (fgets(password, sizeof(password), stdin) == NULL) return;
    password[strcspn(password, "\n")] = '\0';

    User new_user;
    new_user.id = (*user_count > 0) ? users[*user_count -1].id +1 :1;
    strncpy(new_user.username, username, sizeof(new_user.username) -1);
    new_user.username[sizeof(new_user.username) -1] = '\0';
    strncpy(new_user.password, password, sizeof(new_user.password) -1);
    new_user.password[sizeof(new_user.password) -1] = '\0';
    strcpy(new_user.role, "pasien");
    strcpy(new_user.riwayat_penyakit, "-");
    new_user.suhu_tubuh = 0.0f;
    new_user.tekanan_darah_sistolik = 0;
    new_user.tekanan_darah_diastolik = 0;
    new_user.detak_jantung = 0;
    new_user.saturasi_oksigen = 0.0f;
    new_user.kadar_gula_darah = 0;
    new_user.berat_badan = 0.0f;
    new_user.tinggi_badan = 0;
    new_user.kadar_kolesterol = 0;
    new_user.kadar_kolesterol_ldl = 0;
    new_user.trombosit = 0;

    users[*user_count] = new_user;
    (*user_count)++;

    printf("Pasien %s berhasil ditambahkan!\n", username);
}


void menu_login(User users[], int user_count) {
    char username[50], password[50];
    printf(">>> LOGIN\n");

    // Hapus scanf yang tidak perlu
    // int c;
    // while ((c = getchar()) != '\n' && c != EOF);

    while (1) {
        printf("Username: ");
        if (fgets(username, sizeof(username), stdin) == NULL) break;
        username[strcspn(username, "\n")] = '\0';

        if (strlen(username) == 0) {
            printf("Username tidak boleh kosong!\n");
            continue;
        }

        int found = -1;
        for (int i = 0; i < user_count; i++) {
            if (strcmp(username, users[i].username) == 0) {
                found = i;
                break;
            }
        }

        if (found == -1) {
            printf("User tidak ditemukan!\n");
            continue;
        }

        printf("Password: ");
        if (fgets(password, sizeof(password), stdin) == NULL) break;
        password[strcspn(password, "\n")] = '\0';

        if (strcmp(password, users[found].password) == 0) {
            printf("\nLogin berhasil!\n");
            printf("Selamat datang, %s (Role: %s)\n",
                   users[found].username,
                   users[found].role);
            exit(0);
        } else {
            printf("Password salah!\n");
        }
    }
}
