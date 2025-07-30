#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Func_gerais.h"
// #include "Func_gerais.c"
#include "uf1.h"
#include "people.h"
// #include "people.c"
#include "Election.h"
// #include "Election.c"
#include "Candidate.h"
// #include "Candidate.c"
#include "attendance.h"
// #include "attendance.c"
#include "Vote.h"
// #include "Vote.c"
#include "ui1.h"
// #include "ui1.c"




int main()
{
	//UF
	int uf_size;
	uf *uf_array = NULL;
	uf_start(&uf_array, &uf_size);
	//People
	int people_size;
	people *people_array = NULL;
	people_start(&people_array, &people_size);
	//Election
	int election_size;
	election *election_array = NULL;
	election_start(&election_array, &election_size, uf_array);
	//Candidate
	int candidate_size;
	candidate *candidate_array = NULL;
	candidate_start(&candidate_array, &candidate_size, election_array, people_array, people_size, election_size);
	//attendance
	int attendance_size;
	attendance *attendance_array = NULL;
	attendance_start(&attendance_array, &attendance_size, election_array, people_array, people_size, election_size);
	//vote
	int vote_size;
	vote *vote_array = NULL;
	vote_start(&vote_array, &vote_size, candidate_array, election_array);


	menu_start(&uf_array, &uf_size, &people_array, &people_size, &election_array, &election_size, &candidate_array,
	           &candidate_size, &attendance_array, &attendance_size, &vote_array, &vote_size);


	attendance_array_to_file(attendance_array, &attendance_size);
	vote_array_to_file(vote_array, &vote_size);
	candidate_array_to_file(candidate_array, &candidate_size);
	election_array_to_file(election_array, &election_size);
	uf_array_to_file(uf_array, &uf_size);
	people_array_to_file(people_array, &people_size);
	free(uf_array);
	free(people_array);
	free(election_array);
	free(candidate_array);
	free(attendance_array);
	free(vote_array);

	return 0;
}


/*
void free_all(uf *uf_array, FILE *f1, FILE *f2, FILE *f3, FILE *f4)
{
	free(uf_array);
	//free();
	//free();
	//free();
	fclose(f1);
	fclose(f2);
	fclose(f3);
	fclose(f4);
}

*/