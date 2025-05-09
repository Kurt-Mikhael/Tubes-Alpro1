#include "..\header\adt-user.h"
#include <stdio.h>


#include "adt-user.h"
#include <string.h>
#define MARK_ID -1
void createUser(User* account) {
    account->id = MARK_ID;
    strcpy(account->username, "");
    strcpy(account->password, "");
    strcpy(account->role, "");
    account->suhu_tubuh = 0;
    account->tekanan_darah_sistolik = 0;
    account->tekanan_darah_diastolik = 0;
    account->detak_jantung = 0;
    account->saturasi_oksigen = 0;
    account->kadar_gula_darah = 0;
    account->berat_badan = 0;
    account->tinggi_badan = 0;
    account->kadar_kolesterol = 0;
    account->kadar_kolesterol_ldl = 0;
    account->trombosit = 0;
    CreateListObat(&(account->inventory));
    CreateStackObat(&(account->perut));
    createPenyakit(&(account->riwayat_penyakit));
}

void destroyUser(User* account) {
    account->id = MARK_ID;
    strcpy(account->username, "");
    strcpy(account->password, "");
    strcpy(account->role, "");
    account->suhu_tubuh = 0;
    account->tekanan_darah_sistolik = 0;
    account->tekanan_darah_diastolik = 0;
    account->detak_jantung = 0;
    account->saturasi_oksigen = 0;
    account->kadar_gula_darah = 0;
    account->berat_badan = 0;
    account->tinggi_badan = 0;
    account->kadar_kolesterol = 0;
    account->kadar_kolesterol_ldl = 0;
    account->trombosit = 0;
    createListObat(&(account->inventory));
    destroyStackObat(&(account->perut));
    createPenyakit(&(account->riwayat_penyakit));
}

int isUserValid(User account) {
    // User dianggap valid jika memiliki username
    return strlen(account.username) > 0;
}

boolean isSameUser(User account1, User account2) {
    // 2 User dianggap sama jika id dan usernamenya sama
    return (account1.id == account2.id && strcmp(account1.username, account2.username) == 0);
}

void createListUser(ListUser* accountList) {
    accountList->jumlah = 0;
    for (int i = 0; i < MAX_USER; i++) {
        createUser(&(accountList->data[i]));
    }
}

int listLength(ListUser accountList) {
    for(int i = 0; i < MAX_USER; i++) {
        if (accountList.data[i].id == MARK_ID) {
            accountList.jumlah = i;
            break;
        }
    }
}

void insertUserLast(ListUser* accountList, User account) {
    if (accountList->jumlah < MAX_USER) {
        accountList->data[accountList->jumlah] = account;
        accountList->jumlah++;
    }
}
User getUser(ListUser accountList, int index) {
    return accountList.data[index]; // Asumsi ListUser punya array `data`
}

