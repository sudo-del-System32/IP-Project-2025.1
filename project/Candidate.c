//
// Created by franc on 19/07/2025.
//

#include "Candidate.h"
#include "Func_gerais.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void candidate_start(candidate **candidate_array, int *candidate_size, election *election_array, people *people_array)
{
    *candidate_size = file_size("candidate.bin", sizeof(candidate));
    *candidate_array = (candidate *)malloc(*candidate_size * sizeof(candidate));
    candidate_file_to_array(*candidate_array, candidate_size);
    for (int i = 0; i < *candidate_size; i++)
        candidate_get_pointer(*candidate_array, i, election_array, people_array);
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


void candidate_create(candidate **candidate_array, int *candidate_size, election *election_array, int *election_size, people *people_array, int *people_size)
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

    candidate_update(candidate_array, candidate_size, i, election_array, election_size, people_array, people_size);
}


void candidate_read(candidate *candidate_array, const int i)
{
    if (candidate_array[i].status == 0)
        return ;

    printf("---------------------------------------------------------------------------\n");

    #ifdef debug
    printf("DEBUG: STATUS == %d\n\n", candidate_array[i].status);
    #endif

    printf("Nome: %s\n\n", candidate_array[i].ptr_people[0].name);

    printf("Numero: %d\n\n", candidate_array[i].candidate_number);

    printf("Ano: %d\n\n", candidate_array[i].ptr_election[0].year);

    printf("Estado: %s\n\n",  candidate_array[i].ptr_election[0].ptr_state[0].description);

    printf("Descricao da Eleicao: %s\n\n",  candidate_array[i].ptr_election[0].description);



    printf("---------------------------------------------------------------------------\n");

}


void candidate_read_all(candidate *candidate_array, const int *candidate_size)
{

    for (int i = 0; i < *candidate_size; i++)
    {
        if (candidate_array[i].status != 0)
        candidate_read(candidate_array, i);
    }

}

 //How to find the candidates of a year + code
int candidate_find_and_read_for_year_number(candidate *candidate_array, int *candidate_size, int year, int code)
{

    int happened = -1;

    for (int i = 0; i < *candidate_size; i++)
    {
        if (candidate_array[i].status == 0)
            continue;
        if (candidate_array[i].ptr_election[0].year == year && candidate_array[i].ptr_election[0].uf_code == code)
        {
            candidate_read(candidate_array, i);
            happened = 0;
        }
    }

    return happened;
}


int candidate_find_and_read_for_year(candidate *candidate_array, int *candidate_size, int year, int uf_size)
{

    int happened = -1;


    for (int i = 0; i < uf_size; i++)
    {
        for (int j = 0; j < *candidate_size; j++)
        {
            if (candidate_array[j].status == 0)
                continue;
            if (candidate_array[j].ptr_election[0].uf_code == i+1)
                if (candidate_array[j].ptr_election[0].year == year)
                {
                    candidate_read(candidate_array, j);
                    happened = 0;
                }
        }
    }

    return happened;
}



int candidate_find_number_year_code(candidate *candidate_array, int *candidate_size, int year, int uf_code, int number)
{
    for (int i = 0; i < *candidate_size; i++)
    {
        if (candidate_array[i].status == 0)
            continue;
        if (candidate_array[i].ptr_election[0].year == year && candidate_array[i].ptr_election[0].uf_code == uf_code && candidate_array[i].candidate_number == number)
            return i;
    }

    return -1;
}


int candidate_validation(const candidate *candidate_array, const int *candidate_size, int number, const election *election_array, const int *election_size,int year, int code)
{
    int locale = election_find(election_array, election_size, year, code);
    if (locale == -1) //Nao existe a eleiçao
        return -2;
    for (int i = 0; i < *candidate_size; i++)
    {
        if (candidate_array[i].status == 0)
            continue;
        if (candidate_array[i].election_locale == locale && candidate_array[i].candidate_number == number)
            return i;
    }

    return -1;
}

