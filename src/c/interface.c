#include <stdio.h>
#include <stdlib.h>
#include "../header/global.h"
#include <string.h>
#define PINK  "\033[95m"
#define CYAN  "\033[96m"
#define YELLOW "\033[93m"
#define GREEN "\033[92m"
#define RED "\033[91m"
#define BLUE "\033[94m"
#define MAGENTA "\033[95m"
#define BOLD "\033[1m"
#define RESET "\033[0m"

void clear() {
    #ifdef _WIN32
        system("cls");    // Windows
    #else
        system("clear");  // Linux and macOS
    #endif
}

void SelamatDatang() {
    clear();
    printf(PINK
        "  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\ \n"
        " ( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o ) \n"
        " > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  \n"
        " /\\_/\\   ____       _                       _     ____        _                      /\\_/\\ \n"
        "( o.o ) / ___|  ___| | __ _ _ __ ___   __ _| |_  |  _ \\  __ _| |_ __ _ _ __   __ _  ( o.o )\n"
        " > ^ <  \\___ \\ / _ \\ |/ _` | '_ ` _ \\ / _` | __| | | | |/ _` | __/ _` | '_ \\ / _` |  > ^ < \n"
        " /\\_/\\   ___) |  __/ | (_| | | | | | | (_| | |_  | |_| | (_| | || (_| | | | | (_| |  /\\_/\\ \n"
        "( o.o ) |____/ \\___|_|\\__,_|_| |_| |_|\\__,_|\\__| |____/ \\__,_|\\__\\__,_|_| |_|\\__, | ( o.o )\n"
        " > ^ <                                                                       |___/   > ^ < \n"
        " /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\ \n"
        "( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )\n"
        " > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ < \n"
        RESET
    );
}


void pintu(){
    printf("                                      ________  \n");
    printf("                                     / ______ \\ \n");
    printf("                                     || _  _ ||  \n");
    printf("                                     ||| || |||  \n");
    printf("                                     |||_||_|||     \n");
    printf("                                     || _  _o|| (o) \n");
    printf("                                     ||| || |||  \n");
    printf("                                     |||_||_|||      ^~^  , \n");
    printf("                                     ||______||     ('Y') ) \n");
    printf("                                    /__________\\    /   \\/ \n");
    printf("                            ________|__________|__ (\\|||/) _________ \n");
    printf("                                   /____________\\ \n");
    printf("                                   |____________| \n");
}

void HelpHeader() {
    printf(CYAN BOLD);
    printf("\n╔══════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                    🏥 HELP MENU 🏥                               ║\n");
    printf("║                                   Rumah Sakit Nimons                             ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════╝\n");
    printf(RESET);
}

void HelpFooter() {
    printf(YELLOW);
    printf("\n╔══════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                   📝 FOOTNOTE 📝                                 ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║ 1. Untuk menggunakan aplikasi, silahkan masukkan nama fungsi yang terdaftar      ║\n");
    printf("║ 2. Jangan lupa untuk memasukkan input yang valid                                 ║\n");
    printf("║ 3. Gunakan command yang sesuai dengan role Anda                                  ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════╝\n");
    printf(RESET);
}

void HelpBelumLogin() {
    HelpHeader();
    
    printf(RED BOLD);
    printf("⚠️  Kamu belum login sebagai role apapun. Silahkan login terlebih dahulu.\n\n");
    printf(RESET);
    
    printf(GREEN "┌────────────────────────────────────────────────────────────────────────┐\n");
    printf("│                        🔐 FITUR YANG TERSEDIA 🔐                       │\n");
    printf("├────────────────────────────────────────────────────────────────────────┤\n");
    printf("│ 1. 🔑 LOGIN        : Masuk ke dalam akun yang sudah terdaftar          │\n");
    printf("│ 2. 📝 REGISTER     : Membuat akun baru sebagai pasien                  │\n");
    printf("│ 3. 🔒 LUPA_PASSWORD: Reset password jika lupa                          │\n");
    printf("│ 4. ❓ HELP         : Menampilkan menu bantuan ini                      │\n");
    printf("│ 5. 🚪 EXIT         : Keluar dari program                               │\n");
    printf("└────────────────────────────────────────────────────────────────────────┘\n");
    printf(RESET);
    
    HelpFooter();
}

