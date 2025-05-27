#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../header/global.h"          // Contains all ADT headers
#include "../header/file-eksternal.h"
#include "../header/fungsi-prosedur.h"
#include "../header/boolean.h"

#define MAX_LINE 256


/*Akses: Sebelum Login

Mengubah current_user menjadi suatu user jika masukan username dan password sesuai database.*/
void login(User* current_user, ListUser database){
    if (isUserValid(*current_user)) {
        printf("Kamu sudah LOGIN sebagai %s %s!\n", current_user->role, current_user->username);
        printf("Silakan LOGOUT sebelum LOGIN sebagai pengguna lain.\n");
        return;
    }
    char username[50];
    char password[50];
    
    printf(">>> LOGIN\n");
    
    // Input username
    User* found_user = NULL;
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
        found_user = getUserByName(&database, username);
        if (found_user == NULL) {
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
        if (strcasecmp(password, found_user->password) == 0) {
            *current_user = *found_user;
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
            continue;
        }
    }
}

/*Akses: Sebelum Login

Meminta masukan username dan password User baru.
Memeriksa set of username lalu menambahkan User (role pasien) ke database jika username unik.*/
void registerPasien(User current_user, ListUser *database) {
    // Validasi login
    if (isUserValid(current_user)) {
        printf("Kamu sudah LOGIN sebagai %s %s!\n", current_user.role, current_user.username);
        printf("Silakan LOGOUT sebelum REGISTER sebagai pengguna lain.\n");
        return;
    }

    char username[100];
    char password[100];
    int i;
    boolean valid;
    User new_user;
    
    printf(">>> REGISTER\n");
    
    // Input dan validasi username
    do {
        valid = TRUE; // Flag validasi
        
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
                valid = FALSE;
                break;
            }
        }
        if (!valid) continue;
        
        // Validasi 2: Username unik (case-insensitive)
        if(isUsernameInSet(*database, username)){
            printf("Registrasi gagal! Username sudah terdaftar.\n");
            valid = FALSE;
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
    
    if (database->jumlah > 0) {
        new_user.id = database->id_list.buffer[database->jumlah-1].id + 1;
    } else {
        new_user.id = 1; 
    }
    
    strncpy(new_user.username, username, sizeof(new_user.username) - 1);
    new_user.username[sizeof(new_user.username) - 1] = '\0';
    
    strncpy(new_user.password, password, sizeof(new_user.password) - 1);
    new_user.password[sizeof(new_user.password) - 1] = '\0';
    
    strcpy(new_user.role, "pasien");
      // Tambahkan ke database

    insertUser(database, new_user);
    printf("Pasien %s berhasil ditambahkan dengan ID %d!\n", username, new_user.id);

}

