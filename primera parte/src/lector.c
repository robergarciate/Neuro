
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

	
	printf("%s\n", yytext);
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
    	
        switch(tok){
			case TOK_DOUBLE:
				if((j + i) % (data->nclases + data->natributos)==0){
		    		i=0;
		    		j=0;
		    		k++;
		    		reservarTupla(data);
		    	}
				printf("TOK_DOUBLE %1.1f k=%d i=%d\n", atof(yytext), k, j);
				data->atributos[k][i++]=atof(yytext);
				printf("cosa que se guarda:%1.1f\n", data->atributos[k][i-1]);
			break;
			case TOK_INTEGER:
				if((j + i) % (data->nclases + data->natributos)==0){
		    		i=0;
		    		j=0;
		    		k++;
		    		reservarTupla(data);
		    	}
				printf("TOK_INTEGER %d  k=%d j=%d\n", atoi(yytext), k, j);
				data->clase[k][j++]=atoi(yytext);
				printf("cosa que se guarda:%d \n", data->clase[k][i-1]);
			break;
			case TOK_CARACTER:
				printf("TOK_CARACTER %s k=%d j=%d i=%d\n", yytext, k, j, i);
			break;
		
		}
		tok=yylex();
	}
	fclose(yyin);

    printDatos(data);
	

	return 1;
	}