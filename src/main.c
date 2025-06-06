#include "header/adt-map.h"
#include "header/adt-matrix.h"
#include "header/adt-obat.h"
#include "header/adt-penyakit.h"
#include "header/adt-queue.h"
#include "header/adt-stack.h"
#include "header/adt-user.h"
#include "header/boolean.h"
#include "header/file-eksternal.h"
#include "header/fungsi-prosedur.h"
#include "header/global.h"
#include "header/interface.h"
#include "header/loader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Tidak ada nama folder yang diberikan!\n");
        printf("Usage : ./main <<nama_folder>>\n");
        return EXIT_FAILURE;
    }

    const char *folderName = argv[1];
    if (!folderExists(folderName)) {
        printf("Folder \"%s\" tidak ditemukan.\n", folderName);
        return EXIT_FAILURE;
    }
    // inisialisasi pengguna
    User current_user;
    createUser(&current_user);
    loadData(folderName, &database_user, &database_penyakit, &database_obat, &map_obat_penyakit, &rumah_sakit, &max_queue);

    SelamatDatang();
    pintu();

    char command[32] = "";
    int c;
    while (1) {
        strcpy(command, "");
        printf(">>> ");
        scanf("%s", command);
        // Menghapus newline dari input buffer

        while ((c = getchar()) != '\n' && c != EOF) {
        }
        // clear();
        if (strcasecmp(command, "EXIT") == 0) {
            if (exitRumahSakit(&current_user, &rumah_sakit, &database_user, database_penyakit, database_obat, map_obat_penyakit)) {
                break;
            }
        } else if (strcasecmp(command, "LOGIN") == 0) {
            login(&current_user, database_user);
        } else if (strcasecmp(command, "REGISTER") == 0) {
            registerPasien(current_user, &database_user);
        } else if (strcasecmp(command, "LOGOUT") == 0) {
            logout(&current_user);
        } else if (strcasecmp(command, "LUPA_PASSWORD") == 0) {
            lupaPassword(current_user, &database_user);
        } else if (strcasecmp(command, "HELP") == 0) {
            help(current_user);
        } else if (strcasecmp(command, "LIHAT_DENAH") == 0) {
            lihatDenah(current_user, rumah_sakit);
        } else if (strcasecmp(command, "LIHAT_RUANGAN") == 0) {
            lihatRuangan(current_user, rumah_sakit);
        } else if (strcasecmp(command, "LIHAT_ANTREAN") == 0) {
            lihatAntrean(current_user, rumah_sakit);
        } else if (strcasecmp(command, "TAMBAH_DOKTER") == 0) {
            tambahDokter(current_user, &database_user);
        } else if (strcasecmp(command, "ASSIGN_DOKTER") == 0) {
            assignDokter(current_user, database_user, &rumah_sakit);
        } else if (strcasecmp(command, "UNASSIGN_DOKTER") == 0) {
            unassignDokter(current_user, database_user, &rumah_sakit);
        } else if (strcasecmp(command, "TAMBAH_BARIS") == 0) {
            tambahBaris(current_user, &rumah_sakit);
        } else if (strcasecmp(command, "TAMBAH_KOLOM") == 0) {
            tambahKolom(current_user, &rumah_sakit);
        } else if (strcasecmp(command, "KURANGI_BARIS") == 0) {
            kurangiBaris(current_user, &rumah_sakit);
        } else if (strcasecmp(command, "KURANGI_KOLOM") == 0) {
            kurangiKolom(current_user, &rumah_sakit);
        } else if (strcasecmp(command, "DAFTAR_CHECKUP") == 0) {
            daftarCheckUp(&current_user, &database_user, &rumah_sakit);
        } else if (strcasecmp(command, "DIAGNOSIS") == 0) {
            diagnosis(current_user, database_penyakit, &rumah_sakit, &database_user);
        } else if (strcasecmp(command, "NGOBATIN") == 0) {
            ngobatin(current_user, &rumah_sakit, map_obat_penyakit, &database_user);
        } else if (strcasecmp(command, "ANTREAN_SAYA") == 0) {
            antreanSaya(current_user, rumah_sakit);
        } else if (strcasecmp(command, "MINUM_OBAT") == 0) {
            minumObat(&current_user, &database_user);
        } else if (strcasecmp(command, "BOLEH_PULANG") == 0) {
            bolehPulang(&current_user, map_obat_penyakit, &database_user, &rumah_sakit);
        } else if (strcasecmp(command, "MINUM_PENAWAR") == 0) {
            minumPenawar(&current_user, map_obat_penyakit, &database_user, &rumah_sakit);
        } else if (strcasecmp(command, "CARI_USER") == 0) {
            cariUser(current_user, database_user);
        } else if (strcasecmp(command, "CARI_PASIEN") == 0) {
            cariPasien(current_user, database_user);
        } else if (strcasecmp(command, "CARI_DOKTER") == 0) {
            cariDokter(current_user, database_user);
        } else if (strcasecmp(command, "BOLEH_PULANG") == 0) {
            bolehPulang(&current_user, map_obat_penyakit, &database_user, &rumah_sakit);
        } else if (strcasecmp(command, "LIHAT_USER") == 0) {
            lihatUser(current_user, database_user);
        } else if (strcasecmp(command, "LIHAT_PASIEN") == 0) {
            lihatPasien(current_user, database_user);
        } else if (strcasecmp(command, "LIHAT_DOKTER") == 0) {
            lihatDokter(current_user, database_user);
        } else if (strcasecmp(command, "EXIT") == 0) {
            exitRumahSakit(&current_user, &rumah_sakit, &database_user, database_penyakit, database_obat, map_obat_penyakit);
        } else if (strcasecmp(command, "CLEAR") == 0) {
            clear();
        } else if (strcasecmp(command, "SKIP_ANTREAN") == 0) {
            skipAntrean(&current_user, &rumah_sakit);
        } else if (strcasecmp(command, "CANCEL_ANTREAN") == 0) {
            cancelAntrean(&current_user, &rumah_sakit);
        } else if (strcasecmp(command, "GACHA_GAMING") == 0) {
            gachaGaming(&current_user, &database_user, &rng);
        } else if (strcasecmp(command, "LIHAT_DOMPET") == 0) {
            lihatDompet(current_user);
        } else if (strcasecmp(command, "LIHAT_KEUANGAN") == 0) {
            lihatKeuangan(current_user);
        } else {
            printf("Command invalid!\n");
            printf("Masukkan \"HELP\" jika anda tidak tahu harus apa:)\n");
        }
    }
}