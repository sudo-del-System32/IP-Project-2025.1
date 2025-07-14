//
// Created by franc on 09/07/2025.
//

#include "Func_gerais.h"
#include <stdio.h>
#include <stdlib.h>

#include "uf1.h"


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

    _size = ftell(f) / sizeof(_sizeof_typedata);
    printf("%d\n",_size);
    printf("%d\n",ftell(f));
    printf("%d\n",_sizeof_typedata);
    fclose(f);
    return _size;
}



void input_int(int *p ,const int _size ,const char var_name[] ,const char var_type[])
{
    //_size = n* de digitos
    bool flag;
    char str[_size];

    do{

        for (int i = 0; i < _size; i++)
            str[i] = '\0';

        printf ("Digite o %s do %s: ", var_name, var_type);
        fgets (str, _size, stdin);

        flag = verify_input(str , _size);


        //Verificação especifica do codigo
        if (flag == TRUE)

            for (int i = 0; i < _size; i++)
            {
                if ( str[i] != '\0' && ( str[i] < '0' || '9' < str[i] ) )
                {
                    printf ("ERRO: Campo nao foi preenchido somente com numeros existindo espaços, letras ou simbolos\n\n");
                    flag = FALSE;
                    break;
                }

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

        printf ("Digite o %s do %s: ", var_name, var_type);
        fgets (p, _size, stdin);

        flag = verify_input(p , _size);


    } while (flag == FALSE);


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


//Func_gerais.h

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


/*
void uf_file_to_array(uf *uf_array, const int *uf_size)
{

    FILE *f = ptr_file("uf1.bin");
    fread(uf_array,sizeof(uf),*uf_size,f);
    uf_array_fuller(uf_array ,uf_size);
    fclose(f);
}



void uf_array_to_file(uf *uf_array, const int *uf_size)
{
    FILE *f = ptr_file("uf1.bin");
    for (int i = 0; i < *uf_size; i++)
    {
        if (uf_array[i].status == -1)
        {
            fseek(f,sizeof(uf)*i,SEEK_SET);
            fwrite(&uf_array[i],sizeof(uf),1,f);
            fflush(f);
        }
    }
    fclose(f);
}
*/