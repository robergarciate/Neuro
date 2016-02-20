#include "../includes/redNeuronal.h"
#include <time.h>

/*ESTA VARIBLE SE USA PARA LAS CONDICIONES DE PARADA*/
redNeuronal* redpre=NULL;
int etapa=0;

redNeuronal* iniRedPerceptron(int entrada, int oculta,int salida, double tasa){
	double* pesos= NULL,** salidas= NULL;
	int i=0, j=0;
	redNeuronal* red=NULL;
	if( entrada==0 || salida==0 )
		return NULL;
	if(red==NULL){
		red= malloc(sizeof(redNeuronal));
	}
	srand(time(NULL));
	red->entradas=entrada;
	red->salidas=salida;
	red->ocultas=0;
	red->tasa=tasa;
	red->neuronas=malloc(sizeof(neurona)*(1+entrada+salida));
	
	printf("inicializados valores de la red\n");
	for(i =0; i< (1+entrada+salida); i++){
		iniNeurona2( &(red->neuronas[i]));
	}
	
	printf("creadas neuronas\n");

	/*INICIALIZACION NEURONA DE SESGO*/
	setNeurona(&red->neuronas[0], 0, 0, NULL, NULL);
	actualizaNeuronaEntrada(&(red->neuronas[0]), 1.0);

	printf("inicializada neurons de sesgo\n");

	/*INICIALIZACION NEURONAS DE ENTRADA*/
	for(i=0; i<entrada; i++){
		setNeurona(&red->neuronas[i+1], 0.0, 0, NULL, NULL);
	}

	printf("inicializadas neuronas de entrada\n");

	/*INICIALIZACION NEURONAS DE SALIDA*/
	pesos= (double*) malloc(sizeof(double)*(entrada+1));	
    salidas= (double**) realloc(salidas, sizeof(double*)*(entrada+1));
    for(i=0; i<salida; i++){
		salidas[i]= &(red->neuronas[i+1]).salida;
	}

	for(i=0; i<salida; i++){
		for(j=0; j<entrada; j++){
			pesos[j]=(double)rand()/(double)RAND_MAX;
		}
        setNeurona(&red->neuronas[i+1], (double)rand()/(double)RAND_MAX, entrada+1, pesos, salidas);
	}
	printf("inicializadas neuronas de salida\n\n");

	return red;
}

int actualizaPesosPerceptron(redNeuronal* red, int* t){
	int i=0, j=0;
	if(red==NULL || t==NULL){
		printf("ha devuelto mal\n");
		return 1;
	}
	printf("salidas\n");
	for(i=0, j=0; i<red->salidas; i++){
		printf("esp:%d res:%1.1f\n", t[i], red->neuronas[i+1+red->entradas].salida);
		if(t[i]!=red->neuronas[i+1+red->entradas].salida)
			j=1;
	}
	if(j==0)
		return 0;

	for(i=0; i<red->salidas; i++){
		(&red->neuronas[i])->pesos[0]+= t[i];
		for(j=0; j<red->entradas; j++){
			(&red->neuronas[i])->pesos[j+1]+= red->tasa*t[i]*red->neuronas[j+1].salida;
			
		}
	} 
	return 0;
}


int actualizaPesosAdaline(redNeuronal* red, int* t){
	int i=0, j=0;
	if(red==NULL || t==NULL){
		return 1;
	}

	for(i=0; i<red->salidas; i++){	/*	 tj	 - y_inj*/
		(&red->neuronas[i])->pesos[0]+= t[i] - red->neuronas[i+1+red->entradas].salida;
		for(j=0; j<red->entradas; j++){				/*	     tj - y_inj*/
			(&red->neuronas[i])->pesos[j+1]+= red->tasa * (t[i] - red->neuronas[i+1+red->entradas].salida) * red->neuronas[j+1].salida;
			
		}
	} 
	return 0;
}


