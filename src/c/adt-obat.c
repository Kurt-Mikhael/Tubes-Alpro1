#include "..\header\adt-obat.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "..\header\boolean.h"

void createObat(Obat* new_obat){
    new_obat->obat_id = 0;
    strcpy(new_obat->nama_obat, "");
}

int isObatValid(Obat obat){
    if((obat.obat_id != 0 && strcmp(obat.nama_obat, "") != 0)) return TRUE;
    else return FALSE;
}


void createListObat(ListObat* list_obat){
    for (int i = 0; i < MAX_OBAT; i++) {
        createObat(&list_obat->data[i]);
    }
    list_obat->jumlah = 0;
}

int isEmptyObat(ListObat list_obat){
    return (list_obat.jumlah == 0);
}

int isFullObat(ListObat l){
    return (l.jumlah == MAX_OBAT);
}

void insertLastObat(ListObat* list_obat, Obat obat){
    if(!isFullObat(*list_obat)){
        list_obat->data[list_obat->jumlah] = obat;
        list_obat->jumlah++;
    }
    else{
        printf("List Obat Penuh\n");
    }
}

void deleteLastObat(ListObat* list_obat, Obat* deleted_obat){
    if(!isEmptyObat(*list_obat)){
        *deleted_obat = list_obat->data[list_obat->jumlah - 1];
        list_obat->jumlah--;
    }
    else{
        printf("List Obat Kosong\n");
    }
}

int lengthListObat(ListObat list_obat){
    return list_obat.jumlah;
}

Obat getObatByID(ListObat list_obat, int id){
    boolean obat_found = FALSE;
    for(int i=0;i<lengthListObat(list_obat);i++){
        if(list_obat.data[i].obat_id == id){
            obat_found = TRUE;
            return list_obat.data[i];
        }
    }
    if(!obat_found){
        Obat obat_kosong;
        createObat(&obat_kosong);
        return obat_kosong;
    }
}


