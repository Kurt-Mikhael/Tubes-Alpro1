#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../header/global.h"          // Contains all ADT headers
#include "../header/file-eksternal.h"
#include "../header/fungsi-prosedur.h"
#include "../header/interface.h"
#include "../header/boolean.h"
#include "../header/adt-user.h"

#define MAX_LINE 256

void login(User* current_user, ListUser database){
    // Validasi sudah login / belum
    if (isUserValid(*current_user)) {
        printf("Kamu sudah LOGIN sebagai %s %s!\n", current_user->role, current_user->username);
        printf("Silakan LOGOUT sebelum LOGIN sebagai pengguna lain.\n");
        return;
    }
    char username[50];
    char password[50];
    
    // Tampilkan header login yang menarik
    loginHeaderInterface();
    
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
    //Periksa apakah user sudah mati
    if (found_user->nyawa <= 0) {
        printf("User %s sudah meninggal dan tidak dapat login!\n", found_user->username);
        printf("💀 Rest in Peace 💀\n");
        return; // Login ditolak
    }
    // Input password
    while (1) {
        printf("Password: ");
        if (fgets(password, sizeof(password), stdin) == NULL) {
            printf("Error membaca input password\n");
            return;        }
        password[strcspn(password, "\n")] = '\0'; // Hapus newline
        if (strcasecmp(password, found_user->password) == 0) {
            // Validasi apakah user sudah mati

            
            *current_user = *found_user;
            
            // Tampilkan welcome interface yang menarik
            welcomeLoginInterface(*current_user);
            
            return; // Login berhasil
        } else {
            printf("Username atau password salah untuk pengguna yang bernama %s!\n", username);
            continue;
        }
    }
}

