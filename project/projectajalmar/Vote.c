//
// Created by franc on 21/07/2025.
//

#include "Vote.h"

#include "Func_gerais.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void vote_start(vote **vote_array, int *vote_size, candidate *candidate_array, election *election_array)
{
    *vote_size = file_size("vote.bin", sizeof(vote));
    *vote_array = (vote *)malloc(*vote_size * sizeof(vote));
    if (*vote_array == NULL) exit(-1);

    vote_file_to_array(*vote_array, vote_size);
    for (int i = 0; i < *vote_size; i++)
        vote_get_pointer(vote_array, i, candidate_array, election_array);
}



void vote_array_expander(vote **vote_array, int *vote_size)
{
    (*vote_size)++;

    *vote_array = (vote *) realloc (*vote_array, *vote_size * sizeof(vote));
    if (*vote_array == NULL)
    {
        printf("\nError vote_array_expander\n");
        exit (-1);
    }

    #ifdef debug
    printf("\n\nExpanded vote_SIZE: %d\n\n",*vote_size);
    printf("\n\nExpanded *vote_size * sizeof(vote): %llu\n\n",*vote_size * sizeof(vote));
    #endif

    (*vote_array)[*vote_size-1].status = 0;
}




void vote_file_to_array(vote *vote_array, const int *vote_size)
{

    FILE *f = ptr_file("vote.bin");
    fseek(f,0,SEEK_SET);
    fread(vote_array,sizeof(vote),*vote_size,f);
    fclose(f);

}



void vote_array_to_file(vote *vote_array, const int *vote_size)
{
    FILE *f = ptr_file("vote.bin");
    for (int i = 0; i < *vote_size; i++)
    {
        if (vote_array[i].status == -1)
        {
            vote_array[i].status = 1;
            fseek(f,sizeof(vote)*i,SEEK_SET);
            fwrite(&vote_array[i],sizeof(vote),1,f);
            clean(f);
        }
        if (vote_array[i].status == 0)
        {
            fseek(f,sizeof(vote)*i,SEEK_SET);
            fwrite(&vote_array[i],sizeof(vote),1,f);
            clean(f);
        }
    }
    fclose(f);
}



int vote_array_empty_space_finder(const vote *vote_array, const int *vote_size)
{
#ifdef debug
    printf("vote_size == %d\n",*vote_size);
#endif

    for (int i = (*vote_size)-1; i > -1; i--)
    {

        if (vote_array[i].status == 0)
        {
            return i;
        }
    }
    return -1;
}


void vote_create(vote **vote_array, int *vote_size, attendance **attendance_array, int *attendance_size, candidate *candidate_array, int *candidate_size, people *people_array, const int *people_size, election *election_array)
{

    int i = vote_array_empty_space_finder(*vote_array ,vote_size);
#ifdef debug
    printf("\n\nvote_SIZE: %d\n\n",*vote_size);
    printf("\n\n*vote_size * sizeof(election): %llu\n\n",*vote_size * sizeof(election));
#endif
    if (i == -1)
    {
        vote_array_expander(vote_array, vote_size);
        i = vote_array_empty_space_finder(*vote_array ,vote_size);
        if (i == -1)
        {
            printf("Error vote_create");
            exit(-1);
        }
    }
    attendance_create(attendance_array, attendance_size);
    vote_update(vote_array, vote_size, attendance_array, i, candidate_array, candidate_size, people_array, people_size, election_array);
}


void vote_read(vote *vote_array, const int i)
{


    printf("--------------------------------------\n");

#ifdef debug
    printf("DEBUG: STATUS == %d\n\n", vote_array[i].status);
#endif

    if (vote_array[i].status == 0)
        return ;

    printf("Ano: %d\n\n", vote_array[i].year);

    printf("Codigo do estado: %d\n\n",  vote_array[i].code);

    printf("Numero do candidato: %d\n\n",  vote_array[i].ptr_candidate[0].candidate_number);

    printf("Data_Hora: %s\n\n",  vote_array[i].time_day);



    printf("--------------------------------------\n");

}


void vote_read_all(vote *vote_array, const int *vote_size)
{

    for (int i = 0; i < *vote_size; i++)
    {
        if (vote_array[i].status != 0)
        vote_read(vote_array, i);
    }

}

int vote_and_attendance_find(vote *vote_array, int *vote_size, int year, int code)
{
    printf("%d", *vote_size);

    int happened = -1;

    for (int i = 0; i < *vote_size; i++)
    {
        if (vote_array[i].status == 0)
            continue;
        printf("%d", *vote_size);

        if (vote_array[i].ptr_candidate[0].ptr_election[0].year == year && vote_array[i].ptr_candidate[0].ptr_election[0].uf_code == code)
        {
            printf("%d", *vote_size);
            vote_read(vote_array, i);
            happened = 0;
        }
    }

    return happened;
}

int attendance_find_cpf(attendance *attendance_array, int *attendance_size, char cpf[])
{
    for (int i = 0; i < *attendance_size; i++)
    {
        if (attendance_array[i].status == 0)
            continue;
        if (strcmp(attendance_array[i].ptr_people[0].cpf, cpf) == 0)
        {
            return i;
        }
    }

    return -1;
}


