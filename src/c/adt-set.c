#include "..\header\adt-set.h"
#include "..\header\adt-user.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "..\header\boolean.h"

/* Membuat set of username kosong*/
void createUsernameSet(UsernameSet* set_nama) {
    set_nama->length = 0;
    for (int i = 0; i < MAX_USER; i++) {
        strcpy(set_nama->user_name[i], "");
    }
}

/* Mendealokasi set of username*/
void destroyUsernameSet(UsernameSet* set_nama) {
    set_nama->length = 0;
    for (int i = 0; i < MAX_USER; i++) {
        strcpy(set_nama->user_name[i], "");
    }
}

/* Memeriksa apakah username sudah ada dalam set*/
boolean isUsernameInSet(UsernameSet set_nama, char nama[50]) {
    int l = 0;
    int r = set_nama.length - 1;
    while (l <= r) {
        int m = (l+r)/2;
        if (strcasecmp(nama, set_nama.user_name[m]) > 0) {
            l = m + 1;
        } else if (strcasecmp(nama, set_nama.user_name[m]) < 0) {
            r = m - 1;
        } else {
            return TRUE;
        }
    }
    return FALSE;
}

/* Menambahkan username ke set jika belum ada di set*/
void addUsernameToSet(UsernameSet* set_nama, char nama[50]) {
    if (!isUsernameInSet(*set_nama, nama)) {
        int i;
        for (i = set_nama->length; strcasecmp(nama, set_nama->user_name[i-1]) > 0; i--) {
            strcpy(set_nama->user_name[i], set_nama->user_name[i-1]);
        }
        strcpy(set_nama->user_name[i], nama);
    }
}

/* Menghapus username dari set*/
void deleteUsernameFromSet(UsernameSet* set_nama, char nama[50]) {
    int l = 0;
    int r = set_nama->length - 1;
    int idx;
    while (l <= r) {
        int m = (l+r)/2;
        if (strcasecmp(nama, set_nama->user_name[m]) > 0) {
            l = m + 1;
        } else if (strcasecmp(nama, set_nama->user_name[m]) < 0) {
            r = m - 1;
        } else {
            idx = m;
            break;
        }
    }
    for (int i = set_nama->length - 1; i > idx; i--) {
        strcpy(set_nama->user_name[i-1], set_nama->user_name[i]);
    }
    set_nama->length--;
}

/* Menyalin username-username dari list of user ke set of username*/
void copyListToSet(ListUser database, UsernameSet* daftar_nama) {
    for (int i = 0; i < database.jumlah; i++) {
        addUsernameToSet(daftar_nama, database.data[i].username);
    }
}