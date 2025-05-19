#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "..\header\adt-obat.h"
#include "..\header\adt-penyakit.h"
#include "..\header\adt-user.h"
#include "..\header\adt-map.h"
#include "..\header\adt-matrix.h"
#include "..\header\adt-queue.h"
#include "..\header\adt-set.h"
#include "..\header\adt-stack.h"
#include "..\header\file-eksternal.h"
#include "..\header\fungsi-prosedur.h"

#define MAX_LINE 256


/*Akses: Sebelum Login

Mengubah current_user menjadi suatu user jika masukan username dan password sesuai database.*/
void login(User* current_user, ListUser database){
    char username[50];
    char password[50];
    int found_index = -1;
    
    printf(">>> LOGIN\n");
    
    // Input username
    while (1) {
        printf("Username: ");
        if (fgets(username, sizeof(username), stdin) == NULL) {
            printf("Error membaca input username\n");
            return;
        }
        username[strcspn(username, "\n")] = '\0'; // Hapus newline
        
        // Validasi username tidak kosong
        if (strlen(username) == 0) {
            printf("Username tidak boleh kosong!\n");
            continue;
        }
        
        // Cari username dalam database
        for (int i = 0; i < database.jumlah; i++) {
            if (strcmp(username, database.data[i].username) == 0) {
                found_index = i;
                break;
            }
        }
        
        if (found_index == -1) {
            printf("Tidak ada Manager, Dokter, atau Pasien yang bernama %s!\n", username);
            continue;
        }
        
        break; // Username valid, lanjut ke password
    }
    
    // Input password
    while (1) {
        printf("Password: ");
        if (fgets(password, sizeof(password), stdin) == NULL) {
            printf("Error membaca input password\n");
            return;
        }
        password[strcspn(password, "\n")] = '\0'; // Hapus newline
        
        // Validasi password
        if (strcmp(password, database.data[found_index].password) == 0) {
            *current_user = database.data[found_index];
            
            // Tampilkan pesan selamat datang sesuai role
            if (strcmp(current_user->role, "manager") == 0) {
                printf("Selamat pagi Manager %s!\n", current_user->username);
            } 
            else if (strcmp(current_user->role, "dokter") == 0) {
                printf("Selamat pagi Dokter %s!\n", current_user->username);
            } 
            else if (strcmp(current_user->role, "pasien") == 0) {
                printf("Selamat pagi %s! Ada keluhan apa?\n", current_user->username);
            }
            
            return; // Login berhasil
        } else {
            printf("Username atau password salah untuk pengguna yang bernama %s!\n", username);
            return;
        }
    }
}

