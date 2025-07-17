//
// Created by franc on 09/07/2025.
//

#include "Func_gerais.h"
#include <stdio.h>
#include <stdlib.h>

//#include "uf1.h"


FILE *ptr_file(const char path[])
{
    FILE *f = fopen (path,"rb+");
    if (f == NULL)
    {
        f = fopen (path,"wb+");
        if (f == NULL)
            printf("\nErro na abertura do arquivo %s\n",path);
            exit(-1);
    }

    return f;
}


int file_size(const char path[],const int _sizeof_typedata)
{
    int _size = 0;
    FILE *f = ptr_file(path);
    fseek (f, 0, SEEK_END);

    _size = ftell(f) / _sizeof_typedata;

    fclose(f);
    return _size;
}



void input_int(int *p ,const int _size ,const char var_name[] ,const char var_type[])
{
    //_size = n* de digitos que o numero podera ter
    bool flag;
    char str[_size];

    do{

        for (int i = 0; i < _size; i++)
            str[i] ='\0';

        printf ("\nDigite o %s do %s: ", var_name, var_type);
        clean(stdin);
        gets (str);

        flag = verify_input(str , _size);

        //Verificação especifica do codigo
        if (flag == TRUE)

            for (int i = 0; i < _size; i++)
            {
                if (str[i] != '\0' && (str[i] < '0' || '9' < str[i]))
                {
                    printf ("ERRO: Campo nao foi preenchido somente com numeros existindo espassos, letras ou simbolos\n\n");
                    flag = FALSE;
                    break;
                }
                //if (str[i] != '\n') str[i] = '\0';

            }


    } while (flag == FALSE);

    //Conversão em int

    *p = atoi(str);
}



void input_char(char *p ,const int _size , const char var_name[] ,const char var_type[])
{
    //_size = n* de caracteres
    bool flag;

    do{

        for (int i = 0; i < _size; i++)
            p[i] = '\0';

        printf ("\nDigite o %s do %s: ", var_name, var_type);
        clean(stdin);
        gets (p);
        //fgets (p, _size, stdin);

        flag = verify_input(p , _size);


    } while (flag == FALSE);

    strupr(p);
}



bool verify_input(char str[], const int _size)
{

    if (str[0] == '\0')
    {
        printf ("\nERRO: Campo vazio, tente novamente.\n\n");
        return FALSE;
    }


    if (str[_size-1] != '\0')
    {
        printf ("\nERRO: Campo ultrapassa limites estabelecidos de %d espassos.\n\n",_size-1);
        return FALSE;
    }


    return TRUE;
}

//função destinada a manter todos os sistemas acessiveis

void clean(FILE *_File)
{
    #ifdef unix
        fpurge(_File);
    #else
        fflush(_File);
    #endif
}


