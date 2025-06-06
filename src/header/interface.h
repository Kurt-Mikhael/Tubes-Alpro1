#include <stdio.h>
#include "global.h"

//Fungsi yang menampilkan pesan selamat datang
void SelamatDatang();
void pintu();

// Fungsi help dengan tampilan yang menarik

void HelpHeader();
void HelpFooter();
void HelpBelumLogin();
void HelpDokter(const char* username);
void HelpPasien(const char* username);
void HelpManager(const char* username);
void helpInterface(User current_user);

// Fungsi welcome interface untuk login

void welcomeLoginInterface(User user);
void welcomeManager(const char* username);
void welcomeDokter(const char* username);
void welcomePasien(const char* username);

// Header interface untuk berbagai fitur

void loginHeaderInterface();
void registerHeaderInterface();
void lupaPasswordHeaderInterface();
void logoutHeaderInterface();
void lihatDenahHeaderInterface();
void lihatRuanganHeaderInterface();
void lihatUserHeaderInterface();
void cariUserHeaderInterface();
void lihatAntreanHeaderInterface();
void tambahDokterHeaderInterface();
void assignDokterHeaderInterface();
void diagnosisHeaderInterface();
void ngobatinHeaderInterface();
void daftarCheckupHeaderInterface();
void antreanSayaHeaderInterface();
void minumObatHeaderInterface();
void minumPenawarHeaderInterface();
void statusAntreanHeaderInterface();
void skipAntreanHeaderInterface();
void bolehPulangHeaderInterface();
void cariPasienHeaderInterface();
void cariDokterHeaderInterface();
void exitHeaderInterface();
void matiInterface(const char* username);
void cancelAntreanHeaderInterface();
void lihatKeuanganHeaderInterface() ;
void lihatDompetHeaderInterface();
void gachaGamingHeaderInterface();

// Pembersih terminal untuk transisi
void clear();