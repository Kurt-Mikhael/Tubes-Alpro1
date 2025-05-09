#include "..\header\adt-set.h"
#include "..\header\adt-user.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "boolean.h"

boolean isUsernameSetEmpty(UsernameSet u_s) {
    return strlen(u_s.user_name) == 0;
}

boolean isUsernameSetValid(UsernameSet u_s,ListUser list_user) {
    for (int i = 0; i < list_user.jumlah; i++) {
        if (strcmp(u_s.user_name, list_user.data[i].username) == 0) {
            return FALSE; // Username sudah ada
        }
    }
    return TRUE; // Username belum ada
}

void createUsernameSet(UsernameSet* u_s, ListUser list_user) {
    printf("Masukkan username: ");
    do {
        fgets(u_s->user_name, sizeof(u_s->user_name), stdin);
        if (isUsernameSetEmpty(*u_s)) {
            printf("Username tidak boleh kosong. Silakan coba lagi: ");
        }
    } while (!isUsernameSetValid(*u_s,list_user)&& isUsernameSetEmpty(*u_s));
    u_s->user_name[strcspn(u_s->user_name, "\n")] = '\0'; // Menghapus newline
}