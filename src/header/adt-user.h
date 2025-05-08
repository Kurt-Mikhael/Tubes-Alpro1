#ifndef ADTUSER_H
#define ADTUSER_H

#include "adt-penyakit.h"
#include "adt-obat.h"
#include "adt-stack.h"

typedef struct {
    int id;
    char username[50];
    char password[50];
    char role[20];
    Penyakit riwayat_penyakit;
    float suhu_tubuh;
    int tekanan_darah_sistolik;
    int tekanan_darah_diastolik;
    int detak_jantung;
    float saturasi_oksigen;
    int kadar_gula_darah;
    float berat_badan;
    int tinggi_badan;
    int kadar_kolesterol;
    int kadar_kolesterol_ldl;
    int trombosit;
    ListObat inventory;
    StackObat perut;
} User;

void createUser(User* u);

int isUserValid(User u);

/* ADT List elemen User*/

typedef struct 
{
    /* data */
} ListUser;

void createListUser(ListUser* l);

void insertUserLast(ListUser* l, User u);

#endif