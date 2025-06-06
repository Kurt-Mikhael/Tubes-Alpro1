#include "../header/adt-obat.h"
#include "../header/global.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/boolean.h"

// Fungsi untuk membuat obat baru
void createObat(Obat* new_obat){
    new_obat->obat_id = 0;
    strcpy(new_obat->nama_obat, "");
}

// Fungsi untuk memeriksa apakah obat valid
int isObatValid(Obat obat){
    if((obat.obat_id != 0 && strcmp(obat.nama_obat, "") != 0)) return TRUE;
    else return FALSE;
}


// Fungsi untuk membuat list obat
void createListObat(ListObat* list_obat){
    for (int i = 0; i < MAX_OBAT; i++) {
        createObat(&list_obat->data[i]);
    }
    list_obat->jumlah = 0;
}

// Fungsi untuk memeriksa apakah list obat kosong
int isEmptyObat(ListObat list_obat){
    return (list_obat.jumlah == 0);
}

// Fungsi untuk memeriksa apakah list obat sudah penuh
int isFullObat(ListObat l){
    return (l.jumlah == MAX_OBAT);
}

// Fungsi untuk menambahkan obat ke list
void insertLastObat(ListObat* list_obat, Obat obat){
    if(!isFullObat(*list_obat)){
        list_obat->data[list_obat->jumlah] = obat;
        list_obat->jumlah++;
    }
    else{
        printf("List Obat Penuh\n");
    }
}

// Fungsi untuk menambahkan obat ke inventory sesuai urutan resep
void insertObatSesuaiResep(ListObat* inventory, Obat obat, ListObat resep) {
    if (isFullObat(*inventory)) {
        printf("List Obat Penuh\n");
        return;
    }
    if(isEmptyObat(*inventory)) {
        // Jika resep kosong, tambahkan ke akhir inventory
        insertLastObat(inventory, obat);
        
        return;
    }
    // Cari posisi yang tepat berdasarkan urutan resep
    int idxTujuan = -1;
    for (int i = 0; i < resep.jumlah; i++) {
        if (resep.data[i].obat_id == obat.obat_id) {
            idxTujuan = i;
            break;
        }
    }
    
    
    // Cari posisi yang tepat dalam inventory berdasarkan urutan resep
    int idxInsert = inventory->jumlah; 
    
    for (int i = 0; i < inventory->jumlah; i++) {
        // Cari posisi obat ini dalam resep
        int idxObatX = -1;
        for (int j = 0; j < resep.jumlah; j++) {
            if (resep.data[j].obat_id == inventory->data[i].obat_id) {
                idxObatX = j;
                break;
            }
        }
        
        // Jika obat yang akan diinsert seharusnya sebelum obat ini
        if (idxObatX != -1 && idxTujuan < idxObatX) {
            idxInsert = i;
            break;
        }
    }
    
    // Geser semua obat setelah posisi yang ditemukan
    for (int i = inventory->jumlah; i > idxInsert; i--) {
        inventory->data[i] = inventory->data[i-1];
    }
    
    // Insert obat pada posisi yang tepat
    inventory->data[idxInsert] = obat;
    inventory->jumlah++;
}

// Fungsi untuk menghapus obat terakhir dari list
void deleteLastObat(ListObat* list_obat, Obat* deleted_obat){
    if(!isEmptyObat(*list_obat)){
        *deleted_obat = list_obat->data[list_obat->jumlah - 1];
        list_obat->jumlah--;
    }
    else{
        printf("List Obat Kosong\n");
    }
}

// Fungsi untuk menghapus obat berdasarkan ID
int lengthListObat(ListObat list_obat){
    return list_obat.jumlah;
}

Obat getObatByID(ListObat list_obat, int id){
    for(int i=0;i<lengthListObat(list_obat);i++){
        if(list_obat.data[i].obat_id == id){
            return list_obat.data[i];
        }
    }
    // Default return jika tidak ditemukan (Untuk debugging)
    Obat obat_kosong;
    createObat(&obat_kosong);
    obat_kosong.obat_id = id;
    return obat_kosong;
}

// Fungsi untuk mencetak isi list obat
void printListObat(ListObat s){
    printf("Isi List (atas -> bawah):\n");
    for (int i = 0; i <s.jumlah; i++) {
        printf(" (ID: %d) %s\n", s.data[i].obat_id, s.data[i].nama_obat);
    }
}

