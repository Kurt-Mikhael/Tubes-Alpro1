#include "..\header\adt-user.h"
#include <stdio.h>


#include "adt-user.h"
#include <string.h>
#define MARK_ID -1
void createUser(User* u) {
    u->id = MARK_ID;
    strcpy(u->username, "");
    strcpy(u->password, "");
    strcpy(u->role, "");
    u->suhu_tubuh = 0;
    u->tekanan_darah_sistolik = 0;
    u->tekanan_darah_diastolik = 0;
    u->detak_jantung = 0;
    u->saturasi_oksigen = 0;
    u->kadar_gula_darah = 0;
    u->berat_badan = 0;
    u->tinggi_badan = 0;
    u->kadar_kolesterol = 0;
    u->kadar_kolesterol_ldl = 0;
    u->trombosit = 0;
    CreateListObat(&(u->inventory));
    CreateStackObat(&(u->perut));
    createPenyakit(&(u->riwayat_penyakit));
}

int isUserValid(User u) {
    return strlen(u.username) > 0;
}

void createListUser(ListUser* l) {
    l->jumlah = 0;
    for (int i = 0; i < MAX_USER; i++) {
        createUser(&(l->data[i]));
    }
}

int listLength(ListUser l) {
    for(int i = 0; i < MAX_USER; i++) {
        if (l.data[i].id == MARK_ID) {
            l.jumlah = i;
            break;
        }
    }
}

void insertUserLast(ListUser* l, User u) {
    if (l->jumlah < MAX_USER) {
        l->data[l->jumlah] = u;
        l->jumlah++;
    }
}
User getUser(ListUser list, int index) {
    return list.data[index]; // Asumsi ListUser punya array `data`
}

