///
// Created by franc on 17/07/2025.
//

#ifndef PEOPLE_H
#define PEOPLE_H

struct people
{
    char cpf[15]; //Pkey
    char titulo[13]; //key
    char name[255]; //*
    char number[16];
    char address[255];
    char birthdate[11]; //*
    int status; //0 Empty //1 Full //-1 Modified
};

typedef struct people people;


void people_start(people **people_array, int *people_size);

void people_array_expander(people **people_array, int *people_size);

void people_file_to_array(people *people_array, const int *people_size);

void people_array_to_file(people *people_array, const int *people_size);

int people_array_empty_space_finder(const people *people_array, const int *people_size);

void people_create(people **people_array, int *people_size);

void people_read(people *people_array, const int i);

void people_read_all(people *people_array, const int *people_size);

int people_find_cpf(const people *people_array, const int *people_size, const char cpf[]);

int people_find_titulo(const people *people_array,const int *people_size, char str[]);

void people_update(people **people_array, const int *people_size, const int i);


#endif //PEOPLE_H
