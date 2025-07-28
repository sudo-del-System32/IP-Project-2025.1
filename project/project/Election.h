//
// Created by franc on 18/07/2025.
//

#ifndef ELECTION_H
#define ELECTION_H
#include "uf1.h"


struct election
{
    int year; //Pkey 4 digitos
    uf *ptr_state;  //Skey
    int uf_code;
    char description[67];
    int status;
};

typedef struct election election;


void election_start(election **election_array, int *election_size, uf *uf_array);

void election_array_expander(election **election_array, int *election_size);

void election_file_to_array(election *election_array, const int *election_size);

void election_array_to_file(election *election_array, const int *election_size);

int election_array_empty_space_finder(const election *election_array, const int *election_size);

void election_create(election **election_array, int *election_size, uf *uf_array, int *uf_size);

void election_read(election *election_array, const int i);

void election_read_all(election *election_array, const int *election_size);

int election_find(const election *election_array, const int *election_size, int year, int code);

void election_update(election **election_array, const int *election_size, const int i, uf *uf_array, int *uf_size);

void election_get_pointer(election *election_array, int i, uf *uf_array);

void election_get_uf_code(election *election_array, int i);

#endif //ELECTION_H
