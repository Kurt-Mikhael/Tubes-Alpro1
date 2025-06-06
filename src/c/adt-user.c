#include "../header/adt-user.h"
#include <stdio.h>
#include "../header/global.h"
#include <stdlib.h>
#include <string.h>
#define MARK_ID -1

// Prosedur untuk membuat akun user baru
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
    account->trombosit = 0;
    createListObat(&(account->inventory));
    createStackObat(&(account->perut));
    createPenyakit(&(account->riwayat_penyakit));
    account->isGetObat = FALSE;
    account->nyawa = 3; 
    account->banarich = 0;
    account->aura = 0;
}

// Menghapus semua data user
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
    account->trombosit = 0;
    createListObat(&(account->inventory));
    destroyStackObat(&(account->perut));
    createPenyakit(&(account->riwayat_penyakit));
    account->isGetObat = FALSE;
    account->nyawa = 0; 
    account->banarich = 0;
    account->aura = 0;
}

//Periksa apakah user valid
int isUserValid(User account) {
    // User dianggap valid jika memiliki username
    return strlen(account.username) > 0;
}

// Periksa apakah dua user sama
boolean isSameUser(User account1, User account2) {
    // 2 User dianggap sama jika id dan usernamenya sama
    return (account1.id == account2.id && strcasecmp(account1.username, account2.username) == 0);
}

// Membuat list dinamis untuk menyimpan User
void createListDin(ListDin* list, int capacity) {
    list->capacity = capacity;
    list->buffer = malloc(sizeof(User)*capacity);
    list->jumlah = 0;
    for (int i = 0; i < capacity; i++) {
        createUser(&list->buffer[i]);
    }
}

// Membuat set dinamis untuk menyimpan User
void createSetDin(SetDin* set, int capacity) {
    set->capacity = capacity;
    set->buffer = malloc(sizeof(User)*capacity);
    set->jumlah = 0;
    for (int i = 0; i < capacity; i++) {
        createUser(&set->buffer[i]);
    }
}

// Membuat list user yang berisi id_list dan uname_set
void createListUser(ListUser* accountList, int capacity) {
    createListDin(&accountList->id_list, capacity);
    createSetDin(&accountList->uname_set, capacity);
    accountList->jumlah = 0;
}

// Menghapus list dinamis
void destroyListDin(ListDin* list) {
    free(list->buffer);
    list->capacity = 0;
    list->jumlah = 0;
}

// Menghapus set dinamis
void destroySetDin(SetDin* set) {
    free(set->buffer);
    set->capacity = 0;
    set->jumlah = 0;
}


// Menghapus list user
void destroyListUser(ListUser* accountList) {
    destroyListDin(&accountList->id_list);
    destroySetDin(&accountList->uname_set);
    accountList->jumlah = 0;
}

// Mengembalikan panjang list user
int listLength(ListUser accountList) {
    return accountList.jumlah;
}


//Menggeser elemen-elemen dalam list atau set dinamis
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

// Menggeser elemen-elemen dalam set dinamis
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

// Memperbesar atau mengecil list user
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

// Memasukan user baru ke dalam list user
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


// Menghapus user dari list user
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

// Mendapatkan user berdasarkan ID
User* getUserByID(ListUser* accountList, int id_user) {
    if (accountList == NULL || listLength(*accountList) == 0) {
        return NULL;
    }
    
    int l, m, r;
    // Binary search pada id_list yang sudah terurut berdasarkan ID
    l = 0;
    r = listLength(*accountList) - 1;
    
    while (l <= r) {
        m = (l + r) / 2;
        if (accountList->id_list.buffer[m].id < id_user) {
            l = m + 1;
        } else if (accountList->id_list.buffer[m].id > id_user) {
            r = m - 1;
        } else {
            // Found the user
            return &accountList->id_list.buffer[m];
        }
    }
    
    // User tidak ditemukan
    return NULL;
}

// Mendapatkan user berdasarkan nama
User* getUserByName(ListUser* accountList, char* nama) {
    if (accountList == NULL || nama == NULL || listLength(*accountList) == 0) {
        return NULL;
    }
    
    // Sequential search pada uname_set
    for (int i = 0; i < listLength(*accountList); i++) {
        if (strcasecmp(accountList->uname_set.buffer[i].username, nama) == 0) {
            // Found the user
            return &accountList->uname_set.buffer[i];
        }
    }
    
    // User tidak ditemukan
    return NULL;
}

// Memeriksa apakah username sudah ada dalam set
boolean isUsernameInSet(ListUser accountList, char* nama) {
    if (nama == NULL || listLength(accountList) == 0) {
        return FALSE;
    }
    
    // Sequential search pada uname_set
    for (int i = 0; i < listLength(accountList); i++) {
        if (strcasecmp(accountList.uname_set.buffer[i].username, nama) == 0) {
            // Username ditemukan
            return TRUE;
        }
    }
    
    // Username tidak ditemukan
    return FALSE;
}

// Menambahkan obat ke inventory user
void tambahObatKeInventory(User* user, Obat obat) {
    boolean isEmpty = (user->inventory.jumlah == 0);
    insertLastObat(&(user->inventory), obat);
    if (isEmpty && user->inventory.jumlah > 0) {
        if (!isLoadingFromConfig) {
            CountUserDenganObat++;
        }
    }
}

// Menghapus data kesehatan user
void resetDataKesehatan(User* user) {
    user->suhu_tubuh = 0;
    user->tekanan_darah_sistolik = 0;
    user->tekanan_darah_diastolik = 0;
    user->detak_jantung = 0;
    user->saturasi_oksigen = 0;
    user->kadar_gula_darah = 0;
    user->berat_badan = 0;    
    user->tinggi_badan = 0;
    user->kadar_kolesterol = 0;
    user->trombosit = 0;
}