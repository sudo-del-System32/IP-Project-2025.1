//
// Created by franc on 19/07/2025.
//

#ifndef CANDIDATE_H
#define CANDIDATE_H
#include "people.h"
#include "Election.h"

typedef struct candidate
{
    int election_locale; //Pk* year
    int people_locale; //Pk* cpf
    int candidate_number; //* 2 digitos

    election *ptr_election;
    people *ptr_people;

    int status;
}candidate;

void candidate_start(candidate **candidate_array, int *candidate_size, election *election_array, people *people_array);


void candidate_array_expander(candidate **candidate_array, int *candidate_size);


void candidate_file_to_array(candidate *candidate_array, const int *candidate_size);


void candidate_array_to_file(candidate *candidate_array, const int *candidate_size);


int candidate_array_empty_space_finder(const candidate *candidate_array, const int *candidate_size);

//alterado
void candidate_create(candidate **candidate_array, int *candidate_size, election *election_array, int *election_size, people *people_array, int *people_size);


void candidate_read(candidate *candidate_array, const int i);


void candidate_read_all(candidate *candidate_array, const int *candidate_size);

int candidate_find_and_read_for_year_number(candidate *candidate_array, int *candidate_size, int year, int code);

int candidate_find_and_read_for_year(candidate *candidate_array, int *candidate_size, int year, int uf_size);

int candidate_find_number_year_code(candidate *candidate_array, int *candidate_size, int year, int uf_code, int number);


int candidate_validation(const candidate *candidate_array, const int *candidate_size, int number, const election *election_array, const int *election_size,int year, int code);


void candidate_update(candidate **candidate_array, const int *candidate_size, const int i, election *election_array, int *election_size, people *people_array, int *people_size);


void candidate_get_pointer(candidate *candidate_array, int i, election *ptr_election, people *ptr_people);


void candidate_get_locale(candidate *candidate_array, int i, election *election_array, people *people_array);

int candidate_find_number(candidate *candidate_array, int *candidate_size, int code);

int candidate_find_year(candidate *candidate_array, int *candidate_size, int year);

int candidate_find_uf(candidate *candidate_array, int *candidate_size, int uf);


#endif //CANDIDATE_H
