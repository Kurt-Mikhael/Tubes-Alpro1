#ifndef ADTSET_H
#define ADTSET_H

#include "adt-user.h"


typedef struct
{
    char user_name[MAX_USER][50];
    int length;
} UsernameSet;

/* Membuat set of username kosong*/
void createUsernameSet(UsernameSet* set_nama);

/* Mendealokasi set of username*/
void destroyUsernameSet(UsernameSet* set_nama);

/* Memeriksa apakah username sudah ada dalam set*/
boolean isUsernameInSet(UsernameSet set_nama, char nama[50]);

/* Menambahkan username ke set jika belum ada di set*/
void addUsernameToSet(UsernameSet* set_nama, char nama[50]);

/* Menghapus username dari set*/
void deleteUsernameFromSet(UsernameSet* set_nama, char nama[50]);

/* Menyalin username-username dari list of user ke set of username*/
void copyListToSet(ListUser database, UsernameSet* daftar_nama);

#endif