//
// Created by franc on 22/07/2025.
//

#include "attendance.h"
#include "Func_gerais.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void attendance_start(attendance **attendance_array, int *attendance_size, election *election_array, people *people_array, int people_size, int election_size)
{
    *attendance_size = file_size("attendance.bin", sizeof(attendance));
    if (*attendance_size > 0)
    {
        *attendance_array = (attendance *)malloc(*attendance_size * sizeof(attendance));
        if (*attendance_array == NULL) exit(-1);
        attendance_file_to_array(*attendance_array, attendance_size);
        for (int i = 0; i < *attendance_size; i++)
            attendance_get_pointer(attendance_array, i, election_array, people_array, people_size, election_size);
    }
}


void attendance_array_expander(attendance **attendance_array, int *attendance_size)
{
    (*attendance_size)++;

    *attendance_array = (attendance *) realloc (*attendance_array, *attendance_size * sizeof(attendance));
    if (*attendance_array == NULL)
    {
        printf("\nError attendance_array_expander\n");
        exit (-1);
    }

    #ifdef debug
    printf("\n\nExpanded attendance_SIZE: %d\n\n",*attendance_size);
    printf("\n\nExpanded *attendance_size * sizeof(attendance): %llu\n\n",*attendance_size * sizeof(attendance));
    #endif

    (*attendance_array)[*attendance_size-1].status = 0;
}




void attendance_file_to_array(attendance *attendance_array, const int *attendance_size)
{

    FILE *f = ptr_file("attendance.bin");
    fseek(f,0,SEEK_SET);
    fread(attendance_array,sizeof(attendance),*attendance_size,f);
    fclose(f);

}



void attendance_array_to_file(attendance *attendance_array, const int *attendance_size)
{
    FILE *f = ptr_file("attendance.bin");
    for (int i = 0; i < *attendance_size; i++)
    {
        if (attendance_array[i].status == -1)
        {
            attendance_array[i].status = 1;
            fseek(f,sizeof(attendance)*i,SEEK_SET);
            fwrite(&attendance_array[i],sizeof(attendance),1,f);
            clean(f);
        }
        if (attendance_array[i].status == 0)
        {
            fseek(f,sizeof(attendance)*i,SEEK_SET);
            fwrite(&attendance_array[i],sizeof(attendance),1,f);
            clean(f);
        }
    }
    fclose(f);
}



int attendance_array_empty_space_finder(const attendance *attendance_array, const int *attendance_size)
{
#ifdef debug
    printf("attendance_size == %d\n",*attendance_size);
#endif

    for (int i = (*attendance_size)-1; i > -1; i--)
    {

        if (attendance_array[i].status == 0)
        {
            return i;
        }
    }
    return -1;
}


void attendance_create(attendance **attendance_array, int *attendance_size)
{

    int i = attendance_array_empty_space_finder(*attendance_array ,attendance_size);
#ifdef debug
    printf("\n\nvote_SIZE: %d\n\n",*attendance_size);
    printf("\n\n*attendance_size * sizeof(election): %llu\n\n",*attendance_size * sizeof(election));
#endif
    if (i == -1)
    {
        attendance_array_expander(attendance_array ,attendance_size);
        i = attendance_array_empty_space_finder(*attendance_array ,attendance_size);
        if (i == -1)
        {
            printf("Error attendance_create");
            exit(-1);
        }
    }
}


void attendance_read(attendance *attendance_array, const int i)
{
    if (attendance_array[i].status == 0)
        return ;

    printf("--------------------------------------\n");

    #ifdef debug
    printf("DEBUG: STATUS == %d\n\n", attendance_array[i].status);
    #endif

    printf("CPF: %s\n\n",  attendance_array[i].ptr_people[0].cpf);

    printf("Ano: %d\n\n", attendance_array[i].ptr_election[0].year);

    printf("Codigo do Estado: %d\n\n",  attendance_array[i].ptr_election[0].uf_code);


    printf("--------------------------------------\n");

}


