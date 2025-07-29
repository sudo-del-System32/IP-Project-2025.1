//
// Created by franc on 17/07/2025.
//

#include "people.h"
#include "Func_gerais.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void people_start(people **people_array, int *people_size)
{
    *people_size = file_size("people.bin", sizeof(people));
    *people_array = (people *)malloc(*people_size * sizeof(people));
    people_file_to_array(*people_array, people_size);
}



void people_array_expander(people **people_array, int *people_size)
{
    (*people_size)++;

    *people_array = (people *) realloc (*people_array, *people_size * sizeof(people));
    if (*people_array == NULL)
    {
        printf("\nError people_array_expander\n");
        exit (-1);
    }

    #ifdef debug
    printf("\n\nExpanded PEOPLE_SIZE: %d\n\n",*people_size);
    printf("\n\nExpanded *people_size * sizeof(people): %llu\n\n",*people_size * sizeof(people));
    #endif

    (*people_array)[*people_size-1].status = 0;
}




void people_file_to_array(people *people_array, const int *people_size)
{

    FILE *f = ptr_file("people.bin");
    fseek(f,0,SEEK_SET);
    fread(people_array,sizeof(people),*people_size,f);
    fclose(f);

}



void people_array_to_file(people *people_array, const int *people_size)
{
    FILE *f = ptr_file("people.bin");
    for (int i = 0; i < *people_size; i++)
    {
        if (people_array[i].status == -1)
        {
            people_array[i].status = 1;
            fseek(f,sizeof(people)*i,SEEK_SET);
            fwrite(&people_array[i],sizeof(people),1,f);
            clean(f);
        }
        if (people_array[i].status == 0)
        {
            fseek(f,sizeof(people)*i,SEEK_SET);
            fwrite(&people_array[i],sizeof(people),1,f);
            clean(f);
        }
    }
    fclose(f);
}



int people_array_empty_space_finder(const people *people_array, const int *people_size)
{
#ifdef debug
    printf("people_size == %d\n",*people_size);
#endif

    for (int i = (*people_size)-1; i > -1; i--)
    {

        if (people_array[i].status == 0)
        {
            return i;
        }
    }
    return -1;
}


void people_create(people **people_array, int *people_size)
{

    int i = people_array_empty_space_finder(*people_array ,people_size);
#ifdef debug
    printf("\n\nPEOPLE_SIZE: %d\n\n",*people_size);
    printf("\n\n*PEOPLE_size * sizeof(people): %llu\n\n",*people_size * sizeof(people));
#endif
    if (i == -1)
    {
        people_array_expander(people_array ,people_size);
        i = people_array_empty_space_finder(*people_array ,people_size);
        if (i == -1)
        {
            printf("Error people_create");
            exit(-1);
        }
    }

    people_update(people_array, people_size, i);
}


void people_read(people *people_array, const int i)
{
    if (people_array[i].status == 0)
        return ;

    printf("--------------------------------------\n");

    #ifdef debug
    printf("DEBUG: STATUS == %d\n\n", people_array[i].status);
    #endif

    printf("Nome: %s\n\n", people_array[i].name);

    printf("CPF: %s\n\n", people_array[i].cpf);

    printf("Titulo: %s\n\n", people_array[i].titulo);

    if (people_array[i].number[0] != '\0' || people_array[i].number[0] != '\n')
        printf("Numero de telefone: %s\n\n", people_array[i].number);

    if (people_array[i].address[0] != '\0' || people_array[i].address[0] != '\n')
        printf("Endereco: %s\n\n", people_array[i].address);

    printf("Data de Nascimento: %s\n\n", people_array[i].birthdate);


    printf("--------------------------------------\n");

}


void people_read_all(people *people_array, const int *people_size)
{

    for (int i = 0; i < *people_size; i++)
    {
        if (people_array[i].status != 0)
        people_read(people_array, i);
    }

}


int people_find_cpf(const people *people_array, const int *people_size, const char cpf[])
{
    for (int i = 0; i < *people_size; i++)
    {
#ifdef debug
        printf("people_array[%d].cpf: %s\n", i, people_array[i].cpf);
#endif

        if (people_array[i].status == 0)
            continue;
        if (strcmp(cpf,people_array[i].cpf) == 0)
            return i;
    }


    return -1;
}

int people_find_titulo(const people *people_array,const int *people_size, char str[])
{

    for (int i = 0; i < *people_size; i++)
    {
#ifdef debug
        printf("strcmp(str,people_array[%d].description): %d\n", i, strcmp(str,people_array[i].titulo));
#endif

        if (people_array[i].status == 0)
            continue;
        if (strcmp(str,people_array[i].titulo) == 0)
            return i;
    }

    return -1;
}


