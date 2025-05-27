#include "../header/adt-user.h"
#include <stdio.h>
#include "../header/global.h"
#include <stdlib.h>
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
    createListObat(&(account->inventory));
    createStackObat(&(account->perut));
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
    return (account1.id == account2.id && strcasecmp(account1.username, account2.username) == 0);
}

void createListDin(ListDin* list, int capacity) {
    list->capacity = capacity;
    list->buffer = malloc(sizeof(User)*capacity);
    list->jumlah = 0;
    for (int i = 0; i < capacity; i++) {
        createUser(&list->buffer[i]);
    }
}

void createSetDin(SetDin* set, int capacity) {
    set->capacity = capacity;
    set->buffer = malloc(sizeof(User)*capacity);
    set->jumlah = 0;
    for (int i = 0; i < capacity; i++) {
        createUser(&set->buffer[i]);
    }
}

void createListUser(ListUser* accountList, int capacity) {
    createListDin(&accountList->id_list, capacity);
    createSetDin(&accountList->uname_set, capacity);
    accountList->jumlah = 0;
}

void destroyListDin(ListDin* list) {
    free(list->buffer);
    list->capacity = 0;
    list->jumlah = 0;
}

void destroySetDin(SetDin* set) {
    free(set->buffer);
    set->capacity = 0;
    set->jumlah = 0;
}

void destroyListUser(ListUser* accountList) {
    destroyListDin(&accountList->id_list);
    destroySetDin(&accountList->uname_set);
    accountList->jumlah = 0;
}

int listLength(ListUser accountList) {
    return accountList.jumlah;
}


void geserListDin(ListDin* list, int start_idx, int jarak) {
    if (jarak > 0) {
        for (int i = list->jumlah - 1; i >= start_idx ; i--) {
            list->buffer[i+jarak] = list->buffer[i];
            destroyUser(&list->buffer[i]);
        }
    } else if (jarak < 0) {
        for (int i = start_idx; i < list->jumlah ; i++) {
            list->buffer[i+jarak] = list->buffer[i];
            destroyUser(&list->buffer[i]);
        }
    }
}

void geserSetDin(SetDin* set, int start_idx, int jarak) {
    if (jarak > 0) {
        for (int i = set->jumlah - 1; i >= start_idx ; i--) {
            set->buffer[i+jarak] = set->buffer[i];
            destroyUser(&set->buffer[i]);
        }
    } else if (jarak < 0) {
        for (int i = start_idx; i < set->jumlah ; i++) {
            set->buffer[i+jarak] = set->buffer[i];
            destroyUser(&set->buffer[i]);
        }
    }
}

void expandShrinkListUser(ListUser* accountList, float modifier) {
    // Salin isi listdin ke temporary list
    int new_cap = (accountList->id_list.capacity)*modifier;
    int count = accountList->jumlah;
    ListUser new_accountList;
    createListUser(&new_accountList, new_cap);
    for (int i = 0; i < count; i++) {
        new_accountList.id_list.buffer[i] = accountList->id_list.buffer[i];
    }

    // dealokasi dan realokasi dengan kapasitas baru
    destroyListUser(accountList);
    createListUser(accountList, new_cap);

    for (int i = 0; i < count; i++) {
        // salin listdin
        User account = new_accountList.id_list.buffer[i];
        accountList->id_list.buffer[i] = account;
        accountList->id_list.jumlah++;

        // isi setdin
        account = new_accountList.uname_set.buffer[i];
        accountList->uname_set.buffer[i] = account;
        accountList->uname_set.jumlah++;

        accountList->jumlah++;
    }
    destroyListUser(&new_accountList);
}

void insertUser(ListUser* accountList, User account) {
    int idx, l, m, r;

    // binary search untuk mencari indeks user dengan id terkecil yang masih lebih besar dibanding id account
    l = 0, r = listLength(*accountList) - 1, idx = listLength(*accountList);
    while (l <= r) {
        m = (l + r) / 2;
        if (accountList->id_list.buffer[m].id < account.id) {
            l = m + 1;
        } else if (accountList->id_list.buffer[m].id > account.id) {
            idx = m;
            r = m - 1;
        } else {
            // seharusnya tidak terjadi
            printf("%s %s dengan id %d sudah terdaftar!\n", account.role, account.username, account.id);
        }
    }

    // masuk ke listdin
    if (idx != listLength(*accountList)) {
        geserListDin(&accountList->id_list, idx, 1);
    }
    accountList->id_list.buffer[idx] = account;

    // binary search untuk mencari indeks user dengan nama terkecil yang masih lebih besar dibanding nama account
    l = 0, r = listLength(*accountList) - 1, idx = listLength(*accountList);
    while (l <= r) {
        m = (l + r) / 2;
        if (strcasecmp(accountList->uname_set.buffer[m].username, account.username) < 0) {
            l = m + 1;
        } else if (strcasecmp(accountList->uname_set.buffer[m].username, account.username) > 0) {
            idx = m;
            r = m - 1;
        } else {
            // seharusnya tidak terjadi
            printf("%s %s sudah terdaftar!\n", account.role, account.username);
        }
    }

    // masuk ke setdin
    if (idx != listLength(*accountList)) {
        geserSetDin(&accountList->uname_set, idx, 1);
    }
    accountList->uname_set.buffer[idx] = account;

    // tambah panjang
    accountList->id_list.jumlah++;
    accountList->uname_set.jumlah++;
    accountList->jumlah++;

    // expand kalau sudah terisi 75% kapasitas
    if (accountList->jumlah > 3*accountList->id_list.capacity / 4) {
        expandShrinkListUser(accountList, 2);
    }
}

