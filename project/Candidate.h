//
// Created by franc on 19/07/2025.
//

#ifndef CANDIDATE_H
#define CANDIDATE_H

typedef struct candidate
{
    int election_year; //Pk*
    int uf_code; //Pk*
    char people_cpf[15]; //Pk*
    int candidate_number; //* 2 digitos

    election *ptr_election;
    uf *ptr_uf;
    people *ptr_people;

    int status;
}candidate;




#endif //CANDIDATE_H
