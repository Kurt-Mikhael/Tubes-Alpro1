#ifndef ADTSET_H
#define ADTSET_H

#include "adt-user.h"

typedef struct
{
    char user_name[50];
} UsernameSet;


/*Memeriksa apakah username kosong*/
boolean isUsernameSetEmpty(UsernameSet u_s);

/*Memeriksa apakah username sudah terisi sebelumya*/
boolean isUsernameSetValid(UsernameSet u_s);


/*Menerima input username dan mengisi UsernameSet dengan username tersebut*/
void createUsernameSet(UsernameSet* u_s);



#endif