void deleteUser(ListUser* accountList, User account) {
    int idx, l, m, r;

    // binary search untuk mencari indeks user di listdin
    l = 0, r = listLength(*accountList) - 1, idx = listLength(*accountList);
    while (l <= r) {
        m = (l + r) / 2;
        if (accountList->id_list.buffer[m].id < account.id) {
            l = m + 1;
        } else if (accountList->id_list.buffer[m].id > account.id) {
            r = m - 1;
        } else {
            idx = m;
        }
    }

    // hapus dari listdin
    if (idx != listLength(*accountList)) {
        destroyUser(&accountList->id_list.buffer[idx]);
        geserListDin(&accountList->id_list, idx, -1);
    }

    // binary search untuk mencari indeks user di setdin
    l = 0, r = listLength(*accountList) - 1, idx = listLength(*accountList);
    while (l <= r) {
        m = (l + r) / 2;
        if (strcasecmp(accountList->uname_set.buffer[m].username, account.username) < 0) {
            l = m + 1;
        } else if (strcasecmp(accountList->uname_set.buffer[m].username, account.username) > 0) {
            r = m - 1;
        } else {
            idx = m;
        }
    }

    // hapus dari setdin
    if (idx != listLength(*accountList)) {
        destroyUser(&accountList->uname_set.buffer[idx]);
        geserSetDin(&accountList->uname_set, idx, -1);
    }

    // kurangi panjang
    accountList->id_list.jumlah--;
    accountList->uname_set.jumlah--;
    accountList->jumlah--;

    // shrink kalau menyentuh 37,5% kapasitas
    if (accountList->jumlah <= 3*accountList->id_list.capacity / 8) {
        expandShrinkListUser(accountList, 0.5);
    }
}

User* getUserByID(ListUser* accountList, int id_user) {
    int idx, l, m, r;
    // binary search
    l = 0, r = listLength(*accountList) - 1, idx = -1;
    while (l <= r && idx == -1) {
        m = (l + r) / 2;
        if (accountList->id_list.buffer[m].id < id_user) {
            l = m + 1;
        } else if (accountList->id_list.buffer[m].id > id_user) {
            r = m - 1;
        } else {
            idx = m;
        }
    }
    if (idx != -1) return &accountList->id_list.buffer[idx];
    else {
        // kembalikan NULL jika tidak ditemukan
        printf("User dengan id %d tidak ditemukan!\n", id_user);
        return NULL;
    }
}

User* getUserByName(ListUser* accountList, char* nama) {
    int idx, l, m, r;
    // binary search
    l = 0, r = listLength(*accountList) - 1, idx = -1;
    while (l <= r && idx == -1) {
        m = (l + r) / 2;
        if (strcasecmp(accountList->uname_set.buffer[m].username, nama) < 0) {
            l = m + 1;
        } else if (strcasecmp(accountList->uname_set.buffer[m].username, nama) > 0) {
            r = m - 1;
        } else {
            idx = m;
        }
    }
    if (idx != -1) return &accountList->uname_set.buffer[idx];
    else {
        // kembalikan NULL jika tidak ditemukan
        printf("User dengan nama %s tidak ditemukan!\n", nama);
        return NULL;
    }
}

boolean isUsernameInSet(ListUser accountList, char* nama) {
    int  l, m, r;
    // binary search
    l = 0, r = listLength(accountList) - 1;
    while (l <= r) {
        m = (l + r) / 2;
        if (strcasecmp(accountList.uname_set.buffer[m].username, nama) < 0) {
            l = m + 1;
        } else if (strcasecmp(accountList.uname_set.buffer[m].username, nama) > 0) {
            r = m - 1;
        } else {
            return TRUE;
        }
    }
    return FALSE;
}

void tambahObatKeInventory(User* user, Obat obat) {
    // Check if this is the first obat being added to an empty inventory
    boolean wasEmpty = (user->inventory.jumlah == 0);
    
    // Add the obat to the inventory
    insertLastObat(&(user->inventory), obat);
    
    // If this was the first obat added, increment the global counter
    if (wasEmpty && user->inventory.jumlah > 0) {
        // Only increment if we're not already loading from config
        // This prevents double-counting when loading from config.txt
        if (!isLoadingFromConfig) {
            CountUserDenganObat++;
            printf("DEBUG: Incremented CountUserDenganObat to %d for user ID %d\n", 
                   CountUserDenganObat, user->id);
        }
    }
}