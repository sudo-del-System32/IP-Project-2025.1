#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Func_gerais.h"
#include "Func_gerais.c"
#include "uf1.h"
#include "uf1.c"
#include "ui1.h"
#include "ui1.c"




int main()
{
	//UF
	int uf_size;
	uf *uf_array;
	uf_start(&uf_array, &uf_size);


	menu_start(&uf_array, &uf_size);


	uf_array_to_file(uf_array, &uf_size);
	free(uf_array);
	return 0;
}


/*
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

*/