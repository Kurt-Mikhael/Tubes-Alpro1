#include <stdio.h>
#include "..\header\fungsi-prosedur.h"

void help(User* current_user){
    printf("\n================ HELP ====================\n");
    
    if (current_user == NULL) {
        printf("\nKamu belum login sebagai role apapun. Silahkan login terlebih dahulu.\n\n");
        printf("1. LOGIN: Masuk ke dalam akun yang sudah terdaftar\n");
        printf("2. REGISTER: Membuat akun baru\n");
    } 
    else {
        char role_lower[20];
        strncpy(role_lower, current_user->role, sizeof(role_lower));
        for (int i = 0; role_lower[i]; i++) {
            role_lower[i] = tolower(role_lower[i]);
        }

        if (strstr(role_lower, "dokter") != NULL) {
            printf("\nHalo, Dokter %s! Kamu memanggil command HELP. Kamu pasti sedang kebingungan.\n", 
                  current_user->username);
            printf("Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n");
            printf("1. LOGOUT: Keluar dari akun yang sedang digunakan\n");
            printf("2. LUPA_PASSWORD: Mengganti password");
            printf("3. LIHAT_DENAH: Melihat denah rumah sakit\n");
            printf("4. DIAGNOSIS: Melakukan diagnosis penyakit pasien berdasarkan kondisi tubuh pasien\n");
            printf("5. NGOBATIN: Memberi obat kepada pasien\n");
            printf("6. EXIT: Keluar dari program\n");
        }
        else if (strstr(role_lower, "pasien") != NULL) {
            printf("\nSelamat datang, %s. Kamu memanggil command HELP. Kamu pasti sedang kebingungan.\n", 
                current_user->username);
            printf("Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n");
            printf("1. LOGOUT: Keluar dari akun yang sedang digunakan\n");
            printf("2. LUPA_PASSWORD: Mengganti password");
            printf("3. LIHAT_DENAH: Melihat denah rumah sakit\n");
            printf("4. BOLEH_PULANG: Berkonsultasi dengan Dokter terkait status kepulangan\n");
            printf("5. DAFTAR_CHECKUP: Mendaftarkan diri untuk pemeriksaan dokter\n");
            printf("6. STATUS_ANTRIAN: Melihat status antrian\n");
            printf("7. MINUM_OBAT: Meminum obat yang diberikan Dokter\n");
            printf("8. MINUM_PENAWAR: Mengeluarkan obat terakhir yang diminum\n");
            printf("9. EXIT: Keluar dari program\n");  
        }
        else if (strstr(role_lower, "manager") != NULL) {
            printf("\nHalo Manager %s. Kenapa kamu memanggil command HELP? Kan kamu manager, tapi yasudahlah kamu pasti sedang kebingungan.\n", 
                  current_user->username);
            printf("Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n");
            printf("1. LOGOUT: Keluar dari akun yang sedang digunakan\n");
            printf("2. LUPA_PASSWORD: Mengganti password");
            printf("3. LIHAT_DENAH: Melihat denah rumah sakit\n");
            printf("4. LIHAT_USER: Melihat data seluruh pengguna\n");
            printf("5. CARI_USER: Mencari data pengguna\n");
            printf("6. LIHAT_ANTRIAN: Melihat rincian seluruh ruangan\n");
            printf("7. TAMBAH_DOKTER: Mendaftarkan dokter baru ke sistem\n");
            printf("8. EXIT: Keluar dari program\n");
        }
        else {
            printf("Data tidak ditemukan dalam sistem.");
        }
    }
    printf("\nFootnote:\n");
    printf("1. Untuk menggunakan aplikasi, silahkan masukkan nama fungsi yang terdaftar\n");
    printf("2. Jangan lupa untuk memasukkan input yang valid\n");
    printf("==========================================\n");
}