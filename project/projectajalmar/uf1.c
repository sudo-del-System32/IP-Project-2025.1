//
// Created by franc on 09/07/2025.
//

#include "uf1.h"
#include "Func_gerais.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void uf_start(uf **uf_array, int *uf_size)
{
    *uf_size = file_size("uf1.bin", sizeof(uf));
    *uf_array = (uf *)malloc(*uf_size * sizeof(uf));
    uf_file_to_array(*uf_array, uf_size);
}



void uf_array_expander(uf **uf_array, int *uf_size)
{
    (*uf_size)++;

    *uf_array = (uf *) realloc (*uf_array, *uf_size * sizeof(uf));
    if (*uf_array == NULL)
    {
        printf("\nError uf_array_expander\n");
        exit (-1);
    }

    #ifdef debug
    printf("\n\nExpanded UF_SIZE: %d\n\n",*uf_size);
    printf("\n\nExpanded *uf_size * sizeof(uf): %llu\n\n",*uf_size * sizeof(uf));
    #endif

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
#ifdef debug
    printf("\n\nUF_SIZE: %d\n\n",*uf_size);
    printf("\n\n*uf_size * sizeof(uf): %llu\n\n",*uf_size * sizeof(uf));
#endif
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

    //uf_uptade
    uf_update(uf_array, uf_size, i);
}


void uf_read(uf *uf_array, const int i)
{
    if (uf_array[i].status == 0)
        return ;

    printf("--------------------------------------\n");

    #ifdef debug
    printf("DEBUG: STATUS == %d\n\n", uf_array[i].status);
    #endif

    printf("Codigo do UF: %d\n\n", uf_array[i].code);

    printf("Descricao do UF: %s\n\n", uf_array[i].description);

    printf("Sigla do UF: %s\n\n", uf_array[i].acronym);


    printf("--------------------------------------\n");

}


void uf_read_all(uf *uf_array, const int *uf_size)
{

    for (int i = 0; i < *uf_size; i++)
    {
        if (uf_array[i].status != 0)
        uf_read(uf_array, i);
    }

}

//Adicionar no .h



int uf_find_code(const uf *uf_array, const int *uf_size, const int code)
{

    for (int i = 0; i < *uf_size; i++)
    {
#ifdef debug
        printf("uf_array[%d].code: %d\n", i, uf_array[i].code);
#endif
        if (uf_array[i].status == 0)
            continue;
        if (uf_array[i].code == code)
            return i;
    }

    return -1;
}

//Nao é key nao sera utilizada
int uf_find_description(const uf *uf_array,const int *uf_size, char str[])
{

    for (int i = 0; i < *uf_size; i++)
    {
#ifdef debug
        printf("strcmp(str,uf_array[%d].description): %d\n", i, strcmp(str,uf_array[i].description));
#endif
        if (uf_array[i].status == 0)
            continue;
        if (strcmp(str,uf_array[i].description) == 0)
            return i;
    }

    return -1;
}


int uf_find_acronym(const uf *uf_array,const int *uf_size, char str[])
{
    for (int i = 0; i < *uf_size; i++)
    {
#ifdef debug
        printf("strcmp(str,uf_array[%d].acronym): %d\n", i, strcmp(str,uf_array[i].description));
#endif
        if (uf_array[i].status == 0)
            continue;
        if (strcmp(str,uf_array[i].acronym) == 0)
            return i;
    }

    return -1;
}

void uf_update(uf **uf_array, const int *uf_size, const int i)
{
    int state_original = 0;
#ifdef manual_code
    do
    {
        int num;
        input_int(&num,4,"codigo","UF", FALSE);
        state_original = uf_find_code(*uf_array, uf_size, num);

#ifdef debug
        printf("state_original: %d\n", state_original);
#endif
        if (num == (*uf_array)[i].code)
            state_original = -1;

        if (state_original != -1)
        {
            printf("\n\nCodigo ja existe, tente novamente: \n");
            state_original = 0;
            continue;
        }
        (*uf_array)[i].code = num;
    }  while (state_original != -1);
#else
    (*uf_array)[i].code = i + 1;
#endif

    char str[30];
    do
    {
        input_char(str, 30, "nome", "UF", FALSE);


        state_original = -1;

#ifdef debug
        printf("state_original: %d", state_original);
#endif


        strcpy((*uf_array)[i].description, str);
    }  while (state_original != -1);

    do
    {

        input_char(str, 5, "sigla", "UF", FALSE);
        state_original = uf_find_acronym(*uf_array, uf_size, str);

#ifdef debug
        printf("state_original: %d", state_original);
#endif

        if (!strcmp(str,(*uf_array)[i].acronym))
            state_original = -1;


        if (state_original != -1 && strcmp(str,(*uf_array)[i].acronym))
        {
            printf("\n\nSigla ja existe, tente novamente: \n");
            state_original = 0;
            continue;
        }
        strcpy((*uf_array)[i].acronym, str);
    }  while (state_original != -1);

    (*uf_array)[i].status = -1;
}