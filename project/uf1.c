//
// Created by franc on 09/07/2025.
//

#include "Func_gerais.h"
#include "uf1.h"
#include <stdio.h>
#include <stdlib.h>





void uf_array_fuller(uf *uf_array, const int *uf_size)
{
    for (int i = 0; i < *uf_size; i++)
        uf_array->status = 1;
}



void uf_array_expander(uf **uf_array, const int *uf_size)
{
    *uf_array = (uf *) realloc (*uf_array, sizeof(uf)*(*uf_size+1));
    if (*uf_array == NULL)
    {
        printf("Error uf_array_expander");
        exit (-1);
    }
    *uf_size++;
    uf_array[*uf_size-1]->status = 0;
}



// Fazer funçao para liberar todos os tipos

void uf_file_to_array(uf *uf_array, const int *uf_size)
{

    FILE *f = ptr_file("uf1.bin");
    fseek(f,sizeof(uf)*(*uf_size),SEEK_SET);
    fread(uf_array,sizeof(uf),*uf_size,f);
    uf_array_fuller(uf_array ,uf_size);
    fclose(f);

}



void uf_array_to_file(const uf *uf_array, const int *uf_size)
{
    FILE *f = ptr_file("uf1.bin");
    for (int i = 0; i < *uf_size; i++)
    {
        if (uf_array[i].status == -1)
        {
            fseek(f,sizeof(uf)*i,SEEK_SET);
            fwrite(&uf_array[i],sizeof(uf),1,f);
            fflush(f);
        }
    }
    fclose(f);
}

//ate aqui


int uf_array_empty_space_finder(const uf *uf_array, const int *uf_size)
{
    for (int i = *uf_size-1; i >= 0; i--)
    {
        if (uf_array[i].status == 0)
            return i;
    }

    return -1;
}


void uf_create(uf *uf_array, const int *uf_size)
{
    int i = uf_array_empty_space_finder(uf_array ,uf_size);
    if (i == -1)
    {
        uf_array_expander(&uf_array ,uf_size);
        i = uf_array_empty_space_finder(uf_array ,uf_size);

        if (i == -1)
        {
            printf("Error uf_create");
            exit(-1);
        }
    }

    input_int(&uf_array[i].code,4,"codigo","UF");
    input_char(uf_array[i].description, 30, "nome", "UF");
    input_char(uf_array[i].acronym, 5, "sigla", "UF");
    uf_array[i].status = -1;
}

void uf_read(uf *uf_array, const int i)
{

    printf("Codigo do UF: %d\n\n", uf_array[i].code);

    printf("Descrição do UF: %s\n\n", uf_array[i].description);

    printf("Sigla do UF: %s\n\n", uf_array[i].acronym);

}

void uf_read_all(uf *uf_array, const int *uf_size)
{
    printf("--------------------------------------");

    for (int i = 0; i < *uf_size; i++)
    {
        uf_read(uf_array, i);
    }

    printf("--------------------------------------");
}