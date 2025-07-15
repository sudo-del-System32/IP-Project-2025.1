//
// Created by franc on 09/07/2025.
//

#include "Func_gerais.h"
#include "uf1.h"
#include <stdio.h>
#include <stdlib.h>



void uf_array_expander(uf **uf_array, int *uf_size)
{
    (*uf_size)++;

    *uf_array = (uf *) realloc (*uf_array, sizeof(*uf_array) + sizeof(uf));
    if (*uf_array == NULL)
    {
        printf("\nError uf_array_expander\n");
        exit (-1);
    }

    //Por algum motivo uf_array[*uf_size-1]->status = 0; != do abaixo, teria que ser (*uf_array)[*uf_size-1].status = 0;
    //ja que anterior seria igual a *(uf_array + valor)
    //(*uf_array + (*uf_size - 1))->status = 0;
    (*uf_array)[*uf_size-1].status = 0;
}



// Fazer funçao para liberar todos os tipos

void uf_file_to_array(uf *uf_array, const int *uf_size)
{

    FILE *f = ptr_file("uf1.bin");
    fseek(f,0,SEEK_SET);
    fread(uf_array,sizeof(uf),*uf_size,f);
    fclose(f);

}



void uf_array_to_file(uf *uf_array, const int *uf_size)
{
    FILE *f = ptr_file("uf1.bin");
    for (int i = 0; i < *uf_size; i++)
    {
        if (uf_array[i].status == -1)
        {
            uf_array[i].status = 1;
            fseek(f,sizeof(uf)*i,SEEK_SET);
            fwrite(&uf_array[i],sizeof(uf),1,f);
            clean(f);
        }
        if (uf_array[i].status == 0)
        {
            fseek(f,sizeof(uf)*i,SEEK_SET);
            fwrite(&uf_array[i],sizeof(uf),1,f);
            clean(f);
        }
    }
    fclose(f);
}

//ate aqui


int uf_array_empty_space_finder(const uf *uf_array, const int *uf_size)
{
    //printf("uf_size == %d\n",*uf_size);
    for (int i = (*uf_size)-1; i > -1; i--)
    {

        if (uf_array[i].status == 0)
        {
            return i;
        }
    }
    return -1;
}


void uf_create(uf **uf_array, int *uf_size)
{

    int i = uf_array_empty_space_finder(*uf_array ,uf_size);
    if (i == -1)
    {
        uf_array_expander(uf_array ,uf_size);
        i = uf_array_empty_space_finder(*uf_array ,uf_size);
        if (i == -1)
        {
            printf("Error uf_create");
            exit(-1);
        }
    }

    input_int(&(*uf_array)[i].code,4,"codigo","UF");
    input_char((*uf_array)[i].description, 30, "nome", "UF");
    input_char((*uf_array)[i].acronym, 5, "sigla", "UF");
    (*uf_array)[i].status = -1;
}

void uf_read(uf *uf_array, const int i)
{
    printf("DEBUG: STATUS == %d\n\n", uf_array[i].status);

    printf("Codigo do UF: %d\n\n", uf_array[i].code);

    printf("Descricao do UF: %s\n\n", uf_array[i].description);

    printf("Sigla do UF: %s\n\n", uf_array[i].acronym);

}

void uf_read_all(uf *uf_array, const int *uf_size)
{
    printf("--------------------------------------\n");

    for (int i = 0; i < *uf_size; i++)
    {
        uf_read(uf_array, i);
    }

    printf("--------------------------------------");
}