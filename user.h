#ifndef USER_H
#define USER_H

#define MAX_USERS 100
#define MAX_FIELD_LEN 100
#define MAX_LINE_LEN 1024

typedef struct {
    int id;
    char username[50];
    char password[50];
    char role[20];
    char riwayat_penyakit[50];
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
} User;

int load_users(const char *filename, User users[], int max_users);
void menu_login(User users[], int user_count);
void display_user_info(User user);
int username_exists(User users[], int user_count, const char *username);
void register_pasien(User users[], int *user_count, int max_users);


#endif