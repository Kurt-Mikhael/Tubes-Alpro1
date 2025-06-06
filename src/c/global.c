#include "../header/global.h"

// Definee variabel global
MapObatPenyakit map_obat_penyakit;
Queue antrean;
ListPenyakit database_penyakit;
MatriksRuangan rumah_sakit;
ListUser database_user;
ListObat database_obat;
int CountUser;
int CountPenyakit;
int CountObatPenyakit;
int CountUserDenganObat; 
int max_queue;
boolean isLoadingFromConfig = FALSE; 
unsigned rng;
unsigned keuangan;