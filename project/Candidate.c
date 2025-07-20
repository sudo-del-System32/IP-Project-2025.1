//
// Created by franc on 19/07/2025.
//

#include "Candidate.h"


#include "Func_gerais.h"
#include "uf1.h"
//#include "people.h"
//#include "Election.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void candidate_start(candidate **candidate_array, int *candidate_size, uf *uf_array)
{
    *candidate_size = file_size("candidate.bin", sizeof(candidate));
    *candidate_array = (candidate *)malloc(*candidate_size * sizeof(candidate));
    candidate_file_to_array(*candidate_array, candidate_size);
    for (int i = 0; i < *candidate_size; i++)
        candidate_get_pointer(*candidate_array, i, uf_array);
}



void candidate_array_expander(candidate **candidate_array, int *candidate_size)
{
    (*candidate_size)++;

    *candidate_array = (candidate *) realloc (*candidate_array, *candidate_size * sizeof(candidate));
    if (*candidate_array == NULL)
    {
        printf("\nError candidate_array_expander\n");
        exit (-1);
    }

    #ifdef debug
    printf("\n\nExpanded candidate_SIZE: %d\n\n",*candidate_size);
    printf("\n\nExpanded *candidate_size * sizeof(candidate): %llu\n\n",*candidate_size * sizeof(candidate));
    #endif

    (*candidate_array)[*candidate_size-1].status = 0;
}




void candidate_file_to_array(candidate *candidate_array, const int *candidate_size)
{

    FILE *f = ptr_file("candidate.bin");
    fseek(f,0,SEEK_SET);
    fread(candidate_array,sizeof(candidate),*candidate_size,f);
    fclose(f);

}



void candidate_array_to_file(candidate *candidate_array, const int *candidate_size)
{
    FILE *f = ptr_file("candidate.bin");
    for (int i = 0; i < *candidate_size; i++)
    {
        if (candidate_array[i].status == -1)
        {
            candidate_array[i].status = 1;
            fseek(f,sizeof(candidate)*i,SEEK_SET);
            fwrite(&candidate_array[i],sizeof(candidate),1,f);
            clean(f);
        }
        if (candidate_array[i].status == 0)
        {
            fseek(f,sizeof(candidate)*i,SEEK_SET);
            fwrite(&candidate_array[i],sizeof(candidate),1,f);
            clean(f);
        }
    }
    fclose(f);
}



int candidate_array_empty_space_finder(const candidate *candidate_array, const int *candidate_size)
{
#ifdef debug
    printf("candidate_size == %d\n",*candidate_size);
#endif

    for (int i = (*candidate_size)-1; i > -1; i--)
    {

        if (candidate_array[i].status == 0)
        {
            return i;
        }
    }
    return -1;
}


void candidate_create(candidate **candidate_array, int *candidate_size, uf *uf_array, int *uf_size)
{

    int i = candidate_array_empty_space_finder(*candidate_array ,candidate_size);
#ifdef debug
    printf("\n\nelection_SIZE: %d\n\n",*candidate_size);
    printf("\n\n*candidate_size * sizeof(election): %llu\n\n",*candidate_size * sizeof(election));
#endif
    if (i == -1)
    {
        candidate_array_expander(candidate_array ,candidate_size);
        i = candidate_array_empty_space_finder(*candidate_array ,candidate_size);
        if (i == -1)
        {
            printf("Error candidate_create");
            exit(-1);
        }
    }

    candidate_update(candidate_array, candidate_size, i, uf_array, uf_size);
}


void candidate_read(candidate *candidate_array, const int i)
{
    if (candidate_array[i].status == 0)
        return ;

    printf("--------------------------------------\n");

    #ifdef debug
    printf("DEBUG: STATUS == %d\n\n", candidate_array[i].status);
    #endif

    printf("Ano: %d\n\n", candidate_array[i].year);

    printf("Descricao: %s\n\n", candidate_array[i].description);

    printf("Codigo do UF da Eleicao: %d\n\n", candidate_array[i].ptr_state[0].code);

    printf("Nome do UF da Eleicao: %s\n\n",  candidate_array[i].ptr_state[0].description);



    printf("--------------------------------------\n");

}


void candidate_read_all(candidate *candidate_array, const int *candidate_size)
{

    for (int i = 0; i < *candidate_size; i++)
    {
        if (candidate_array[i].status != 0)
        candidate_read(candidate_array, i);
    }

}


int candidate_find(const candidate *candidate_array, const int *candidate_size, int year, int code)
{
    int i;

    for (i = 0; i < *candidate_size; i++)
    {

        if (candidate_array[i].status == 0)
            continue;
        if (candidate_array[i].year == year && candidate_array[i].uf_code == code)
            return i;
    }

    return -1;
}

void candidate_update(candidate **candidate_array, const int *candidate_size, const int i, uf *uf_array, int *uf_size)
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

        state_original = election_find(*candidate_array, candidate_size, year, code);

        if (state_original != -1 && (year == (*candidate_array)[i].year && code == (*candidate_array)[i].uf_code))
            state_original = -1;
        if (state_original != -1)
        {
            printf("A eleicao de %d para %s ja existe", year, uf_array[state_original-1].description);
            continue;
        }

    } while (state_original != -1);

    (*candidate_array)[i].year = year;
    (*candidate_array)[i].uf_code = code;



    //Description
    {
        input_char(str, 67, "Descricao", "Eleicao", TRUE);
        strcpy((*candidate_array)[i].description, str);
    }

    candidate_get_pointer(*candidate_array, i, uf_array);

    (*candidate_array)[i].status = -1;
}


void candidate_get_pointer(candidate *candidate_array, int i, uf *uf_array)
{
    candidate_array[i].ptr_state = &uf_array[candidate_array[i].uf_code - 1];
}

void candidate_get_uf_code(candidate *candidate_array, int i)
{
    candidate_array[i].uf_code = candidate_array[i].ptr_state->code;
}