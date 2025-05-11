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
void destroyQueue(Queue* antrean);

/* Jika tidak ada antrean, mengembalikan true, else false*/
boolean isQueueEmpty(Queue antrean);

int queueLength(Queue antrean);

/* Menambah elemen ke dalam antrean (paling belakang) */
void enqueue(Queue *antrean, User pasien);

/* Mengembalikan elemen paling depan */
User dequeue(Queue **antrean);

/* Mengembalikan urutan User dalam Queue (HEAD = 0)*/
int findInQueue(Queue antrean, User pasien);

#endif