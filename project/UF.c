// ARQUIVOS FUNÇOES UFS


#include "UF.h"

FILE *uf_arquivo()
{
	FILE *f = fopen ("UFs.bin","rb+");
	if (f == NULL)
	{	
		f = fopen ("UFs.bin","wb+");
		if (f == NULL)
			exit(-1);
	}	


	return f;
}


//FUÇÕES MEMORIA RAM


uf *uf_create()
{
	uf *p = NULL;
	p = (uf *) malloc (sizeof (uf ) );
	if (p == NULL) exit (-1);
	
	uf_esvaziar (p);
	
	return p;
}


void uf_esvaziar(uf *p)
{
	p->codigo = 0;
	strcpy (p->descricao,"\0");
	strcpy (p->sigla,"\0");
}


void uf_output(uf *p)
{
	printf ("Codigo do UF: %d\n", p->codigo);
	printf ("Descrição do UF: %s\n", p->descricao);
	printf ("Sigla do UF: %s\n", p->sigla);
}


void uf_input(uf *p)
{
	int codigo_size = 5;
	int descricao_size = sizeof (p->descricao);
	int sigla_size = sizeof (p->sigla);

	uf_input_int(&p->codigo, codigo_size, "codigo");

	uf_input_char(p->descricao, descricao_size, "descrição");

	uf_input_char(p->sigla, sigla_size, "sigla");

}

void uf_input_int(int *p ,const int _size ,const char var_name[])
{
	//_size = n* de digitos
	int flag = 1;
	char str[_size];


	do{

		//Utilização desse como substituição do string copy, pois este nao funcionou...
		for (int i = 0; i < _size; i++)
			str[i] = '\0';
		
		printf ("Digite o %s do UF: ", var_name);
		gets (str);
		
		flag = verificar_input(str , _size);
		

		//Verificação especifica do codigo
		if (flag)

			for (int i = 0; i < _size; i++)
			{
				if ( str[i] != '\0' && ( str[i] < '0' || '9' < str[i] ) )
				{
					printf ("ERRO: NUMERO NAO EH INTEIRO OU CONTEM DIGITOS/ESPASSOS\n\n");
					flag = 0;
					break;
				}

			}


	} while (!flag);
	
	//Conversão em int
		
		*p = atoi(str);

}


void uf_input_char(char *p ,const int _size , const char var_name[])
{
	//_size = n* de caracteres
	int flag = 1;

	do{

		//Utilização desse como substituição do string copy, pois este nao funcionou...
		for (int i = 0; i < _size; i++)
			p[i] = '\0';

		printf ("Digite a %s do UF: ", var_name);
		gets (p);

		flag = verificar_input(p , _size);


	} while (!flag);


}


int verificar_input(char str[], const int x)
{

	if (str[0] == '\0')
	{
		printf ("\nERRO: CAMPO VAZIO, TENTE NOVAMENTE\n\n");
		return 0;
	}
	
	
	if (str[x-1] != '\0')
	{
		printf ("\nERRO: NUMERO MUITO GRANDE, LIMITE DE %d DIGITOS\n\n",x-1);
		return 0;
	}


	return 1;
}

void uf_inserir (const uf *p)
{
	FILE *f = uf_arquivo();
	fseek (f, 0, SEEK_END);
	fwrite (p, sizeof(uf), 1, f);
	fclose(f);

}

void uf_retirar (uf *p, int leitura)
{
	FILE *f = uf_arquivo();
	fseek (f, 0, SEEK_SET);
	fread (p, sizeof(uf), leitura, f);
	fclose(f);
}

int uf_arquivo_qnt()
{
	int qnt = 0;
	FILE *f = uf_arquivo();
	fseek (f, 0, SEEK_END);

	qnt = ftell(f) / sizeof(uf);

	fclose(f);
	return qnt;
}