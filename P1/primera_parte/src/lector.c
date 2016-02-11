
#include "../includes/lector.h"
extern int yylex();

int main(int argc, char** argv){
	datos* data,* train=NULL,* test=NULL;
	int i=0, j=0, k=-1, tok=0;
	extern FILE* yyin;
    extern FILE* yyout;
    extern char* yytext;
    yyin=NULL;
    yyout=NULL;
	yyin=fopen(argv[1],"r");
	if(yyin==NULL){
		printf("Error al abrir el fichero\n"); 
		return 0;
	}
	/*LEEMOS TODOS LOS CARACTERES INECESARIOS HASTA ENCONTRAR UN NUMERO*/
	while((tok=yylex())==TOK_CARACTER){
	}

	data=iniDatos();
	
	/*LEEMOS CUAL ES EL NUMERO DE ATRIBUTOS*/
	if(tok!=0){
		switch(tok){
			case TOK_DOUBLE:
				fprintf(yyout,"ERROR: el formato del fichero es erroneo");
				return 1;
			break;
			case TOK_INTEGER:
				data->natributos=atoi(yytext);
			break;
			case TOK_CARACTER:
			break;
		
		}
	}

	/*LEEMOS TODOS LOS CARACTERES INECESARIOS HASTA ENCONTRAR UN NUMERO*/
	while((tok=yylex())==TOK_CARACTER){
	}

	/*LEEMOS CUAL ES EL NUMERO DE CLASES */
	if(tok!=0){
		switch(tok){
			case TOK_DOUBLE:
				fprintf(yyout,"ERROR: el formato del fichero es erroneo");
				return 1;
			break;
			case TOK_INTEGER:
			printf("1\n");
				data->nclases=atoi(yytext);
			break;
			case TOK_CARACTER:
			break;
		
		}
	}

	/*LEEMOS TODOS LOS CARACTERES INECESARIOS HASTA ENCONTRAR UN NUMERO*/

	while((tok=yylex())==TOK_CARACTER){
	}
	/*LEEMOS LOS DATOS*/
	while(tok!=0){
    	
        switch(tok){
			case TOK_DOUBLE:
				if((j + i) % (data->nclases + data->natributos)==0){
		    		i=0;
		    		j=0;
		    		k++;
		    		reservarTupla(data);
		    	}
				data->atributos[k][i++]=atof(yytext);
			break;
			case TOK_INTEGER:
				if((j + i) % (data->nclases + data->natributos)==0){
		    		i=0;
		    		j=0;
		    		k++;
		    		reservarTupla(data);
		    	}
				if(i<data->natributos)
					data->atributos[k][i++]=atof(yytext);
				
				else
					data->clase[k][j++]=atoi(yytext);
			break;
			case TOK_CARACTER:
			break;
		
		}
		tok=yylex();
	}


	train= iniDatos();
	test= iniDatos();
	particionado(data, train, test, 0.5);

	
	printf("\ntrain\n");
    printDatos(train);
	printf("\ntest\n");
    printDatos(test);
	
	freeDatos(train);
	freeDatos(test);
	freeDatos(data);
	free(yytext);
	fclose(yyin);
	fclose(yyout);

	return 1;
	}