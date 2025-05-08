#ifndef ADTQUEUE_H
#define ADTQUEUE_H

#include "adt-user.h"
#include "boolean.h"

typedef struct queue* Address;
typedef struct queue {
    User pasien;
    Address next;
} Queue;

/* Menginisialisasi Queue kosong yang sudah dideklarasikan */
Queue* createQueue();

/* Mendealokasikan Queue */
void destroyQueue(Queue* q);

/* Jika tidak ada antrean, mengembalikan true, else false*/
boolean isEmpty(Queue q);

int queueLength(Queue q);

/* Menambah elemen ke dalam antrean (paling belakang) */
void enqueue(Queue *q, User x);

/* Mengembalikan elemen paling depan */
User dequeue(Queue **q);

#endif