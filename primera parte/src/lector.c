
#include "../includes/lector.h"

extern int yylex();

int main(int argc, char** argv){
	datos* data;
	int i=0, j=0, k=-1, tok=0;
	extern FILE* yyin;
    extern FILE* yyout;
    extern char* yytext;
    extern int yyleng;
    yyin=NULL;
    yyout=stdout;
	yyin=fopen(argv[1],"r");
	if(yyin==NULL){
		printf("Error al abrir el fichero\n"); 
		return 0;
	}

	/*tok=yylex();
	while(tok!=0){
		switch(tok){
			case TOK_DOUBLE:
				printf("TOK_DOUBLE:%s\n", yytext);
			break;
			case TOK_INTEGER:
				printf("TOK_INTEGER:%s\n", yytext);
			break;
			case TOK_CARACTER:
				printf("TOK_CARACTER:%s\n", yytext);
			break;
		
		}

		tok=yylex();
	}*/

	data=iniDatos();
	tok=yylex();
	printf("%s\n", yytext);
	if(tok!=0){
		switch(tok){
			case TOK_DOUBLE:
				fprintf(yyout,"ERROR: el formato del fichero es erroneo",yytext);
			break;
			case TOK_INTEGER:
				data->natributos=atoi(yytext);
			break;
			case TOK_CARACTER:

				printf("TOK_CARACTER\n");
			break;
		
		}
	}
	while((tok=yylex())==TOK_CARACTER){
	}

	
	if(tok!=0){
		switch(tok){
			case TOK_DOUBLE:
				fprintf(yyout,"ERROR: el formato del fichero es erroneo",yytext);
			break;
			case TOK_INTEGER:
				data->nclases=atoi(yytext);
			break;
			case TOK_CARACTER:
				printf("TOK_CARACTER\n");
			break;
		
		}
	}
	while((tok=yylex())==TOK_CARACTER){
	}

	while(tok!=0){
    	printf("i+j= %d %% %d \n", i+j, data->nclases + data->natributos);
    	printf("%d %% %d== %d\n",i+j, data->nclases + data->natributos, (j + i) % (data->nclases + data->natributos) );
    	if((j + i) % (data->nclases + data->natributos)==0){
    		i=0;
    		j=0;
    		k++;
    		reservarTupla(data);
    	}
    	printDatos(data);
    	printf("%d %d %d\n", i, j, k);
        switch(tok){
			case TOK_DOUBLE:
				printf("TOK_DOUBLE %s\n", yytext);
				data->atributos[k][i++]=atof(yytext);
			break;
			case TOK_INTEGER:
				printf("TOK_INTEGER %s\n", yytext);
				data->prediccion[k][j++]=atoi(yytext);
			break;
			case TOK_CARACTER:
				printf("TOK_CARACTER %s\n", yytext);
			break;
		
		}
		printf("i=%d j=%d\n", i, j);
		tok=yylex();
	}
	fclose(yyin);
	

	return 1;
	}