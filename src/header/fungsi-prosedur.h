#ifndef FUNGSIPROSEDUR_H
#define FUNGSIPROSEDUR_H

#include "adt-obat.h"
#include "adt-penyakit.h"
#include "adt-user.h"
#include "adt-list.h"
#include "adt-map.h"
#include "adt-matrix.h"
#include "adt-queue.h"
#include "adt-set.h"
#include "adt-stack.h"
#include "file-eksternal.h"

void login(User* current_user, ListUser database);

void registerPasien(UsernameSet* username, ListUser* database);

void logout(User* current_user);

void lupaPassword(ListUser* database);

void help(User current_user);

void lihatDenah(MatriksRuangan denah);

void lihatRuangan(MatriksRuangan denah, char* kode_ruangan);

void lihatUser(User current_user, ListUser database);

void lihatPasien(User current_user, ListUser database);

void lihatDokter(User current_user, ListUser database);

void cariUser(User current_user, ListUser database);

void cariPasien(User current_user, ListUser database);

void cariDokter(User current_user, ListUser database);

void lihatAntrean(User current_user, MatriksRuangan denah);

void tambahDokter(User current_user, UsernameSet* username, ListUser* database);

void diagnosis(User current_user, User* pasien, ListPenyakit ensiklopedia);

void ngobatin(User current_user, User pasien, MapObatPenyakit obat_penyakit);

void exitRumahSakit(ListUser database);

#endif