void HelpDokter(const char* username) {
    HelpHeader();
    
    printf(GREEN BOLD);
    printf("👨‍⚕️ Halo, Dokter %s! Kamu memanggil command HELP. Kamu pasti sedang kebingungan.\n", username);
    printf("   Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n");
    printf(RESET);
    
    printf(BLUE "┌────────────────────────────────────────────────────────────────────────┐\n");
    printf("│                        👨‍⚕️ FITUR DOKTER 👨‍⚕️                              │\n");
    printf("├────────────────────────────────────────────────────────────────────────┤\n");    
    printf("│ 1. 🚪 LOGOUT        : Keluar dari akun yang sedang digunakan           │\n");
    printf("│ 2. 🏥 LIHAT_DENAH   : Melihat denah rumah sakit                        │\n");
    printf("│ 3. 🏠 LIHAT_RUANGAN : Melihat detail ruangan tertentu                  │\n");
    printf("│ 4. 🩺 DIAGNOSIS     : Melakukan diagnosis penyakit pasien              │\n");
    printf("│ 5. 💊 NGOBATIN      : Memberi obat kepada pasien                       │\n");
    printf("│ 6. ❓ HELP          : Menampilkan menu bantuan ini                     │\n");
    printf("│ 7. 🚪 EXIT          : Keluar dari program                              │\n");
    printf("│ 8. 🧹 CLEAR         : Membersihkan layar terminal                      │\n");
    printf("│ 9. 💰 LIHAT_DOMPET  : Melihat isi dompet Anda                          │\n");
    printf("└────────────────────────────────────────────────────────────────────────┘\n");
    printf(RESET);
    
    HelpFooter();
}

void HelpPasien(const char* username) {
    HelpHeader();
    
    printf(GREEN BOLD);
    printf("🤒 Selamat datang, %s. Kamu memanggil command HELP. Kamu pasti sedang kebingungan.\n", username);
    printf("   Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n");
    printf(RESET);    printf(PINK "┌─────────────────────────────────────────────────────────────────────────┐\n");
    printf("│                        🤒 FITUR PASIEN 🤒                               │\n");
    printf("├─────────────────────────────────────────────────────────────────────────┤\n");    
    printf("│ 1. 🚪 LOGOUT         : Keluar dari akun yang sedang digunakan           │\n");
    printf("│ 2. 🏥 LIHAT_DENAH    : Melihat denah rumah sakit                        │\n");
    printf("│ 3. 🏠 LIHAT_RUANGAN  : Melihat detail ruangan tertentu                  │\n");
    printf("│ 4. 🏠 BOLEH_PULANG   : Konsultasi dengan Dokter terkait kepulangan      │\n");
    printf("│ 5. 📋 DAFTAR_CHECKUP : Mendaftarkan diri untuk pemeriksaan dokter       │\n");
    printf("│ 6. ⏰ ANTREAN_SAYA   : Melihat status antrean                           │\n");
    printf("│ 7. ⏩ SKIP_ANTREAN   : Pindah ke antrean terdepan                       │\n");
    printf("│ 8. ❌ CANCEL_ANTREAN : Batalkan pendaftaran antrean                     │\n");
    printf("│ 9. 💊 MINUM_OBAT     : Meminum obat yang diberikan Dokter               │\n");
    printf("│ 10. 🧪 MINUM_PENAWAR : Mengeluarkan obat terakhir yang diminum          │\n");
    printf("│ 11. ❓ HELP          : Menampilkan menu bantuan ini                     │\n");
    printf("│ 12. 🚪 EXIT          : Keluar dari program                              │\n");
    printf("│ 13. 🧹 CLEAR         : Membersihkan layar terminal                      │\n");
    printf("│ 14. 💰 LIHAT_DOMPET  : Melihat isi dompet Anda                          │\n");
    printf("│ 15. 🎲 GACHA_GAMING  : Bermain gacha untuk mendapatkan hadiah           │\n");
    printf("└─────────────────────────────────────────────────────────────────────────┘\n");
    printf(RESET);
    
    HelpFooter();
}

