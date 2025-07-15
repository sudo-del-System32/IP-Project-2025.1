//
// Created by franc on 09/07/2025.
//

#ifndef UF1_H
#define UF1_H

struct uf
{
    int code;
    char description[30];
    char acronym[5];
    int status; //0 Empty //1 Full //-1 Modified
};

typedef struct uf uf;






/*
 **
 */
void uf_array_expander(uf **uf_array, int *uf_size);



/**/
void uf_file_to_array(uf *uf_array, const int *uf_size);



/**/
void uf_array_to_file(uf *uf_array, const int *uf_size);



/*
 **
 */
int uf_array_empty_space_finder(const uf *uf_array, const int *uf_size);



/*
 **
 */
void uf_create(uf **uf_array, int *uf_size);



/**/
void uf_read(uf *uf_array, const int i);



/**/
void uf_read_all(uf *uf_array, const int *uf_size);


#endif //UF1_H
