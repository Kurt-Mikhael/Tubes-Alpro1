#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/global.h"
#include "../header/file-eksternal.h"
#include "../header/adt-map.h"
#include "../header/adt-user.h"
#include "../header/adt-obat.h"
#include "../header/adt-penyakit.h"
#include "../header/adt-stack.h"
#include "../header/adt-queue.h"
#include "../header/adt-matrix.h"
#include "../header/boolean.h"
#include "../header/fungsi-prosedur.h"
#include "../header/interface.h"
#include "../header/adt-stack.h"
#include "../header/adt-queue.h"
#include "../header/adt-matrix.h"
#include "../header/adt-map.h"
#include "../header/adt-user.h"
#include "../header/adt-obat.h"
#include "../header/adt-penyakit.h"

// Fungsi untuk memuat data dari folder yang diberikan
void loadData(const char *folderName, ListUser *database_user, ListPenyakit *database_penyakit, ListObat *daftar_obat, MapObatPenyakit *map, MatriksRuangan *denah_ruang, int *max_queue);