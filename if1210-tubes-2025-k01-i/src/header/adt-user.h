#ifndef ADTUSER_H
#define ADTUSER_H

#include "adt-penyakit.h"
#include "adt-obat.h"
#include "adt-stack.h"
#include "boolean.h"
#define MAX_USER 100
#define BASE_CAP 64

typedef struct {
    int id;
    char username[50];
    char password[50];
    char role[20];
    Penyakit riwayat_penyakit;    float suhu_tubuh;
    int tekanan_darah_sistolik;
    int tekanan_darah_diastolik;
    int detak_jantung;
    float saturasi_oksigen;
    float kadar_gula_darah;
    float berat_badan;
    int tinggi_badan;
    int kadar_kolesterol;
    int kadar_kolesterol_ldl;
    int trombosit;
    ListObat inventory;
    StackObat perut;
} User;


void createUser(User* account);

void destroyUser(User* account);

int isUserValid(User account);

boolean isSameUser(User account1, User account2);

typedef struct {
    User* buffer;
    int capacity;
    int jumlah;
} ListDin;

typedef struct {
    User* buffer;
    int capacity;
    int jumlah;
} SetDin;

/* ADT List elemen User*/
typedef struct {
    ListDin id_list;  // array of User
    SetDin uname_set;
    int jumlah;           // jumlah user
} ListUser;

void createListDin(ListDin* list, int capacity);

void createSetDin(SetDin* set, int capacity);

//Mengisi list user dengan MARK
void createListUser(ListUser* accountList, int capacity); 

void destroyListDin(ListDin* list);

void destroySetDin(SetDin* set);

void destroyListUser(ListUser* accountList);

//Menghitung jumlah user dalam list
int listLength(ListUser accountList); 

//Menambahkan user baru ke listdin lalu ke setdin
void insertUser(ListUser* accountList, User account);

//Menghapus user dari setdin dan listdin
void deleteUser(ListUser* accountList, User account);

//Menggeser data user dari start_idx hingga end of list sebanyak jarak
void geserListDin(ListDin* list, int start_idx, int jarak);

//Menggeser data user dari start_idx hingga end of set sebanyak jarak
void geserSetDin(SetDin* set, int start_idx, int jarak);

//Mengubah kapasitas list user
void expandShrinkListUser(ListUser* accountList, float modifier);

//Mengambil user dari list berdasarkan ID (binSearch listdin)
User* getUserByID(ListUser* accountList, int id_user); 

//Mengambil user dari list berdasarkan username (binSearch setdin case insensitive)
User* getUserByName(ListUser* accountList, char* nama);

//Memeriksa availability username
boolean isUsernameInSet(ListUser accountList, char* nama);

//Menambahkan obat ke inventory pasien
void tambahObatKeInventory(User* pasien, Obat obat);

#endif