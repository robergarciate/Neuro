#include "../includes/redNeuronal.h"
#include <time.h>

int iniRedPerceptron(redNeuronal* red, int entrada, int salida, double tasa){
	double* pesos= NULL,** salidas= NULL;
	int i=0, j=0;
	if(red==NULL || entrada==0 || salida==0 )
		return 1;

	srand(time(NULL));
	red= malloc(sizeof(redNeuronal));
	red->entradas=entrada;
	red->salidas=salida;
	red->ocultas=0;
	red->tasa=tasa;
	red->neuronas=malloc(sizeof(neurona)*(1+entrada+salida));

	for(i =0; i< (1+entrada+salida); i++){
		iniNeurona2( &(red->neuronas[i]));
	}
	/*INICIALIZACION NEURONA DE SESGO*/
	setNeurona(&red->neuronas[0], 0, 0, NULL, NULL);
	actualizaNeuronaEntrada(&(red->neuronas[0]), 1.0);


	/*INICIALIZACION NEURONAS DE ENTRADA*/
	for(i=0; i<entrada; i++){
		setNeurona(&red->neuronas[i+1], 0.0, 1, NULL, NULL);
	}


	/*INICIALIZACION NEURONAS DE SALIDA*/
	pesos= (double*) malloc(sizeof(double)*entrada);	
    salidas= (double**) realloc(salidas, sizeof(double*)*(entrada+1));
    for(i=0; i<salida; i++){
		salidas[i]= &(red->neuronas[i+1]).salida;
	}

	for(i=0; i<salida; i++){
		for(j=0; j<entrada; j++){
			pesos[j]=(double)rand()/(double)RAND_MAX;
		}
        setNeurona(&red->neuronas[i+1], (double)rand()/(double)RAND_MAX, entrada, pesos, salidas);
	}

	return 0;
}

int actualizaPesosPerceptron(redNeuronal* red, int* t){
	
	return 0;

}


int actualizaPesosAdaline(redNeuronal* red, int* t){
	return 0;
}