#include "..\header\adt-queue.h"
#include <stdio.h>

/* Menginisialisasi Queue kosong yang sudah dideklarasikan */
Queue* createQueue() {
    Queue* q = (Queue*) malloc(sizeof(Queue));
    q->next = NULL;
    createUser(&(q->pasien));
}

/* Mendealokasikan Queue */
void destroyQueue(Queue* q) {
    while ((*q).next != NULL) {
        Address prev = q;
        Address temp = ((*q).next);
        while ((*temp).next != NULL) {
            prev = temp;
            temp = (*temp).next;
        }
        prev->next = NULL;
        free(temp);
    }
    free(q);
}

/* Jika tidak ada antrean, mengembalikan true, else false*/
boolean isEmpty(Queue q) {
    if (!isUserValid(q.pasien) && q.next == NULL) return 1;
    else return 0;
}

int queueLength(Queue q) {
    if (isEmpty(q)) return 0;
    else {
        int length = 1;
        while (q.next != NULL) {
            q = *(q.next);
            length++;
        }
        return length;
    }
}

/* Menambah elemen ke dalam antrean (paling belakang) */
void enqueue(Queue *q, User x) {
    if (isEmpty(*q)) q->pasien = x;
    else {
        Address newNode = (Address) malloc(sizeof(Queue));
        newNode->next = NULL;
        newNode->pasien = x;
        Address temp = q;
        while ((*temp).next != NULL) {
            temp = (*temp).next;
        }
        temp->next = newNode;
    }
}

/* Mengembalikan elemen paling depan */
User dequeue(Queue **q) {
    User val;
    if (isEmpty(**q)) {
        createUser(&val);
    } else if ((**q).next == NULL) {
        val = (**q).pasien;
        createUser(&((*q)->pasien));
    } else {
        Address temp = (**q).next;
        val = (**q).pasien;
        Queue* t = *q;
        *q = temp;
        free(t);
    }
    return val;
}