void HelpManager(const char* username) {
    HelpHeader();
    
    printf(GREEN BOLD);
    printf("👔 Halo Manager %s. Kenapa kamu memanggil command HELP? Kan kamu manager,\n", username);
    printf("   tapi yasudahlah kamu pasti sedang kebingungan.\n");
    printf("   berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n");
    printf(RESET);
    
    printf(YELLOW "┌─────────────────────────────────────────────────────────────────────────┐\n");
    printf("│                        👔 FITUR MANAGER 👔                              │\n");
    printf("├─────────────────────────────────────────────────────────────────────────┤\n");    
    printf("│ 1. 🚪 LOGOUT         : Keluar dari akun yang sedang digunakan           │\n");
    printf("│ 2. 🏥 LIHAT_DENAH    : Melihat denah rumah sakit                        │\n");
    printf("│ 3. 🏠 LIHAT_RUANGAN  : Melihat detail ruangan tertentu                  │\n");    
    printf("│ 4. 👥 LIHAT_USER     : Melihat data seluruh pengguna                    │\n");
    printf("│ 5. 🤒 LIHAT_PASIEN   : Melihat data seluruh pasien                      │\n");
    printf("│ 6. 👨‍⚕️ LIHAT_DOKTER   : Melihat data seluruh dokter                      │\n");
    printf("│ 7. 🔍 CARI_USER      : Mencari data pengguna                            │\n");
    printf("│ 8. 🔍 CARI_PASIEN    : Mencari data pasien                              │\n");
    printf("│ 9. 🔍 CARI_DOKTER    : Mencari data dokter                              │\n");    
    printf("│ 10. 📊 LIHAT_ANTREAN : Melihat rincian seluruh ruangan tidak kosong     │\n");
    printf("│ 11. ➕ TAMBAH_DOKTER : Mendaftarkan dokter baru ke sistem               │\n");    
    printf("│ 12. 🏥 ASSIGN_DOKTER : Menempatkan dokter ke ruangan                    │\n");
    printf("│ 13. ➕ TAMBAH_BARIS  : Menambah baris pada denah rumah sakit            │\n");
    printf("│ 14. ➖ KURANGI_BARIS : Mengurangi baris pada denah rumah sakit          │\n");
    printf("│ 15. ➕ TAMBAH_KOLOM  : Menambah kolom pada denah rumah sakit            │\n");
    printf("│ 16. ➖ KURANGI_KOLOM : Mengurangi kolom pada denah rumah sakit          │\n");
    printf("│ 17. ❓ HELP          : Menampilkan menu bantuan ini                     │\n");
    printf("│ 18. 🚪 EXIT          : Keluar dari program                              │\n");
    printf("│ 19. 💰 LIHAT_KEUANGAN: Melihat kondisi keuangan rumah sakit             │\n");
    printf("└─────────────────────────────────────────────────────────────────────────┘\n");
    printf(RESET);
    
    HelpFooter();
}

void helpInterface(User current_user) {
    if (!isUserValid(current_user)) {
        HelpBelumLogin();
        return;
    }
    
    char role_lower[20];
    strncpy(role_lower, current_user.role, sizeof(role_lower));
    for (int i = 0; role_lower[i]; i++) {
        if (role_lower[i] >= 'A' && role_lower[i] <= 'Z') {
            role_lower[i] = role_lower[i] + ('a' - 'A');
        }
    }

    if (strstr(role_lower, "dokter") != NULL) {
        HelpDokter(current_user.username);
    }
    else if (strstr(role_lower, "pasien") != NULL) {
        HelpPasien(current_user.username);
    }
    else if (strstr(role_lower, "manager") != NULL) {
        HelpManager(current_user.username);
    }
    else {
        printf(RED BOLD "❌ Data tidak ditemukan dalam sistem.\n" RESET);
    }
}
void welcomeManager(const char* username) {
    printf(YELLOW BOLD);
    printf("\n  🏢 SELAMAT PAGI MANAGER %s! 🏢\n", username);
    printf(RESET);
    
    printf(YELLOW);
    printf("┌────────────────────────────────────────────────────────────────────────┐\n");
    printf("│  👔 Selamat datang di Rumah Sakit Nimons                               │\n");
    printf("│  🎯 Anda masuk sebagai Manager dengan kewenangan penuh                 │\n");
    printf("│  📊 Siap mengelola rumah sakit hari ini?                               │\n");
    printf("└────────────────────────────────────────────────────────────────────────┘\n");
    printf(RESET);
    
    printf(GREEN);
    printf("  🌟 Kewenangan Anda:\n");
    printf("  • Mengelola data pengguna\n");
    printf("  • Mengatur dokter dan ruangan\n");
    printf("  • Memantau antrean rumah sakit\n");
    printf("  • Menambah dokter baru ke sistem\n\n");
    printf(RESET);
}

