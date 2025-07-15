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
	uf *uf_array = (uf *)malloc(uf_size * sizeof(uf));
	uf_file_to_array(uf_array, &uf_size);


	//uf_create(&uf_array, &uf_size);
	//uf_create(&uf_array, &uf_size);
	//uf_create(&uf_array, &uf_size);


	uf_array_to_file(uf_array, &uf_size);
	uf_read(uf_array, 0);
	uf_read(uf_array, 1);
	uf_read(uf_array, 2);

	//menu_start();

	free(uf_array);
	return 0;
}

