
#include "../includes/lector.h"
extern int yylex();


datos* leerDatos(FILE* fin){
	datos* data;
	int i=0, j=0, k=-1, tok=0;
	extern FILE* yyin;
    extern FILE* yyout;
    extern char* yytext;
    yytext=NULL;
    yyout=NULL;
    yyin=NULL;
	yyin=fin;
	if(yyin==NULL){
		printf("Error al abrir el fichero\n"); 
		return NULL;
	}
	/*LEEMOS TODOS LOS CARACTERES INECESARIOS HASTA ENCONTRAR UN NUMERO*/
	printf("cosa\n");
	while((tok=yylex())==TOK_CARACTER){
	}
	data=iniDatos();
	
	/*LEEMOS CUAL ES EL NUMERO DE ATRIBUTOS*/
	if(tok!=0){
		switch(tok){
			case TOK_DOUBLE:
				fprintf(yyout,"ERROR: el formato del fichero es erroneo");
				printf("se lee double %s\n", yytext );
				return NULL;
			break;
			case TOK_INTEGER:
				printf("se lee entero\n");
				data->natributos=atoi(yytext);
			break;
			case TOK_CARACTER:
			printf("se lee caracter %s \n", yytext );
			break;
		
		}
	}

	/*LEEMOS TODOS LOS CARACTERES INECESARIOS HASTA ENCONTRAR UN NUMERO*/
	while((tok=yylex())==TOK_CARACTER){
	}
	printf("cosa\n");
	/*LEEMOS CUAL ES EL NUMERO DE CLASES */
	if(tok!=0){
		switch(tok){
			case TOK_DOUBLE:
				fprintf(yyout,"ERROR: el formato del fichero es erroneo");
				printf("se lee double %s\n", yytext );
				return NULL;
			break;
			case TOK_INTEGER:
				printf("se lee entero\n");
				data->nclases=atoi(yytext);
			break;
			case TOK_CARACTER:
			printf("se lee caracter %s \n", yytext );
			break;
		
		}
	}

	/*LEEMOS TODOS LOS CARACTERES INECESARIOS HASTA ENCONTRAR UN NUMERO*/

	while((tok=yylex())==TOK_CARACTER){
	}
	/*LEEMOS LOS DATOS*/
	printf("cosa3\n");
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
	yytext=NULL;
	printf("cosa\n");
	return data;
	}