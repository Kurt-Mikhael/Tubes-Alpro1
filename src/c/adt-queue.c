#include "../header/adt-queue.h"
#include <stdio.h>
#include <stdlib.h>
#include "../header/global.h"
/* Menginisialisasi Queue kosong yang sudah dideklarasikan */
Queue* createQueue() {
    Queue* antrean = (Queue*) malloc(sizeof(Queue));
    antrean->next = NULL;
    createUser(&(antrean->pasien));
    return antrean;
}

/* Mendealokasikan Queue */
void destroyQueue(Queue* antrean) {
    while ((*antrean).next != NULL) {
        Address prev = antrean;
        Address temp = ((*antrean).next);
        while ((*temp).next != NULL) {
            prev = temp;
            temp = (*temp).next;
        }
        prev->next = NULL;
        free(temp);
    }
    free(antrean);
}

/* Jika tidak ada antrean, mengembalikan true, else false*/
boolean isQueueEmpty(Queue antrean) {
    if (!isUserValid(antrean.pasien) && antrean.next == NULL) return 1;
    else return 0;
}

/* Mengembalikan panjang antrean */
int queueLength(Queue antrean) {
    if (isQueueEmpty(antrean)) return 0;
    else {
        int length = 1;
        while (antrean.next != NULL) {
            antrean = *(antrean.next);
            length++;
        }
        return length;
    }
}

/* Menambah elemen ke dalam antrean (paling belakang) */
void enqueue(Queue *antrean, User pasien) {
    if (isQueueEmpty(*antrean)) antrean->pasien = pasien;
    else {
        Address newNode = (Address) malloc(sizeof(Queue));
        newNode->next = NULL;
        newNode->pasien = pasien;
        Address temp = antrean;
        while ((*temp).next != NULL) {
            temp = (*temp).next;
        }
        temp->next = newNode;
    }
}

/* Mengembalikan elemen paling depan */
User dequeue(Queue **antrean) {
    User val;
    if (isQueueEmpty(**antrean)) {
        createUser(&val);
    } else if ((**antrean).next == NULL) {
        val = (**antrean).pasien;
        createUser(&((*antrean)->pasien));
    } else {
        Address temp = (**antrean).next;
        val = (**antrean).pasien;
        Queue* t = *antrean;
        *antrean = temp;
        free(t);
    }
    return val;
}

/* Menghapus elemen dari antrean */
int findInQueue(Queue antrean, User pasien) {
    if (isQueueEmpty(antrean)) return -1;
    else {
        int index = 0;
        while (!isSameUser(antrean.pasien, pasien) && antrean.next != NULL) {
            antrean = *(antrean.next);
            index++;
        }
        if (isSameUser(antrean.pasien, pasien)) return index;
        else return -1;
    }
}

/* Mengembalikan address elemen paling depan */
User* getQueueHead(Queue *antrean) {    return &(antrean->pasien);
}