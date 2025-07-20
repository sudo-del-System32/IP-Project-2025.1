//
// Created by franc on 09/07/2025.
//

#ifndef UF1_H
#define UF1_H

//#define manual_code


struct uf
{
    int code; //Pkey
    char description[30]; //*
    char acronym[5]; //Key
    int status; //0 Empty //1 Full //-1 Modified
};

typedef struct uf uf;



/*
 ** Faz tudo preciso para uf_array e size poderem funcionar
 */
void uf_start(uf **uf_array, int *uf_size);


/*
 ** Aumneta o tamanho do array de uf
 */
void uf_array_expander(uf **uf_array, int *uf_size);



/*
 ** Transfere os dados do disco para a memoria ram.
 */
void uf_file_to_array(uf *uf_array, const int *uf_size);



/*
 ** Transfere os dados da memoria ram para o disco.
 */
void uf_array_to_file(uf *uf_array, const int *uf_size);



/*
 ** Retorna um numero inteiro equivalente ao local do array com status == 0.
 */
int uf_array_empty_space_finder(const uf *uf_array, const int *uf_size);



/*
 ** Cria um novo uf.
 */
void uf_create(uf **uf_array, int *uf_size);



/*
 ** Lê um unico uf do array.
 */
void uf_read(uf *uf_array, const int i);



/*
 ** Lê todos os ufs do array.
 */
void uf_read_all(uf *uf_array, const int *uf_size);

/**/
int uf_find_code(const uf *uf_array,const int *uf_size,const int code);

/**/
int uf_find_description(const uf *uf_array,const int *uf_size, char str[]);

/**/
int uf_find_acronym(const uf *uf_array,const int *uf_size, char str[]);

/**/
void uf_update(uf **uf_array, const int *uf_size, const int i);

#endif //UF1_H
