#include "..\header\adt-queue.h"
#include <stdio.h>
#include <stdlib.h>

/* Menginisialisasi Queue kosong yang sudah dideklarasikan */
Queue* createQueue() {
    Queue* antrean = (Queue*) malloc(sizeof(Queue));
    antrean->next = NULL;
    createUser(&(antrean->pasien));
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
boolean isEmpty(Queue antrean) {
    if (!isUserValid(antrean.pasien) && antrean.next == NULL) return 1;
    else return 0;
}

int queueLength(Queue antrean) {
    if (isEmpty(antrean)) return 0;
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
    if (isEmpty(*antrean)) antrean->pasien = pasien;
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
    if (isEmpty(**antrean)) {
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

int findInQueue(Queue antrean, User pasien) {
    if (isEmpty(antrean)) return -1;
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