//
// Created by franc on 22/07/2025.
//

#ifndef ATTENDANCE_H
#define ATTENDANCE_H
#include "people.h"
#include "Election.h"

typedef struct attendance
{
    int people_locale; //PK
    int election_locale; //PK
    people *ptr_people; //PK
    election *ptr_election; //PK

    int year;
    int uf_code;
    char cpf[15];
    char acronym[5];
    int status;
}attendance;



void attendance_start(attendance **attendance_array, int *attendance_size, election *election_array, people *people_array);

void attendance_array_expander(attendance **attendance_array, int *attendance_size);

void attendance_file_to_array(attendance *attendance_array, const int *attendance_size);

void attendance_array_to_file(attendance *attendance_array, const int *attendance_size);

int attendance_array_empty_space_finder(const attendance *attendance_array, const int *attendance_size);

void attendance_create(attendance **attendance_array, int *attendance_size);

void attendance_read(attendance *attendance_array, const int i);

void attendance_read_all(attendance *attendance_array, const int *attendance_size);

void attendance_get_pointer(attendance **attendance_array, int i, election *election_array, people *people_array);

void attendance_get_locale(attendance *attendance_array, int i, election *election_array, people *people_array);

int attendance_find_and_read_for_year(attendance *attendance_array, int *attendance_size, int year, int uf_size);



int attendance_find_and_read_for_year_number(attendance *attendance_array, int *attendance_size, int year, int code);


int attendance_votes_for_uf_year(attendance *attendance_array, int *attendance_size, int year, int uf_code, uf *uf_array, int uf_size);

int attendance_all_quantities(attendance *attendance_array, int *attendance_size, int year, uf *uf_array, int uf_size);




#endif //ATTENDANCE_H