void people_update(people **people_array, const int *people_size, const int i)
{
    int state_original = 0;
    char str[255];

    //CPF
    do
    {
        input_char(str,15,"CPF","usuario", FALSE);
        state_original = people_find_cpf(*people_array, people_size, str);
        if (state_original == -1 && (str[3] != '.' || str[7] != '.' || str[11] != '-'))
            state_original = 0;
#ifdef debug
        printf("3c: %c\n", str[3]);
        printf("7c: %c\n", str[7]);
        printf("11c: %c\n", str[11]);
#endif

        if (state_original == -1)
            state_original = just_numbers(FALSE, str, 0, 2);
        if (state_original == -1)
            state_original = just_numbers(FALSE, str, 4, 6);
        if (state_original == -1)
            state_original = just_numbers(FALSE, str, 8, 10);
        if (state_original == -1)
            state_original = just_numbers(FALSE, str, 12, 13);

#ifdef debug
        printf("state_original: %d\n", state_original);
#endif
        if (state_original != -1 && !strcmp(str,(*people_array)[i].cpf))
            state_original = -1;

        if (state_original != -1)
        {
            printf("\n\nCPF ja existe ou possui erro de digitacao: \n");
            printf("\n\nExemplo de cpf: 123.132.122-42 \n");
            state_original = 0;
            continue;
        }
        strcpy((*people_array)[i].cpf, str);
    }  while (state_original != -1);

    //TITULO
    do
    {
        input_char(str,13,"titulo de eleitor","usuario", FALSE);
        state_original = people_find_titulo(*people_array, people_size, str);

        if (state_original == -1)
            state_original = just_numbers(FALSE, str, 0, 11);

#ifdef debug
        printf("state_original: %d\n", state_original);
#endif
        if (!strcmp(str,(*people_array)[i].titulo))
            state_original = -1;

        if (state_original != -1)
        {
            printf("\n\nTitulo ja existe ou possui erro de digitacao: \n");
            printf("\n\nExemplo de titulo: 123412341234  \n");
            state_original = 0;
            continue;
        }
        strcpy((*people_array)[i].titulo, str);
    }  while (state_original != -1);

    //NAME
    {
        input_char(str,255,"nome","usuario", FALSE);
        strcpy((*people_array)[i].name, str);
    }

    //number
    do
    {
        input_char(str, 16, "Numero de telefone", "usuario", TRUE);
        state_original = -1;
        if (str[0] != '\0' && str[0] != '\n' && (str[0] != '(' || str[3] != ')' || str[10] != '-'))
            state_original = 0;

#ifdef debug
        printf("str0: %c\n", str[0]);
        printf("str3: %c\n", str[3]);
        printf("str10: %c\n", str[10]);
        printf("str14: %c\n", str[14]);
#endif


        if (state_original == -1)
            state_original = just_numbers(TRUE, str, 1, 2);
        if (state_original == -1 && (str[0] != '\n' || str[0] != '\0') )
        {
            state_original = just_numbers(TRUE, str, 5, 5);
            if (state_original != -1 && str[5] == ' ') state_original = -1;
        }
        if (state_original == -1 && (str[0] != '\n' || str[0] != '\0') )
            state_original = just_numbers(TRUE, str, 6, 9);
        if (state_original == -1 && (str[0] != '\n' || str[0] != '\0') )
            state_original = just_numbers(TRUE, str, 11, 14);

#ifdef debug
        printf("state_original: %d\n", state_original);
#endif

        if (str[0] == '\0' || str[0] == '\n')
            state_original = -1;

        if (state_original != -1)
        {
            printf("\n\nO Numero de telefone possui erro de digitacao: \n");
            printf("\n\nExemplo de telefone: (85) 99141-7289 ou (82)  2574-5382  \n");
            state_original = 0;
            continue;
        }
        strcpy((*people_array)[i].number, str);
    }  while (state_original != -1);


    //address
    {
        input_char(str, 255, "Endereco", "usuario", TRUE);

        strcpy((*people_array)[i].address, str);
    }

    //birthdate
    do
    {
        input_char(str,11,"Data de nascimento","usuario", FALSE);
        if (str[2] != '/' || str[5] != '/')
            state_original = 0;

        if (state_original == -1)
            state_original = just_numbers(FALSE, str, 0, 1);
        if (state_original == -1)
            state_original = just_numbers(FALSE, str, 3, 4);
        if (state_original == -1)
            state_original = just_numbers(FALSE, str, 6, 9);

#ifdef debug
        printf("state_original: %d\n", state_original);
#endif

        if (state_original != -1)
        {
            printf("\n\nA data de nascimento possui erro de digitacao: \n");
            printf("\n\nExemplo de data: 01/01/2001  \n");
            state_original = 0;
            continue;
        }
        strcpy((*people_array)[i].birthdate, str);
    }  while (state_original != -1);

    (*people_array)[i].status = -1;
}