void registerPasien(User current_user, ListUser *database) {
    // Validasi login
    if (isUserValid(current_user)) {
        printf("Kamu sudah LOGIN sebagai %s %s!\n", current_user.role, current_user.username);
        printf("Silakan LOGOUT sebelum REGISTER sebagai pengguna lain.\n");
        return;
    }    char username[100];
    char password[100];
    int i;
    boolean valid;
    User new_user;
    
    // Tampilkan header register yang menarik
    registerHeaderInterface();
    
    // Input dan validasi username
    do {
        valid = TRUE; // Flag validasi
        
        printf("Username: ");
        if (fgets(username, sizeof(username), stdin) == NULL) {
            printf("Error membaca input username\n");
            return;
        }
        username[strcspn(username, "\n")] = '\0'; // Hapus newline
        
        // Validasi hanya mengandung huruf (a-z, A-Z)
        for (i = 0; username[i] != '\0'; i++) {
            if (!((username[i] >= 'a' && username[i] <= 'z') || 
                  (username[i] >= 'A' && username[i] <= 'Z'))) {
                printf("Registrasi gagal! Username hanya boleh berisi huruf (tanpa angka atau simbol).\n");
                valid = FALSE;
                break;
            }
        }
        if (!valid) continue;
        
        // Validasi susername unik (case-insensitive) - Binary Search
        // Buat versi lowercase untuk perbandingan
        if(isUsernameInSet(*database, username)){
            printf("Registrasi gagal! Username sudah terdaftar.\n");
            valid = FALSE;
            continue;
        }
        // Don't add to set here, will add after successful registration
        
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
void logout(User* current_user){
    // Tampilkan header decorative
    logoutHeaderInterface();

    // Validasi login
    if (!isUserValid(*current_user)) {
        printf("Kamu belum LOGIN sebagai role apapun.\n");
        return;
    }

    createUser(current_user);
    printf("Berhasil LOGOUT!\n");
    printf("Silakan LOGIN kembali untuk mengakses fitur rumah sakit.\n\n");
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

    int hasil = strcasecmp(temp, kodeUnik) == 0;
    free(temp);
    return hasil;
}


void gantiPasswordDiList(User *user, const char *passwordBaru) {
    //memperbarui data password di ADT List (fungsi perantara)
    strncpy(user->password, passwordBaru, sizeof(user->password) - 1);
    user->password[sizeof(user->password) - 1] = '\0';
}

void lupaPassword(User current_user, ListUser* database){

    // Validasi login
    if (isUserValid(current_user)) {
        printf("Kamu sudah LOGIN sebagai %s %s!\n", current_user.role, current_user.username);
        printf("Silakan LOGOUT sebelum menggunakan fitur LUPA_PASSWORD.\n");
        return;
    }    char username[50];
    char kodeUnik[100];
    char passwordBaru[50];
    
    // Tampilkan header lupa password yang menarik
    lupaPasswordHeaderInterface();
    
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
    }    // Minta password baru
    printf("Halo %s %s, silakan daftarkan ulang password anda!\n", 
          found_user->role, found_user->username);
    printf("Password Baru: ");
    if (fgets(passwordBaru, sizeof(passwordBaru), stdin) == NULL) {
        printf("Error membaca input password\n");
        return;
    }
    passwordBaru[strcspn(passwordBaru, "\n")] = '\0';
    
    // Update password di kedua list (uname_set dan id_list)
    gantiPasswordDiList(found_user, passwordBaru);
    
    // Cari user yang sama di id_list berdasarkan ID dan update passwordnya juga
    User* user_by_id = getUserByID(database, found_user->id);
    if (user_by_id != NULL) {
        gantiPasswordDiList(user_by_id, passwordBaru);
    }
    
    
    printf("Password berhasil diubah! Silakan login dengan password baru.\n");
}

/* Akses: Manager, Dokter, Pasien

Menampilkan panduan prosedur yang tersedia untuk current_user.*/
void help(User current_user){
    helpInterface(current_user);
}

/*Akses: Manajer*/
void lihatDenah(User current_user, MatriksRuangan denah) {
    
    // Tampilkan header decorative
    lihatDenahHeaderInterface();

    // Validasi login
    if (!isUserValid(current_user)) {
        printf("Login untuk melihat denah!\n");
        return;
    }
    // Display matriks ruangan
    printf("\n    "); // padding
    for (int j = 0; j < denah.column; j++) {
        printf("   %d ", j+1); // info kolom
    } printf("\n");

    printf("    "); // padding
    for (int j = 0; j < denah.column; j++) {
        if (j + 1 < 10) printf("+----");
        else printf("+-----");
        if (j == denah.column-1) printf("+\n");
    }


    for (int i = 0; i < denah.row; i++) {
        printf("  %c ", (char) (i+65)); // info baris
        for (int j = 0; j < denah.column; j++) {
            printf("| %c%d ", (char)(i+65), j+1);
            if (j == denah.column-1) printf("|\n");
        }
        printf("    "); // padding
        for (int j = 0; j < denah.column; j++) {
            if (j + 1 < 10) printf("+----");
            else printf("+-----");
            if (j == denah.column-1) printf("+\n");
        }
    }
    printf("\n");
}

void cariUser(User current_user, ListUser database){
    // Tampilkan header decorative
    cariUserHeaderInterface();
    
    // Validasi akses
    if(!isUserValid(current_user)) {
        printf("Kamu harus login terlebih dahulu\n");
        return;
    } else if (strcasecmp(current_user.role, "manager") != 0) {
        printf("Kamu tidak memiliki akses untuk cari user\n");
        return;
    }

    // Kasus list kosong
    if (database.id_list.jumlah == 0) {
        printf("Tidak ada user yang terdaftar!\n");
        return;
    }

    // Atribut searching
    printf("Cari berdasarkan?\n");
    printf("1. ID\n");
    printf("2. Nama\n");
    printf(">>> Pilihan: ");

    char pilihan[100];
    scanf("%s", pilihan);
    getchar(); // Clear newline from buffer

    if ( strcasecmp(pilihan,"1")==0|| strcasecmp(pilihan, "ID") == 0) {
        // Cari berdasarkan ID
        int id;
        printf("\n>>> Masukkan nomor ID user: ");
        scanf("%d", &id);
        getchar(); // Clear newline from buffer

        User* userDicari = getUserByID(&database, id);
        if (userDicari == NULL) {
            printf("Tidak ditemukan pengguna dengan ID %d\n", id);
        } else {
            printf("\nMenampilkan pengguna dengan nomor ID %d...\n", id);
            printf("ID | Nama     | Role     | Penyakit\n");
            printf("-------------------------------------\n");
            printf("%-2d | %-8s | %-8s | %s\n", 
                   userDicari->id, 
                   userDicari->username, 
                   userDicari->role, 
                   (strlen(userDicari->riwayat_penyakit.nama) > 0 && 
                    strcmp(userDicari->riwayat_penyakit.nama, "-") != 0) ? 
                   userDicari->riwayat_penyakit.nama : "-");
        }
    } else if (strcasecmp(pilihan,"2")==0 || strcasecmp(pilihan, "NAMA") == 0) {
        // Cari berdasarkan nama
        char nama[100];
        printf("\n>>> Masukkan nama user: ");
        if (fgets(nama, sizeof(nama), stdin) != NULL) {
            nama[strcspn(nama, "\n")] = '\0'; // Hapus newline
            
            User* userDicari = getUserByName(&database, nama);
            if (userDicari == NULL) {
                printf("Tidak ditemukan pengguna dengan nama %s\n", nama);
            } else {
                printf("\nMenampilkan pengguna dengan nama %s...\n", nama);
                printf("ID | Nama     | Role     | Penyakit\n");
                printf("-------------------------------------\n");
                printf("%-2d | %-8s | %-8s | %s\n", 
                       userDicari->id, 
                       userDicari->username, 
                       userDicari->role, 
                       (strlen(userDicari->riwayat_penyakit.nama) > 0 && 
                        strcmp(userDicari->riwayat_penyakit.nama, "-") != 0) ? userDicari->riwayat_penyakit.nama : "-");
            }
        } else {
            printf("Error membaca input nama\n");
        }
    } else {
        printf("Pilihan tidak valid!\n");
    }
}


void cariPasien(User current_user, ListUser database){
    // Tampilkan header decorative
    cariPasienHeaderInterface();
    
    // Validasi akses
    if (!isUserValid(current_user)) {
        printf("Kamu harus login terlebih dahulu\n");
        return;
    } else if (strcasecmp(current_user.role, "manager") != 0) {
        printf("Kamu tidak memiliki akses untuk cari pasien\n");
        return;
    }

    // Atribut searching
    int pilihan;
    printf("Cari pasien berdasarkan?\n1. ID\n2. Nama\n3. Penyakit\n>>> Pilihan : ");
    scanf("%d", &pilihan);
    if(pilihan == 1){
        // Cari berdasarkan ID
        int id;
        printf(">>> masukkan nomor ID pasien: ");
        scanf("%d", &id);

        User *pasiendicari = getUserByID(&database, id);
        if(pasiendicari == NULL || strcasecmp(pasiendicari->role, "pasien") != 0){
            printf("Tidak ditemukan pasien dengan ID %d\n", id);
        }
        else{
            printf("Menampilkan pasien dengan ID %d\n", id);
            printf("ID | Nama    | Penyakit\n");
            printf("-----------------------------------\n");
            printf("%d | %s    | %s\n", pasiendicari->id, pasiendicari->username, pasiendicari->riwayat_penyakit.nama);

        }
        
    }else if(pilihan == 2){
        // Cari berdasarkan nama
        char nama[100];
        printf(">>>Masukkan nama : ");
        scanf("%s", nama);

        User *pasiendicari = getUserByName(&database, nama);
        if(pasiendicari == NULL || strcasecmp(pasiendicari->role, "pasien") != 0){
            printf("Tidak ditemukan pasien dengan nama %s\n", nama);

        }else{
            printf("Menampilkan pasien dengan nama %s\n", nama);
            printf("ID | Nama    | Penyakit\n");
            printf("-----------------------------------\n");
            printf("%d | %s      | %s\n", pasiendicari->id, pasiendicari->username, pasiendicari->riwayat_penyakit.nama);
        }
    }else if(pilihan == 3){
        // Cari berdasarkan penyakit
        char nama_penyakit[100];
        printf("Masukkan nama penyakit : ");
        scanf("%s", nama_penyakit); 

        User pasiendicari[100];
        int jumlahpasien = 0;

        for(int i = 0; i < database.jumlah; i++){
            if(strcasecmp(database.id_list.buffer[i].role, "pasien") == 0 &&
        strcasecmp(database.id_list.buffer[i].riwayat_penyakit.nama, nama_penyakit) == 0){
            pasiendicari[jumlahpasien++] = database.id_list.buffer[i];
            }   
        }

        if(jumlahpasien == 0){
            printf("Tidak ditemukan pasien dengan penyakit %s\n", nama_penyakit);
            return;
        }

        // Pengurutan tampilan jika ditemukan pasien yang sesuai kriteria
        int pilihan2;
        int sort;
        printf("Urutkan berdasarkan?\n1. ID\n2. Nama\n>>> Pilihan : ");
        scanf("%d", &pilihan2);
        printf("Urutkan sort ?\n1. ASC(A-Z)\n2. DESC(Z-A)\n>>> Pilihan : ");
        scanf("%d", &sort);

        for(int i = 0; i < jumlahpasien - 1; i++){
            for(int j = 0; j < jumlahpasien - i - 1; j++){
                int comp = 0;
                if(pilihan2 == 1){
                    comp = pasiendicari[j].id - pasiendicari[j + 1].id;
                    
                }else if(pilihan2 == 2){
                    comp = strcasecmp(pasiendicari[j].username, pasiendicari[j + 1].username);
        
                }
                if((sort == 1 && comp > 0) || (sort == 2 && comp < 0)){
                    User temp = pasiendicari[j];
                    pasiendicari[j] = pasiendicari[j + 1];
                    pasiendicari[j + 1] = temp;
                }
            }
        }
        
        printf("Menampilkan pasien dengan penyakit %s\n", nama_penyakit);
        printf("ID | Nama    | Penyakit\n");
        printf("-----------------------------------\n");
        for (int i = 0; i < jumlahpasien; i++)
        {
            printf("%d | %s      | %s\n", pasiendicari[i].id, pasiendicari[i].username, pasiendicari[i].riwayat_penyakit.nama);
        }
        return;
        
    }
}

void cariDokter(User current_user, ListUser database){
    // Tampilkan header decorative
    cariDokterHeaderInterface();
    
    // validasi akses
    if (!isUserValid(current_user)) {
        printf("Kamu harus login terlebih dahulu\n");
        return;
    } else if (strcasecmp(current_user.role, "manager") != 0) {
        printf("Kamu tidak memiliki akses untuk cari dokter\n");
        return;
    }

    // s=atribut searching
    int pilihan;
    printf("Cari dokter berdasarkan?\n1. ID\n2. Nama\n>>> Pilihan : ");
    scanf("%d", &pilihan);
    if(pilihan == 1){
        // berdasrkan id
        int id;
        printf(">>> masukkan nomor ID dokter : ");
        scanf("%d", &id);

        User *dokterdicari = getUserByID(&database, id);
        if(dokterdicari == NULL || strcasecmp(dokterdicari->role, "dokter") != 0){
            printf("Tidak ditemukan dokter dengan ID %d\n", id);
        }
        else{
            printf("Menampilkan dokter dengan ID %d\n", id);
            printf("ID | Nama\n");
            printf("-----------------------------------\n");
            printf("%d | %s\n", dokterdicari->id, dokterdicari->username);

        }
    }else if(pilihan == 2){
        // berdasarkan nama
        char nama[100];
        printf(">>> Masukkan nama : ");
        scanf("%s", nama);

        User *dokterdicari = getUserByName(&database, nama);
        if(dokterdicari == NULL || strcasecmp(dokterdicari->role, "dokter") != 0){
            printf("Tidak ditemukan dokter dengan nama %s\n", nama);

        }else{
            printf("Menampilkan dokter dengan nama %s\n", nama);
            printf("ID | Nama\n");
            printf("-----------------------------------\n");
            printf("%d | %s\n", dokterdicari->id, dokterdicari->username);
        }
    }
}

void lihatAntrean(User current_user, MatriksRuangan denah) {
    // Tampilkan header decorative
    lihatAntreanHeaderInterface();
    
    // Validasi role
    if (strcasecmp(current_user.role, "manager") != 0) {
        printf("Anda tidak memiliki akses untuk fitur lihat antrean!\n\n");
        return;
    }

    printf(">>> LIHAT ANTREAN\n");

    // Menampilkan denah rumah sakit
    printf("\n    "); // padding
    for (int j = 0; j < denah.column; j++) {
        printf("   %d ", j+1); // info kolom
    } printf("\n");

    printf("    "); // padding
    for (int j = 0; j < denah.column; j++) {
        if (j + 1 < 10) printf("+----");
        else printf("+-----");
        if (j == denah.column-1) printf("+\n");
    }

    for (int i = 0; i < denah.row; i++) {
        printf("  %c ", (char) (i+65)); // info baris
        for (int j = 0; j < denah.column; j++) {
            printf("| %c%d ", (char)(i+65), j+1);
            if (j == denah.column-1) printf("|\n");
        }
        printf("    "); // padding
        for (int j = 0; j < denah.column; j++) {
            if (j + 1 < 10) printf("+----");
            else printf("+-----");
            if (j == denah.column-1) printf("+\n");
        }
    }
    printf("\n");
    printf("\n");

    // Menampilkan informasi setiap ruangan yang tidak kosong (setidaknya ada dokter)
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
    // Tampilkan header decorative
    tambahDokterHeaderInterface();
    
    // Validasi role
    if (strcasecmp(current_user.role, "manager") != 0) {
        printf("Anda tidak memiliki akses untuk fitur tambah dokter!\n\n");
        return;
    }
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
        
        // Validas hanya mengandung huruf (a-z, A-Z)
        for (i = 0; nama[i] != '\0'; i++) {
            if (!((nama[i] >= 'a' && nama[i] <= 'z') || 
                  (nama[i] >= 'A' && nama[i] <= 'Z'))) {
                printf("Registrasi gagal! Username hanya boleh berisi huruf (tanpa angka atau simbol).\n");
                valid = FALSE;
                break;
            }
        }

        // Validasi username unik
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
    // Tampilkan header decorative
    assignDokterHeaderInterface();
    
    if (strcasecmp(current_user.role, "manager") != 0) {
        printf("Anda tidak memiliki akses untuk fitur assign dokter!\n\n");
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
    if (strcasecmp(found_user->role, "dokter") != 0) {
        printf("User %s bukan seorang dokter!\n", found_user->username);
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

void unassignDokter(User current_user, ListUser database, MatriksRuangan* denah) {
    // validasi akses
    if (strcasecmp(current_user.role, "manager") != 0) {
        printf("Anda tidak memiliki akses untuk fitur unassign dokter!\n\n");
        return;
    }
    // input username
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
    if (strcasecmp(found_user->role, "dokter") != 0) {
        printf("User %s bukan seorang dokter!\n", found_user->username);
        return;
    }
    // Cek apakah dokter sudah di-assign
    int row_ruang = -1, col_ruang = -1;
    Ruangan* ruang_dokter = NULL;
    for (int row = 0; row < denah->row; row++) {
        for (int col = 0; col < denah->column; col++) {
            if (isSameUser(denah->ruang[row][col].dokter, *found_user)) {
                printf("Dokter %s di-assign di ruangan %c%d.\n", 
                       found_user->username, row + 'A', col + 1);
                ruang_dokter = &denah->ruang[row][col];
                row_ruang = row; col_ruang = col;
            }
        }
    }
    if (ruang_dokter == NULL) {
        printf("Dokter %s belum di-assign ke ruang mana pun!\n", found_user->username);
    } else if (!isQueueEmpty(*ruang_dokter->antrean)) {
        if (queueLength(*ruang_dokter->antrean) > ruang_dokter->kapasitas) {
            printf("Ada pasien di ruangan dan antrean untuk dokter ini!\n");
        } else {
            printf("Ada pasien di ruangan dokter ini!\n");
        }
        printf("Dokter yang sedang melayani pasien tidak bisa di-unassign!\n");

    } else {
        destroyUser(&ruang_dokter->dokter);
        printf("Berhasil unassign dokter %s, ruangan %c%d kosong.\n", found_user->username,
        (char) 'A' + row_ruang, col_ruang+1);
    }
}

void tambahBaris(User current_user, MatriksRuangan* denah) {
    // validasi akses
    if (strcasecmp(current_user.role, "manager") != 0) {
        printf("Anda tidak memiliki akses untuk mengubah layout rumah sakit!\n\n");
        return;
    }
    // validasi ketersediaan lahan
    if (denah->row < MAX_ROWS) {
        expandRow(denah);
        // tampilan denah
        printf("\n    "); // padding
        for (int j = 0; j < denah->column; j++) {
            printf("   %d ", j+1); // info kolom
        } printf("\n");

        printf("    "); // padding
        for (int j = 0; j < denah->column; j++) {
            if (j + 1 < 10) printf("+----");
            else printf("+-----");
            if (j == denah->column-1) printf("+\n");
        }

        for (int i = 0; i < denah->row; i++) {
            printf("  %c ", (char) (i+65)); // info baris
            for (int j = 0; j < denah->column; j++) {
                printf("| %c%d ", (char)(i+65), j+1);
                if (j == denah->column-1) printf("|\n");
            }
            printf("    "); // padding
            for (int j = 0; j < denah->column; j++) {
                if (j + 1 < 10) printf("+----");
                else printf("+-----");
                if (j == denah->column-1) printf("+\n");
            }
        }
        printf("\n");

        // keterangan tambahan
        printf("\nBaris ruangan %c ditambahkan ke rumah sakit!\n", (char) 'A' + denah->row-1);
        printf("Jumlah ruangan bertambah sebanyak %d!\n", denah->column);
        printf("Jumlah baris saat ini: %d\n", denah->row);
        if (denah->row == MAX_ROWS) printf("Tidak ada lahan tersisa untuk menambah baris.\n\n");
        else printf("Masih tersisa lahan untuk menambah %d baris.\n\n", MAX_ROWS - denah->row);
    } else {
        printf("\nGagal menambah baris: lahan sudah habis!\n");
        printf("Jumlah baris saat ini: %d\n\n", denah->row);
    }
}

void tambahKolom(User current_user, MatriksRuangan* denah) {
    // validasi akses
    if (strcasecmp(current_user.role, "manager") != 0) {
        printf("Anda tidak memiliki akses untuk mengubah layout rumah sakit!\n\n");
        return;
    }
    // validasi ketersediaan lahan
    if (denah->column < MAX_COLS) {
        expandCol(denah);
        // tampilan denah
        printf("\n    "); // padding
        for (int j = 0; j < denah->column; j++) {
            printf("   %d ", j+1); // info kolom
        } printf("\n");

        printf("    "); // padding
        for (int j = 0; j < denah->column; j++) {
            if (j + 1 < 10) printf("+----");
            else printf("+-----");
            if (j == denah->column-1) printf("+\n");
        }

        for (int i = 0; i < denah->row; i++) {
            printf("  %c ", (char) (i+65)); // info baris
            for (int j = 0; j < denah->column; j++) {
                printf("| %c%d ", (char)(i+65), j+1);
                if (j == denah->column-1) printf("|\n");
            }
            printf("    "); // padding
            for (int j = 0; j < denah->column; j++) {
                if (j + 1 < 10) printf("+----");
                else printf("+-----");
                if (j == denah->column-1) printf("+\n");
            }
        }
        printf("\n");

        // keterangan tambahan
        printf("\nKolom ruangan %d ditambahkan ke rumah sakit!\n", denah->column);
        printf("Jumlah ruangan bertambah sebanyak %d!\n", denah->row);
        printf("Jumlah kolom saat ini: %d\n", denah->column);
        if (denah->column == MAX_COLS) printf("Tidak ada lahan tersisa untuk menambah kolom.\n\n");
        else printf("Masih tersisa lahan untuk menambah %d kolom.\n\n", MAX_COLS - denah->column);
    } else {
        printf("Gagal menambah kolom: lahan sudah habis!\n");
        printf("Jumlah kolom saat ini: %d\n\n", denah->column);
    }
}

void kurangiBaris(User current_user, MatriksRuangan* denah) {
    // validasi akses
    if (strcasecmp(current_user.role, "manager") != 0) {
        printf("Anda tidak memiliki akses untuk mengubah layout rumah sakit!\n\n");
        return;
    }
    // validasi jumlah baris (tidak bisa dikurangi jika = 1)
    if (denah->row > 1) {
        boolean deletable = TRUE;
        printf("\n");
        // validasi keberadaan pasien di baris terakhir
        for (int j = 0; j < denah->column; j++) {
            if (!isQueueEmpty(*denah->ruang[denah->row - 1][j].antrean)) {
                printf("WARNING: dr. %s sedang melayani pasien di ruangan %c%d!\n",
                    denah->ruang[denah->row - 1][j].dokter.username, (char) (denah->row + 64), j+1);
                deletable = FALSE;
            }
        }
        // hapus jika tidak ada pasien di baris terakhir
        if (deletable) {
            shrinkRow(denah);
            // tampilan denah
            printf("\n    "); // padding
            for (int j = 0; j < denah->column; j++) {
                printf("   %d ", j+1); // info kolom
            } printf("\n");

            printf("    "); // padding
            for (int j = 0; j < denah->column; j++) {
                if (j + 1 < 10) printf("+----");
                else printf("+-----");
                if (j == denah->column-1) printf("+\n");
            }

            for (int i = 0; i < denah->row; i++) {
                printf("  %c ", (char) (i+65)); // info baris
                for (int j = 0; j < denah->column; j++) {
                    printf("| %c%d ", (char)(i+65), j+1);
                    if (j == denah->column-1) printf("|\n");
                }
                printf("    "); // padding
                for (int j = 0; j < denah->column; j++) {
                    if (j + 1 < 10) printf("+----");
                    else printf("+-----");
                    if (j == denah->column-1) printf("+\n");
                }
            }
            printf("\n");
            for (int j = 0; j < denah->column; j++) {
                if (isUserValid(denah->ruang[denah->row][j].dokter)) {
                    printf("dr. %s di-unassign dari ruangan %c%d!\n", 
                        denah->ruang[denah->row][j].dokter.username, (char) (denah->row + 65), j+1);
                    destroyUser(&denah->ruang[denah->row][j].dokter);
                }
            }
            printf("Jumlah baris saat ini: %d\n\n", denah->row);
        } else {
            printf("Gagal mengurangi baris: dokter di baris terakhir sedang melayani pasien!\n\n");
        }
    } else {
        printf("Gagal mengurangi baris: rumah sakit butuh ruangan untuk beroperasi!\n");
        printf("Saat ini tersisa 1 baris ruangan untuk pasien!\n\n");
    }
}

void kurangiKolom(User current_user, MatriksRuangan* denah) {
    // validasi akses
    if (strcasecmp(current_user.role, "manager") != 0) {
        printf("Anda tidak memiliki akses untuk mengubah layout rumah sakit!\n\n");
        return;
    }
    // validasi jumlah kolom (tidak bisa dikurangi jika = 1)
    if (denah->column > 1) {
        boolean deletable = TRUE;
        printf("\n");
        // validasi keberadaan pasien di kolom terakhir
        for (int i = 0; i < denah->row; i++) {
            if (!isQueueEmpty(*denah->ruang[i][denah->column - 1].antrean)) {
                printf("WARNING: dr. %s sedang melayani pasien di ruangan %c%d!\n",
                    denah->ruang[i][denah->column - 1].dokter.username, (char) (i + 65), denah->column);
                deletable = FALSE;
            }
        }
        // jika tidak ada pasien di kolom terakhir, hapus
        if (deletable) {
            shrinkCol(denah);
            // tampilan denah
            printf("\n    "); // padding
            for (int j = 0; j < denah->column; j++) {
                printf("   %d ", j+1); // info kolom
            } printf("\n");

            printf("    "); // padding
            for (int j = 0; j < denah->column; j++) {
                if (j + 1 < 10) printf("+----");
                else printf("+-----");
                if (j == denah->column-1) printf("+\n");
            }

            for (int i = 0; i < denah->row; i++) {
                printf("  %c ", (char) (i+65)); // info baris
                for (int j = 0; j < denah->column; j++) {
                    printf("| %c%d ", (char)(i+65), j+1);
                    if (j == denah->column-1) printf("|\n");
                }
                printf("    "); // padding
                for (int j = 0; j < denah->column; j++) {
                    if (j + 1 < 10) printf("+----");
                    else printf("+-----");
                    if (j == denah->column-1) printf("+\n");
                }
            }
            printf("\n");
            for (int i = 0; i < denah->row; i++) {
                if (isUserValid(denah->ruang[i][denah->column].dokter)) {
                    printf("dr. %s di-unassign dari ruangan %c%d!\n", 
                        denah->ruang[i][denah->column].dokter.username, (char) (i + 65), denah->column + 1);
                    destroyUser(&denah->ruang[i][denah->column].dokter);
                }
            }
            printf("Jumlah kolom saat ini: %d\n\n", denah->column);
        } else {
            printf("Gagal mengurangi kolom: dokter di kolom terakhir sedang melayani pasien!\n\n");
        }
    } else {
        printf("Gagal mengurangi kolom: rumah sakit butuh ruangan untuk beroperasi!\n");
        printf("Saat ini tersisa 1 kolom ruangan untuk pasien!\n\n");
    }
}

/* 
Memberikan informasi terkait penyakit yang diderita pasien
I.S : Anteran mungkin kosong
F.S : Menampilkan informasi terkait penyakit yang diderita pasien
*/
void diagnosis(User current_user, ListPenyakit ensiklopedia, MatriksRuangan* denah_ruang, ListUser* database) {
    // Tampilkan header decorative
    diagnosisHeaderInterface();
    
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

    // ambil pasien terdepan
    User* pasien = getQueueHead(denah_ruang->ruang[idxI][idxJ].antrean);

    if (strcmp(pasien->riwayat_penyakit.nama, "") != 0) {
        printf("Pasien %s sudah terdiagnosis sebelumnya!\n", pasien->username);
        return;
    }    printf(">>> DIAGNOSIS\n");
    boolean foundPenyakit = FALSE;

    // periksa data kesehatan dari list penyakit
    for (int i = 0; i < ensiklopedia.jumlah; i++) {
        Penyakit p = ensiklopedia.data[i];
        boolean match = TRUE;        if (!(pasien->suhu_tubuh >= p.suhu_min && pasien->suhu_tubuh <= p.suhu_max)) match = FALSE;
        if (!(pasien->tekanan_darah_sistolik >= p.tekanan_sistolik_min && pasien->tekanan_darah_sistolik <= p.tekanan_sistolik_max)) match = FALSE;
        if (!(pasien->tekanan_darah_diastolik >= p.tekanan_diastolik_min && pasien->tekanan_darah_diastolik <= p.tekanan_diastolik_max)) match = FALSE;
        if (!(pasien->detak_jantung >= p.detak_jantung_min && pasien->detak_jantung <= p.detak_jantung_max)) match = FALSE;
        if (!(pasien->saturasi_oksigen >= p.saturasi_oksigen_min && pasien->saturasi_oksigen <= p.saturasi_oksigen_max)) match = FALSE;
        if (!(pasien->kadar_gula_darah >= p.kadar_gula_min && pasien->kadar_gula_darah <= p.kadar_gula_max)) match = FALSE;        
        if (!(pasien->berat_badan >= p.berat_badan_min && pasien->berat_badan <= p.berat_badan_max)) match = FALSE;
        if (!(pasien->tinggi_badan >= p.tinggi_badan_min && pasien->tinggi_badan <= p.tinggi_badan_max)) match = FALSE;
        if (!(pasien->kadar_kolesterol >= p.kadar_kolesterol_min && pasien->kadar_kolesterol <= p.kadar_kolesterol_max)) match = FALSE;
        if (!(pasien->trombosit >= p.trombosit_min && pasien->trombosit <= p.trombosit_max)) match = FALSE;

        if (match) {
            // ada penyakit yang gejalanya sesuai
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
        // tidak ada penyakit yang gejalanya sesuai
        printf("Pasien %s , tidak memiliki gejala penyakit apapun\n", pasien->username);
        printf("Kemungkinan pasien sehat atau memiliki penyakit yang tidak tercatat dalam sistem.\n");
        // Keluarkan pasien dari antrean
        dequeue(&denah_ruang->ruang[idxI][idxJ].antrean);
        printf("Pasien %s telah dikeluarkan dari antrean.\n", pasien->username);

    }
}


// Memberikan obat ke pasien sesuai penyakit yang diderita
void ngobatin(User current_user, MatriksRuangan* denah_ruang, MapObatPenyakit obat_penyakit, ListUser* database){
    // Tampilkan header decorative
    ngobatinHeaderInterface();
    
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

    //Periksa apakah pasien telah dapat obat?
    if(pasien->isGetObat == TRUE) {
        printf("Pasien telah mendapat obat\n"); 
        return;
    }

    printf(">>> NGOBATIN\n");

    // dapatkan list obat dari map
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
                // printf("DEBUG: Penambahan CountUserDenganObat menjadi %d untuk user ID %d\n", CountUserDenganObat, pasien->id);
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
            pasien->isGetObat = TRUE;
            break;
        }
    }

    if (!found) {
        printf("Tidak ada obat yang tersedia untuk penyakit %s dalam database!\n", pasien->riwayat_penyakit.nama);
    }
}

void daftarCheckUp(User* current_user, ListUser* database, MatriksRuangan* rumah_sakit) {
    // Tampilkan header decorative
    daftarCheckupHeaderInterface();
    
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

    // Input data kesehatan
    User* pointerID = getUserByID(database, current_user->id);
    User* pointerName = getUserByName(database, current_user->username);
    float suhu_tubuh;
    int tekanan_darah_sistolik;
    int tekanan_darah_diastolik;
    int detak_jantung;
    float saturasi_oksigen;
    int kadar_gula_darah;
    float berat_badan;
    int tinggi_badan;
    int kadar_kolesterol;
    int trombosit;

    printf("Silakan masukkan data kesehatan anda\n");    for(;;) {
        printf("Suhu tubuh (celcius): ");
        if (scanf("%f", &suhu_tubuh) == 1 && suhu_tubuh > 0) break;
        else {
            printf("Suhu tubuh harus berupa angka positif!\n");
            // Riset buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
    pointerID->suhu_tubuh = suhu_tubuh;
    pointerName->suhu_tubuh = suhu_tubuh;
    current_user->suhu_tubuh = suhu_tubuh;
    for(;;) {
        printf("Tekanan darah (sistol/diastol, misal 120 80): ");
        if (scanf("%d", &tekanan_darah_sistolik) == 1 && scanf("%d", &tekanan_darah_diastolik) == 1 
            && tekanan_darah_diastolik > 0 && tekanan_darah_sistolik > 0) break;
        else {
            printf("Tekanan darah harus berupa bilangan bulat positif!\n");
            // Clear input buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
    current_user->tekanan_darah_sistolik = tekanan_darah_sistolik;
    current_user->tekanan_darah_diastolik = tekanan_darah_diastolik;
    pointerID->tekanan_darah_sistolik = tekanan_darah_sistolik;
    pointerID->tekanan_darah_diastolik = tekanan_darah_diastolik;
    pointerName->tekanan_darah_sistolik = tekanan_darah_sistolik;
    pointerName->tekanan_darah_diastolik = tekanan_darah_diastolik;
    for(;;) {
        printf("Detak jantung (bpm): ");
        if (scanf("%d", &detak_jantung) == 1 && detak_jantung > 0) break;
        else {
            printf("Detak jantung harus berupa angka positif!\n");
            // Clear input buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
    current_user->detak_jantung = detak_jantung;
    pointerID->detak_jantung = detak_jantung;
    pointerName->detak_jantung = detak_jantung;
    for(;;) {
        printf("Saturasi oksigen (%%): ");
        if (scanf("%f", &saturasi_oksigen) == 1 && saturasi_oksigen > 0 && saturasi_oksigen <= 100) break;
        else {
            printf("Saturasi oksigen harus berupa angka positif <= 100!\n");
            // Clear input buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
    current_user->saturasi_oksigen = saturasi_oksigen;
    pointerID->saturasi_oksigen = saturasi_oksigen;
    pointerName->saturasi_oksigen = saturasi_oksigen;
    for(;;) {
        printf("Kadar gula darah (mg/dL): ");
        if (scanf("%d", &kadar_gula_darah) == 1 && kadar_gula_darah > 0) break;
        else {
            printf("Kadar gula darah harus berupa angka positif!\n");
            // Reset Buffet
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
    current_user->kadar_gula_darah = kadar_gula_darah;
    pointerID->kadar_gula_darah = kadar_gula_darah;
    pointerName->kadar_gula_darah = kadar_gula_darah;
    for(;;) {
        printf("Berat badan (kg): ");
        if (scanf("%f", &berat_badan) == 1 && berat_badan > 0) break;
        else {
            printf("Berat badan harus berupa angka positif!\n");
            // Reset Buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
    current_user->berat_badan = berat_badan;
    pointerID->berat_badan = berat_badan;
    pointerName->berat_badan = berat_badan;
    for(;;) {
        printf("Tinggi badan (cm): ");
        if (scanf("%d", &tinggi_badan) == 1 && tinggi_badan > 0) break;
        else {
            printf("Tinggi badan harus berupa angka positif!\n");
            // Clear input buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
    current_user->tinggi_badan = tinggi_badan;
    pointerID->tinggi_badan = tinggi_badan;
    pointerName->tinggi_badan = tinggi_badan;
    for(;;) {
        printf("Kadar kolesterol (mg/dL): ");
        if (scanf("%d", &kadar_kolesterol) == 1 && kadar_kolesterol > 0) break;
        else {
            printf("Kadar kolesterol harus berupa angka positif!\n");
            // Clear input buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }    current_user->kadar_kolesterol = kadar_kolesterol;
    pointerID->kadar_kolesterol = kadar_kolesterol;
    pointerName->kadar_kolesterol = kadar_kolesterol;

    for(;;) {
        printf("Trombosit (ribu/uL): ");
        if (scanf("%d", &trombosit) == 1 && trombosit > 0) break;
        else {
            printf("Trombosit harus berupa angka positif!\n");
            // Clear input buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
    current_user->trombosit = trombosit;
    pointerID->trombosit = trombosit;
    pointerName->trombosit = trombosit;

    // tampilkan dokter dan ruangan yang tersedia beserta keterangannya
    printf("\nBerikut adalah daftar dokter yang tersedia:\n\n");
    int drcount = 0;
    int* price = (int*) malloc(rumah_sakit->column*rumah_sakit->row*sizeof(int));
    Ruangan** rooms = (Ruangan**) malloc(rumah_sakit->column*rumah_sakit->row*sizeof(Ruangan*));
    for (int row = 0; row < rumah_sakit->row; row++) {
        for (int col = 0; col < rumah_sakit->column; col++) {
            Ruangan current = rumah_sakit->ruang[row][col];
            if (!isRuanganEmpty(current) && queueLength(*current.antrean) < max_queue) {
                drcount++;
                rooms[drcount-1] = &rumah_sakit->ruang[row][col];
                printf("%d. Dr. %s - Ruangan %c%d\n", drcount,
                    current.dokter.username, (char) 'A' + row, col+1);
                printf("   %-19s: %d\n", "Aura", current.dokter.aura);
                if (isQueueEmpty(*current.antrean)) {
                    printf("   %-19s: -\n   %-19s: -\n", "Pasien di ruangan", "Pasien di antrean");
                } else if (queueLength(*current.antrean) > current.kapasitas) {
                    printf("   %-19s: %d\n   %-19s: %d\n", "Pasien di ruangan", current.kapasitas, "Pasien di antrean", queueLength(*current.antrean)-current.kapasitas);
                } else printf("   %-19s: %d\n   %-19s: -\n", "Pasien di ruangan", queueLength(*current.antrean), "Pasien di antrean");
                if (current.dokter.aura <= 0) {
                    price[drcount-1] = 1;
                } else {
                    price[drcount-1] = 3*current.dokter.aura/2 + 1;
                }
                printf("   %-19s: %d\n\n", "Biaya checkup", price[drcount-1]);
            }
        }
    }
    // pilih dokter jika tersedia
    if (drcount > 0) {
        int pilihan;
        for (;;) {
            printf("Pilih dokter yang tersedia (1-%d, 0 untuk batal): ", drcount);
            if (scanf("%d", &pilihan) == 1 && pilihan >= 0 && pilihan <= drcount) {
                if (pilihan == 0) {
                    printf("Pendaftaran checkup Anda dibatalkan.\n");
                    resetDataKesehatan(current_user);
                    resetDataKesehatan(pointerID);
                    resetDataKesehatan(pointerName);
                    return;
                } else if (current_user->banarich < price[pilihan-1]) {
                    printf("Maaf, banarich kamu tidak cukup.\n\n");
                } else {
                    break;
                }
            }
            else {
                printf("Pilihan tidak valid!\n");
                // Clear input buffer
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
            }
        }
        // modify banarich dan matriks berdasaran pilihan
        pointerID->banarich -= price[pilihan-1];
        pointerName->banarich -= price[pilihan-1];
        current_user->banarich -= price[pilihan-1];
        int jatah_RS = price[pilihan-1]/5;
        if (jatah_RS == 0) jatah_RS = 1;
        keuangan += jatah_RS;
        int jatah_dokter = price[pilihan-1] - jatah_RS;
        free(price);
        User* dokter_in_list = getUserByID(database, rooms[pilihan-1]->dokter.id);
        User* dokter_in_set = getUserByName(database, rooms[pilihan-1]->dokter.username);
        dokter_in_list->banarich += jatah_dokter;
        dokter_in_set->banarich += jatah_dokter;
        int offset = ((long)rooms[pilihan-1] - (long)rumah_sakit) / sizeof(Ruangan);
        int baris = offset / MAX_COLS;
        int kolom = offset % MAX_COLS;
        enqueue(rooms[pilihan-1]->antrean, *current_user);
        printf("\nPendaftaran berhasil!\n");
        printf("Anda terdaftar antrean checkup dengan dr. %s di ruangan %c%d.\n",
                rooms[pilihan-1]->dokter.username, (char) (65+baris), kolom+1);
        if (queueLength(*rooms[pilihan-1]->antrean) <= rooms[pilihan-1]->kapasitas) {
            printf("Anda bisa langsung masuk ke ruangan\n");
        } else {
            printf("Nomor antrean anda: %d\n", queueLength(*rooms[pilihan-1]->antrean) - rooms[pilihan-1]->kapasitas);
        }
        free(rooms);
    } else {
        printf("\nMaaf, tidak ada dokter yang tersedia saat ini.\n");
        printf("Coba sesaat lagi.\n");
        return;
    }
}

void minumObat(User* current_user, ListUser* database){
    // Tampilkan header decorative
    minumObatHeaderInterface();
    
    // validasi role
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

    // validasi jumlah obat
    if(current_user ->inventory.jumlah == 0){
        printf("obat abis bang\n");
        return;
    }

    // tampilan daftar obat
    printf("============ DAFTAR OBAT ============\n");

    for(int i = 0; i < current_user->inventory.jumlah; i++){
        printf("%d. %s\n", i+ 1, current_user->inventory.data[i].nama_obat);
    }

    int pilihan;
    printf(">>>Pilih obat untuk diminum : ");
    scanf("%d", &pilihan);

    if(pilihan < 1 || pilihan > current_user->inventory.jumlah){
        printf("Pilihan tidak tersedia!\n");
        return;
    }


    // update stack
    Obat obat_pilihan = current_user->inventory.data[pilihan - 1];
    pushStack(&current_user->perut, obat_pilihan);
    printf("GULUKGULUKGULUK... %s berhasil diminum!!!\n", obat_pilihan.nama_obat);

    // update inventory
    for(int i = pilihan - 1; i < current_user->inventory.jumlah - 1; i++){
        current_user->inventory.data[i] = current_user->inventory.data[i + 1];    
    }    current_user->inventory.jumlah--;
    
    if (current_user->inventory.jumlah == 0) {
        CountUserDenganObat--;
    }
    
    // ✅ SINKRONKAN DENGAN DATABASE (sync changes back to database_user)
    User* userByID = getUserByID(database, current_user->id);
    User* userByName = getUserByName(database, current_user->username);
    if (userByID != NULL) {
        userByID->inventory = current_user->inventory;
        userByID->perut = current_user->perut;
    }
    if (userByName != NULL) {
        userByName->inventory = current_user->inventory;
        userByName->perut = current_user->perut;
    }


}

void minumPenawar(User* pasien, MapObatPenyakit map_obat_penyakit, ListUser* database_pengguna, MatriksRuangan* rumah_sakit) {
    // Tampilkan header decorative
    minumPenawarHeaderInterface();
    
    if (isStackEmpty(pasien->perut)) {
        printf("Perut kosong!! Belum ada obat yang dimakan.\n");
        return;
    }

    // Cek apakah pasien sudah terdiagnosis
    if (strcmp(pasien->riwayat_penyakit.nama, "-") == 0 || strlen(pasien->riwayat_penyakit.nama) == 0) {
        printf("Kamu belum menerima diagnosis apapun dari dokter!\n");
        printf("Tanpa resep dokter, tidak bisa menggunakan penawar dengan aman.\n");
        return;
    }

    // Ambil resep obat berdasarkan penyakit pasien
    ListObat resep;
    boolean found = FALSE;
    for (int i = 0; i < map_obat_penyakit.length && !found; i++) {
        if (strcmp(map_obat_penyakit.data[i].key, pasien->riwayat_penyakit.nama) == 0) {
            resep = map_obat_penyakit.data[i].value;
            found = TRUE;
        }
    }

    if (!found) {
        printf("Data penyakit %s tidak ditemukan dalam database obat.\n", pasien->riwayat_penyakit.nama);
        return;
    }

    printf("Dokter akan membantu kamu menggunakan penawar untuk mengeluarkan obat...⚠️⚠️⚠️\n\n");

    // printf("DEBUG: Resep obat yang benar:\n");
    // for (int i = 0; i < resep.jumlah; i++) {
    //     printf("  %d. %s\n", i + 1, resep.data[i].nama_obat);
    // }

    int n = pasien->perut.top + 1;
    // printf("DEBUG: Obat yang sudah diminum (dari bawah ke atas):\n");
    // for (int i = 0; i < n; i++) {
    //     printf("  %d. %s\n", i + 1, pasien->perut.data[i].nama_obat);
    // }

    // Periksa urutan obat yang diminum terhadap resep
    boolean urutanBenar = TRUE;
    
    for (int i = 0; i < n && i < resep.jumlah; i++) {
        if (strcmp(pasien->perut.data[i].nama_obat, resep.data[i].nama_obat) != 0) {
            urutanBenar = FALSE;
            break;
        }
    }    
    if (!urutanBenar || n > resep.jumlah) {
        if (!isStackEmpty(pasien->perut)) {
            Obat dikeluarkan = popStack(&pasien->perut);
            pasien->nyawa--;              if (pasien->nyawa <= 0) {
                printf("💀 Anda Meninggal💀\n");
                //simpan nama pasien yang meninggal
                char username_temp[MAX_LINE];
                strncpy(username_temp, pasien->username, sizeof(username_temp) - 1);
                username_temp[sizeof(username_temp) - 1] = '\0';
                
                if (pasien->inventory.jumlah > 0) {
                    CountUserDenganObat--;

                }
                
                // Hapus pasien dari antrean
                boolean keluar = FALSE;                
                for (int i = 0; i < rumah_sakit->row && !keluar; i++) {
                    for (int j = 0; j < rumah_sakit->column && !keluar; j++) {                        
                        if (!isRuanganEmpty(rumah_sakit->ruang[i][j])) {
                            if (!isQueueEmpty(*rumah_sakit->ruang[i][j].antrean) && 
                                isSameUser(rumah_sakit->ruang[i][j].antrean->pasien, *pasien)) {
                                dequeue(&rumah_sakit->ruang[i][j].antrean);
                                User* dokter = &rumah_sakit->ruang[i][j].dokter;
                                User* pointer_id = getUserByID(database_pengguna, dokter->id);
                                pointer_id->aura--;
                                User* pointer_name = getUserByName(database_pengguna, dokter->username);
                                pointer_name->aura--;
                                dokter->aura--;
                                printf("dr. %s mengalami penurunan aura karena malpraktik\n", dokter->username);
                                printf("📋 Pasien dihapus dari antrian ruangan %c%d.\n", 'A' + i, j + 1);
                                keluar = TRUE;
                            }
                        }
                    }                
                }
                
                
                //Sinkronkan
                User* user_id = getUserByID(database_pengguna, pasien->id);
                User* user_name = getUserByName(database_pengguna, pasien->username);
                if (user_id != NULL) {
                    user_id->nyawa = 0;
                    strcpy(user_id->riwayat_penyakit.nama, "Meninggal");
                }
                if (user_name != NULL) {
                    user_name->nyawa = 0;
                    strcpy(user_name->riwayat_penyakit.nama, "Meninggal");
                }
                matiInterface(username_temp);
                
                // Reset akun agar kembali ke login
                destroyUser(pasien); 
                return;
            }
            printf("🤮 Penawar bekerja! Mengeluarkan satu obat teratas dari perutmu...\n");
            printf("Uwekkk!!! %s telah dikeluarkan dari perutmu.\n", dikeluarkan.nama_obat);
            if (!isFullObat(pasien->inventory)) {
                if (pasien->inventory.jumlah == 0) {
                    CountUserDenganObat++;
                    pasien->isGetObat = TRUE;
                }
                insertObatSesuaiResep(&pasien->inventory, dikeluarkan, resep);
                printf("↩️ Obat %s dikembalikan ke inventory sesuai urutan resep.\n", dikeluarkan.nama_obat);
            } else {
                printf("⚠️ Inventory penuh! Obat %s tidak bisa dikembalikan.\n", dikeluarkan.nama_obat);
            }
        }

        // Sinkronkan perubahan ke database
        User* user_id = getUserByID(database_pengguna, pasien->id);
        User* user_name = getUserByName(database_pengguna, pasien->username);
        if (user_id != NULL) {
            user_id->perut = pasien->perut;
            user_id->inventory = pasien->inventory;
        }
        if (user_name != NULL) {
            user_name->perut = pasien->perut;
            user_name->inventory = pasien->inventory;
        }

        printf("\n💡 Penawar berhasil digunakan! Coba minum obat sesuai urutan resep.\n");
        printf("Sisa nyawa kamu: %d\n", pasien->nyawa);
    } else {
        printf("✅ Obat yang kamu minum sudah sesuai resep dokter!\n");
        printf("Tidak perlu menggunakan penawar. Kamu bisa mencoba BOLEH_PULANG untuk pulang.\n");
    }
}

void antreanSaya(User current_user, MatriksRuangan rumah_sakit) {
    // Tampilkan header decorative
    antreanSayaHeaderInterface();
    
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
    // Tampilkan header decorative
    exitHeaderInterface();
    
    // Validasi akses
    if (isUserValid(*current_user)) {
        printf("Rumah sakit hanya dapat dihancurkan jika tidak ada pengguna yang mengakses!\n");
        printf("Silakan LOGOUT untuk EXIT\n");
        return FALSE;
    }

    char c;
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

void lihatUser(User current_user, ListUser database_pengguna) {
    // Tampilkan header decorative
    lihatUserHeaderInterface();
    
    // Validasi role - hanya manager yang dapat mengakses fitur ini
    if (strcmp(current_user.role, "manager") != 0) {
        printf("Hanya manager yang dapat mengakses fitur ini!\n");
        return;
    }

    // Validasi database kosong
    if (database_pengguna.id_list.jumlah == 0) {
        printf("Tidak ada pengguna yang terdaftar dalam sistem!\n");
        return;
    }

    printf("Urutkan berdasarkan?\n");
    printf("1. ID\n");
    printf("2. Nama\n");
    printf(">>> Pilihan: ");
    
    int kriteria_urutan;
    scanf("%d", &kriteria_urutan);
    getchar(); // Membersihkan newline
    
    printf("\nUrutan sort?\n");
    printf("1. ASC (A-Z)\n");
    printf("2. DESC (Z-A)\n");
    printf(">>> Pilihan: ");
    
    int arah_urutan;
    scanf("%d", &arah_urutan);
    getchar(); // Membersihkan newline

    // Salin data dari database ke array sementara untuk sorting
    int jumlah_pengguna = database_pengguna.id_list.jumlah;
    User* daftar_pengguna_terurut = malloc(jumlah_pengguna * sizeof(User));
    if (daftar_pengguna_terurut == NULL) {
        printf("Gagal mengalokasikan memori untuk menampilkan data pengguna!\n");
        return;
    }
    for (int indeks = 0; indeks < jumlah_pengguna; indeks++) {
        daftar_pengguna_terurut[indeks] = database_pengguna.id_list.buffer[indeks];
    }

    // Sorting menggunakan bubble sort
    for (int indeks_luar = 0; indeks_luar < jumlah_pengguna - 1; indeks_luar++) {
        for (int indeks_dalam = 0; indeks_dalam < jumlah_pengguna - indeks_luar - 1; indeks_dalam++) {
            int perlu_tukar = 0;

            if (kriteria_urutan == 1) { // Sort berdasarkan ID
                perlu_tukar = (arah_urutan == 1) ? (daftar_pengguna_terurut[indeks_dalam].id > daftar_pengguna_terurut[indeks_dalam + 1].id)
                                                 : (daftar_pengguna_terurut[indeks_dalam].id < daftar_pengguna_terurut[indeks_dalam + 1].id);
            } else { // Sort berdasarkan username
                int hasil_perbandingan = strcasecmp(daftar_pengguna_terurut[indeks_dalam].username, daftar_pengguna_terurut[indeks_dalam + 1].username);
                perlu_tukar = (arah_urutan == 1) ? (hasil_perbandingan > 0) : (hasil_perbandingan < 0);
            }

            if (perlu_tukar) {
                User pengguna_sementara = daftar_pengguna_terurut[indeks_dalam];
                daftar_pengguna_terurut[indeks_dalam] = daftar_pengguna_terurut[indeks_dalam + 1];
                daftar_pengguna_terurut[indeks_dalam + 1] = pengguna_sementara;
            }
        }
    }

    // Tampilkan hasil dalam format tabel
    printf("\nID | Nama        | Role      | Penyakit\n");
    printf("---------------------------------------------\n");

    for (int indeks = 0; indeks < jumlah_pengguna; indeks++) {
        User pengguna_sekarang = daftar_pengguna_terurut[indeks];
        const char* nama_penyakit = (strcmp(pengguna_sekarang.riwayat_penyakit.nama, "-") == 0 || strlen(pengguna_sekarang.riwayat_penyakit.nama) == 0)
                                   ? "-" : pengguna_sekarang.riwayat_penyakit.nama;

        printf("%-2d | %-11s | %-9s | %s\n", pengguna_sekarang.id, pengguna_sekarang.username, pengguna_sekarang.role, nama_penyakit);
    }

    free(daftar_pengguna_terurut);
}


// Menampilkan informasi kapasitas, nama dokter, daftar pasien dalam ruangan, dan antrean pasien suatu ruangan berdasarkan kodenya.*/
void lihatRuangan(User current_user, MatriksRuangan denah_rumah_sakit) {
    char kode_ruangan[10];
    int idxBaris, idxKolom;
    
    // Tampilkan header decorative
    lihatRuanganHeaderInterface();
    
    // Validasi role - hanya manager, dokter, dan pasien yang bisa mengakses
    if (strcmp(current_user.role, "manager") != 0 && 
        strcmp(current_user.role, "dokter") != 0 && 
        strcmp(current_user.role, "pasien") != 0) {
        printf("Anda tidak memiliki izin untuk mengakses informasi ruangan!\n");
        return;
    }
    
    printf("Masukkan kode ruangan: ");
    scanf("%s", kode_ruangan);
    
    // Parse kode ruangan (misal: A1 -> baris 0, kolom 1)
    if (strlen(kode_ruangan) < 2) {
        printf("Format kode ruangan tidak valid! Contoh: A1, B2, C3\n");
        return;
    }
    
    idxBaris = kode_ruangan[0] - 'A';
    idxKolom = kode_ruangan[1] - '0' - 1;
    
    // Validasi kode ruangan apakah berada dalam range denah
    if (idxBaris < 0 || idxBaris >= denah_rumah_sakit.row || idxKolom < 0 || idxKolom >= denah_rumah_sakit.column) {
        printf("Ruangan dengan kode %s tidak ditemukan dalam denah rumah sakit!\n", kode_ruangan);
        return;
    }
    
    // Tampilkan informasi lengkap ruangan
    printInfoRuangan(denah_rumah_sakit, idxBaris, idxKolom);
}


void bolehPulang(User* current_user, MapObatPenyakit map_obat_penyakit, ListUser* database_pengguna, MatriksRuangan* rumah_sakit) {
    bolehPulangHeaderInterface();

    if (strcasecmp(current_user->role, "pasien") != 0) {
        printf("Hanya pasien yang dapat mengakses fitur ini!\n");
        return;
    }

    if (strcmp(current_user->riwayat_penyakit.nama, "-") == 0 || strlen(current_user->riwayat_penyakit.nama) == 0) {
        printf("Kamu belum menerima diagnosis apapun dari dokter, jangan buru-buru pulang!\n");
        return;
    }

    ListObat resep;
    boolean found = FALSE;
    for (int i = 0; i < map_obat_penyakit.length && !found; i++) {
        if (strcmp(map_obat_penyakit.data[i].key, current_user->riwayat_penyakit.nama) == 0) {
            resep = map_obat_penyakit.data[i].value;
            found = TRUE;
        }
    }

    if (!found) {
        printf("Data penyakit %s tidak ditemukan dalam database obat.\n", current_user->riwayat_penyakit.nama);
        return;
    }

    printf("Dokter sedang memeriksa keadaanmu...\n\n");

    int n = current_user->perut.top + 1;

    // Periksa urutan obat yang diminum
    boolean urutanBenar = TRUE;
    int idxSalah = -1;

    for (int i = 0; i < n && i < resep.jumlah; i++) {
        if (strcmp(current_user->perut.data[i].nama_obat, resep.data[i].nama_obat) != 0) {
            urutanBenar = FALSE;
            idxSalah = i;
            break;
        }
    }

    if (!urutanBenar || n > resep.jumlah) {
        printf("Maaf, tapi kamu masih belum bisa pulang!\n\n");

        // Tampilkan urutan resep
        printf("Urutan peminuman obat yang diharapkan:\n");
        for (int i = 0; i < resep.jumlah; i++) {
            printf("%s%s", resep.data[i].nama_obat, (i != resep.jumlah - 1) ? " -> " : "\n");
        }

        // Tampilkan obat yang diminum
        printf("\nUrutan obat yang kamu minum:\n");
        for (int i = 0; i < n; i++) {
            if (i == idxSalah && idxSalah != -1) {
                // Tampilkan dalam warna merah
                printf("\x1b[31m%s\x1b[0m", current_user->perut.data[i].nama_obat);
            } else {
                printf("%s", current_user->perut.data[i].nama_obat);
            }
            if (i != n - 1) printf(" -> ");
        }
        printf("\n\nSilahkan kunjungi dokter untuk meminta penawar yang sesuai!\n");
        printf("Gunakan perintah: \x1b[36mMINUM_PENAWAR\x1b[0m\n");
        return;
    }

    if (n != resep.jumlah) {
        printf("Masih ada obat yang belum kamu habiskan, minum semuanya dulu yukk!\n");
        return;
    }    printf("🎉 Selamat! Kamu sudah dinyatakan sembuh oleh dokter! 🎉\n");
    printf("Silahkan pulang dan semoga sehat selalu!\n");

    // Hapus pasien dari antrean
    boolean keluar = FALSE;
    for (int i = 0; i < rumah_sakit->row && !keluar; i++) {
        for (int j = 0; j < rumah_sakit->column && !keluar; j++) {            
            if (!isRuanganEmpty(rumah_sakit->ruang[i][j])) {
                // Check if the patient is at the front of the queue
                if (!isQueueEmpty(*rumah_sakit->ruang[i][j].antrean) && 
                    isSameUser(rumah_sakit->ruang[i][j].antrean->pasien, *current_user)) {
                    dequeue(&rumah_sakit->ruang[i][j].antrean);
                    printf("✅ Kamu telah dihapus dari antrean ruangan %c%d.\n", 'A' + i, j + 1);
                    User* dokter = &rumah_sakit->ruang[i][j].dokter;
                    User* pointer_id = getUserByID(database_pengguna, dokter->id);
                    pointer_id->aura++;
                    User* pointer_name = getUserByName(database_pengguna, dokter->username);
                    pointer_name->aura++;
                    dokter->aura++;
                    printf("dr. %s mengalami peningkatan aura karena berhasil menyembuhkan pasien!\n\n", dokter->username);
                    keluar = TRUE;
                }
            }
        }
    }

    // Reset status pasien
    strcpy(current_user->riwayat_penyakit.nama, "");
    current_user->riwayat_penyakit.id = -1;
    createListObat(&current_user->inventory);
    createStackObat(&current_user->perut);
    resetDataKesehatan(current_user);

    // Sinkronkan ke database
    User* user_id = getUserByID(database_pengguna, current_user->id);
    User* user_name = getUserByName(database_pengguna, current_user->username);
    if (user_id != NULL) {
        strcpy(user_id->riwayat_penyakit.nama, "");
        user_id->riwayat_penyakit.id = -1;
        createListObat(&user_id->inventory);
        createStackObat(&user_id->perut);
        resetDataKesehatan(user_id);
    }
    if (user_name != NULL) {
        strcpy(user_name->riwayat_penyakit.nama, "");
        user_name->riwayat_penyakit.id = -1;
        createListObat(&user_name->inventory);
        createStackObat(&user_name->perut);
        resetDataKesehatan(user_name);
    }
}

/*Akses: Manajer

Menampilkan daftar ID dan Nama semua Dokter secara urut.
Pengurutan bisa berdasarkan ID (numerik) atau Nama (Leksikografis, Case-Insensitive).
Pengurutan bisa menaik / ascending atau menurun / descending.*/

void lihatDokter(User current_user, ListUser database) {

    // Tampilkan header decorative
    lihatUserHeaderInterface();

    // validasi akses
    if (strcmp(current_user.role, "manager") != 0) {
        printf("Hanya manager yang dapat mengakses fitur ini!\n");
        return;
    }

    // kasus list kosong
    if (database.id_list.jumlah == 0) {
        printf("Tidak ada user yang terdaftar!\n");
        return;
    }

    printf("Urutkan berdasarkan?\n");
    printf("1. ID\n");
    printf("2. Nama\n");
    printf("3. Aura\n");
    printf(">>> Pilihan: ");

    int sortBy;
    scanf("%d", &sortBy);
    getchar();
    User* aura_sorted = (User*) malloc(database.id_list.jumlah*sizeof(User));

    int n = 0;

    // sort by aura
    for (int i = 0; i < database.id_list.jumlah; i++) {
        int loc = i;
        for (int j = 0; j < i; j++) {
            if (aura_sorted[j].aura >= database.id_list.buffer[i].aura) {
                loc = j;
                break;
            }
        }
        for (int j = i; j > loc; j--) {
            aura_sorted[j] = aura_sorted[j-1];
        }
        aura_sorted[loc] = database.id_list.buffer[i];
        if (strcasecmp(database.id_list.buffer[i].role, "dokter") == 0) n++;
    }

    if (sortBy != 3) free(aura_sorted);

    printf("\nUrutan sort?\n");
    printf("1. ASC (A-Z)\n");
    printf("2. DESC (Z-A)\n");
    printf(">>> Pilihan: ");

    int sortOrder;
    scanf("%d", &sortOrder);
    getchar();

    // kasus tidak ada dokter
    if (n == 0) {
        printf("Tidak ada dokter yang terdaftar.\n");
        return;
    }

    printf("\nID | Nama        | Aura");
    printf("\n---+-------------+-----\n");
    if (sortBy == 1) {
        // sorted by ID
        if (sortOrder == 1) {
            for (int i = 0; i < database.jumlah; i++) {
                if (strcasecmp(database.id_list.buffer[i].role, "dokter") == 0) {
                    printf("%-2d | %-11s | %-2d\n", database.id_list.buffer[i].id, database.id_list.buffer[i].username, database.id_list.buffer[i].aura);
                }
            }
        } else {
             for (int i = database.jumlah - 1; i >= 0; i--) {
                if (strcasecmp(database.id_list.buffer[i].role, "dokter") == 0) {
                    printf("%-2d | %-11s | %-2d\n", database.id_list.buffer[i].id, database.id_list.buffer[i].username, database.id_list.buffer[i].aura);
                }
            }
        }
    } else if (sortBy == 2) {
        // sorted by Name
        if (sortOrder == 1) {
            for (int i = 0; i < database.jumlah; i++) {
                if (strcasecmp(database.uname_set.buffer[i].role, "dokter") == 0) {
                    printf("%-2d | %-11s | %-2d\n", database.uname_set.buffer[i].id, database.uname_set.buffer[i].username, database.uname_set.buffer[i].aura);
                }
            }
        } else {
             for (int i = database.jumlah - 1; i >= 0; i--) {
                if (strcasecmp(database.uname_set.buffer[i].role, "dokter") == 0) {
                    printf("%-2d | %-11s | %-2d\n", database.uname_set.buffer[i].id, database.uname_set.buffer[i].username, database.uname_set.buffer[i].aura);
                }
            }
        }
    } else if (sortBy == 3) {
        // sorted by Aura
        if (sortOrder == 1) {
            for (int i = 0; i < database.jumlah; i++) {
                if (strcasecmp(aura_sorted[i].role, "dokter") == 0) {
                    printf("%-2d | %-11s | %-2d\n", aura_sorted[i].id, aura_sorted[i].username, aura_sorted[i].aura);
                }
            }
        } else {
             for (int i = database.jumlah - 1; i >= 0; i--) {
                if (strcasecmp(aura_sorted[i].role, "dokter") == 0) {
                    printf("%-2d | %-11s | %-2d\n", aura_sorted[i].id, aura_sorted[i].username, aura_sorted[i].aura);
                }
            }
        }
        free(aura_sorted);
    }
}

/*Akses: Manajer

Menampilkan daftar ID, Nama, dan Penyakit semua Pasien secara urut.
Pengurutan bisa berdasarkan ID (numerik) atau Nama (Leksikografis, Case-Insensitive).
Pengurutan bisa menaik / ascending atau menurun / descending.*/
void lihatPasien(User current_user, ListUser database) {

    // Tampilkan header decorative
    lihatUserHeaderInterface();

    // validasi akses
    if (strcmp(current_user.role, "manager") != 0) {
        printf("Hanya manager yang dapat mengakses fitur ini!\n");
        return;
    }

    // kasus list kosong
    if (database.id_list.jumlah == 0) {
        printf("Tidak ada user yang terdaftar!\n");
        return;
    }

    printf("Urutkan berdasarkan?\n");
    printf("1. ID\n");
    printf("2. Nama\n");
    printf(">>> Pilihan: ");

    int sortBy;
    scanf("%d", &sortBy);
    getchar();

    printf("\nUrutan sort?\n");
    printf("1. ASC (A-Z)\n");
    printf("2. DESC (Z-A)\n");
    printf(">>> Pilihan: ");

    int sortOrder;
    scanf("%d", &sortOrder);
    getchar();

    // Salin data pasien
    int n = 0;
    User* pasienList = malloc(database.id_list.jumlah * sizeof(User));
    for (int i = 0; i < database.id_list.jumlah; i++) {
        if (strcasecmp(database.id_list.buffer[i].role, "pasien") == 0) {
            pasienList[n++] = database.id_list.buffer[i];
        }
    }

    if (n == 0) {
        printf("Tidak ada pasien yang terdaftar.\n");
        free(pasienList);
        return;
    }

    // Sorting
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            int shouldSwap = 0;
            if (sortBy == 1) {
                shouldSwap = (sortOrder == 1) ? (pasienList[j].id > pasienList[j + 1].id)
                                              : (pasienList[j].id < pasienList[j + 1].id);
            } else {
                int cmp = strcasecmp(pasienList[j].username, pasienList[j + 1].username);
                shouldSwap = (sortOrder == 1) ? (cmp > 0) : (cmp < 0);
            }

            if (shouldSwap) {
                User temp = pasienList[j];
                pasienList[j] = pasienList[j + 1];
                pasienList[j + 1] = temp;
            }
        }
    }

    printf("\nID | Nama        | Penyakit\n");
    printf("----+-------------+-----------\n");

    for (int i = 0; i < n; i++) {
        const char* penyakit = (strcmp(pasienList[i].riwayat_penyakit.nama, "-") == 0 || strlen(pasienList[i].riwayat_penyakit.nama) == 0)
                                 ? "-" : pasienList[i].riwayat_penyakit.nama;

        printf("%-2d | %-11s | %s\n", pasienList[i].id, pasienList[i].username, penyakit);
    }

    free(pasienList);
}

void skipAntrean(User* current_user, MatriksRuangan* rumah_sakit) {
    // Tampilkan header decorative
    skipAntreanHeaderInterface();
    
    if (strcasecmp(current_user->role, "pasien") != 0) {
        printf("Hanya pasien yang dapat mengakses fitur ini!\n");
        return;
    }

    //Cari lokasi ruangan pasien
    int idxI = -1, idxJ = -1;
    boolean found = FALSE;
    for (int i = 0; i < rumah_sakit->row && !found; i++) {
        for (int j = 0; j < rumah_sakit->column && !found; j++) {
            Ruangan current = rumah_sakit->ruang[i][j];
            if (!isRuanganEmpty(current) && !isQueueEmpty(*current.antrean)) {
                Address q = current.antrean;
                while (q != NULL) {
                    if (isSameUser(q->pasien, *current_user)) {
                        idxI = i;
                        idxJ = j;
                        found = TRUE;
                        break;
                    }
                    q = q->next;
                }
            }
        }
    }

    // Validasi apakah pasien ditemukan di ruangan manapun
    if (!found || idxI == -1 || idxJ == -1) {
        printf("Anda tidak terdaftar dalam antrean!\n");
        return;
    }

    // Cari lokasi pasien dalam antrean
    int idxPasien = findInQueue(*(rumah_sakit->ruang[idxI][idxJ].antrean), *current_user);
    if (idxPasien == -1) {
        printf("Anda tidak terdaftar dalam antrean!\n");
        return;
    }

    // Cek apakah pasien sudah berada di dalam ruangan (tidak dalam antrean)
    if (idxPasien < rumah_sakit->ruang[idxI][idxJ].kapasitas) {
        printf("Anda sudah berada di dalam ruangan, tidak bisa skip antrean!\n");
        return;
    }

    // Cek apakah pasien sudah berada di antrean terdepan
    if (idxPasien == rumah_sakit->ruang[idxI][idxJ].kapasitas) {
        printf("Anda sudah berada di antrean terdepan, tidak perlu skip!\n");
        return;
    }

    // Pindahkan pasien ke antrean terdepan
    // Simpan semua pasien yang akan dipindahkan
    User userDalam[MAX_USER];
    int tempCount = 0;
    
    // Simpan pasien yang berada di dalam ruangan (tidak boleh dipindah)
    for (int i = 0; i < rumah_sakit->ruang[idxI][idxJ].kapasitas; i++) {
        if (!isQueueEmpty(*rumah_sakit->ruang[idxI][idxJ].antrean)) {
            userDalam[tempCount++] = dequeue(&rumah_sakit->ruang[idxI][idxJ].antrean);
        }
    }
    
    // Simpan pasien yang berada di antrean sebelum current_user
    int antreanCount = 0;
    User antreanUsers[MAX_USER];
    while (!isQueueEmpty(*rumah_sakit->ruang[idxI][idxJ].antrean) && !isSameUser(rumah_sakit->ruang[idxI][idxJ].antrean->pasien, *current_user)) {
        antreanUsers[antreanCount++] = dequeue(&rumah_sakit->ruang[idxI][idxJ].antrean);
    }
    
    // Hapus current_user dari queue
    User prioritas;
    if (!isQueueEmpty(*rumah_sakit->ruang[idxI][idxJ].antrean) && isSameUser(rumah_sakit->ruang[idxI][idxJ].antrean->pasien, *current_user)) {
        prioritas = dequeue(&rumah_sakit->ruang[idxI][idxJ].antrean);
    }
    
    // Simpan sisa pasien di antrean
    User sisaUsers[MAX_USER];
    int sisaCount = 0;
    while (!isQueueEmpty(*rumah_sakit->ruang[idxI][idxJ].antrean)) {
        sisaUsers[sisaCount++] = dequeue(&rumah_sakit->ruang[idxI][idxJ].antrean);
    }
    
    for (int i = 0; i < tempCount; i++) {
        enqueue(rumah_sakit->ruang[idxI][idxJ].antrean, userDalam[i]);
    }
    
    enqueue(rumah_sakit->ruang[idxI][idxJ].antrean, prioritas);
    
    for (int i = 0; i < antreanCount; i++) {
        enqueue(rumah_sakit->ruang[idxI][idxJ].antrean, antreanUsers[i]);
    }
    
    for (int i = 0; i < sisaCount; i++) {
        enqueue(rumah_sakit->ruang[idxI][idxJ].antrean, sisaUsers[i]);
    }

    printf("✅ Anda berhasil dipindahkan ke antrean terdepan di ruangan dokter %s ruangan %c%d\n",
           rumah_sakit->ruang[idxI][idxJ].dokter.username,
           'A' + idxI, idxJ + 1);
    printf("Posisi baru Anda: Antrean ke-1 (setelah pasien yang sedang dalam ruangan)\n");
}

void cancelAntrean(User* current_user, MatriksRuangan* rumah_sakit) {
    // Tampilkan header decorative
    cancelAntreanHeaderInterface();
    
    if (strcasecmp(current_user->role, "pasien") != 0) {
        printf("Hanya pasien yang dapat mengakses fitur ini!\n");
        return;
    }

    // Cari lokasi ruangan pasien
    int idxI = -1, idxJ = -1;
    boolean found = FALSE;
    for (int i = 0; i < rumah_sakit->row && !found; i++) {
        for (int j = 0; j < rumah_sakit->column && !found; j++) {
            Ruangan current = rumah_sakit->ruang[i][j];
            if (!isRuanganEmpty(current) && !isQueueEmpty(*current.antrean)) {
                Address q = current.antrean;
                while (q != NULL) {
                    if (isSameUser(q->pasien, *current_user)) {
                        idxI = i;
                        idxJ = j;
                        found = TRUE;
                        break;
                    }
                    q = q->next;
                }
            }
        }
    }

    // Validasi apakah pasien ditemukan di ruangan manapun
    if (!found || idxI == -1 || idxJ == -1) {
        printf("Anda tidak terdaftar dalam antrean!\n");
        return;
    }
    int idxPasien = findInQueue(*(rumah_sakit->ruang[idxI][idxJ].antrean), *current_user);
    // Cek apakah pasien sudah berada di dalam ruangan (tidak dalam antrean)
    if (idxPasien < rumah_sakit->ruang[idxI][idxJ].kapasitas) {
        printf("Anda sudah berada di dalam ruangan, tidak bisa membatalkan antrean!\n");
        return;
    }

    // Cek apakah pasien sudah berada di antrean terdepan
    if (idxPasien == rumah_sakit->ruang[idxI][idxJ].kapasitas) {
        dequeue(&rumah_sakit->ruang[idxI][idxJ].antrean);
        printf("✅ Anda berhasil membatalkan antrean dokter %s ruangan %c%d\n",
               rumah_sakit->ruang[idxI][idxJ].dokter.username,
               'A' + idxI, idxJ + 1);
        return;
    }
    // Simpan semua pasien yang akan dipindahkan
    User userDalam[MAX_USER];
    int tempCount = 0;
    // Simpan pasien yang berada di dalam ruangan (tidak boleh dipindah)
    for (int i = 0; i < rumah_sakit->ruang[idxI][idxJ].kapasitas; i++) {
        if (!isQueueEmpty(*rumah_sakit->ruang[idxI][idxJ].antrean)) {
            userDalam[tempCount++] = dequeue(&rumah_sakit->ruang[idxI][idxJ].antrean);
        }
    }
    // Simpan pasien yang berada di antrean sebelum current_user
    int antreanCount = 0;
    User antreanUsers[MAX_USER];
    while (!isQueueEmpty(*rumah_sakit->ruang[idxI][idxJ].antrean) && !isSameUser(rumah_sakit->ruang[idxI][idxJ].antrean->pasien, *current_user)) {
        antreanUsers[antreanCount++] = dequeue(&rumah_sakit->ruang[idxI][idxJ].antrean);
    }
    // Hapus current_user dari queue
    if (!isQueueEmpty(*rumah_sakit->ruang[idxI][idxJ].antrean) && isSameUser(rumah_sakit->ruang[idxI][idxJ].antrean->pasien, *current_user)) {
        dequeue(&rumah_sakit->ruang[idxI][idxJ].antrean);
    } 
    // Simpan sisa pasien di antrean
    User sisaUsers[MAX_USER];
    int sisaCount = 0;
    while (!isQueueEmpty(*rumah_sakit->ruang[idxI][idxJ].antrean)) {
        sisaUsers[sisaCount++] = dequeue(&rumah_sakit->ruang[idxI][idxJ].antrean);
    }
    // Rekonstruksi queue dengan urutan baru:
    for (int i = 0; i < tempCount; i++) {
        enqueue(rumah_sakit->ruang[idxI][idxJ].antrean, userDalam[i]);
    }
    // Masukkan pasien sebelum current_user ke antrean
    for (int i = 0; i < antreanCount; i++) {
        enqueue(rumah_sakit->ruang[idxI][idxJ].antrean, antreanUsers[i]);
    }
    // Masukkan sisa pasien di antrean
    for (int i = 0; i < sisaCount; i++) {
        enqueue(rumah_sakit->ruang[idxI][idxJ].antrean, sisaUsers[i]);
    }
        printf("✅ Anda berhasil membatalkan antrean dokter %s ruangan %c%d\n",
            rumah_sakit->ruang[idxI][idxJ].dokter.username,
            'A' + idxI, idxJ + 1);

}

void gachaGaming(User* current_user, ListUser* database_user, unsigned* prev_rng) {
    gachaGamingHeaderInterface();
    // validasi akses
    if (!isUserValid(*current_user)) {
        printf("Login sebagai pasien untuk menggunakan fitur gacha!\n\n");
        return;
    }
    if (strcasecmp(current_user->role, "pasien") != 0) {
        printf("Hanya pasien yang dapat menggunakan fitur gacha!\n\n");
        return;
    }
    // RNG dengan LCG
    printf("Kchak.. Kchak.. Thunk!\n");
    unsigned gain = (3*(*prev_rng) + 1) % 29;
    *prev_rng = gain;
    printf("Kamu mendapatkan %d banarich!\n\n", gain);
    // update current user dan list
    current_user->banarich += gain;
    User* pointer_id = getUserByID(database_user, current_user->id);
    pointer_id->banarich = current_user->banarich;
    User* pointer_username = getUserByName(database_user, current_user->username);
    pointer_username->banarich = current_user->banarich;
}

void lihatDompet(User current_user) {
    lihatDompetHeaderInterface();

    // validasi akses
    if (!isUserValid(current_user)) {
        printf("Login untuk mengakses dompet!\n\n");
        return;
    }
    if (strcasecmp(current_user.role, "manager") == 0) {
        printf("Manager tidak memiliki dompet pribadi!\n");
        printf("Gunakan LIHAT_FINANSIAL untuk melihat kondisi keuangan rumah sakit!\n\n");
        return;
    }
    // tampilan dompet
    if (current_user.banarich == 0) {
        printf("Seekor lalat terbang dari dalam dompetmu yang kosong...\n\n");
    } else {
        printf("Dompetmu saat ini berisi %d banarich.\n\n", current_user.banarich);
    }
}

void lihatKeuangan(User current_user) {
    lihatKeuanganHeaderInterface();
    // validasi akses
    if (strcasecmp(current_user.role, "manager") != 0) {
        printf("Hanya manager yang berhak melihat kondisi keuangan rumah sakit!\n\n");
        return;
    }
    // tampilan keuangan
    printf("Rumah sakit saat ini memiliki %d banarich.\n", keuangan);
    printf("Tetaplah bekerja keras untuk memperkaya pemilik rumah sakit!\n\n");
}