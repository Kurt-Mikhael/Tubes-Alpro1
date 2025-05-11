//NOTE: implementasi validasiKodeUnik, gantiPassworDiList, dan lupaPassword sudah di fungsi-prosedur.c

#ifndef  FUNGSI_H
#define  FUNGSI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256

// int validasiKodeUnik(char* username, char *kodeUnik) {
//     int k = 0;
//     int len = strlen(username);
//     char* temp = (char*)malloc(len + 1);

//     for (int i = 0; i < len; i++) {
//         int count = 1;
//         char hurufUsername = username[i];
//         while (i + 1 < len && hurufUsername == username[i + 1]) {
//             count++;
//             i++;
//         }
//         if (count > 1) {
//             char hurufCount[MAX_LINE];
//             sprintf(hurufCount, "%d", count);
//             for (int l = 0; hurufCount[l] != '\0'; l++) {
//                 temp[k++] = hurufCount[l];
//             }
//         }
//         temp[k++] = hurufUsername;
//     }
//     temp[k] = '\0';

//     int hasil = strcmp(temp, kodeUnik) == 0;
//     free(temp);
//     return hasil;
// }

void ambilUsernameDariBaris(char *baris, char *username) {
    int koma = 0, i = 0, j = 0;
    while (baris[i] != '\0' && baris[i] != '\n') {
        if (baris[i] == ',') {
            koma++;
            i++;
            continue;
        }
        if (koma == 2) {
            username[j++] = baris[i];
        }
        i++;
    }
    username[j] = '\0';
}

// void gantiPasswordDiList(char *baris, const char *passwordBaru, char *outputBaris) {
//     int koma = 0, i = 0, j = 0;
//     while (baris[i] != '\0' && baris[i] != '\n') {
//         if (koma == 3) {
//             while (baris[i] != ',' && baris[i] != '\0' && baris[i] != '\n') {
//                 i++;
//             }
//             outputBaris[j++] = ',';
//             for (int k = 0; passwordBaru[k] != '\0'; k++) {
//                 outputBaris[j++] = passwordBaru[k];
//             }
//             koma++;
//             continue;
//         }
//         outputBaris[j++] = baris[i];
//         if (baris[i] == ',') koma++;
//         i++;
//     }
//     outputBaris[j++] = '\n';
//     outputBaris[j] = '\0';
// }

// void lupaPassword(char *username, char *kodeUnik) {
//     FILE *file = fopen("data/user.csv", "r");
//     if (file == NULL) {
//         printf("Gagal membuka file.\n");
//         return;
//     }

//     char data[100][MAX_LINE];
//     int totalBaris = 0;
//     int ditemukan = 0;

//     while (fgets(data[totalBaris], MAX_LINE, file)) {
//         char user[MAX_LINE];
//         ambilUsernameDariBaris(data[totalBaris], user);

//         if (strcmp(user, username) == 0 && validasiKodeUnik(username, kodeUnik)) {
//             ditemukan = 1;
//             printf("Masukkan password baru: ");
//             char passwordBaru[MAX_LINE];
//             scanf("%s", passwordBaru);
//             char barisBaru[MAX_LINE];
//             gantiPasswordDiBaris(data[totalBaris], passwordBaru, barisBaru);
//             strcpy(data[totalBaris], barisBaru);
//         }
//         totalBaris++;
//     }
//     fclose(file);

//     if (!ditemukan) {
//         printf("Username tidak ditemukan atau kode unik salah.\n");
//         return;
//     }

//     FILE *tulis = fopen("data/user.csv", "w");
//     for (int i = 0; i < totalBaris; i++) {
//         fputs(data[i], tulis);
//     }
//     fclose(tulis);
//     printf("Password berhasil diubah.\n");
// }

#endif // FUNGSI_H