void candidate_update(candidate **candidate_array, const int *candidate_size, const int i, election *election_array, int *election_size, people *people_array, int *people_size)
{
    int state_original = 0;
    char str[15];
    int year = 0, code = 0, number =0;

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
        input_int(&code,8,"codigo","UF da eleicao", FALSE);

        //Numero do candidato
        number = 0;
        input_int(&number,3,"numero","candidato", FALSE);

        state_original = candidate_validation(*candidate_array, candidate_size, number, election_array, election_size, year, code);

        if (state_original == -2)
        {
            printf("\nEleicao inexistente, tente se candidatar a outra.\n\n");
            state_original = 0;
            continue;
        }


        if (state_original != -1 && state_original != i)
        {
            printf("\nCandidato com o numero %d, do UF de codigo %d, da eleicao do ano %d, ja existe\n\n",number, code, year);
            state_original = 0;
            continue;
        }


    } while (state_original != -1 && state_original != i);


    //CPF
    do
    {
        input_char(str,15,"CPF","candidato", FALSE);
        if (str[3] != '.' || str[7] != '.' || str[11] != '-')
            state_original = 0;

        if (state_original == -1)
            state_original = just_numbers(FALSE, str, 0, 2);
        if (state_original == -1)
            state_original = just_numbers(FALSE, str, 4, 6);
        if (state_original == -1)
            state_original = just_numbers(FALSE, str, 8, 10);
        if (state_original == -1)
            state_original = just_numbers(FALSE, str, 12, 13);

        if (state_original != -1)
        {
            printf("\n\nCPF possui erro de digitacao: \n");
            printf("\n\nExemplo de cpf: 123.132.122-42 \n");
            state_original = -1;
            continue;
        }

        state_original = people_find_cpf(people_array, people_size, str);
        if (state_original == -1)
        {
            printf("\n\nCPF nao existe. \n");
            continue;
        }

        (*candidate_array)[i].people_locale = state_original;
    }  while (state_original == -1);

    (*candidate_array)[i].election_locale = election_find(election_array, election_size, year, code);

    candidate_get_pointer(*candidate_array, i, election_array, people_array);

    (*candidate_array)[i].candidate_number = number;

    (*candidate_array)[i].status = -1;
}


void candidate_get_pointer(candidate *candidate_array, int i, election *ptr_election, people *ptr_people)
{
    candidate_array[i].ptr_election = &ptr_election[candidate_array[i].election_locale];
    candidate_array[i].ptr_people = &ptr_people[candidate_array[i].people_locale];
}

void candidate_get_locale(candidate *candidate_array, int i, election *election_array, people *people_array)
{
    candidate_array[i].election_locale = (candidate_array[i].ptr_election - election_array)/sizeof(election);
    candidate_array[i].people_locale = (candidate_array[i].ptr_people - people_array)/sizeof(people);

}

//Using into vote

int candidate_find_number(candidate *candidate_array, int *candidate_size, int code)
{

    int happened = -1;

    for (int i = 0; i < *candidate_size; i++)
    {
        if (candidate_array[i].status == 0)
            continue;
        if (candidate_array[i].candidate_number == code)
        {
            return i;
        }
    }

    return happened;
}

int candidate_find_year(candidate *candidate_array, int *candidate_size, int year)
{

    int happened = -1;

    for (int i = 0; i < *candidate_size; i++)
    {
        if (candidate_array[i].status == 0)
            continue;
        if (candidate_array[i].ptr_election[0].year == year)
        {
            return i;
        }
    }

    return happened;
}

int candidate_find_uf(candidate *candidate_array, int *candidate_size, int uf)
{

    int happened = -1;

    for (int i = 0; i < *candidate_size; i++)
    {
        if (candidate_array[i].status == 0)
            continue;
        if (candidate_array[i].ptr_election[0].uf_code == uf)
        {
            return i;
        }
    }

    return happened;
}