void welcomeDokter(const char* username) {
    printf(BLUE BOLD);
    printf("\n  👨‍⚕️ SELAMAT PAGI DOKTER %s! 👨‍⚕️\n", username);
    printf(RESET);
    
    printf(BLUE);
    printf("┌────────────────────────────────────────────────────────────────────────┐\n");
    printf("│  🩺 Selamat datang di Rumah Sakit Nimons                               │\n");
    printf("│  💼 Anda masuk sebagai Dokter yang siap melayani                       │\n");
    printf("│  🏥 Siap membantu pasien hari ini?                                     │\n");
    printf("└────────────────────────────────────────────────────────────────────────┘\n");
    printf(RESET);
    
    printf(GREEN);
    printf("  🌟 Tugas Anda:\n");
    printf("  • Melakukan diagnosis pasien\n");
    printf("  • Memberikan obat yang tepat\n");
    printf("  • Membantu proses penyembuhan\n");
    printf("  • Menjaga kesehatan masyarakat\n\n");
    printf(RESET);
}

void welcomePasien(const char* username) {
    printf(PINK BOLD);
    printf("\n  🤒 SELAMAT PAGI %s! 🤒\n", username);
    printf(RESET);
    
    printf(PINK);
    printf("┌────────────────────────────────────────────────────────────────────────┐\n");
    printf("│  🏥 Selamat datang di Rumah Sakit Nimons                               │\n");
    printf("│  💊 Anda masuk sebagai Pasien                                          │\n");
    printf("│  ❤️  Ada keluhan apa hari ini?                                         │\n");
    printf("└────────────────────────────────────────────────────────────────────────┘\n");
    printf(RESET);
    
    printf(GREEN);
    printf("  🌟 Layanan untuk Anda:\n");
    printf("  • Konsultasi dengan dokter\n");
    printf("  • Pemeriksaan kesehatan\n");
    printf("  • Mendapatkan obat yang tepat\n");
    printf("  • Layanan kesehatan terbaik\n\n");
    printf(RESET);
}

void welcomeLoginInterface(User user) {
    printf(CYAN BOLD);
    printf("\n╔══════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                              🎉 LOGIN BERHASIL! 🎉                               ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════╝\n");
    printf(RESET);
    
    // Tampilkan sambutan sesuai role
    if (strcmp(user.role, "manager") == 0) {
        welcomeManager(user.username);
    } 
    else if (strcmp(user.role, "dokter") == 0) {
        welcomeDokter(user.username);
    } 
    else if (strcmp(user.role, "pasien") == 0) {
        welcomePasien(user.username);
    }
    
    printf(CYAN);
    printf("╔══════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                        Ketik 'HELP' untuk melihat menu                           ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════╝\n");
    printf(RESET);
}


void loginHeaderInterface() {
    printf(CYAN BOLD);
    printf("\n╔══════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                 🔐 LOGIN SISTEM 🔐                               ║\n");
    printf("║                                Rumah Sakit Nimons                                ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════╝\n");
    printf(RESET);
}

void registerHeaderInterface() {
    printf(GREEN BOLD);
    printf("\n╔══════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                               📝 REGISTER PASIEN 📝                              ║\n");
    printf("║                                Rumah Sakit Nimons                                ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════╝\n");
    printf(RESET);
}

void lupaPasswordHeaderInterface() {
    printf(YELLOW BOLD);
    printf("\n╔══════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                              🔒 LUPA PASSWORD 🔒                                 ║\n");
    printf("║                                Rumah Sakit Nimons                                ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════╝\n");
    printf(RESET);
}