/*Akses: Sebelum Login

Meminta masukan username dan password User baru.
Memeriksa set of username lalu menambahkan User (role pasien) ke database jika username unik.*/
void registerPasien(UsernameSet *username_set, ListUser *database) {
    char username[50];
    char password[50];
    char temp_username[50];
    int valid, i, m, l, r;
    User new_user;
    
    printf(">>> REGISTER\n");
    
    // Input dan validasi username
    do {
        valid = 1; // Flag validasi
        
        printf("Username: ");
        if (fgets(username, sizeof(username), stdin) == NULL) {
            printf("Error membaca input username\n");
            return;
        }
        username[strcspn(username, "\n")] = '\0'; // Hapus newline
        
        // Validasi 1: Hanya mengandung huruf (a-z, A-Z)
        for (i = 0; username[i] != '\0'; i++) {
            if (!((username[i] >= 'a' && username[i] <= 'z') || 
                  (username[i] >= 'A' && username[i] <= 'Z'))) {
                printf("Registrasi gagal! Username hanya boleh berisi huruf (tanpa angka atau simbol).\n");
                valid = 0;
                break;
            }
        }
        if (!valid) continue;
        
        // Validasi 2: Username unik (case-insensitive) - Binary Search
        // Buat versi lowercase untuk perbandingan
        strcpy(temp_username, username);
        for (i = 0; temp_username[i]; i++) {
            if (temp_username[i] >= 'A' && temp_username[i] <= 'Z') {
                temp_username[i] += 32; // Ke lowercase
            }
        }
        
        // Implementasi binary search langsung di sini
        l = 0;
        r = username_set->length - 1;
        while (l <= r) {
            m = (l + r) / 2;
            
            // Bandingkan lowercase dengan lowercase
            int cmp = 0;
            char set_name_lower[50];
            strcpy(set_name_lower, username_set->user_name[m]);
            for (i = 0; set_name_lower[i]; i++) {
                if (set_name_lower[i] >= 'A' && set_name_lower[i] <= 'Z') {
                    set_name_lower[i] += 32;
                }
            }
            
            cmp = strcmp(temp_username, set_name_lower);
            
            if (cmp > 0) {
                l = m + 1;
            } else if (cmp < 0) {
                r = m - 1;
            } else {
                valid = 0;
                break;
            }
        }
        
        if (!valid) {
            printf("Registrasi gagal! Pasien dengan nama %s sudah terdaftar.\n", username);
            continue;
        }
    } while (!valid);
    
    // Input password
    printf("Password: ");
    if (fgets(password, sizeof(password), stdin) == NULL) {
        printf("Error membaca input password\n");
        return;
    }
    password[strcspn(password, "\n")] = '\0'; // Hapus newline
    
    // Inisialisasi user baru
    createUser(&new_user);
    
    // Set ID (auto-increment)
    if (database->jumlah > 0) {
        new_user.id = database->data[database->jumlah-1].id + 1;
    } else {
        new_user.id = 1; // ID pertama
    }
    
    strncpy(new_user.username, username, sizeof(new_user.username) - 1);
    new_user.username[sizeof(new_user.username) - 1] = '\0';
    
    strncpy(new_user.password, password, sizeof(new_user.password) - 1);
    new_user.password[sizeof(new_user.password) - 1] = '\0';
    
    strcpy(new_user.role, "pasien");
    
    // Tambahkan ke database
    if (database->jumlah < MAX_USER) {
        database->data[database->jumlah] = new_user;
        database->jumlah++;
        
        // Tambahkan username ke set (dalam lowercase)
        // Implementasi insert langsung di sini
        if (!isUsernameInSet(*username_set, username)) {
            int pos;
            for (pos = username_set->length; 
                 pos > 0 && strcasecmp(username, username_set->user_name[pos-1]) < 0; 
                 pos--) {
                strcpy(username_set->user_name[pos], username_set->user_name[pos-1]);
            }
            strcpy(username_set->user_name[pos], username);
            username_set->length++;
        }
        
        printf("Pasien %s berhasil ditambahkan dengan ID %d!\n", username, new_user.id);
    } else {
        printf("Maaf, kapasitas database penuh! Tidak bisa menambah pasien baru.\n");
    }
}

/*Akses: Manajer, Dokter, Pasien

Mengubah current_user menjadi NO_USER.*/
void logout(User* current_user){
    createUser(current_user);
}

/*Akses: Sebelum Login

Mengubah password seorang user jika username ada dan kode unik sesuai ketentuan.*/
int validasiKodeUnik(char* username, char *kodeUnik) { //validasi kode unik apakah sesuai ketentuan
    int k = 0;
    int len = strlen(username);
    char* temp = (char*)malloc(len + 1);

    for (int i = 0; i < len; i++) {
        int count = 1;
        char hurufUsername = username[i];
        while (i + 1 < len && hurufUsername == username[i + 1]) {
            count++;
            i++;
        }
        if (count > 1) {
            char hurufCount[MAX_LINE];
            sprintf(hurufCount, "%d", count);
            for (int l = 0; hurufCount[l] != '\0'; l++) {
                temp[k++] = hurufCount[l];
            }
        }
        temp[k++] = hurufUsername;
    }
    temp[k] = '\0';

    int hasil = strcmp(temp, kodeUnik) == 0;
    free(temp);
    return hasil;
}

void gantiPasswordDiList(User *user, const char *passwordBaru) { //memperbarui data password di ADT List
    strncpy(user->password, passwordBaru, sizeof(user->password) - 1);
    user->password[sizeof(user->password) - 1] = '\0';
}

