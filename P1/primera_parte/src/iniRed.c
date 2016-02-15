#include "redNeuronal.h"
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

	/*INICIALIZACION NEURONA DE SESGO*/
	red->neuronas[0]=iniNeurona();
	setNeurona(red->neuronas[0], 0, 0, NULL, NULL);
	actualizaNeuronaEntrada(red->neuronas[0], 1.0);


	/*INICIALIZACION NEURONAS DE ENTRADA*/
	for(i=0; i<entrada; i++){
		red->neuronas[i+1]=iniNeurona();
		setNeurona(red->neuronas[i+1], 0.0, 1, NULL, NULL);
	}

	/*INICIALIZACION NEURONAS DE CAPA OCULTA*/
	pesos= (double*) malloc(sizeof(double)*entrada);	
    salidas= (double**) malloc(sizeof(double*)*entrada);
    for(i=0; i<entrada; i++){
		salidas[i]= &(redNeuronal->neuronas[i+1]->salida);
	}

	for(i=0; i<oculta; i++){
		for(j=0; j<entrada; j++){
			pesos[j]=(double)rand()/(double)RAND_MAX;
		}
		red->neuronas[i+1+entrada]=iniNeurona();
        setNeurona(red->neuronas[i+1+entrada], (double)rand()/(double)RAND_MAX, entrada, pesos, salidas);
	}

	/*INICIALIZACION NEURONAS DE SALIDA*/
	pesos= (double*) malloc(sizeof(double)*entrada);	
    salidas= (double**) realloc(oculta, sizeof(double*));
    for(i=0; i<oculta; i++){
		salidas[i]= &(redNeuronal->neuronas[i+1+entrada]->salida);
	}

	for(i=0; i<oculta; i++){
		for(j=0; j<oculta; j++){
			pesos[j]=(double)rand()/(double)RAND_MAX;
		}
		red->neuronas[i+1+entrada]=iniNeurona();
        setNeurona(red->neuronas[i+1+entrada], (double)rand()/(double)RAND_MAX, entrada, pesos, salidas);
	}

	return 0;
}