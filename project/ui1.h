//
// Created by franc on 09/07/2025.
//

#ifndef UI1_H
#define UI1_H

typedef struct input
{
    int integer;
    char str[2];

}input;

typedef enum menu_options
{
    Vote = 10,
    Create_Data = 20,
    Read_Data = 30,
    Update_Data = 40,
    Delete_Data = 50,
    Exit_options = 60

}var_options;

typedef enum types
{
    Electors = 1,
    Candidate = 2,
    Electoral_College = 3,
    Election = 4,
    Exit_type = 6

}var_types;



/*
 ** Checa o input dos menus, para garantir que existe uma opção e é um numero.
 * Recebe um ponteiro pra inteiro(o qual sera usado no switch), um ponteiro para inteiro da
 * variavel erro(para podermos dizer o input que obteve erro), uma string de caracterios que
 * sera utilizada para falar o input incorreto, um inteiro constante sendo a primeira opção
 * e um inteiro constante sendo a segunda opção.
 */
void input_menu_checker();

/**/
void front_to_backend(uf **uf_array, int *uf_size, people **people_array, int *people_size, election **election_array, int *election_size, candidate **candidate_array, int *candidate_size);



/*
 ** Utilizado para escolha das opções do menu de inicio.
 */
void menu_start(uf **uf_array, int *uf_size, people **people_array, int *people_size, election **election_array, int *election_size, candidate **candidate_array, int *candidate_size);

/*
 ** Utilizado para o output das opções do menu de inicio.
 */
void ui_start();

/*
 ** Utilizado para escolher o tipo de processo que sera feito.
 */
var_options menu_process();

/*
 ** UI do menu process.
 */
void ui_process();

/*
 ** Utilizado para escolha das opções do menu de voto.
 */
void menu_vote();

/*
 ** Utilizado para o output das opções do menu de voto.
 */
void ui_vote();

/*
 ** Utilizado para escolha das opções do menu de tipos dados.
 */
var_types menu_data_types(const var_options *ptr_option);

/*
 ** Utilizado para o output das opções do menu de menus que utilizão tipos.
 */
void ui_data_types(char str[]);

/*
 ** Function for chosing the string for the ui_data_types. Qual comentario
 */
void ui_string_choice(char str[] ,const var_options *ptr_option);

/**/
void ui_find_uf();

/**/
int uf_find(uf *uf_array, const int *uf_size);


void ui_find_people();

int people_find(people *people_array, const int *people_size);

int election_find_input(election *election_array, const int *election_size);

void ui_find_candidate();

int candidate_find(candidate *candidate_array, int *candidate_size, int uf_size);


//MENU CONTINUAR
/**/
void menu_continue();

/**/
void ui_read_options();

/**/
int menu_read_options();


#endif //UI1_H