void logoutHeaderInterface() {
    printf(RED BOLD);
    printf("\n╔══════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                 🚪 LOGOUT SISTEM 🚪                              ║\n");
    printf("║                            Sampai jumpa lagi di Nimons!                          ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════╝\n");
    printf(RESET);
}

void lihatDenahHeaderInterface() {
    printf(BLUE BOLD);
    printf("\n╔══════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                               🏥 DENAH RUMAH SAKIT 🏥                            ║\n");
    printf("║                           Peta Ruangan Rumah Sakit Nimons                        ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════╝\n");
    printf(RESET);
}

void lihatRuanganHeaderInterface() {
    printf(CYAN BOLD);
    printf("\n╔══════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                              🏠 LIHAT RUANGAN 🏠                                 ║\n");
    printf("║                         Detail Informasi Ruangan Spesifik                        ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════╝\n");
    printf(RESET);
}

void lihatUserHeaderInterface() {
    printf(GREEN BOLD);
    printf("\n╔══════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                               👥 DAFTAR PENGGUNA 👥                              ║\n");
    printf("║                          Data Semua Pengguna Sistem Nimons                       ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════╝\n");
    printf(RESET);
}

void cariUserHeaderInterface() {
    printf(YELLOW BOLD);
    printf("\n╔══════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                               🔍 CARI PENGGUNA 🔍                                ║\n");
    printf("║                           Pencarian Data Pengguna Sistem                         ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════╝\n");
    printf(RESET);
}

void lihatAntreanHeaderInterface() {
    printf(PINK BOLD);
    printf("\n╔══════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                              📊 LIHAT ANTREAN 📊                                 ║\n");
    printf("║                        Status Antrean Seluruh Ruangan Aktif                      ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════╝\n");
    printf(RESET);
}

void tambahDokterHeaderInterface() {
    printf(BLUE BOLD);
    printf("\n╔══════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                              ➕ TAMBAH DOKTER ➕                                  ║\n");
    printf("║                         Pendaftaran Dokter Baru ke Sistem                        ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════╝\n");
    printf(RESET);
}

void assignDokterHeaderInterface() {
    printf(CYAN BOLD);
    printf("\n╔══════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                              🏥 ASSIGN DOKTER 🏥                                 ║\n");
    printf("║                          Penempatan Dokter ke Ruangan                            ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════╝\n");
    printf(RESET);
}

void diagnosisHeaderInterface() {
    printf(GREEN BOLD);
    printf("\n╔══════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                               🩺 DIAGNOSIS PASIEN 🩺                             ║\n");
    printf("║                           Pemeriksaan dan Diagnosis Medis                        ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════╝\n");
    printf(RESET);
}

void ngobatinHeaderInterface() {
    printf(PINK BOLD);
    printf("\n╔══════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                               💊 PEMBERIAN OBAT 💊                               ║\n");
    printf("║                           Resep dan Distribusi Obat Pasien                       ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════╝\n");
    printf(RESET);
}

void daftarCheckupHeaderInterface() {
    printf(YELLOW BOLD);
    printf("\n╔══════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                              📋 DAFTAR CHECKUP 📋                                ║\n");
    printf("║                           Pendaftaran Pemeriksaan Kesehatan                      ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════╝\n");
    printf(RESET);
}

void antreanSayaHeaderInterface() {
    printf(BLUE BOLD);
    printf("\n╔══════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                              ⏰ ANTREAN SAYA ⏰                                   ║\n");
    printf("║                             Status Antrean Pemeriksaan                           ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════╝\n");
    printf(RESET);
}

void minumObatHeaderInterface() {
    printf(GREEN BOLD);
    printf("\n╔══════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                               💊 MINUM OBAT 💊                                   ║\n");
    printf("║                            Konsumsi Obat dari Inventory                          ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════╝\n");
    printf(RESET);
}

void minumPenawarHeaderInterface() {
    printf(CYAN BOLD);
    printf("\n╔══════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                              🧪 MINUM PENAWAR 🧪                                 ║\n");
    printf("║                           Mengeluarkan Obat Terakhir Diminum                     ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════╝\n");
    printf(RESET);
}

void statusAntreanHeaderInterface() {
    printf(PINK BOLD);
    printf("\n╔══════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                              📋 STATUS ANTREAN 📋                                ║\n");
    printf("║                             Informasi Posisi dalam Antrean                       ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════╝\n");
    printf(RESET);
}

