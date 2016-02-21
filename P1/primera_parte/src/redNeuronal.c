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
	
	for(i =0; i< (1+entrada+salida); i++){
		iniNeurona2( &(red->neuronas[i]));
	}
	

	/*INICIALIZACION NEURONA DE SESGO*/
	setNeurona(&red->neuronas[0], 0, 0, NULL, NULL);
	actualizaNeuronaEntrada(&(red->neuronas[0]), 1.0);


	/*INICIALIZACION NEURONAS DE ENTRADA*/
	for(i=0; i<entrada; i++){
		setNeurona(&red->neuronas[i+1], 0.0, 0, NULL, NULL);
	}


	/*INICIALIZACION NEURONAS DE SALIDA*/
	pesos= (double*) malloc(sizeof(double)*(entrada+1));	
    salidas= (double**) realloc(salidas, sizeof(double*)*(entrada+1));
    for(i=0; i<entrada+1; i++){
		salidas[i]= &(red->neuronas[i+1]).salida;
	}

	for(i=1+entrada; i<salida+1+entrada; i++){
		for(j=0; j<entrada+1; j++){
			pesos[j]=(double)rand()/(double)RAND_MAX;
		}
        setNeurona(&red->neuronas[i], (double)rand()/(double)RAND_MAX, entrada+1, pesos, salidas);
	}

	return red;
}

int actualizaPesosPerceptron(redNeuronal* red, int* t){
	int i=0, j=0;
	double val=0;
	if(red==NULL || t==NULL){
		return 1;
	}
	for(i=0; i<red->salidas; i++){
		/*printf("esp:%d res:%1.1f\n", t[i], red->neuronas[i+1+red->entradas].salida);
		*/
		val=red->neuronas[i+1+red->entradas].salida;
		
		if( (t[i]==0 && val!=0) || (t[i]==-1 && val!=-1) || (t[i]==1 && val!=1)){
			/*printf("se reajusta la salida %d\n", i);
			*/(&red->neuronas[i])->pesos[0]+= red->tasa*t[i];
			/*printf("%2.4f ", (&red->neuronas[i])->pesos[0]);
			*/for(j=0; j<red->entradas; j++){
				(&red->neuronas[i+1+red->entradas])->pesos[j+1]+= red->tasa* (t[i]-val)*red->neuronas[j+1].salida;
				/*printf("%2.4f ", (&red->neuronas[i+1+red->entradas])->pesos[j+1]);
				*/
			}
			/*printf("\n");
			*/
		}
	} 
	/*printf("\n");
	*/return 0;
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
				return 1;
			}
		}
	}
	/*printf("etapa2:%d\n", etapa);*/
	redpre=NULL;
	return 0;
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



int actualizaSalida(redNeuronal* red, double (*fActualizacion)(neurona*), double* entrada){

	int i = 0;

	if ((red == NULL) || (fActualizacion == NULL) || (entrada == NULL)){
		return 1;
	}
	/*printf("actualiza neuronas de entrada\n");
	*/for(i = 0 ; i < red->entradas ; i++)
		actualizaNeuronaEntrada(&(red->neuronas[i+1]), entrada[i]);

	/*printf("actualiza neuronas de salida\n");
*/
	for(i = red->entradas+1 ; i < (red->entradas + red->salidas)+1 ; i++){
		(*fActualizacion)(&(red->neuronas[i]));
	}

	return 0;

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
	if(data==NULL || nentreada==0 || nsalida==0){
		return NULL;
	}
	red =(*fini)(nentreada, noculta, nsalida, tasa);


	if(red==NULL){
		return NULL;
	}
	while((*fParada)(red)){
		for(i=0; i<data->ndatos; i++){
			(*fsalida) (red, (*fActualizacion), data->atributos[i]);
			(*fPesos) (red, data->clase[i]);
		}

	}
	return red;
}

int redTest(datos* data, redNeuronal* red,
			int (*fsalida) (redNeuronal*, double (*fActualizacion)(neurona*), double*),
			double (*fActualizacion)(neurona*)){

 	int res=0, i=0, j=0;
 	for(i=0; i<data->ndatos; i++){
 		(*fsalida) (red, (*fActualizacion), data->atributos[i]);
 		for(j=0; j<data->nclases; j++){
 			
 			if((double)data->clase[i][j] != red->neuronas[j + 1 + red->entradas].salida){
 				res++;
 				break;
 			}
 		}
 	}

 	return res;

}
