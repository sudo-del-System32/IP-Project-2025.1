//
// Created by franc on 09/07/2025.
//

#include "ui1.h"




input input_menu;
bool error = FALSE;


void input_menu_checker()
{

    if (error == TRUE)
    {
        printf("ERRO: '%s' nao esta entre as opcoes.", input_menu.str);
        error = FALSE;
    }

    clean(stdin);
    scanf("%s", input_menu.str);
    getchar();
    clean(stdin);

    input_menu.integer = atoi(input_menu.str);
}




//Functions for menu_start

void front_to_backend(uf **uf_array, int *uf_size, people **people_array, int *people_size, election **election_array, int *election_size, candidate **candidate_array, int *candidate_size, attendance **attendance_array, int *attendance_size, vote **vote_array, int *vote_size)
{
    var_options option;
    var_types type;

    do
    {
        type = Exit_type;
        option = menu_process();
        if (option != Exit_options && option != Vote)
            type = menu_data_types(&option);
    } while (option != Exit_options && option != Vote && type == Exit_type );

    if (option == Exit_options)
        return;

    if (option == Vote)
    {
        menu_vote(vote_array, vote_size, attendance_array, attendance_size, candidate_array, candidate_size, *people_array, people_size, *uf_array, uf_size, *election_array);
        return;
    }


    //Muito ineficiente e feio no codigo e desorganizado, mas unica maneira que eu achei de fazer.
    //Create
    int i;
    if (option == Create_Data)
    {
        clean_stdin();
        if (type == Electors)
        {
            people_create(people_array, people_size);
        }
        else if (type == Candidate)
        {
            candidate_create(candidate_array, candidate_size, *election_array, election_size, *people_array, people_size);
        }
        else if (type == Electoral_College)
        {
            uf_create(uf_array, uf_size);
        }
        else if (type == Election)
        {
            election_create(election_array, election_size, *uf_array, uf_size);
        }
        get_pointer_all(*uf_array, *people_array, *election_array, *election_size, *candidate_array, *candidate_size, vote_array, *vote_size, attendance_array, *attendance_size);
    }
    //Read
    else if (option == Read_Data)
    {
        i = menu_read_options();
        if (i == -1)
            return ;
        if (i == 1)
        {
            if (type == Electors)
            {
                i = people_find(*people_array, people_size);
                if (i == -1)
                    return ;
                do
                {
                    clean_stdin();
                    people_read(*people_array, i);
                    menu_continue();
                } while (error == TRUE);
            }
            else if (type == Candidate)
            {
                i = candidate_find(*candidate_array, candidate_size, *uf_size);
                if (i == -1)
                    return;
                do{
                    menu_continue();
                } while (error == TRUE);
            }
            else if (type == Electoral_College)
            {
                i = uf_find(*uf_array, uf_size);
                if (i == -1)
                    return ;
                do
                {
                    clean_stdin();
                    uf_read(*uf_array, i);
                    menu_continue();
                } while (error == TRUE);
            }
            else if (type == Election)
            {
                i = election_find_input(*election_array, election_size);
                if (i == -1)
                    return ;
                do
                {
                    clean_stdin();
                    election_read(*election_array, i);
                    menu_continue();
                } while (error == TRUE);
            }
        }
        else
        {
            clean_stdin();

            if (type == Electors)
            {
                do
                {
                    clean_stdin();

                    people_read_all(*people_array, people_size);
                    menu_continue();
                } while (error == TRUE);

            }
            else if (type == Candidate)
            {
                do
                {
                    clean_stdin();

                    candidate_read_all(*candidate_array, candidate_size);
                    menu_continue();
                } while (error == TRUE);
            }
            else if (type == Electoral_College)
            {
                do
                {
                    clean_stdin();

                    uf_read_all(*uf_array, uf_size);
                    menu_continue();
                } while (error == TRUE);
            }
            else if (type == Election)
            {
                do
                {
                    clean_stdin();

                    election_read_all(*election_array, election_size);
                    menu_continue();
                } while (error == TRUE);
            }
        }
    }
    //Update
    else if (option == Update_Data)
    {
        if (type == Electors)
        {
            i = people_find(*people_array, people_size);
            if (i == -1)
                return ;
            clean_stdin();
            people_read(*people_array, i);
            people_update(people_array, people_size, i);
            do{
                menu_continue();
            } while (error == TRUE);
        }
        else if (type == Candidate)
        {
            clean_stdin();
            int year, code, number;
            input_int(&year,5,"Ano","qual o candidato participou", FALSE);
            input_int(&code,8,"Codigo do Estado","qual o candidato faz parte", FALSE);
            input_int(&number,3,"Numero","candidato", FALSE);

            i = candidate_find_number_year_code(*candidate_array, candidate_size, year, code, number);
            if (i == -1)
            {
                do{
                    clean_stdin(); //testar
                    printf("Candidato nao exite");
                    menu_continue();
                } while (error == TRUE);
                return ;
            }
            clean_stdin();
            candidate_read(*candidate_array, i);
            candidate_update(candidate_array, candidate_size, i, *election_array, election_size, *people_array, people_size);
            do{
                menu_continue();
            } while (error == TRUE);

        }
        else if (type == Electoral_College)
        {
            i = uf_find(*uf_array, uf_size);
            if (i == -1)
                return ;
            clean_stdin();
            uf_read(*uf_array, i);
            uf_update(uf_array, uf_size, i);
            do{
                menu_continue();
            } while (error == TRUE);


        }
        else if (type == Election)
        {
            i = election_find_input(*election_array, election_size);
            if (i == -1)
                return ;
            clean_stdin();
            election_read(*election_array, i);
            election_update(election_array, election_size, i, *uf_array, uf_size);
            do{
                menu_continue();
            } while (error == TRUE);

        }

    }
    //Delete
    else if (option == Delete_Data)
    {
        if (type == Electors)
        {
            i = people_find(*people_array, people_size);
            if (i == -1)
                return ;
            (*people_array)[i].status = 0;
            do{
                menu_continue();
            } while (error == TRUE);


        }
        else if (type == Candidate)
        {
            clean_stdin();
            int year, code, number;
            input_int(&year,5,"Ano","qual o candidato participou", FALSE);
            input_int(&code,8,"Codigo do Estado","qual o candidato faz parte", FALSE);
            input_int(&number,3,"Numero","candidato", FALSE);

            i = candidate_find_number_year_code(*candidate_array, candidate_size, year, code, number);
            if (i == -1)
            {
                do{
                    clean_stdin();
                    printf("\nCandidato nao exite.\n\n");
                    menu_continue();
                } while (error == TRUE);

                return ;
            }
            (*candidate_array)[i].status = 0;
            do{
                menu_continue();
            } while (error == TRUE);
        }
        else if (type == Electoral_College)
        {
            i = uf_find(*uf_array, uf_size);
            if (i == -1)
                return ;
            (*uf_array)[i].status = 0;
            do{
                menu_continue();
            } while (error == TRUE);
        }
        else if (type == Election)
        {
            i = election_find_input(*election_array, election_size);
            if (i == -1)
                return ;
            (*election_array)[i].status = 0;
            do{
                menu_continue();
            } while (error == TRUE);
        }

    }

}