void bolehPulangHeaderInterface() {
    printf(YELLOW BOLD);
    printf("\n╔══════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                              🏠 BOLEH PULANG 🏠                                  ║\n");
    printf("║                           Konsultasi Kepulangan dengan Dokter                    ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════╝\n");
    printf(RESET);
}

void cariPasienHeaderInterface() {
    printf(RED BOLD);
    printf("\n╔══════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                               🔍 CARI PASIEN 🔍                                  ║\n");
    printf("║                            Pencarian Data Pasien Spesifik                        ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════╝\n");
    printf(RESET);
}

void cariDokterHeaderInterface() {
    printf(BLUE BOLD);
    printf("\n╔══════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                               🔍 CARI DOKTER 🔍                                  ║\n");
    printf("║                            Pencarian Data Dokter Spesifik                        ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════╝\n");
    printf(RESET);
}

void exitHeaderInterface() {
    printf(RED BOLD);
    printf("\n╔══════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                 🚪 EXIT SISTEM 🚪                                ║\n");
    printf("║                           Terima kasih telah menggunakan                         ║\n");
    printf("║                              Sistem Rumah Sakit Nimons!                          ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════╝\n");
    printf(RESET);
}

void matiInterface(const char* username) {
    printf("\n");
    printf(YELLOW);
    printf("              ┌─────────────────────────────────────────────────────┐\n");
    printf("              │  💀 ACHIEVEMENT UNLOCKED: ULTIMATE NOOB 💀          │\n");
    printf("              │  🏆 CONGRATULATIONS ON BEING CRINGE! 🏆             │\n");
    printf("              │  📉 LIFE SPEEDRUN ANY%% (FAILED) 📉                  │\n");
    printf("              │  🤡 HOSPITAL EMPLOYEE OF THE MONTH: NONE 🤡         │\n");
    printf("              │  💊 MEDICINE COMPREHENSION: 0/100 💊                │\n");
    printf("              │  🧠 BRAIN CELLS REMAINING: 404 NOT FOUND 🧠         │\n");
    printf("              └─────────────────────────────────────────────────────┘\n");
    printf("\n");
    printf(RED);
    printf("                  🤡 COULDN'T FOLLOW SIMPLE DOCTOR INSTRUCTIONS 🤡\n");
    printf("                      🚨 EMERGENCY BRAINROT DETECTED 🚨\n");
    printf("                    💀 PATIENT HAS BEEN SENT TO SHADOW REALM 💀\n");
    printf("                      🎮 RESPAWN DISABLED - GIT GUD 🎮\n");
    printf("\n");
    printf(RESET);
}

void skipAntreanHeaderInterface() {
    printf(MAGENTA BOLD);
    printf("\n╔══════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                              ⏩ SKIP ANTREAN ⏩                                  ║\n");
    printf("║                         Pindah ke Antrean Terdepan                               ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════╝\n");
    printf(RESET);
}

void cancelAntreanHeaderInterface() {
    printf(RED BOLD);
    printf("\n╔══════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                              ❌ CANCEL ANTREAN ❌                                 ║\n");
    printf("║                         Batalkan Pendaftaran Antrean                              ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════════════════╝\n");
    printf(RESET);
}

void lihatKeuanganHeaderInterface() {
    printf(GREEN BOLD);
    printf("\n╔══════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                              💰 LIHAT KEUANGAN 💰                                ║\n");
    printf("║                          Kondisi Keuangan Rumah Sakit Nimons                     ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════╝\n");
    printf(RESET);
}

void lihatDompetHeaderInterface() {
    printf(YELLOW BOLD);
    printf("\n╔══════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                               💰 LIHAT DOMPET 💰                                 ║\n");
    printf("║                            Informasi Saldo dan Isi Dompet                        ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════╝\n");
    printf(RESET);
}

void gachaGamingHeaderInterface() {
    printf(PINK BOLD);
    printf("\n╔══════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                               🎲 GACHA GAMING 🎲                                 ║\n");
    printf("║                           Bermain Gacha untuk Mendapatkan Hadiah                 ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════╝\n");
    printf(RESET);
}