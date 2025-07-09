#ifndef UF_H
#define UF_H

/*
 ** Cabeçarios das funções implementadas no modulo UF.c,
 *
 ** que servem para administrar e criar o tipo UF, principalmente na função main.c do arquivo project.
*/

struct UF
{
	int codigo;
	char descricao[30];
	char sigla[3];
};

typedef struct UF uf;


/*
 ** Retorna um ponteiro para um arquivo que contem os dados de UF.
*/
FILE *uf_arquivo();


/*
 ** Cria na memoria heap uma variavel do tipo UF,
e retorna o ponteiro para essa variavel.
*/
uf *uf_create();


/*
 ** Recebe um ponteiro para variavel do tipo UF
e coloca um \0 no primeiro espaço de memoria de cada variavel do struct.
 */
void uf_esvaziar(uf *p);


/*
 ** Recebe um ponteiro do tipo UF e mostra todas as variaveis dele.
*/
void uf_output(uf *p);


/*
 ** Recebe um ponteiro de UF e pede ao console inputs para suas variaveis.
*/
void uf_input(uf *p);


/*
 ** Recebe um ponteiro de int e pede ao console input para uma variavel
inteira usado para verificação de input de int, mas tbm recebe o nome
para a pergunta
*/
void uf_input_int(int *p ,const int _size ,const char var_name[]);


/*
 ** Recebe um ponteiro de int e pede ao console input para uma variavel
caractere usado para verificação de input de char, , mas tbm recebe o nome
para a pergunta
*/
void uf_input_char(char *p ,const int _size , const char var_name[]);


/*
 ** Recebe um endereço de string e o int tamanho maximo de caracterios da variavel,
Verifica se o input é viavel para variavel codigo de UF
*/
int verificar_input(char str[], const int x);


void uf_inserir (const uf *p);


void uf_retirar (uf *p, int leitura);


#include "uf.c"
#endif //UF_H