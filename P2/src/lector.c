
#include "../includes/lector.h"
extern int yylex();

int liberarLex(){
    extern char* yytext;
    free(yytext);
    yytext=NULL;
    return 0;
}
datos* leerDatos(FILE* fin){
	datos* data;
	int i=0, j=0, k=-1;
	extern FILE* yyin;
    extern FILE* yyout;
    extern char* yytext;
    int tok=0;
    yyin=fin;
    yyout=stdout;
	if(yyin==NULL){
		printf("Error al abrir el fichero\n"); 
		return NULL;
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
				return NULL;
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
				return NULL;
			break;
			case TOK_INTEGER:
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
	return data;
	}