#include "../includes/redNeuronal.h"
#include <time.h>

int iniRedPerceptron(redNeuronal* red, int entrada, int salida, int oculta, double tasa){
	double* pesos= NULL,** salidas= NULL;
	int i=0, j=0;
	if(red==NULL || entrada==0 || salida==0 || oculta==0)
		return 1;

	srand(time(NULL));
	red= malloc(sizeof(redNeuronal));
	red->entradas=entrada;
	red->salidas=salida;
	red->ocultas=oculta;
	red->tasa=tasa;
	red->neuronas=malloc(sizeof(neurona)*(1+entrada+oculta+salida));

	for(i =0; i< (1+entrada+oculta+salida); i++){
		iniNeurona2( &(red->neuronas[i]));
	}
	/*INICIALIZACION NEURONA DE SESGO*/
	setNeurona(&red->neuronas[0], 0, 0, NULL, NULL);
	actualizaNeuronaEntrada(&(red->neuronas[0]), 1.0);


	/*INICIALIZACION NEURONAS DE ENTRADA*/
	for(i=0; i<entrada; i++){
		setNeurona(&red->neuronas[i+1], 0.0, 1, NULL, NULL);
	}

	/*INICIALIZACION NEURONAS DE CAPA OCULTA*/
	pesos= (double*) malloc(sizeof(double)*entrada+1);	
    salidas= (double**) malloc(sizeof(double*)*entrada+1);
    for(i=0; i<entrada+1; i++){
		salidas[i]= &((red->neuronas[i]).salida);
	}

	for(i=0; i<oculta; i++){
		for(j=0; j<entrada+1; j++){
			pesos[j]=(double)rand()/(double)RAND_MAX;
		}
        setNeurona(&red->neuronas[i+1+entrada], (double)rand()/(double)RAND_MAX, entrada+1, pesos, salidas);
	}

	/*INICIALIZACION NEURONAS DE SALIDA*/
	pesos= (double*) malloc(sizeof(double)*entrada);	
    salidas= (double**) realloc(salidas, sizeof(double*)*oculta);
    for(i=0; i<oculta; i++){
		salidas[i]= &(red->neuronas[i+1+entrada]).salida;
	}

	for(i=0; i<oculta; i++){
		for(j=0; j<oculta; j++){
			pesos[j]=(double)rand()/(double)RAND_MAX;
		}
        setNeurona(&red->neuronas[i+1+entrada], (double)rand()/(double)RAND_MAX, entrada, pesos, salidas);
	}

	return 0;
}

int actualizaPesosPerceptron(redNeuronal* red, int* t){
	

}


int actualizaPesosAdaline(redNeuronal* red, int* t){

}