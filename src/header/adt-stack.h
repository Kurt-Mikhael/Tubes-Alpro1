#ifndef ADTSTACK_H
#define ADTSTACK_H

#include "adt-obat.h"
#include "boolean.h"

typedef struct
{
    /* data */
} StackObat;

void createStackObat(StackObat* s_o);

void destroyStackObat(StackObat* s_o);

boolean isStackEmpty(StackObat s_o);

int stackLength(StackObat s_o);

Obat getTopStack(StackObat s_o);

void pushStack(StackObat* s_o, Obat o);

Obat popStack(StackObat* s_o);

#endif