//START
void menu_start(uf **uf_array, int *uf_size, people **people_array, int *people_size, election **election_array, int *election_size, candidate **candidate_array, int *candidate_size, attendance **attendance_array, int *attendance_size, vote **vote_array, int *vote_size)
{
    do
    {
        //for menu things
        clean_stdin();
        ui_start();

        input_menu_checker();
        if (input_menu.integer != 1 && input_menu.integer != 2)
        {
            error = TRUE;
            continue;
        }
        if (input_menu.integer == 2)
            break;

        front_to_backend(uf_array, uf_size, people_array, people_size, election_array, election_size, candidate_array, candidate_size, attendance_array, attendance_size, vote_array, vote_size);


    } while (TRUE);

    clean_stdin();
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

            clean_stdin();

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

void menu_vote(vote **vote_array, int *vote_size, attendance **attendance_array, int *attendance_size, candidate **candidate_array, int *candidate_size, people *people_array, int *people_size, uf *uf_array, int *uf_size, election *election_array)
{
    do{

        clean_stdin();


        ui_vote();
        input_menu_checker();


        clean_stdin();
        switch (input_menu.integer)
        {
            case 1:
                vote_create(vote_array, vote_size, attendance_array, attendance_size, *candidate_array, candidate_size, people_array, people_size, election_array);
                //do{
                    menu_continue();
                //} while (error == TRUE);
                break;
            case 2:
                vote_results(vote_array, vote_size, attendance_array, attendance_size, uf_array, *uf_size);
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

    printf("\tVamos: \n");
    printf("\t1.Comecar: \n");
    printf("\t2.Ver Resultados: \n");
    printf("\t3.Voltar\n");

    printf("\n==================Votar==================\n");
}

void vote_results(vote **vote_array, int *vote_size, attendance **attendance_array, int *attendance_size, uf *uf_array, int uf_size)
{
    int year = 0;
    int code = 0;
    int i;
    do{
        clean_stdin();


        ui_vote_results();
        input_menu_checker();


        clean_stdin();

        switch (input_menu.integer)
        {
            case 1:
                input_int(&year,5,"Ano","Candidato", FALSE);
                input_int(&code,8,"codigo da UF","Candidato", FALSE);

                i = vote_find_and_read_for_year_number(*vote_array, vote_size, year, code);

                if (i == -1)
                    printf("\n\nNINGUEM VOTOU AINDA\n\n");

                do{
                    menu_continue();
                } while (error == TRUE);

                break;
            case 2:
                input_int(&year,5,"Ano","Candidato", FALSE);

                i = vote_find_and_read_for_year(*vote_array, vote_size, year, uf_size);

                if (i == -1)
                    printf("\n\nNINGUEM VOTOU AINDA\n\n");

                do{
                    menu_continue();
                } while (error == TRUE);

                break;
            case 3:
                input_int(&year,5,"Ano","Candidato", FALSE);
                input_int(&code,8,"codigo da UF","Candidato", FALSE);

                i = attendance_votes_for_uf_year(*attendance_array, attendance_size, year, code, uf_array, uf_size);

                if (i == -1)
                    printf("\n\nNINGUEM VOTOU AINDA\n\n");

                do{
                    menu_continue();
                } while (error == TRUE);

                break;
            case 4:
                input_int(&year,5,"Ano","Candidato", FALSE);

                i = attendance_find_and_read_for_year(*attendance_array, attendance_size, year, uf_size);

                if (i == -1)
                    printf("\n\nNINGUEM VOTOU AINDA\n\n");

                do{
                    menu_continue();
                } while (error == TRUE);
                break;
            case 5:
                break;
            default:
                error = TRUE;
        }


    }   while (error == TRUE);
}


void ui_vote_results()
{
    printf("\n==================Votar==================\n\n");

    printf("\tMostrar: \n");
    printf("\t1.Votos com UF e Ano: \n");
    printf("\t2.Votos com Ano: \n");
    printf("\t3.Quantidade de votos com Ano e UF: \n");
    printf("\t4.Comparecimento com Ano: \n");
    printf("\t5.Voltar\n");

    printf("\n==================Votar==================\n");
}




//Criar Dados

var_types menu_data_types(const var_options *ptr_option)
{
    var_types tem_type = Exit_type;
    do{

            clean_stdin();

            char str[12];
            ui_string_choice(str, ptr_option);
            ui_data_types(str);

            input_menu_checker();

        switch (input_menu.integer)
        {
            case 1:
                tem_type = Electors;
                break;
            case 2:
                tem_type = Candidate;
                break;
            case 3:
                tem_type = Electoral_College;
                break;
            case 4:
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


//UF

void ui_find_uf()
{
    printf("\n==================Procurar==================\n\n");

    printf("\tProcurar a UF por:\n");
    printf("\t1.Codigo\n");
    //printf("\t2.Descricao\n");
    printf("\t2.Sigla\n");
    printf("\t3.Sair\n");

    printf("\n==================Procurar==================\n");

}

int uf_find(uf *uf_array, const int *uf_size)
{
    int i;

    do{

        clean_stdin();

        ui_find_uf();
        if (i == -1)
        {
            printf("\n\n-UF NAO ENCONTRADA-\n\n");
            error = FALSE;
            i = 0;
        }

        input_menu_checker();

        clean_stdin();
        char str[30];
        switch (input_menu.integer)
        {
            case 1:
                input_int(&i,8,"codigo","UF", FALSE);
                i = uf_find_code(uf_array, uf_size, i);
                break;
                /*
            case 2:
                input_char(str, 30, "nome", "UF", FALSE);
                i = uf_find_description(uf_array, uf_size, str);
                break;
                */
            case 2: //3
                input_char(str, 5, "sigla", "UF", FALSE);
                i = uf_find_acronym(uf_array, uf_size, str);
                break;
            case 3: //4
                return -1;
            default:
                error = TRUE;
        }
        if (i == -1)
            error = TRUE;


    }   while (error == TRUE);


    return i;

}

//People

void ui_find_people()
{
    printf("\n==================Procurar==================\n\n");

    printf("\tProcurar por uma pessoa por meio do:\n");
    printf("\t1.CPF\n");
    printf("\t2.Titulo\n");
    printf("\t3.Sair\n");

    printf("\n==================Procurar==================\n");

}

int people_find(people *people_array, const int *people_size)
{
    int i = 0;

    do{

        clean_stdin();

        ui_find_people();
        if (i == -1)
        {
            printf("\n\n-Pessoa NAO ENCONTRADA-\n\n");
            error = FALSE;
            i = 0;
        }

        input_menu_checker();

        clean_stdin();
        char str[15];
        switch (input_menu.integer)
        {
            case 1:
                input_char(str,15,"CPF","Pessoas", FALSE);
                i = people_find_cpf(people_array, people_size, str);
                break;
            case 2:
                input_char(str, 13, "titulo de eleitor", "Pessoas", FALSE);
                i = people_find_titulo(people_array, people_size, str);
                break;
            case 3:
                return -1;
            default:
                error = TRUE;
        }
        if (i == -1)
            error = TRUE;


    }   while (error == TRUE);


    return i;

}

//Election


int election_find_input(election *election_array, const int *election_size)
{
    int year, uf_code;
    clean_stdin();

    input_int(&year,5,"ano","eleicao", FALSE);
    input_int(&uf_code,8,"codigo","UF", FALSE);

    int i = election_find(election_array, election_size, year, uf_code);

    if (i == -1)
    {
        do{
            clean_stdin();
            printf("\n\n-Eleicao NAO ENCONTRADA-\n\n");
            menu_continue();
        } while (error == TRUE);
    }
    return i;

}

//Candidate

void ui_find_candidate()
{
    printf("\n==================Procurar==================\n\n");

    printf("\tListar candidatos de um:\n");
    printf("\t1.Ano e uma UF\n");
    printf("\t2.Ano\n");
    printf("\t3.Sair\n");

    printf("\n==================Procurar==================\n");

}

int candidate_find(candidate *candidate_array, int *candidate_size, int uf_size)
{
    int i = 0;
    do{

        clean_stdin();

        ui_find_candidate();
        if (i == -1)
        {
            printf("\n\n-Candidato NAO ENCONTRADA-\n\n");
            error = FALSE;
            i = 0;
        }

        input_menu_checker();

        clean_stdin();
        int year;
        int uf_code;
        switch (input_menu.integer)
        {
            case 1:
                input_int(&year,5,"Ano","qual o candidato participou", FALSE);
                input_int(&uf_code,8,"Codigo do Estado","qual o candidato faz parte", FALSE);
                i = candidate_find_and_read_for_year_number(candidate_array, candidate_size, year, uf_code);
                break;
            case 2:
                input_int(&year,5,"Ano","qual o candidato participou", FALSE);
                i = candidate_find_and_read_for_year(candidate_array, candidate_size, year, uf_size);
                break;
            case 3:
                return -1;
            default:
                error = TRUE;
        }
        if (i == -1)
            error = TRUE;


    }   while (error == TRUE);


    return i;

}

//menu continue

void menu_continue()
{
    printf("\nClick 1 para continuar\n\n");
    input_menu_checker();
    if (input_menu.integer != 1)
        error = TRUE;
}

void ui_read_options()
{
    printf("\n==================Mostrar==================\n\n");

    printf("\tMostrar: \n");
    printf("\t1.Uma do tipo\n");
    printf("\t2.Todos do tipo\n");
    printf("\t3.Sair\n");

    printf("\n==================Mostrar==================\n");

}


int menu_read_options()
{
    do{
        clean_stdin();
        ui_read_options();
        input_menu_checker();
        switch (input_menu.integer)
        {
            case 1:
                return 1;
            case 2:
                return 2;
            case 3:
                return -1;
            default:
                error = TRUE;
                break;

        }

    } while (TRUE);

}


void get_pointer_all(uf *uf_array, people *people_array, election *election_array, int election_size, candidate *candidate_array, int candidate_size, vote **vote_array, int vote_size, attendance **attendance_array, int attendance_size)
{
    for (int i = 0; i < election_size; i++)
    election_get_pointer(election_array, i, uf_array);

    for (int i = 0; i < candidate_size; i++)
    candidate_get_pointer(candidate_array, i, election_array, people_array);

    for (int i = 0; i < vote_size; i++)
    vote_get_pointer(vote_array, i, candidate_array, election_array);

    for (int i = 0; i < attendance_size; i++)
    attendance_get_pointer(attendance_array, i, election_array, people_array);
}