void lupaPassword(ListUser* database){
    char username[50];
    char kodeUnik[100];
    char passwordBaru[50];
    
    printf(">>> LUPA_PASSWORD\n");
    printf("Username: ");
    if (fgets(username, sizeof(username), stdin) == NULL) {
        printf("Error membaca input username\n");
        return;
    }
    username[strcspn(username, "\n")] = '\0';
    
    // Cari user di database
    int found_index = -1;
    for (int i = 0; i < database->jumlah; i++) {
        if (strcmp(database->data[i].username, username) == 0) {
            found_index = i;
            break;
        }
    }
    
    if (found_index == -1) {
        printf("Username tidak terdaftar!\n");
        return;
    }
    
    // Minta kode unik
    printf("Kode Unik: ");
    if (fgets(kodeUnik, sizeof(kodeUnik), stdin) == NULL) {
        printf("Error membaca input kode unik\n");
        return;
    }
    kodeUnik[strcspn(kodeUnik, "\n")] = '\0';
    
    // Validasi kode unik
    if (!validasiKodeUnik(username, kodeUnik)) {
        printf("Kode unik salah!\n");
        return;
    }
    
    // Minta password baru
    printf("Halo %s %s, silakan daftarkan ulang password anda!\n", 
          database->data[found_index].role, database->data[found_index].username);
    printf("Password Baru: ");
    if (fgets(passwordBaru, sizeof(passwordBaru), stdin) == NULL) {
        printf("Error membaca input password\n");
        return;
    }
    passwordBaru[strcspn(passwordBaru, "\n")] = '\0';
    
    // Ganti password di ListUser
    gantiPasswordDiList(&database->data[found_index], passwordBaru);
    
    printf("Password berhasil diubah! Silakan login dengan password baru.\n");
}

/* Akses: Manager, Dokter, Pasien

Menampilkan panduan prosedur yang tersedia untuk current_user.*/
void help(User current_user){
    printf("\n================ HELP ====================\n");
    
    if (!isUserValid(current_user)) {
        printf("\nKamu belum login sebagai role apapun. Silahkan login terlebih dahulu.\n\n");
        printf("1. LOGIN: Masuk ke dalam akun yang sudah terdaftar\n");
        printf("2. REGISTER: Membuat akun baru\n");
    } 
    else {
        char role_lower[20];
        strncpy(role_lower, current_user.role, sizeof(role_lower));
        for (int i = 0; role_lower[i]; i++) {
            if (role_lower[i] >= 'A' && role_lower[i] <= 'Z') {
                role_lower[i] = role_lower[i] + ('a' - 'A');
            }
        }

        if (strstr(role_lower, "dokter") != NULL) {
            printf("\nHalo, Dokter %s! Kamu memanggil command HELP. Kamu pasti sedang kebingungan.\n", 
                  current_user.username);
            printf("Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n");
            printf("1. LOGOUT: Keluar dari akun yang sedang digunakan\n");
            printf("2. LUPA_PASSWORD: Mengganti password\n");
            printf("3. LIHAT_DENAH: Melihat denah rumah sakit\n");
            printf("4. DIAGNOSIS: Melakukan diagnosis penyakit pasien berdasarkan kondisi tubuh pasien\n");
            printf("5. NGOBATIN: Memberi obat kepada pasien\n");
            printf("6. EXIT: Keluar dari program\n");
        }
        else if (strstr(role_lower, "pasien") != NULL) {
            printf("\nSelamat datang, %s. Kamu memanggil command HELP. Kamu pasti sedang kebingungan.\n", 
                current_user.username);
            printf("Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n");
            printf("1. LOGOUT: Keluar dari akun yang sedang digunakan\n");
            printf("2. LUPA_PASSWORD: Mengganti password\n");
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
                  current_user.username);
            printf("Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n");
            printf("1. LOGOUT: Keluar dari akun yang sedang digunakan\n");
            printf("2. LUPA_PASSWORD: Mengganti password\n");
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

/*Akses: Manajer

Menampilkan bentuk denah ruangan beserta kodenya.*/
void lihatDenah(User current_user, MatriksRuangan denah) {

    // Validasi login
    if (!isUserValid(current_user)) {
        printf("Login untuk melihat denah!\n");
        return;
    }

    // Display matriks ruangan
    for (int i = 0; i < denah.row; i++) {
        for (int j = 0; j < denah.column; j++) {
            printf("+----");
            if (j == denah.column-1) printf("+\n");
            printf("| %c%d ", (char)(i+65), j+1);
            if (j == denah.column-1) printf("|\n");
            if (i == denah.row - 1 && j < denah.column-1) printf("+----");
            if (i == denah.row - 1 && j == denah.column-1) printf("+\n");
        }
    }
}

void lihatAntrean(User current_user, MatriksRuangan denah) {
    
    if (!isUserValid(current_user)) {
        printf("Login untuk melihat seluruh antrean!\n");
        return;
    } else if (strcasecmp(current_user.role, "manajer") != 0) {
        printf("Kamu bukan manajer rumah sakit, lamar kerja jadi manajer dulu ya...\n");
        return;
    }
    lihatDenah(current_user, denah);
    for (int i = 0; i < denah.row; i++) {
        for (int j = 0; j < denah.column; j++) {
            if (isUserValid(denah.ruang[i][j].dokter)) {
                printInfoRuangan(denah, i, j);
                printf("\n");
            }
        }
    }
}