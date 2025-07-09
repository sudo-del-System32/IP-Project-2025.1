#ifndef UI_H
#define UI_H


/*
 ** Retorna um ponteiro de arquivo com a senha, tal senha pode ser alterada, por meio da alteração do arquivo.
*/
FILE *senha_arquivo();

/*
 ** Pede ao usuario uma string e, retorna 1 se igual ao arquivo oque existe em senha.bin e 0 se diferente.
*/
int senha_verificar();


/*
 ** Pede ao usuario um numero e em caso que seja um caracterio manda uma mensagem de erro.
*/
int check_input_ui(char *input ,int *erro);


/*
 ** Inicia o programa com uma ui personalizada.
*/
int iniciar_ui();


/*
 ** UI utilizada pela func iniciar_ui.
 */
void menu_iniciar();


/*
 ** Abre a UI para alterar e adicionar os dados.
*/
int alterar_dados();


/*
 ** UI utilizada pela func alterar_dados.
*/
void menu_alterar_dados();


/*
 ** Abre a UI para votar.
*/
int votar();


/*
 ** UI utilizada pela func votar.
*/
void menu_votar();


/*
 ** Inicia os arquivos on estao os dados ou os cria e retorna um ponteiro para arquivo.
*/
FILE **arquivos_iniciar();

#include "UI.c"
#endif //UI_H