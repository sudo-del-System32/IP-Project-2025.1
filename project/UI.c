
FILE *senha_arquivo()
{
    FILE *f = fopen ("Senha.bin","rb+");
    if (f == NULL)
    {
        f = fopen ("Senha.bin","wb+");
        if (f == NULL)
            exit(-1);
    }
    return f;
}


int senha_verificar()
{
    FILE *f = senha_arquivo();

    fseek (f, 0, SEEK_END);
    char senha_user[ftell(f)], senha_system[ftell(f)];

    fseek (f, 0, SEEK_SET);
    fread (&senha_system, sizeof(senha_system), 1, f);
    fclose(f);


    printf("\nPARA ACESSAR ESTA FUNÇÃO NECESSITA DE UMA SENHA\n\n");
    printf("\nInsira a senha: ");
    scanf("%s",senha_user);


    if (strcmp (senha_user, senha_system) == 0)
    {
        return 1;
    }

    return 0;
}


int check_input_ui(char *input ,int *erro)
{

    if (*erro)
    {
        printf ("\nERRO: NAO EXISTE A OPÇÃO '%c', PORFAVOR TENTE NOVAMENTE\n",*input);
        *erro = 0;
    }

    scanf (" %c", input);
    return atoi (input);
}



int iniciar_ui()
{
    int i = 12;
    int erro = 0;
    int senha_correta = 1;
    char input;



    do{

        menu_iniciar();

        if (!senha_correta)
            printf("\nSENHA ERRADA\n");

        i = check_input_ui(&input , &erro);


        switch (i)
        {
            case 1:
                system("cls");
                do
                {
                    i = votar();
                } while (i);
                break;
            case 2:
                senha_correta = senha_verificar();

                system("cls");
                if (senha_correta)
                {}

                break;
            case 3:
                senha_correta = senha_verificar();

                system("cls");
                if (senha_correta)
                {
                    do
                    {
                        i = alterar_dados();
                    } while (i);
                }

                break;
            case 4:
                system("cls");
                printf ("\nObrigado por utilizar Daniel's data bank, Boa noite.\n");
                return 0;
            default:
                system("cls");
                erro = 1;
        }


    }   while ((i < 1 || i > 4) || !senha_correta);

    return 12;
}


void menu_iniciar()
{
    printf("\n==================Inicio==================\n\n");

    printf("\t1.Votar\n");
    printf("\t2.Mostrar Dados\n");
    printf("\t3.Alterar Dados\n");
    printf("\t4.Sair\n");

    printf("\n==================Inicio==================\n");
}



int alterar_dados()
{
    int i = 13;
    int erro = 0;
    char input;


    do{

        menu_alterar_dados();

        i = check_input_ui(&input , &erro);


        switch (i)
        {
            case 1:
                system("cls");
                uf j;
                uf_input(&j);
                uf_output(&j);
                uf_inserir(&j);
                break;
            case 2:
                system("cls");
                printf("%d",uf_arquivo_qnt(uf_arquivo()));
                break;
            case 3:
                system("cls");
                return 0;
            default:
                system("cls");
                erro = 1;
        }


    }   while (i < 1 || i > 3);

    return 12;
}


void menu_alterar_dados()
{
    printf ("\n===================Alterar=Dados===================\n\n");

    printf ("\t1.Alterar Dados Existentes\n");
    printf ("\t2.Adicionar Dados\n");
    printf ("\t3.Voltar\n");

    printf ("\n===================Alterar=Dados===================\n");
}



int votar()
{
    int i = 13;
    int erro = 0;
    char input;


    do{

        menu_votar();
        i = check_input_ui(&input , &erro);


        switch (i)
        {
            case 1:
                system("cls");
                break;
            case 2:
                system("cls");
                break;
            case 3:
                system("cls");
                return 0;
            default:
                system("cls");
                erro = 1;
        }


    }   while (i < 1 || i > 3);

    return 12;
}


void menu_votar()
{
    printf("\n==================Votar==================\n\n");

    printf ("\t1.CPF\n");
    printf ("\t2.Titulo de Eleitor\n");
    printf ("\t3.Voltar\n");

    printf("\n==================Votar==================\n\n");
}



FILE **arquivos_iniciar()
{
    FILE **temp =(FILE **)malloc(4 * sizeof(FILE *));
    temp[0] = uf_arquivo();
    //temp[1] = eleitor_arquivos();
    //temp[2] = candidato_arquivos();
    //temp[3] = votar_arquivos();

    return temp;
}
