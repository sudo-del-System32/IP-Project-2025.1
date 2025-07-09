#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "UF.h"

typedef struct podepah
{
    char codigo[50];
    int numero;
}podepah;


int main()
{
    FILE *f = fopen ("Eleitor.bin","rb+");
    if (f == NULL)
    {
        f = fopen ("Eleitor.bin","wb+");
        if (f == NULL)
            exit(-1);
    }

    char str[100] = "Eu odeio minha vida e o jayce de arcane";
    char str2[100];

    fseek (f, 0, SEEK_END);
    fwrite(str,sizeof(str),1,f);

    fseek (f, 0, SEEK_SET);
    fread(str2,sizeof(str),1,f);

    printf("%s\n",str);
    printf("%s\n",str2);

    return 0;
}