int copiaRed(redNeuronal* redIn, redNeuronal* redOut){
	int numNeu1=0, numNeu2=0, i=0;
	if (redIn==NULL|| redOut==NULL){
		return 1;
	}
	numNeu1= redIn->entradas + redIn->salidas + redIn->ocultas;
	numNeu2= redOut->entradas + redOut->salidas + redOut->ocultas;
	/*REDIMENSIONAMOS LA RED*/
	if(numNeu1!=numNeu2){
		for(i=0; i<numNeu2+1; i++){
			destroyNeurona(&redOut->neuronas[i]);
		}
		free(redOut->neuronas);
		redOut->neuronas=malloc(sizeof(neurona)*(numNeu1+1));

	}
	redOut->entradas= redIn->entradas;
	redOut->salidas= redIn->salidas;
	redOut->ocultas= redIn->ocultas;
	redOut->tasa= redIn->tasa;
	for(i =0; i< numNeu1+1; i++){
		iniNeurona2( &(redOut->neuronas[i]));
		setNeurona(&redOut->neuronas[i], redOut->neuronas[i].sigma, redOut->neuronas[i].nentradas, redOut->neuronas[i].pesos, NULL);
	}
	return 0;
}

int paradaPerceptron(redNeuronal* red){
	int i=0, j=0, num=0;
	if(redpre==NULL){
		redpre=iniRedPerceptron( red->entradas, 0, red->salidas, red->tasa);
		copiaRed(red, redpre);
		etapa=0;
		return 1;
	}
	/**/
	if(etapa==MAX_ETAPAS){

		redpre=NULL;
		return 0;
	}
	num=1+ red->entradas + red->salidas;
	for(i=0; i< num; i++){
		for(j=0;j<red->neuronas[i].nentradas; j++){
			if(red->neuronas[i].pesos[j] != redpre->neuronas[i].pesos[j]){
				copiaRed(red, redpre);
				etapa++;
				return 0;
			}
		}
	}

	redpre=NULL;
	return 1;
}



int paradaAdaline(redNeuronal* red){
	int i=0, j=0, num=0;
	if(redpre==NULL){
		redpre=iniRedPerceptron(red->entradas, 0, red->salidas, red->tasa);
		copiaRed(red, redpre);
		etapa=0;
		return 0;
	}
	/**/
	if(etapa==MAX_ETAPAS){

		redpre=NULL;
		return 1;
	}
	num=1+ red->entradas + red->salidas;
	for(i=0; i< num; i++){
		for(j=0;j<red->neuronas[i].nentradas; j++){
			if(redpre->neuronas[i].pesos[j] - MAX_TOLERANCIA > red->neuronas[i].pesos[j]
				&& redpre->neuronas[i].pesos[j] + MAX_TOLERANCIA < red->neuronas[i].pesos[j]) { 
				copiaRed(red, redpre);
				etapa++;
				return 0;
			}
		}
	}

	redpre=NULL;
	return 1;
}




void printSalidas(redNeuronal* red){

	int i=0, j=0;

	if (red==NULL)
		return;
	printf("\n");
	printf("%1.1f\n", red->neuronas[0].salida);
	j= 1 + red->entradas;
	for(i=1 ; i<red->entradas+1; i++){
		if(j>= red->entradas+1 +red->salidas)
			printf("%1.1f\n", red->neuronas[i].salida);
		else
			printf("%1.1f\t %1.1f\n", red->neuronas[i].salida, red->neuronas[j++].salida);
	}
	printf("\n");
}


redNeuronal* redTrain(int tentrada, datos* data,
					redNeuronal* (*fini)(int, int, int, double),
					int (*fsalida) (redNeuronal*, double (*fActualizacion)(neurona*), double*),
					int (*fParada) (redNeuronal*),
					int (*fPesos) (redNeuronal*, int*),
					double (*fActualizacion)(neurona*),
					int nentreada, int nsalida, int noculta, double tasa){

	redNeuronal* red= NULL;
	int i=0;
	printf("ndatos:%d\n",data->ndatos );
	if(data==NULL || nentreada==0 || nsalida==0){
		return NULL;
	}
	red =(*fini)(nentreada, noculta, nsalida, tasa);

	if(red==NULL){
		printf("cosa\n");
		return NULL;
	}
	printf("ndatos:%d\n",data->ndatos );
	printf("compuebca parada\n");
	while((*fParada)(red)){
		for(i=0; i<data->ndatos; i++){
			printf("actualiza salida\n");
			(*fsalida) (red, (*fActualizacion), data->atributos[i]);
			printSalidas(red);
			printf("actualiza pesos\n");
			(*fPesos) (red, data->clase[i]);
		}
		printf("compuebca parada\n");

	}
	printf("fin\n");
	return red;
}

