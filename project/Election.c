//
// Created by franc on 18/07/2025.
//

#include "Election.h"


// #include "Func_gerais.h"
// #include "uf1.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>


void election_start(election **election_array, int *election_size, uf *uf_array)
{
    *election_size = file_size("election.bin", sizeof(election));
    *election_array = (election *)malloc(*election_size * sizeof(election));
    election_file_to_array(*election_array, election_size);
    for (int i = 0; i < *election_size; i++)
        election_get_pointer(*election_array, i, uf_array);
}



void election_array_expander(election **election_array, int *election_size)
{
    (*election_size)++;

    *election_array = (election *) realloc (*election_array, *election_size * sizeof(election));
    if (*election_array == NULL)
    {
        printf("\nError election_array_expander\n");
        exit (-1);
    }

    #ifdef debug
    printf("\n\nExpanded election_SIZE: %d\n\n",*election_size);
    printf("\n\nExpanded *election_size * sizeof(election): %llu\n\n",*election_size * sizeof(election));
    #endif

    (*election_array)[*election_size-1].status = 0;
}




void election_file_to_array(election *election_array, const int *election_size)
{

    FILE *f = ptr_file("election.bin");
    fseek(f,0,SEEK_SET);
    fread(election_array,sizeof(election),*election_size,f);
    fclose(f);

}



void election_array_to_file(election *election_array, const int *election_size)
{
    FILE *f = ptr_file("election.bin");
    for (int i = 0; i < *election_size; i++)
    {
        if (election_array[i].status == -1)
        {
            election_array[i].status = 1;
            fseek(f,sizeof(election)*i,SEEK_SET);
            fwrite(&election_array[i],sizeof(election),1,f);
            clean(f);
        }
        if (election_array[i].status == 0)
        {
            fseek(f,sizeof(election)*i,SEEK_SET);
            fwrite(&election_array[i],sizeof(election),1,f);
            clean(f);
        }
    }
    fclose(f);
}



int election_array_empty_space_finder(const election *election_array, const int *election_size)
{
#ifdef debug
    printf("election_size == %d\n",*election_size);
#endif

    for (int i = (*election_size)-1; i > -1; i--)
    {

        if (election_array[i].status == 0)
        {
            return i;
        }
    }
    return -1;
}


void election_create(election **election_array, int *election_size, uf *uf_array, int *uf_size)
{

    int i = election_array_empty_space_finder(*election_array ,election_size);
#ifdef debug
    printf("\n\nelection_SIZE: %d\n\n",*election_size);
    printf("\n\n*election_size * sizeof(election): %llu\n\n",*election_size * sizeof(election));
#endif
    if (i == -1)
    {
        election_array_expander(election_array ,election_size);
        i = election_array_empty_space_finder(*election_array ,election_size);
        if (i == -1)
        {
            printf("Error election_create");
            exit(-1);
        }
    }

    election_update(election_array, election_size, i, uf_array, uf_size);
}


void election_read(election *election_array, const int i)
{
    if (election_array[i].status == 0)
        return ;

    printf("--------------------------------------\n");

    #ifdef debug
    printf("DEBUG: STATUS == %d\n\n", election_array[i].status);
    #endif

    printf("Ano: %d\n\n", election_array[i].year);

    printf("Descricao: %s\n\n", election_array[i].description);

    printf("Codigo do UF da Eleicao: %d\n\n", election_array[i].ptr_state[0].code);

    printf("Nome do UF da Eleicao: %s\n\n",  election_array[i].ptr_state[0].description);



    printf("--------------------------------------\n");

}


void election_read_all(election *election_array, const int *election_size)
{

    for (int i = 0; i < *election_size; i++)
    {
        if (election_array[i].status != 0)
        election_read(election_array, i);
    }

}


int election_find(const election *election_array, const int *election_size, int year, int code)
{
    int i;

    for (i = 0; i < *election_size; i++)
    {
        if (election_array[i].status == 0)
            continue;
        if (election_array[i].year == year && election_array[i].uf_code == code)
            return i;
    }

    return -1;
}

void election_update(election **election_array, const int *election_size, const int i, uf *uf_array, int *uf_size)
{
    int state_original = 0;
    char str[67];
    int year = 0, code = 0;

    do
    {
        //year
        year = 0;
        input_int(&year,5,"Ano","Eleicao", FALSE);
            if (year < 1000)
            {
                printf("Ano invalido, ano tem que possuir 4 digitos.");
                continue;
            }
        //UF
        code = 0;
        input_int(&code,8,"codigo","UF", FALSE);

        state_original = uf_find_code(uf_array, uf_size, code);

        if (state_original == -1)
        {
            printf("A UF nao existe");
            state_original = 0;
            continue;
        }

        state_original = election_find(*election_array, election_size, year, code);

        if (state_original != -1 && (year == (*election_array)[i].year && code == (*election_array)[i].uf_code))
            state_original = -1;
        if (state_original != -1)
        {
            printf("A eleicao de %d para %s ja existe", year, uf_array[state_original-1].description);
            continue;
        }

    } while (state_original != -1);

    (*election_array)[i].year = year;
    (*election_array)[i].uf_code = code;



    //Description
    {
        input_char(str, 67, "Descricao", "Eleicao", TRUE);
        strcpy((*election_array)[i].description, str);
    }

    election_get_pointer(*election_array, i, uf_array);

    (*election_array)[i].status = -1;
}


void election_get_pointer(election *election_array, int i, uf *uf_array)
{
    election_array[i].ptr_state = &uf_array[election_array[i].uf_code - 1];
}

void election_get_uf_code(election *election_array, int i)
{
    election_array[i].uf_code = election_array[i].ptr_state->code;
}