void vote_update(vote **vote_array, const int *vote_size, attendance **attendance_array, const int i, candidate *candidate_array, int *candidate_size, people *people_array, const int *people_size, election *election_array)
{
    int state_original = 0;
    char str[15];

    //CPF
    do
    {
        state_original = -1;
        input_char(str,15,"CPF","quem esta votando", FALSE);
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

        (*attendance_array)[i].people_locale = state_original;

        if (state_original == -1)
        {
            printf("\n\nCPF nao existe. \n");
            continue;
        }

        // state_original = attendance_find_cpf(*attendance_array, attendance_size, str);
        // if (state_original != -1)
        // {
        //     printf("\n\nCPF ja votou. \n");
        //     continue;
        // }


    }  while (state_original == -1);

    int year = 0, code = 0, number =0;

    do
    {

        do
        {

            //year
            year = 0;
            input_int(&year,5,"Ano","Eleicao", FALSE);

            if (year < 1000)
            {
                state_original = -1;
                printf("\n\nAno invalido, ano tem que possuir 4 digitos.\n\n");
                continue;
            }

            state_original = candidate_find_year(candidate_array, candidate_size, year);

            if (state_original == -1)
            {
                printf("Nao existe uma eleicao nesse ano.");
                continue;
            }

        } while (state_original == -1);

        do{
            //UF
            code = 0;
            input_int(&code,8,"codigo","UF da eleicao", FALSE);


            printf("\n\n=============================CANDIDATOS DA ELEICAO=============================\n\n");
            state_original = candidate_find_and_read_for_year_number(candidate_array, candidate_size, year, code);
            printf("\n\n=============================CANDIDATOS DA ELEICAO=============================\n\n");

            if (state_original == -1)
            {
                printf("\n\nNao existe uma uf com eleicao com esse codigo.\n\n");
                continue;
            }

        } while (state_original == -1);

        do{

            //Numero do candidato
            number = 0;
            input_int(&number,3,"numero","candidato", FALSE);

            state_original = candidate_find_number(candidate_array, candidate_size, number);

            if (state_original == -1)
            {
                printf("\n\nNao existe uma candidato com esse numero.\n\n");
                continue;
            }


        } while (state_original == -1);

        state_original = candidate_find_number_year_code(candidate_array, candidate_size, year, code, number);


        if (state_original == -1)
        {
            printf("\nCandidato com o numero %d, do UF de codigo %d, da eleicao do ano %d, não existe\n\n",number, code, year);
            continue;
        }

        (*vote_array)[i].candidate_locale = state_original;
        (*vote_array)[i].election_locale = candidate_array[state_original].election_locale;
        (*attendance_array)[i].election_locale = candidate_array[state_original].election_locale;


    } while (state_original == -1);

    state_original = -1;
    do
    {
        printf("\n\nPorfavor coloque data_hora sendo similar ah : 12:20 12/09\n");
        if (state_original != -1)
        {
            printf("\n\nDATA JA EXISTE, MULTIPLOS VOTOS NO MESMO TEMPO, POSSIVEL FRAUDE\n\n");
            state_original = -1;
        }
        input_char(str,15,"Data_Hora","Votacao", FALSE);

        state_original = vote_find_time(*vote_array, vote_size, str);

    } while (state_original != -1);
    strcpy((*vote_array)[i].time_day, str);

    vote_get_pointer(vote_array, i, candidate_array, election_array);
    attendance_get_pointer(attendance_array, i, election_array, people_array);

    (*vote_array)[i].status = -1;
    (*attendance_array)[i].status = -1;
}


void vote_get_pointer(vote **vote_array, int i, candidate *candidate_array, election *election_array)
{
    (*vote_array)[i].ptr_candidate = &candidate_array[(*vote_array)[i].candidate_locale];
    (*vote_array)[i].election_locale = candidate_array[(*vote_array)[i].candidate_locale].election_locale;
    (*vote_array)[i].ptr_election = &election_array[(*vote_array)[i].election_locale];
    (*vote_array)[i].year = election_array[(*vote_array)[i].election_locale].year;
    (*vote_array)[i].code = election_array[(*vote_array)[i].election_locale].uf_code;
}

void vote_get_locale(vote *vote_array, int i, candidate *candidate_array, election *election_array)
{
    vote_array[i].candidate_locale = (vote_array[i].ptr_candidate - candidate_array)/sizeof(candidate);
    vote_array[i].election_locale = (vote_array[i].ptr_election - election_array)/sizeof(election);
}


int vote_find_and_read_for_year_number(vote *vote_array, int *vote_size, int year, int code)
{

    int happened = -1;

    for (int i = 0; i < *vote_size; i++)
    {
        if (vote_array[i].status == 0)
            continue;

        if (vote_array[i].year == year && vote_array[i].code == code)
        {

            vote_read(vote_array, i);
            happened = 0;
        }
    }

    return happened;
}


int vote_find_and_read_for_year(vote *vote_array, int *vote_size, int year, int uf_size)
{

    int happened = -1;


    for (int i = 0; i < uf_size; i++)
    {
        for (int j = 0; j < *vote_size; j++)
        {
            if (vote_array[j].status == 0)
                continue;
            if (vote_array[j].code == i+1)
                if (vote_array[j].year == year)
                {
                    vote_read(vote_array, j);
                    happened = 0;
                }
        }
    }

    return happened;
}

int vote_find_time(vote *vote_array, const int *vote_size, char str[])
{

        for (int j = 0; j < *vote_size; j++)
        {
            if (vote_array[j].status == 0)
                continue;
            if (strcmp(vote_array[j].time_day,str) == 0)
            {
                return j;
            }
        }

    return -1;

}