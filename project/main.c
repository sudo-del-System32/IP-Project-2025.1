#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Func_gerais.h"
#include "Func_gerais.c"
#include "ui1.h"
#include "ui1.c"
#include "uf1.h"
#include "uf1.c"


int main()
{
	//UF
	int uf_size = file_size("uf1.bin", sizeof(uf));
	if(uf_size<0) uf_size = 1;
	uf *uf_array = malloc(sizeof(uf)*(uf_size));
	uf_file_to_array(uf_array, &uf_size);

	//menu_start();

	free(uf_array);
	return 0;
}

