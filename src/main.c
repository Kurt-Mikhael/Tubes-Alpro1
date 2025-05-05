#include "user.h"
#include "penyakit.h"
#include "obat.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

void loadData(const char *folderName, User users[], int *user_count, Obat obats[], int *obat_count, Penyakit penyakit[], int *penyakit_count) {
    char path[256];

    // Load users
    snprintf(path, sizeof(path), "%s/user.csv", folderName);
    *user_count = load_users(path, users, MAX_USERS);
    if (*user_count == 0) {
        printf("Tidak ada data pengguna yang dapat dimuat.\n");
    }

    // Load obat
    snprintf(path, sizeof(path), "%s/obat.csv", folderName);
    *obat_count = load_obat(obats);

    // Load penyakit
    snprintf(path, sizeof(path), "%s/penyakit.csv", folderName);
    *penyakit_count = load_penyakit(path, penyakit, MAX_PENYAKIT);

    // Load config (kalau perlu, tinggal tambahkan di sini)
    printf("Selamat datang kembali di rumah sakit Nimons!\n");
}

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

    User users[MAX_USERS];
    int user_count;
    Obat obats[MAX_OBAT];
    int obat_count;
    Penyakit penyakit[MAX_PENYAKIT];
    int penyakit_count;

    loadData(folderName, users, &user_count, obats, &obat_count, penyakit, &penyakit_count);

    // Mulai menu interaktif
    while (1) {
        printf("\nMENU:\n");
        printf("1. REGISTER\n");
        printf("2. LOGIN\n");
        printf("3. EXIT\n");
        printf("Pilih: ");

        int choice;
        if (scanf("%d", &choice) != 1) break;
        while (getchar() != '\n'); // flush stdin

        if (choice == 1) {
            register_pasien(users, &user_count, MAX_USERS);
        } else if (choice == 2) {
            menu_login(users, user_count);
        } else if (choice == 3) {
            printf("Keluar dari program.\n");
            break;
        } else {
            printf("Pilihan tidak valid.\n");
        }
    }

    return 0;
}
