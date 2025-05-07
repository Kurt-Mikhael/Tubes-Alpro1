#ifndef ADTLIST_H
#define ADTLIST_H

#include "adt-user.h"
#include "adt-obat.h"
#include "adt-penyakit.h"

/* ADT List elemen User*/

typedef struct 
{
    /* data */
} ListUser;

void createListUser(ListUser* l);

void insertUserLast(ListUser* l, User u);
// dan primitif lain

/* ADT List elemen Obat*/

typedef struct 
{
    /* data */
} ListObat;


/* ADT List elemen Penyakit*/

typedef struct
{
    /* data */
} ListPenyakit;

#endif