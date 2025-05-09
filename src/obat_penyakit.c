#include <stdio.h>
#include <stdlib.h>
#include "obat_penyakit.h"


obatpenyakit* load_obat_penyakit(const char *namafile, int *count){
    FILE* file = fopen(namafile, "r");
    if(!file){
        printf("file tidak dapat dibuka");
        return NULL;

    }
    *count = 0;
    char buffer[64];
    fgets(buffer, sizeof(buffer), file);

    while (fgets(buffer, sizeof(buffer), file))
    {
        (*count)++;
    }
    rewind (file);
    obatpenyakit* data =  (obatpenyakit*)malloc((*count) * sizeof(obatpenyakit));

    fgets(buffer, sizeof(buffer), file);

    int idx = 0;
    while (fgets(buffer, sizeof(buffer), file))
    {
        int nilai = 0;
        int cols = 0;
        int i = 0;
        while (buffer[i] != '\0')
        {
            if(buffer[i] >= '0' && buffer[i] <= '9'){
                nilai = nilai * 10 + (buffer[i] - '0');
                i++;
            }
            else if(buffer[i] == ',' || buffer[i] == '\n'){
                
                if(cols == 0){
                    data[idx].obat_id = nilai;
                }
                else if(cols == 1){
                    data[idx].penyakit_id = nilai;
                }
                else if(cols == 2){
                    data[idx].urutan_minum = nilai;
                }
                i++;
                nilai = 0;
                cols++;
            }
        }
        idx++;
    }

    fclose(file);
    return data;
    
}

void freeObatPenyakit(obatpenyakit* data) {
    free(data);
}