void attendance_read_all(attendance *attendance_array, const int *attendance_size)
{

    for (int i = 0; i < *attendance_size; i++)
    {
        if (attendance_array[i].status != 0)
        attendance_read(attendance_array, i);
    }

}


void attendance_get_pointer(attendance **attendance_array, int i, election *election_array, people *people_array, int people_size, int election_size)
{
    if ((*attendance_array)[i].status == 0 || (*attendance_array)[i].people_locale >= people_size || (*attendance_array)[i].election_locale>= election_size || people_array[(*attendance_array)[i].people_locale].status == 0 || election_array[(*attendance_array)[i].election_locale].status == 0)
    {
        (*attendance_array)[i].status = 0;
        return;
    }

    (*attendance_array)[i].ptr_people = &people_array[(*attendance_array)[i].people_locale];

    strcpy((*attendance_array)[i].cpf, people_array[(*attendance_array)[i].people_locale].cpf);

    (*attendance_array)[i].ptr_election = &election_array[(*attendance_array)[i].election_locale];

    (*attendance_array)[i].year = election_array[(*attendance_array)[i].election_locale].year;

    (*attendance_array)[i].uf_code = election_array[(*attendance_array)[i].election_locale].uf_code;

    strcpy((*attendance_array)[i].acronym, election_array[(*attendance_array)[i].election_locale].ptr_state[0].acronym);

}


void attendance_get_locale(attendance *attendance_array, int i, election *election_array, people *people_array)
{
    if (attendance_array[i].status == 0)
        return;
    attendance_array[i].people_locale = (attendance_array[i].ptr_people - people_array)/sizeof(people);
    attendance_array[i].election_locale = (attendance_array[i].ptr_election - election_array)/sizeof(election);
}


int attendance_find_and_read_for_year(attendance *attendance_array, int *attendance_size, int year, int uf_size)
{

    int happened = -1;


    for (int i = 0; i < uf_size; i++)
    {
        for (int j = 0; j < *attendance_size; j++)
        {

            if (attendance_array[j].status == 0)
                continue;
            if (attendance_array[i].uf_code == i+1)
                if (attendance_array[j].year == year)
                {
                    attendance_read(attendance_array, j);
                    happened = 0;
                }
        }
    }

    return happened;
}


int attendance_find_and_read_for_year_number(attendance *attendance_array, int *attendance_size, int year, int code)
{

    int happened = -1;

    for (int i = 0; i < *attendance_size; i++)
    {
        if (attendance_array[i].status == 0)
            continue;
        if (attendance_array[i].year == year && attendance_array[i].uf_code == code)
        {
            attendance_read(attendance_array, i);
            happened = 0;
        }
    }

    return happened;
}

int attendance_votes_for_uf_year(attendance *attendance_array, int *attendance_size, int year, int uf_code, uf *uf_array)
{

    int happened = -1;
    int qnt = 0;


        for (int j = 0; j < *attendance_size; j++)
        {
            if (attendance_array[j].status == 0)
                continue;
            if (attendance_array[j].uf_code == uf_code)
                if (attendance_array[j].year == year)
                {
                    qnt++;
                    happened = 0;
                }
        }

        printf("\nVotos de %s: %d\n",uf_array[uf_code - 1].acronym, qnt);

    return happened;
}


int attendance_all_quantities(attendance *attendance_array, int *attendance_size, int year, uf *uf_array, int uf_size)
{

    int happened = -1;
    int qnt = 0;
    for (int i = 0; i < uf_size; i++)
    {

        qnt = 0;
        for (int j = 0; j < *attendance_size; j++)
        {
            if (attendance_array[j].status == 0)
                continue;
            if (attendance_array[j].uf_code == i+1)
                if (attendance_array[j].year == year)
                {
                    qnt++;
                    happened = 0;
                }
        }
        printf("\nVotos de %s: %d\n",uf_array[i].acronym, qnt);
    }

    return happened;
}