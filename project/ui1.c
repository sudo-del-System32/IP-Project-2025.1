//
// Created by franc on 09/07/2025.
//

#include "Func_gerais.h"
#include "ui1.h"

#include <stdio.h>
#include <stdlib.h>


input input_menu;
bool error = FALSE;


void input_menu_checker()
{

    if (error == TRUE)
    {
        printf("ERRO: '%s' nao esta entre as opcoes.", input_menu.str);
        error = FALSE;
    }

    //fpurge(stdin); //codigo não compila com esta função
    clean(stdin);
    scanf("%s", input_menu.str);

    input_menu.integer = atoi(input_menu.str);
}




//Functions for menu_start

bool front_to_backend()
{
    var_options option;
    var_types type = Exit_type;

    do
    {
        option = menu_process();
        if (option != Exit_options && option != Vote)
            type = menu_data_types(&option);
    } while (type == Exit_type && option != Vote);

    if (option == Exit_options)
        return FALSE;

    if (option == Vote)
    {
        menu_vote();
        return FALSE;
    }


    if (type == Electors)
    {
    }
    else if (type == Candidate)
    {
    }
    else if (type == Electoral_College)
    {
    }
    else if (type == Election)
    {
    }


    return TRUE;
}


//START
void menu_start()
{
    do
    {
        //for menu things
        system("cls");
        ui_start();

        input_menu_checker();
        if (input_menu.integer != 1 && input_menu.integer != 2)
        {
            error = TRUE;
            continue;
        }
        if (input_menu.integer == 2)
            break;

        front_to_backend();

    } while (1);

    system("cls");
    printf ("\nObrigado por utilizar Daniel's data bank, Boa noite.\n");
}

void ui_start()
{
    printf("\n==================Inicio==================\n\n");

    printf("\t1.Iniciar\n");
    printf("\t2.Sair\n");

    printf("\n==================Inicio==================\n");
}



//Process Choice
var_options menu_process()
{
    var_options temp_option = Exit_options;
    do{

            system("cls");

            ui_process();
            input_menu_checker();


        switch (input_menu.integer)
        {
            case 1:
                temp_option = Vote;
                break;
            case 2:
                temp_option = Create_Data;
                break;
            case 3:
                temp_option = Read_Data;
                break;
            case 4:
                temp_option = Update_Data;
                break;
            case 5:
                temp_option = Delete_Data;
                break;
            case 6:
                temp_option = Exit_options;
                break;
            default:
                error = TRUE;
        }


    }   while (error == TRUE);

    return temp_option;
}


void ui_process()
{
    printf("\n==================Processos==================\n\n");

    printf("\tEscolha um processo: \n");
    printf("\t1.Votar\n");
    printf("\t2.Criar Dados\n");
    printf("\t3.Mostrar Dados\n");
    printf("\t4.Alterar Dados\n");
    printf("\t5.Excluir Dados\n");
    printf("\t6.Voltar\n");

    printf("\n==================Processos==================\n");
}




//VOTAR

void menu_vote()
{
    do{
            system("cls");

            ui_vote();
            input_menu_checker();


        switch (input_menu.integer)
        {
            case 1:
                printf("APERTOU 1");
                break;
            case 2:
                printf("APERTOU 2");
                break;
            case 3:
                break;
            default:
                error = TRUE;
        }


    }   while (error == TRUE);
}


void ui_vote()
{
    printf("\n==================Votar==================\n\n");

    printf("\tEntrar em seu perfil com: \n");
    printf("\t1.CPF: \n");
    printf("\t2.Titulo de Eleitor: \n");
    printf("\t3.Voltar\n");

    printf("\n==================Votar==================\n");
}




//Criar Dados

var_types menu_data_types(const var_options *ptr_option)
{
    var_types tem_type = Exit_type;
    do{

            system("cls");

            char str[12];
            ui_string_choice(str, ptr_option);
            ui_data_types(str);

            input_menu_checker();

        switch (input_menu.integer)
        {
            case 1:
                printf("APERTOU 1");
                tem_type = Electors;
                break;
            case 2:
                printf("APERTOU 2");
                tem_type = Candidate;
                break;
            case 3:
                printf("APERTOU 3");
                tem_type = Electoral_College;
                break;
            case 4:
                printf("APERTOU 4");
                tem_type = Election;
                break;
            case 5:
                tem_type = Exit_type;
                break;
            default:
                error = TRUE;
        }


    }   while (error == TRUE);

    return tem_type;
}



//Data types for multiple menu functions

void ui_data_types(char str[])
{
    printf("\n==================Tipos Dados==================\n\n");

    printf("\tVamos %s qual tipo de dados?\n",str);
    printf("\t1.Eleitor\n");
    printf("\t2.Candidato\n");
    printf("\t3.Unidade Federal\n");
    printf("\t4.Eleicao\n");
    printf("\t5.Voltar\n");

    printf("\n==================Tipos de Dados==================\n");
}

//Function for chosing the string for the ui_data_types

void ui_string_choice(char str[] ,const var_options *ptr_option)
{
    switch (*ptr_option)
    {
        case Create_Data:
            strcpy(str, "criar");
            break;

        case Read_Data:
            strcpy(str, "mostrar");
            break;

        case Update_Data:
            strcpy(str, "alterar");
            break;

        case Delete_Data:
            strcpy(str, "excluir");

            break;

        default:
            exit (-1);
    }
}



