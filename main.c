#include "user.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    User users[MAX_USERS];
    int user_count = load_users("user.csv", users, MAX_USERS);
    
    if (user_count == 0) {
        printf("Tidak ada data pengguna yang dapat dimuat.\n");
    }

    while (1) {
        printf("\nMENU:\n");
        printf("1. REGISTER\n");
        printf("2. LOGIN\n");
        printf("3. EXIT\n");
        printf("Pilih: ");

        int choice;
        if (scanf("%d", &choice) !=1) break;
        while (getchar() != '\n'); // flush stdin

        if (choice ==1) {
            register_pasien(users, &user_count, MAX_USERS);
        } else if (choice ==2) {
            menu_login(users, user_count);
        } else if (choice ==3) {
            printf("Keluar dari program.\n");
            break;
        } else {
            printf("Pilihan tidak valid.\n");
        }
    }

    return 0;
}
