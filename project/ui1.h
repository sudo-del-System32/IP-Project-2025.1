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


bool front_to_backend();



/*
 ** Utilizado para escolha das opções do menu de inicio.
 */
void menu_start();

/*
 ** Utilizado para o output das opções do menu de inicio.
 */
void ui_start();


var_options menu_process();

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
 ** Utilizado para escolha das opções do menu de criar dados.
 */
bool menu_create_data();
var_types menu_data_types(const var_options *ptr_option);

/*
 ** Utilizado para o output das opções do menu de menus que utilizão tipos.
 */
void ui_data_types(char str[]);

void ui_string_choice(char str[] ,const var_options *ptr_option);


#endif //UI1_H
