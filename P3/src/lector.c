
#include "../includes/lector.h"
extern int yylex();

int liberarLex(){
    extern char* yytext;
    free(yytext);
    yytext=NULL;
    return 0;
}

datos* lectorAlfabetico(FILE * fin ){
	datos* data=NULL;
	int i=-1, j=0;
	extern FILE* yyin;
    extern FILE* yyout;
    extern char* yytext;
    int tok=0;
   	int nuemeroMagico=35;
    yyin=fin;
    yyout=stdout;
	data=iniDatos();
	data->nclases=nuemeroMagico;
	data->natributos=nuemeroMagico;
	if(yyin==NULL){
		printf("Error al abrir el fichero\n"); 
		return NULL;
	}
	/*LEEMOS TODOS LOS CARACTERES INECESARIOS HASTA ENCONTRAR UN NUMERO*/
	while((tok=yylex())!=0){
		switch(tok){
			case TOK_DOUBLE:
				data->atributos[i][j]=atof(yytext);
				data->clase[i][j++]=atof(yytext);
			break;
			case TOK_INTEGER:
				data->atributos[i][j]=atof(yytext);
				data->clase[i][j++]=atof(yytext);
			break;
			case TOK_CARACTER:
				
			break;

			case TOK_COMENTARIO:
				i++;
				j=0;
				reservarTupla(data);
			break;
		}
	}

	return data;
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
					data->clase[k][j++]=atof(yytext);
			break;
			case TOK_CARACTER:
			break;
		
		}
		tok=yylex();
	}
	return data;
}


void permutaArray(double * array, int tam){
	int i = 0;
	double* aux;

	aux = malloc(sizeof(double) * tam);

	for(i = 0; i < tam; i++){
		aux[i] = array[i];
	}

	for(i = 0; i < tam; i++){
		array[i] = aux[(i + 1) % tam];
	}
	free(aux);

}


datos* lectorSerie(FILE * fin, int prev, int post){
	datos* data;
	double* serie;
	int i=0, k=0, l = 0;
	extern FILE* yyin;
    extern FILE* yyout;
    extern char* yytext;
    int tok=0;	
    int total = prev + post;
    yyin=fin;
    yyout=stdout;

	if(yyin==NULL){
		printf("Error al abrir el fichero\n"); 
		return NULL;
	}

	data=iniDatos();
	data->natributos=prev;
	data->nclases=post;
	serie = malloc(sizeof(double) * total);

	for(l = 0; l < total; l++){
		switch(tok){
			case TOK_DOUBLE:
				serie[l] = atof(yytext);
			break;
		}
		tok=yylex();
	}
	reservarTupla(data);
	for(i = 0; i < data->natributos; i++){
		data->atributos[k][i] = serie[i];
	}
	for(i = 0; i < data->nclases; i++){
		data->clase[k][i] = serie[i];
	}

	tok=yylex();

    /*LEEMOS LOS DATOS*/
	while(tok!=0){
		switch(tok){
			case TOK_DOUBLE:
				reservarTupla(data);
				k++;
				permutaArray(serie, total);
				serie[total - 1] = atof(yytext);
				for(i = 0; i < data->natributos; i++){
					data->atributos[k][i] = serie[i];
				}
				for(i = 0; i < data->nclases; i++){
					data->clase[k][i] = serie[i+prev];
				}
			break;
			case TOK_INTEGER:
			break;
			case TOK_CARACTER:
			break;
		
		}
		tok=yylex();
	}
	free(serie);
	
	return data;
}