/*Akses: Manajer, Dokter, Pasien

Mengubah current_user menjadi NO_USER.*/
void logout(User* current_user, ListUser* database) {
    if (!isUserValid(*current_user)) {
        printf("Kamu belum LOGIN sebagai role apapun.\n");
        return;
    }

    // Simpan info username dan role sebelum logout
    char username[50], role[20];
    strcpy(username, current_user->username);
    strcpy(role, current_user->role);

    // Update data user di id_list (ListDin)
    for (int i = 0; i < database->id_list.jumlah; i++) {
        if (strcasecmp(database->id_list.buffer[i].username, username) == 0) {
            database->id_list.buffer[i] = *current_user; // Simpan semua perubahan (inventory, perut, dll)
            break;
        }
    }

    // Reset current_user (logout)
    createUser(current_user);

    printf("Pengguna %s (%s) berhasil LOGOUT!\n", role, username);
    printf("Data telah disimpan ke database.\n\n");
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

void lupaPassword(User current_user, ListUser* database){

    // Validasi login
    if (isUserValid(current_user)) {
        printf("Kamu sudah LOGIN sebagai %s %s!\n", current_user.role, current_user.username);
        printf("Silakan LOGOUT sebelum menggunakan fitur LUPA_PASSWORD.\n");
        return;
    }

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
    User* found_user = getUserByName(database, username);
    
    if (found_user == NULL) {
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
          found_user->role, found_user->username);
    printf("Password Baru: ");
    if (fgets(passwordBaru, sizeof(passwordBaru), stdin) == NULL) {
        printf("Error membaca input password\n");
        return;
    }
    passwordBaru[strcspn(passwordBaru, "\n")] = '\0';
    
    User* userByID = getUserByID(database, found_user->id);
    if (userByID != NULL) {
        gantiPasswordDiList(userByID, passwordBaru);
    }
    
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
            printf("6. STATUS_ANTREAN: Melihat status antrean\n");
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
            printf("6. LIHAT_ANTREAN: Melihat rincian seluruh ruangan yang tidak kosong\n");
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

    for (int j = 0; j < denah.column; j++) {
        printf("+----");
        if (j == denah.column-1) printf("+\n");
    }
    // Display matriks ruangan
    for (int i = 0; i < denah.row; i++) {
        for (int j = 0; j < denah.column; j++) {
            printf("| %c%d ", (char)(i+65), j+1);
            if (j == denah.column-1) printf("|\n");
        }
        for (int j = 0; j < denah.column; j++) {
            printf("+----");
            if (j == denah.column-1) printf("+\n");
        }
    }
}

/*Akses: Manajer, Dokter, Pasien

Menampilkan informasi kapasitas, nama dokter, daftar pasien dalam ruangan, dan antrean pasien suatu ruangan berdasarkan kodenya.*/
void lihatRuangan(User current_user, MatriksRuangan denah) {
    char ruang_code[10];
    int row, col;
    
    printf(">>> LIHAT RUANGAN\n");
    
    if (strcmp(current_user.role, "manager") != 0 && 
        strcmp(current_user.role, "dokter") != 0 && 
        strcmp(current_user.role, "pasien") != 0) {
        printf("Anda tidak memiliki izin untuk mengakses ruangan!\n");
        return;
    }
    
    printf("Masukkan kode ruangan: ");
    scanf("%s", ruang_code);
    
    // Parse room code (e.g., A1 -> row 0, col 1)
    if (strlen(ruang_code) < 2) {
        printf("Format kode ruangan tidak valid!\n");
        return;
    }
    
    row = ruang_code[0] - 'A';
    col = ruang_code[1] - '0' - 1;
    
    // Cek validitas row dan col
    if (row < 0 || row >= denah.row || col < 0 || col >= denah.column) {
        printf("Ruangan dengan kode %s tidak ditemukan!\n", ruang_code);
        return;
    }
    
    // Display ruangan info
    printInfoRuangan(denah, row, col);
}


void lihatAntrean(User current_user, MatriksRuangan denah) {
    // Validasi role
    if (strcasecmp(current_user.role, "manager") != 0) {
        printf("Anda tidak memiliki akses untuk fitur lihat antrean!\n\n");
        return;
    }

    printf(">>> LIHAT ANTREAN\n");
    printf("*** DENAH RUMAH SAKIT ***\n");
    lihatDenah(current_user, denah);
    printf("\n");
    printf("*** DETAIL RUANGAN YANG TIDAK KOSONG ***\n");
    for (int i = 0; i < denah.row; i++) {
        for (int j = 0; j < denah.column; j++) {
            if (isUserValid(denah.ruang[i][j].dokter)) {
                printInfoRuangan(denah, i, j);
                printf("\n");
            }
        }
    }
}


void tambahDokter(User current_user, ListUser* database) {
    // Validasi role
    if (strcasecmp(current_user.role, "manager") != 0) {
        printf("Anda tidak memiliki akses untuk fitur tambah dokter!\n\n");
        return;
    }
    printf(">>> TAMBAH DOKTER\n");
    char nama[50];
    char password[50];
    int i;
    User new_user;
    boolean valid;
    do {
    valid = TRUE; // Flag validasi
        
        printf("Username: ");
        if (fgets(nama, sizeof(nama), stdin) == NULL) {
            printf("Error membaca input username\n");
            return;
        }
        nama[strcspn(nama, "\n")] = '\0'; // Hapus newline
        
        // Validasi 1: Hanya mengandung huruf (a-z, A-Z)
        for (i = 0; nama[i] != '\0'; i++) {
            if (!((nama[i] >= 'a' && nama[i] <= 'z') || 
                  (nama[i] >= 'A' && nama[i] <= 'Z'))) {
                printf("Registrasi gagal! Username hanya boleh berisi huruf (tanpa angka atau simbol).\n");
                valid = FALSE;
                break;
            }
        }

        // Validasi 2: Username unik
        if (isUsernameInSet(*database, nama)) {
            printf("User %s sudah terdaftar.\n", nama);
            printf("Daftar dengan username lain\n");
            printf("atau\n");
            printf("gunakan command LUPA_PASSWORD jika kamu lupa password akunmu.\n");
            valid = FALSE;
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
        new_user.id = database->id_list.buffer[database->jumlah-1].id + 1;
    } else {
        new_user.id = 1; // ID pertama
    }
    
    strncpy(new_user.username, nama, sizeof(new_user.username) - 1);
    new_user.username[sizeof(new_user.username) - 1] = '\0';
    
    strncpy(new_user.password, password, sizeof(new_user.password) - 1);
    new_user.password[sizeof(new_user.password) - 1] = '\0';
    
    strcpy(new_user.role, "dokter");
    
    // Tambahkan ke database
    insertUser(database, new_user);
    printf("Dokter %s berhasil ditambahkan dengan ID %d!\n", nama, new_user.id);
}

void assignDokter(User current_user, ListUser database, MatriksRuangan* denah) {
    if (strcasecmp(current_user.role, "manager") != 0) {
        printf("Anda tidak memiliki akses untuk fitur tambah dokter!\n\n");
        return;
    }
    char nama_dokter[50];
    printf("Username: ");
    if (fgets(nama_dokter, sizeof(nama_dokter), stdin) == NULL) {
        printf("Error membaca input username\n");
        return;
    }
    nama_dokter[strcspn(nama_dokter, "\n")] = '\0'; // Hapus newline 
    // Cari user di database
    User* found_user = getUserByName(&database, nama_dokter);

    if (found_user == NULL) {
        printf("Username tidak terdaftar!\n");
        return;
    }
    // Cek apakah dokter sudah terdaftar
    for (int row = 0; row < denah->row; row++) {
        for (int col = 0; col < denah->column; col++) {
            if (isSameUser(denah->ruang[row][col].dokter, *found_user)) {
                printf("Dokter %s sudah terdaftar di ruangan %c%d!\n", 
                       found_user->username, row + 'A', col + 1);
                return;
            }
        }
    }
    // Assign dokter ke ruangan
    char kode_ruangan[10];
    printf("Masukkan kode ruangan (misal A1): ");
    if (fgets(kode_ruangan, sizeof(kode_ruangan), stdin) == NULL) {
        printf("Error membaca input kode ruangan\n");
        return;
    }
    kode_ruangan[strcspn(kode_ruangan, "\n")] = '\0'; // Hapus newline
    // Parse kode ruangan
    int row = kode_ruangan[0] - 'A';
    int col = kode_ruangan[1] - '0' - 1;
    // Cek validitas kode ruangan
    if (row < 0 || row >= denah->row || col < 0 || col >= denah->column) {
        printf("Ruangan dengan kode %s tidak ditemukan!\n", kode_ruangan);
        return;
    }
    // Cek apakah ruangan sudah terisi
    if (isUserValid(denah->ruang[row][col].dokter)) {
        printf("Ruangan %s sudah terisi oleh dokter %s!\n", kode_ruangan, 
               denah->ruang[row][col].dokter.username);
        return;
    }
    // Assign dokter ke ruangan
    denah->ruang[row][col].dokter = *found_user;
    printf("Dokter %s berhasil di-assign ke ruangan %c%d!\n", 
           found_user->username, row + 'A', col + 1);
}


/* 
Memberikan informasi terkait penyakit yang diderita pasien
I.S : Anteran mungkin kosong
F.S : Menampilkan informasi terkait penyakit yang diderita pasien
*/
void diagnosis(User current_user, ListPenyakit ensiklopedia, MatriksRuangan* denah_ruang, ListUser* database) {
    if (strcmp(current_user.role, "dokter") != 0) {
        printf("Hanya dokter yang dapat melakukan diagnosis!\n");
        return;
    }

    // Cari posisi ruangan dokter
    int idxI = -1, idxJ = -1;
    for (int i = 0; i < denah_ruang->row && idxI == -1; i++) {
        for (int j = 0; j < denah_ruang->column; j++) {
            if (isSameUser(denah_ruang->ruang[i][j].dokter, current_user)) {
                idxI = i;
                idxJ = j;
                break;
            }
        }
    }

    if (idxI == -1 || idxJ == -1) {
        printf("Dokter tidak ditemukan di ruangan manapun!\n");
        return;
    }

    if (isQueueEmpty(*(denah_ruang->ruang[idxI][idxJ].antrean))) {
        printf("Tidak ada pasien dalam antrean!\n");
        return;
    }

    User* pasien = getQueueHead(denah_ruang->ruang[idxI][idxJ].antrean);

    if (strcmp(pasien->riwayat_penyakit.nama, "") != 0) {
        printf("Pasien %s sudah terdiagnosis sebelumnya!\n", pasien->username);
        return;
    }

    printf(">>> DIAGNOSIS\n");
    boolean foundPenyakit = FALSE;

    for (int i = 0; i < ensiklopedia.jumlah; i++) {
        Penyakit p = ensiklopedia.data[i];
        boolean match = TRUE;

        if (!(pasien->suhu_tubuh >= p.suhu_min && pasien->suhu_tubuh <= p.suhu_max)) match = FALSE;
        if (!(pasien->tekanan_darah_sistolik >= p.tekanan_sistolik_min && pasien->tekanan_darah_sistolik <= p.tekanan_sistolik_max)) match = FALSE;
        if (!(pasien->tekanan_darah_diastolik >= p.tekanan_diastolik_min && pasien->tekanan_darah_diastolik <= p.tekanan_diastolik_max)) match = FALSE;
        if (!(pasien->detak_jantung >= p.detak_jantung_min && pasien->detak_jantung <= p.detak_jantung_max)) match = FALSE;
        if (!(pasien->saturasi_oksigen >= p.saturasi_oksigen_min && pasien->saturasi_oksigen <= p.saturasi_oksigen_max)) match = FALSE;
        if (!(pasien->kadar_gula_darah >= p.kadar_gula_min && pasien->kadar_gula_darah <= p.kadar_gula_max)) match = FALSE;
        if (!(pasien->berat_badan >= p.berat_badan_min && pasien->berat_badan <= p.berat_badan_max)) match = FALSE;
        if (!(pasien->tinggi_badan >= p.tinggi_badan_min && pasien->tinggi_badan <= p.tinggi_badan_max)) match = FALSE;
        if (!(pasien->kadar_kolesterol >= p.kadar_kolesterol_min && pasien->kadar_kolesterol <= p.kadar_kolesterol_max)) match = FALSE;
        if (!(pasien->kadar_kolesterol_ldl >= p.kadar_kolesterol_ldl_min && pasien->kadar_kolesterol_ldl <= p.kadar_kolesterol_ldl_max)) match = FALSE;
        if (!(pasien->trombosit >= p.trombosit_min && pasien->trombosit <= p.trombosit_max)) match = FALSE;

        if (match) {
            foundPenyakit = TRUE;
            strcpy(pasien->riwayat_penyakit.nama, p.nama);
            pasien->riwayat_penyakit.id = p.id;

            printf("Pasien %s terdiagnosis menderita penyakit %s.\n", pasien->username, p.nama);

            // ✅ Sinkronkan ke database (kedua buffer)
            User* userByID = getUserByID(database, pasien->id);
            User* userByName = getUserByName(database, pasien->username);
            if (userByID != NULL) {
                strcpy(userByID->riwayat_penyakit.nama, p.nama);
                userByID->riwayat_penyakit.id = p.id;
            }
            if (userByName != NULL) {
                strcpy(userByName->riwayat_penyakit.nama, p.nama);
                userByName->riwayat_penyakit.id = p.id;
            }

            break;
        }
    }

    if (!foundPenyakit) {
        printf("Pasien %s tidak menunjukkan gejala yang cocok dengan penyakit manapun dalam ensiklopedia.\n", pasien->username);
        printf("Kemungkinan pasien sehat atau memiliki penyakit yang tidak tercatat dalam sistem.\n");
    }
}


void ngobatin(User current_user, MatriksRuangan* denah_ruang, MapObatPenyakit obat_penyakit, ListUser* database){
    if (strcmp(current_user.role, "dokter") != 0) {
        printf("Hanya dokter yang dapat memberikan obat!\n");
        return;
    }

    // Cari ruangan dokter
    int idxI = -1, idxJ = -1;
    for (int i = 0; i < denah_ruang->row && idxI == -1; i++) {
        for (int j = 0; j < denah_ruang->column; j++) {
            if (isSameUser(denah_ruang->ruang[i][j].dokter, current_user)) {
                idxI = i;
                idxJ = j;
                break;
            }
        }
    }

    if (idxI == -1 || idxJ == -1) {
        printf("Dokter tidak ditemukan di ruangan manapun!\n");
        return;
    }

    if (isQueueEmpty(*denah_ruang->ruang[idxI][idxJ].antrean)) {
        printf("Tidak ada pasien dalam antrean!\n");
        return;
    }

    User* pasien = getQueueHead(denah_ruang->ruang[idxI][idxJ].antrean);
    if (strcmp(pasien->riwayat_penyakit.nama, "") == 0) {
        printf("Pasien %s belum terdiagnosis!\n", pasien->username);
        return;
    }

    printf(">>> NGOBATIN\n");

    boolean found = FALSE;
    for (int i = 0; i < obat_penyakit.length; i++) {
        if (strcmp(pasien->riwayat_penyakit.nama, obat_penyakit.data[i].key) == 0) {
            found = TRUE;
            printf("Pasien %s terdiagnosis menderita penyakit %s.\n", pasien->username, pasien->riwayat_penyakit.nama);
            printf("Obat yang harus diberikan:\n");
            ListObat* obat = &obat_penyakit.data[i].value;

            boolean hadMedications = (pasien->inventory.jumlah > 0);
            pasien->inventory.jumlah = 0;

            if (hadMedications) {
                CountUserDenganObat--;
                printf("DEBUG: Decremented CountUserDenganObat to %d (cleared inventory) for user ID %d\n", 
                       CountUserDenganObat, pasien->id);
            }

            int jumlah_obat = (obat->jumlah <= MAX_OBAT) ? obat->jumlah : MAX_OBAT;
            boolean userDuluTidakAdaObat = !hadMedications;

            for (int j = 0; j < jumlah_obat; j++) {
                printf(" (ID: %d) %s\n", obat->data[j].obat_id, obat->data[j].nama_obat);
                pasien->inventory.data[j] = obat->data[j];
            }
            pasien->inventory.jumlah = jumlah_obat;

            if (userDuluTidakAdaObat && jumlah_obat > 0) {
                CountUserDenganObat++;
                printf("DEBUG: Incremented CountUserDenganObat to %d for user ID %d\n", CountUserDenganObat, pasien->id);
            }

            // ✅ SINKRONKAN DENGAN DUA BUFFER (id_list dan uname_set)
            User* userByID = getUserByID(database, pasien->id);
            User* userByName = getUserByName(database, pasien->username);
            if (userByID != NULL) {
                userByID->inventory = pasien->inventory;
            }
            if (userByName != NULL) {
                userByName->inventory = pasien->inventory;
            }

            printf("Semua obat berhasil diberikan ke inventory pasien %s.\n", pasien->username);
            break;
        }
    }

    if (!found) {
        printf("Tidak ada obat yang tersedia untuk penyakit %s dalam database!\n", pasien->riwayat_penyakit.nama);
    }
}


void daftarCheckUp(User* current_user, ListUser* database, MatriksRuangan* rumah_sakit) {
    // Validasi akses
    if (strcasecmp(current_user->role, "pasien") != 0) {
        printf("Kamu tidak terdaftar sebagai pasien!\n");
        printf("LOGIN sebagai pasien untuk daftar checkup!\n");
        return;
    }

    // Validasi terdaftar
    if (isUserInMatriks(*current_user, *rumah_sakit)) {
        printf("Kamu sudah terdaftar dalam antrean!\n");
        printf("lihat ANTREAN_SAYA untuk informasi lebih lengkap.\n");
        printf("Selesaikan checkup sebelum mendaftar lagi ya!\n");
        return;
    }

    User* pointerID = getUserByID(database, current_user->id);
    User* pointerName = getUserByName(database, current_user->username);

    // data kesehatan
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

    printf("Silakan masukkan data kesehatan anda\n");
    for(;;) {
        printf("Suhu tubuh (celcius): ");
        scanf("%f", &suhu_tubuh);
        if (suhu_tubuh > 0) break;
        else printf("Suhu tubuh harus berupa angka positif!\n");
    }
    pointerID->suhu_tubuh = suhu_tubuh;
    pointerName->suhu_tubuh = suhu_tubuh;
    current_user->suhu_tubuh = suhu_tubuh;
    for(;;) {
        printf("Tekanan darah (sistol/diastol, misal 120 80): ");
        scanf("%d", &tekanan_darah_sistolik);
        scanf("%d", &tekanan_darah_diastolik);
        if (tekanan_darah_diastolik > 0 && tekanan_darah_sistolik > 0) break;
        else printf("Tekanan darah harus berupa angka positif!\n");
    }
    current_user->tekanan_darah_sistolik = tekanan_darah_sistolik;
    current_user->tekanan_darah_diastolik = tekanan_darah_diastolik;
    pointerID->tekanan_darah_sistolik = tekanan_darah_sistolik;
    pointerID->tekanan_darah_diastolik = tekanan_darah_diastolik;
    pointerName->tekanan_darah_sistolik = tekanan_darah_sistolik;
    pointerName->tekanan_darah_diastolik = tekanan_darah_diastolik;
    for(;;) {
        printf("Detak jantung (bpm): ");
        scanf("%d", &detak_jantung);
        if (detak_jantung > 0) break;
        else printf("Detak jantung harus berupa angka positif!\n");
    }
    current_user->detak_jantung = detak_jantung;
    pointerID->detak_jantung = detak_jantung;
    pointerName->detak_jantung = detak_jantung;
    for(;;) {
        printf("Saturasi oksigen (%%): ");
        scanf("%f", &saturasi_oksigen);
        if (saturasi_oksigen > 0 && saturasi_oksigen <= 100) break;
        else printf("Saturasi oksigen harus berupa angka positif <= 100!\n");
    }
    current_user->saturasi_oksigen = saturasi_oksigen;
    pointerID->saturasi_oksigen = saturasi_oksigen;
    pointerName->saturasi_oksigen = saturasi_oksigen;
    for(;;) {
        printf("Kadar gula darah (mg/dL): ");
        scanf("%d", &kadar_gula_darah);
        if (kadar_gula_darah > 0) break;
        else printf("Kadar gula darah harus berupa angka positif!\n");
    }
    current_user->kadar_gula_darah = kadar_gula_darah;
    pointerID->kadar_gula_darah = kadar_gula_darah;
    pointerName->kadar_gula_darah = kadar_gula_darah;
    for(;;) {
        printf("Berat badan (kg): ");
        scanf("%f", &berat_badan);
        if (berat_badan > 0) break;
        else printf("Berat badan harus berupa angka positif!\n");
    }
    current_user->berat_badan = berat_badan;
    pointerID->berat_badan = berat_badan;
    pointerName->berat_badan = berat_badan;
    for(;;) {
        printf("Tinggi badan (cm): ");
        scanf("%d", &tinggi_badan);
        if (tinggi_badan > 0) break;
        else printf("Tinggi badan harus berupa angka positif!\n");
    }
    current_user->tinggi_badan = tinggi_badan;
    pointerID->tinggi_badan = tinggi_badan;
    pointerName->tinggi_badan = tinggi_badan;
    for(;;) {
        printf("Kadar kolesterol (mg/dL): ");
        scanf("%d", &kadar_kolesterol);
        if (kadar_kolesterol > 0) break;
        else printf("Kadar kolesterol harus berupa angka positif!\n");
    }
    current_user->kadar_kolesterol = kadar_kolesterol;
    pointerID->kadar_kolesterol = kadar_kolesterol;
    pointerName->kadar_kolesterol = kadar_kolesterol;
    for(;;) {
        printf("Kadar kolesterol LDL (mg/dL): ");
        scanf("%d", &kadar_kolesterol_ldl);
        if (kadar_kolesterol_ldl > 0) break;
        else printf("Kadar kolesterol LDL harus berupa angka positif!\n");
    }
    current_user->kadar_kolesterol_ldl = kadar_kolesterol_ldl;
    pointerID->kadar_kolesterol_ldl = kadar_kolesterol_ldl;
    pointerName->kadar_kolesterol_ldl = kadar_kolesterol_ldl;
    for(;;) {
        printf("Trombosit (ribu/uL): ");
        scanf("%d", &trombosit);
        if (trombosit > 0) break;
        else printf("Trombosit harus berupa angka positif!\n");
    }
    current_user->trombosit = trombosit;
    pointerID->trombosit = trombosit;
    pointerName->trombosit = trombosit;

    printf("Berikut adalah daftar dokter yang tersedia:\n");
    int drcount = 0;
    for (int row = 0; row < rumah_sakit->row; row++) {
        for (int col = 0; col < rumah_sakit->column; col++) {
            Ruangan current = rumah_sakit->ruang[row][col];
            if (!isRuanganEmpty(current) && queueLength(*current.antrean) < 10) {
                drcount++;
                printf("%d. Dr. %s - Ruangan %c%d (Antrean: %d orang)\n", drcount,
                    current.dokter.username, (char) 'A' + row, col+1, queueLength(*current.antrean));
            }
        }
    }
    printf("\n");
    if (drcount > 0) {
        printf("Pilih dokter yang tersedia (1-%d): ", drcount);
        int pilihan;
        for (;;) {
            scanf("%d", &pilihan);
            if (pilihan < 1 || pilihan > drcount) printf("Pilihan tidak valid!\n");
            else break;
        }
        int count = 0;
        for (int row = 0; row < rumah_sakit->row; row++) {
            for (int col = 0; col < rumah_sakit->column; col++) {
                Ruangan current = rumah_sakit->ruang[row][col];
                if (!isRuanganEmpty(current) && queueLength(*current.antrean) < 10) {
                    count++;
                    if (count == pilihan) {
                        printf("\nPendaftaran berhasil!\n");
                        printf("Anda terdaftar antrean checkup dengan dr. %s di ruangan %c%d.\n",
                        current.dokter.username, (char) 'A' + row, col+1);
                        printf("Nomor antrean anda: %d\n", queueLength(*current.antrean) + 1);
                        enqueue(rumah_sakit->ruang[row][col].antrean, *current_user);
                        break;
                    }
                }
            }
            if (count == pilihan) break;
        }
    } else {
        printf("\nMaaf, tidak ada dokter yang tersedia saat ini.\n");
        printf("Coba sesaat lagi.\n");
        return;
    }
}
void minumObat(User* current_user, ListUser* database) {
    if (!isUserValid(*current_user)) {
        printf("Kamu tidak memiliki akses untuk minum obat!\n");
        return;
    } else if (strcasecmp(current_user->role, "manajer") == 0) {
        printf("Manajer kok minum obat? Kalo stres bilang...\n");
        return;
    } else if (strcasecmp(current_user->role, "dokter") == 0) {
        printf("anda kan yang ngasih obat\n");
        return;
    }

    if (current_user->inventory.jumlah == 0) {
        printf("obat abis bang\n");
        return;
    }

    printf("============ DAFTAR OBAT ============\n");

    for (int i = 0; i < current_user->inventory.jumlah; i++) {
        printf("%d. %s\n", i + 1, current_user->inventory.data[i].nama_obat);
    }

    int pilihan;
    printf(">>>Pilih obat untuk diminum : ");
    scanf("%d", &pilihan);

    if (pilihan < 1 || pilihan > current_user->inventory.jumlah) {
        printf("Pilihan tidak tersedia!\n");
        return;
    }

    Obat* obat_pilihan = &current_user->inventory.data[pilihan - 1];
    pushStack(&current_user->perut, *obat_pilihan);

    for (int i = pilihan - 1; i < current_user->inventory.jumlah - 1; i++) {
        current_user->inventory.data[i] = current_user->inventory.data[i + 1];
    }

    current_user->inventory.jumlah--;

    if (current_user->inventory.jumlah == 0) {
        CountUserDenganObat--;
        printf("(DEBUG: Decremented CountUserDenganObat to %d)\n", CountUserDenganObat);
    }

    printf("GULUKGULUKGULUK... %s berhasil diminum!!!\n", obat_pilihan->nama_obat);

    // === Update database ===
    User* stored_user = getUserByName(database, current_user->username);
    if (stored_user != NULL) {
        *stored_user = *current_user;
    }
}
void minumPenawar(User* current_user, ListUser* database) {
    if (isStackEmpty(current_user->perut)) {
        printf("Perut kosong!! Belum ada obat yang dimakan.\n");
        return;
    }

    Obat terakhir = popStack(&(current_user->perut));
    if (!isFullObat(current_user->inventory)) {
        insertLastObat(&(current_user->inventory), terakhir);
        printf("Uwekkk!!! %s keluar dan kembali ke inventory\n", terakhir.nama_obat);
    } else {
        printf("Inventory penuh! %s tidak bisa dimasukkan kembali.\n", terakhir.nama_obat);
        pushStack(&(current_user->perut), terakhir);
    }

    // === Update database ===
    User* stored_user = getUserByName(database, current_user->username);
    if (stored_user != NULL) {
        *stored_user = *current_user;
    }
}

void antreanSaya(User current_user, MatriksRuangan rumah_sakit) {
    if (strcasecmp(current_user.role, "pasien") != 0) {
        printf("Fitur ini hanya bisa diakses oleh pasien.\n");
        return;
    }

    boolean found = FALSE;
    for (int i = 0; i < rumah_sakit.row && !found; i++) {
        for (int j = 0; j < rumah_sakit.column && !found; j++) {
            Ruangan ruangan = rumah_sakit.ruang[i][j];
            if (!isRuanganEmpty(ruangan)) {
                Address q = ruangan.antrean;
                int pos = 1;
                int total = queueLength(*ruangan.antrean);

                while (q != NULL) {
                    if (isSameUser(q->pasien, current_user)) {
                        if (pos <= ruangan.kapasitas) {
                            // Kasus 3: Sudah berada di dalam ruangan
                            printf("Anda sedang berada di dalam ruangan dokter!\n");
                        } else {
                            // Kasus 1: Masih dalam antrean
                            printf("Status antrian Anda:\n");
                            printf("Dokter: Dr. %s\n", ruangan.dokter.username);
                            printf("Ruangan: %c%d\n", 'A' + i, j + 1);
                            printf("Posisi antrian: %d dari %d\n", pos, total);
                        }
                        found = TRUE;
                        break;
                    }
                    q = q->next;
                    pos++;
                }
            }
        }
    }

    if (!found) {
        // Kasus 2: Belum terdaftar
        printf("Anda belum terdaftar dalam antrian check-up!\n");
        printf("Silakan daftar terlebih dahulu dengan command DAFTAR_CHECKUP.\n");
    }
}

boolean exitRumahSakit(User* current_user, MatriksRuangan* denah, ListUser* database, ListPenyakit daftar_penyakit, ListObat daftar_obat, MapObatPenyakit map) {
    // Validasi akses
    if (isUserValid(*current_user)) {
        printf("Rumah sakit hanya dapat dihancurkan jika tidak ada pengguna yang mengakses!\n");
        printf("Silakan LOGOUT untuk EXIT\n");
        return FALSE;
    }

    char c;
    printf(">>> EXIT\n");
    char opt = ' ';
    /*Clear input buffer, sehingga ga ada sisa input*/
    fflush(stdin);
    do {
        printf("Mau save perubahan? (Y/N)\n");
        scanf(" %c", &opt); //
        // Clear input buffer 
        while ((c = getchar()) != '\n' && c != EOF);
        
        //Case insensitive
        if (opt == 'y') opt = 'Y';
        if (opt == 'n') opt = 'N';
        
    } while (opt != 'Y' && opt != 'N');
    if (opt == 'Y') saveData(&rumah_sakit, &database_user, database_penyakit, database_obat, map_obat_penyakit);
    destroyUser(current_user);
    destroyListUser(&database_user);
    // destroyMap(&resep_obat);
    destroyMatriksRuangan(&rumah_sakit);
    printf("Terima kasih telah menggunakan aplikasi Rumah Sakit Nimons!\n");
    printf("Sampai jumpa lagi!\n");
    return TRUE;
}