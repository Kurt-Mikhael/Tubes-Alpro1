#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char line[256];
    int angka = 135;
    sprintf(line,"%d", angka);
    char nama[256];
    strcpy(nama, line);
    for (int i = 0; i < strlen(nama); i++) {
        printf("%c", nama[i]);
    }
    
}