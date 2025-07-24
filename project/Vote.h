//
// Created by franc on 21/07/2025.
//

#ifndef VOTE_H
#define VOTE_H

typedef struct vote
{
    int election_locale; //PK
    election *ptr_election; //PK
    int candidate_locale; //PK
    candidate *ptr_candidate; //PK

    int year;
    int code;
    char time_day[100]; //PK

    int status;
}vote;



void vote_start(vote **vote_array, int *vote_size, candidate *candidate_array, election *election_array);

void vote_array_expander(vote **vote_array, int *vote_size);


void vote_file_to_array(vote *vote_array, const int *vote_size);

void vote_array_to_file(vote *vote_array, const int *vote_size);

int vote_array_empty_space_finder(const vote *vote_array, const int *vote_size);

void vote_create(vote **vote_array, int *vote_size, attendance **attendance_array, int *attendance_size, candidate *candidate_array, int *candidate_size, people *people_array, const int *people_size, election *election_array);

void vote_read(vote *vote_array, const int i);

void vote_read_all(vote *vote_array, const int *vote_size);

int vote_and_attendance_find(vote *vote_array, int *vote_size, int year, int code);

int attendance_find_cpf(attendance *attendance_array, int *attendance_size, char cpf[]);

int vote_validation(const vote *vote_array, const int *vote_size, int number, const election *election_array, const int *election_size,int year, int code);

void vote_update(vote **vote_array, const int *vote_size, attendance **attendance_array, int *attendance_size, const int i, candidate *candidate_array, int *candidate_size, people *people_array, const int *people_size, election *election_array);

void vote_get_pointer(vote **vote_array, int i, candidate *candidate_array, election *election_array);

void vote_get_locale(vote *vote_array, int i, candidate *candidate_array, election *election_array);

int vote_find_and_read_for_year_number(vote *vote_array, int *vote_size, int year, int code);

int vote_find_and_read_for_year(vote *vote_array, int *vote_size, int year, int uf_size);

int vote_find_time(vote *vote_array, const int *vote_size, char str[]);


#endif //VOTE_H
