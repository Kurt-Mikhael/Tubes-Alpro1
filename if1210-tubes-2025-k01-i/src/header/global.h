#ifndef GLOBAL_H
#define GLOBAL_H

#include "adt-obat.h"
#include "adt-penyakit.h"
#include "adt-user.h"
#include "adt-map.h"
#include "adt-matrix.h"
#include "adt-queue.h"
#include "adt-stack.h"
extern MapObatPenyakit map_obat_penyakit;
extern  Queue antrean;
extern ListPenyakit database_penyakit;
extern ListObat database_obat; 
extern MatriksRuangan rumah_sakit;
extern ListUser database_user;
extern int CountUser;
extern int CountPenyakit;
extern int CountObatPenyakit;
extern int max_queue;
extern int CountUserDenganObat;
extern boolean isLoadingFromConfig; // 
#endif