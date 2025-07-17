//
// Created by franc on 09/07/2025.
//

#ifndef FUNC_GERAIS_H
#define FUNC_GERAIS_H

//SE SISTEMA UNIX, MacOS ou Linux, PORFAVOR RETIRAR OS // ABAIXO E ATIVAR A DEFINIÇAO
//#define unix

//Debug mode
//#define debug

typedef enum bool
{
    FALSE,
    TRUE
}bool;


/*
 ** Recebe um nome de arquivo, cria-o ou recebe seu ponteiro e o retorna.
 */
FILE *ptr_file(const char path[]);



/*
 ** Recebe um nome de arquivo e o sizeof do tipo de dados que ele contem,
  devolve a quantidade de bytes que o arquivo possu
 */
int file_size(const char path[],const int _sizeof_typedata);



/*
 ** Recebe um ponteiro de int, quantos digitos esse int terá, nome da variavel que estará na pergunta e
  o tipo de variavel que estara na pergunta. Pede o input da variavel do ponteiro de int e a preenche
  com ate _size digitos.
 */
void input_int(int *p ,const int _size ,const char var_name[] ,const char var_type[]);



/*
 ** Recebe um ponteiro de char, quantos digitos esse int terá, nome da variavel que estará na pergunta e
  o tipo de variavel que estara na pergunta. Pede o input da variavel do ponteiro de char e a preenche
  com ate _size digitos.
 */
void input_char(char *p ,const int _size , const char var_name[] ,const char var_type[]);



/*
 ** Verifica se o input ultrapassa o _size e se esta em branco. Retorna false se nao preencher os requisitos e
  True se preencher.
 */
bool verify_input(char str[], const int _size);



/*
 ** Uma funçao para parar a dor de cabeça de mudança de fflush pra fpurge dependendo de seu sistema operacional =)
 */
void clean(FILE *_File);


#endif //FUNC_GERAIS_H
