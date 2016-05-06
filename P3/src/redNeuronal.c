#include "../includes/redNeuronal.h"
#include <time.h>
#include <math.h>

/*ESTA VARIBLE SE USA PARA LAS CONDICIONES DE PARADA*/
redNeuronal* redpre=NULL;
int etapa=0;
double ecmAnt, ecmAhr;


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
	

	
	/*INICIALIZACION NEURONAS DE ENTRADA*/
	for(i=0; i<entrada; i++){
		setNeurona(&red->neuronas[i], 0.0, 0, NULL, NULL);
	}

	/*INICIALIZACION NEURONA DE SESGO*/

	setNeurona(&red->neuronas[entrada], 0, 0, NULL, NULL);
	actualizaNeuronaEntrada(&(red->neuronas[entrada]), 1.0);



	/*INICIALIZACION NEURONAS DE SALIDA*/
	pesos= (double*) malloc(sizeof(double)*(entrada+1));	
    salidas= (double**) realloc(salidas, sizeof(double*)*(entrada+1));
    for(i=0; i<entrada+1; i++){
		salidas[i]= &(red->neuronas[i]).salida;
	}

	for(i=1+entrada; i<salida+1+entrada; i++){
		for(j=0; j<entrada+1; j++){
			if(aleat!=0)
				pesos[j]= (double)rand()/(double)RAND_MAX -0.5;
			else
				pesos[j]=0;
		}
        setNeurona(&red->neuronas[i], aleat!=0 ? (double)rand()/(double)RAND_MAX -0.5 : 0, entrada+1, pesos, salidas);
	}
	free(pesos);
	free(salidas);
	return red;
}

redNeuronal* iniRedRetropropagacion(int entrada, int oculta,int salida, double tasa){
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
	red->ocultas=oculta;
	red->tasa=tasa;
	red->neuronas=malloc(sizeof(neurona)*(2+entrada+salida+oculta));
	
	for(i =0; i< (1+entrada+salida); i++){
		iniNeurona2( &(red->neuronas[i]));
	}

	
	/*INICIALIZACION NEURONAS DE ENTRADA*/
	for(i=0; i<entrada; i++){
		setNeurona(&red->neuronas[i], 0.0, 0, NULL, NULL);
	}

	/*INICIALIZACION NEURONA DE SESGO*/

	setNeurona(&red->neuronas[entrada], 0, 0, NULL, NULL);
	actualizaNeuronaEntrada(&(red->neuronas[entrada]), 1.0);

	/**/
	/*INICIALIZACION NEURONAS DE OCULTA*/
	pesos= (double*) malloc(sizeof(double)*(entrada+2));	
    salidas= (double**) realloc(salidas, sizeof(double*)*(entrada+2));
    for(i=0; i<entrada+2; i++){
		salidas[i]= &(red->neuronas[i]).salida;
	}

	for(i=1+entrada; i<oculta+1+entrada; i++){
		for(j=0; j<entrada+1; j++){
			pesos[j]= (double)rand()/(double)RAND_MAX -0.5;
		}
        setNeurona(&red->neuronas[i], 0, entrada+1, pesos, salidas);
	}

	setNeurona(&red->neuronas[entrada+oculta+1], 0, 0, NULL, NULL);
	actualizaNeuronaEntrada(&(red->neuronas[entrada+oculta+1]), 1.0);

	/*cambiado entrada por oculta*/
	/*INICIALIZACION NEURONAS DE SALIDA*/
	pesos= (double*) realloc(pesos, sizeof(double)*(oculta+1));	
    salidas= (double**) realloc(salidas, sizeof(double*)*(oculta+1));
    for(i=0; i<oculta+1; i++){
		salidas[i]= &(red->neuronas[i+entrada+1]).salida;
	}

	/*Añadido el "+oculta"*/
	for(i=2+entrada+oculta; i<salida+2+entrada+oculta; i++){
		for(j=0; j<1+oculta; j++){
			pesos[j]= (double)rand()/(double)RAND_MAX -0.5;
		}
        setNeurona(&red->neuronas[i], 0, 1+oculta, pesos, salidas);
	}

	free(pesos);
	free(salidas);

	return red;
}

void destRed1(redNeuronal* red){
	int i=0, n=0;
	if(red->ocultas == 0){
		n= 1+ red->entradas + red->salidas ;
	}else{
		n= 2+ red->entradas + red->salidas + red->ocultas;
	}
	for(i=0; i<n; i++){
		destroyNeurona(&red->neuronas[i]);		
	}
	free(red->neuronas);
	free(red);
}

void destRed2(redNeuronal* red){
	int i=0, n=0;
	if(red->ocultas == 0){
		n= 1+ red->entradas + red->salidas ;
	}else{
		n= 2+ red->entradas + red->salidas + red->ocultas;
	}
	n= 1+ red->entradas + red->salidas +red->ocultas;
	for(i=0; i<n; i++){
		destroyNeurona(&(red->neuronas[i]));		
	}
	free(red->neuronas);
}

int copiaRed(redNeuronal* redIn, redNeuronal* redOut){
	int numNeu1=0, i=0;
	if (redIn==NULL|| redOut==NULL){
		return 1;
	}
	numNeu1= 1+ redIn->entradas + redIn->salidas + redIn->ocultas;
	redOut->neuronas= malloc(sizeof(neurona)*numNeu1);
	for(i=0 ; i<numNeu1;i++){
		iniNeurona2(&redOut->neuronas[i]);
	}
	redOut->entradas= redIn->entradas;
	redOut->salidas= redIn->salidas;
	redOut->ocultas= redIn->ocultas;
	redOut->tasa= redIn->tasa;

	/*COPIAMOS LA RED*/
	for(i=0; i< numNeu1; i++){
		copiaNeurona(&redIn->neuronas[i], &redOut->neuronas[i]);
	}
	return 0;
}

double actualizaPesosPerceptron(redNeuronal* red, double* t){
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
			*/for(j=0; j<red->entradas; j++){
				(&red->neuronas[i+1+red->entradas])->pesos[j]+= red->tasa*t[i]*red->neuronas[j].salida;
				/*printf("j=%d %2.4f ", j, (&red->neuronas[i+1+red->entradas])->pesos[j]);
				*/
			}

			(&red->neuronas[i+1+red->entradas])->pesos[j]+= red->tasa*t[i];
			/*printf("j=%d %2.4f\n", j, (&red->neuronas[i+1+red->entradas])->pesos[j]);
			*/
		}
		
	} 
	return 0;
}


double actualizaPesosAdaline(redNeuronal* red, double* t){
	int i=0, j=0;
	double esperado=0, prediccion=0;
	if(red==NULL || t==NULL){
		return 1;
	}
	for(i=0; i<red->salidas; i++){		
		esperado= t[i];
		prediccion=red->neuronas[i+red->entradas+1].salida;
		/*printf("se reajusta la salida %d\n", i);
		*/for(j=0; j<red->entradas+1; j++){
			(&red->neuronas[i+1+red->entradas])->pesos[j]+= red->tasa*
						(esperado - prediccion)*
						(*red->neuronas[i+1+red->entradas].entradas[j]);
			/*printf("j=%d %2.4f ", j, (&red->neuronas[i+1+red->entradas])->pesos[j]);
			*/
		}
		/*printf("j=%d %2.4f\n", j, (&red->neuronas[i+1+red->entradas])->pesos[j]);
		*/
	
		
	} 
	return 0;
}




double actualizaPesosRetropropagacion(redNeuronal* red, double* t){
	double delta = 0.0;
	int i = 0, j = 0, k=0;
	double ecm=0, prediccion=0, esperado=0;
	/*DELTAS DE SALIDA*/ 
	for(i = 2 + red->ocultas + red->entradas, j = 0; i < 2 + red->salidas + red->ocultas + red->entradas; ++i, j++){
		prediccion = red->neuronas[i].salida;
		esperado = (double)t[j];
		ecm += pow(esperado - prediccion,2);
		delta = esperado - prediccion;
		delta *= 0.5 * (1 -prediccion);
		
		delta *= (1 + prediccion);
		
		(&red->neuronas[i])->delta = delta;
	}
	/*DELTAS DE OCULTA*/
	for(k=0, i = 1 + red->entradas; i <  1 + red->entradas + red->ocultas; ++i, k++){
		delta = 0;
		prediccion=red->neuronas[i].salida;
		for(j = red->entradas + 2 + red->ocultas; j < red->salidas + red->entradas + 2 + red->ocultas; ++j){
			delta += red->neuronas[j].delta * red->neuronas[j].pesos[k];
		}
		delta *= 0.5 * (1 + prediccion);

		delta *= (1 - prediccion);

		(&red->neuronas[i])->delta = delta;

	}
	/*PESOS DE SALIDA*/
	for(i = 2+red->entradas+red->ocultas; i < 2+red->entradas+red->ocultas+red->salidas; ++i){
		for(j = 0; j < red->neuronas[i].nentradas; ++j){
			(&red->neuronas[i ])->pesos[j] += red->tasa *
											red->neuronas[i].delta *
											(*red->neuronas[i].entradas[j]);
			
		}
	}
	/*PESOS DE OCULTA*/
	for(i = 1+red->entradas; i < 1+red->entradas+red->ocultas; ++i){
		for(j = 0; j < red->neuronas[i].nentradas; ++j){
			(&red->neuronas[i])->pesos[j] += red->tasa *
											red->neuronas[i].delta *
											(*red->neuronas[i].entradas[j]);
			
			
		}
	}
	return ecm;

}



double actualizaPesosRetropropagacion2(redNeuronal* red, double* t){
	double delta = 0.0;
	int i = 0, j = 0, k=0;
	double ecm=0, prediccion=0, esperado=0;
	/*DELTAS DE SALIDA*/ 
	for(i = 2 + red->ocultas + red->entradas, j = 0; i < 2 + red->salidas + red->ocultas + red->entradas; ++i, j++){
		prediccion = red->neuronas[i].salida;
		esperado = (double)t[j];
		ecm += pow(esperado - prediccion,2);
		delta = esperado - prediccion;
		
		(&red->neuronas[i])->delta = delta;
	}
	/*DELTAS DE OCULTA*/
	for(k=0, i = 1 + red->entradas; i <  1 + red->entradas + red->ocultas; ++i, k++){
		delta = 0;
		prediccion=red->neuronas[i].salida;
		for(j = red->entradas + 2 + red->ocultas; j < red->salidas + red->entradas + 2 + red->ocultas; ++j){
			delta += red->neuronas[j].delta * red->neuronas[j].pesos[k];
		}
		delta *= 0.5 * (1 + prediccion);

		delta *= (1 - prediccion);

		(&red->neuronas[i])->delta = delta;

	}
	/*PESOS DE SALIDA*/
	for(i = 2+red->entradas+red->ocultas; i < 2+red->entradas+red->ocultas+red->salidas; ++i){
		for(j = 0; j < red->neuronas[i].nentradas; ++j){
			(&red->neuronas[i ])->pesos[j] += red->tasa *
											red->neuronas[i].delta *
											(*red->neuronas[i].entradas[j]);
			
		}
	}
	/*PESOS DE OCULTA*/
	for(i = 1+red->entradas; i < 1+red->entradas+red->ocultas; ++i){
		for(j = 0; j < red->neuronas[i].nentradas; ++j){
			(&red->neuronas[i])->pesos[j] += red->tasa *
											red->neuronas[i].delta *
											(*red->neuronas[i].entradas[j]);
			
			
		}
	}
	return ecm;

}



int paradaPerceptron(redNeuronal* red){
	int i=0, j=0, num=0;
	if(redpre==NULL){
		redpre=malloc(sizeof(redNeuronal));
		redpre->entradas=0;
		redpre->ocultas=0;
		redpre->salidas=0;
		copiaRed(red, redpre);
		etapa=0;
		return 1;
	}
	
	if(etapa==maxEtapas){
		destRed1(redpre);
		redpre=NULL;
		return 0;
	}
	if(etapa%100==0)
		printf("etapa:%d\n", etapa);
	num=1 + red->entradas + red->salidas;

	for(i=0; i< num; i++){
		for(j=0;j<red->neuronas[i].nentradas; j++){
			if(red->neuronas[i].pesos[j] != redpre->neuronas[i].pesos[j]){
				destRed2(redpre);
				copiaRed(red, redpre);
				etapa++;
				return 1;
			}
		}
	}
	printf("etapa2:%d\n", etapa);
	/*destRed2(redpre);
	*/free(redpre);
	redpre=NULL;
	return 0;
}



int paradaAdaline(redNeuronal* red){
	int i=0, j=0, num=0;
	if(redpre==NULL){
		redpre=malloc(sizeof(redNeuronal));
		redpre->entradas=0;
		redpre->ocultas=0;
		redpre->salidas=0;
		copiaRed(red, redpre);
		etapa=0;
		return 1;
	}
	
	if(etapa==maxEtapas){
		destRed1(redpre);
		redpre=NULL;
		return 0;
	}
	if(etapa%100==0)
		printf("etapa:%d\n", etapa);
	num=1 + red->entradas + red->salidas;

	for(i=0; i< num; i++){
		for(j=0;j<red->neuronas[i].nentradas; j++){
			if(red->neuronas[i].pesos[j] > redpre->neuronas[i].pesos[j] + maxTolerancia ||
				red->neuronas[i].pesos[j] < redpre->neuronas[i].pesos[j] - maxTolerancia){
				destRed2(redpre);
				copiaRed(red, redpre);
				etapa++;
				return 1;
			}
		}
	}
	printf("etapa2:%d\n", etapa);
	destRed1(redpre);
	redpre=NULL;
	return 0;
}

double absolute(double val){
	if(val<0)
		return -val;
	return val;
}

int paradaRetropropagacion2(redNeuronal* red){
	if (etapa ==0){
		ecmAnt=ecmAhr;
		etapa++;
		return 1;
	}
	if (etapa==maxEtapas)
		return 0;
	etapa++;
	if(absolute(ecmAhr -ecmAnt)>maxTolerancia){
		if(etapa%100==0)
			printf("etapa %d %1.8f ecm:%1.4f\n", etapa, absolute(ecmAnt - ecmAhr), ecmAhr);
		ecmAnt=ecmAhr;
		return 1;
	}

	return 0; 

}

int paradaRetropropagacion(redNeuronal* red){
	if (etapa ==0){
		ecmAnt=ecmAhr;
		etapa++;
		return 1;
	}
	if (etapa==maxEtapas)
		return 0;
	etapa++;
	if(absolute(1.0 - ecmAhr/ecmAnt)>maxTolerancia){
		if(etapa%100==0)
			printf("etapa %d %1.8f ecm:%1.4f\n", etapa, absolute(1.0 - ecmAhr/ecmAnt), ecmAhr);
		ecmAnt=ecmAhr;
		return 1;
	}

	return 0; 

}


int actualizaSalida(redNeuronal* red, double (*fActualizacion)(neurona*), double* entrada){

	int i = 0;

	if ((red == NULL) || (fActualizacion == NULL) || (entrada == NULL)){
		return 1;
	}
	/*printf("actualiza neuronas de entrada\n");
	*/for(i = 0 ; i < red->entradas ; i++)
		actualizaNeuronaEntrada(&(red->neuronas[i]), entrada[i]);

	/*printf("actualiza neuronas de salida\n");
*/

	if(red->ocultas > 0){
		for(i = red->entradas+1 ; i < (red->entradas + red->ocultas + red->salidas +2); i++){
			(*fActualizacion)(&(red->neuronas[i]));
		}
	}
	else{
		for(i = red->entradas+1 ; i < (red->entradas + red->salidas)+1 ; i++){
			(*fActualizacion)(&(red->neuronas[i]));
		}
	}
	return 0;

}




int actualizaSalida2(redNeuronal* red, double (*fActualizacion)(neurona*), double* entrada){

	int i = 0;

	if ((red == NULL) || (fActualizacion == NULL) || (entrada == NULL)){
		return 1;
	}
	/*printf("actualiza neuronas de entrada\n");
	*/for(i = 0 ; i < red->entradas ; i++)
		actualizaNeuronaEntrada(&(red->neuronas[i]), entrada[i]);

	/*printf("actualiza neuronas de salida\n");
*/

	if(red->ocultas > 0){
		for(i = red->entradas+1 ; i < (red->entradas + red->ocultas + red->salidas +2); i++){
			if (i < red->entradas + red->ocultas + 2){
				(*fActualizacion)(&(red->neuronas[i]));
			}
			else{
				actualizaNeuronaLineal(&(red->neuronas[i]));
			}
		}
	}
	else{
		for(i = red->entradas+1 ; i < (red->entradas + red->salidas)+1 ; i++){
			(*fActualizacion)(&(red->neuronas[i]));
		}

	}
	return 0;
}
redNeuronal* redTrain(int tentrada, datos* data,
					redNeuronal* (*fini)(int, int, int, double),
					int (*fsalida) (redNeuronal*, double (*fActualizacion)(neurona*), double*),
					int (*fParada) (redNeuronal*),
					double (*fPesos) (redNeuronal*, double*),
					double (*fActualizacion)(neurona*),
					int nentreada, int nsalida, int noculta, double tasa){

	redNeuronal* red= NULL;
	int i=0, fallos=0;
	FILE * f=NULL,* fecm=NULL;
	double ecm=0;
	if(data==NULL || nentreada==0 || nsalida==0){
		printf("algo raro aha pasado\n");
		printf("%d\n", nentreada);
		printf("%d\n", nsalida);
		return NULL;
	}
	red =(*fini)(nentreada, noculta, nsalida, tasa);


	if(red==NULL){
		return NULL;
	}
	f=fopen("adaptacion.data", "w");

	fecm=fopen("ecm.data", "w");
	while((*fParada)(red)){
		/*QUITAR ESO PARA LA ENTREGA*/
		fallos=redTest(adapt, red,fsalida, fActualizacion);
		fprintf(f, "%2.4f\n", (double)fallos/(double)data->ndatos);
		/**/
		for(i=0, ecm=0; i<data->ndatos; i++){
			(*fsalida) (red, (*fActualizacion), data->atributos[i]);
			ecm+=(*fPesos) (red, data->clase[i]);

		}
		ecmAhr=ecm/(data->ndatos*data->nclases);
		fprintf(fecm, "%1.6f\n",ecm/(data->ndatos*data->nclases) );
	}
	fclose(fecm);
	fclose(f);
	return red;
}

double redTest(datos* data, redNeuronal* red,
			int (*fsalida) (redNeuronal*, double (*fActualizacion)(neurona*), double*),
			double (*fActualizacion)(neurona*)){

 	int i=0, j=0;
 	double res=0;
 	int* salidas= malloc(sizeof(int) * red->salidas);
 	for(i=0; i<data->ndatos; i++){
 		(*fsalida) (red, (*fActualizacion), data->atributos[i]);
 		salidasBipolares(salidas, red);
 		for(j=0; j < red->salidas; j++){
 			if(salidas[j]!=data->clase[i][j]){
 				res++;
 				/*break;*/
 			}
 		} 
 	}
 	free(salidas);
 	return res;

}

void salidasBipolares(int* salida, redNeuronal* red){
	int i=0, pos=2 + red->entradas + red->ocultas;

	for(i=0; i < red->salidas ; i++){
		if(red->neuronas[i+pos].salida<0)
			salida[i] = -1;
		else
			salida[i] = 1;

	}

}

int clasificar(datos* data, redNeuronal* red,
			int (*fsalida) (redNeuronal*, double (*fActualizacion)(neurona*), double*),
			double (*fActualizacion)(neurona*), FILE* fout){

 	int i=0, j=0, k=0;
 	char s[32]="";
 	double  maxRed=-100;
 	int maxR=0;
 	if(fout ==NULL || red==NULL || data==NULL)
 		return 1;
 

 	for(i=0; i<data->ndatos; i++,maxRed=INT_MIN){
 		(*fsalida) (red, (*fActualizacion), data->atributos[i]);
 		for(j=0, maxRed=INT_MIN; j<data->nclases; j++){
 			if(red->ocultas==0){
 				if(maxRed<red->neuronas[j + 1 + red->entradas].salida){
	 				maxRed= red->neuronas[j + 1 + red->entradas].salida;
	 				maxR=j;
	 			}
 			}
 			else{
 				/*printf("%1.4f ", red->neuronas[j + 2 + red->entradas+ red->ocultas].salida);
 				*/if(maxRed<red->neuronas[j + 2 + red->entradas+ red->ocultas].salida){
	 				maxRed= red->neuronas[j + 2 + red->entradas +red->ocultas].salida;
	 				maxR=j;
	 			}
 			}

 		}
 		for(j= 0; j< data->nclases; j++){
 			if(j==maxR)
 				sprintf(s, "1.0 ");
 			else
 				sprintf(s, "-1.0 ");
			k=0;
 			while(s[k]!='\0'){
 				printf("%s\n", s);
 				fwrite(&s[k++], 1,1, fout);
 			}
 		}
 		s[0]='\n';
 		fwrite(&s[0], 1,1, fout);
 	}

 	return 0;

}

int clasificarSerie(datos* data, redNeuronal* red,
			int (*fsalida) (redNeuronal*, double (*fActualizacion)(neurona*), double*),
			double (*fActualizacion)(neurona*), FILE* fout){

 	int i=0, j=0;
 	if(fout ==NULL || red==NULL || data==NULL)
 		return 1;
 
 	for(i=0; i<data->ndatos; i++){
 		(*fsalida) (red, (*fActualizacion), data->atributos[i]);
 		for(j=0; j<data->nclases; j++){
 			fprintf(fout, "%1.4f %1.4f %1.4f ", red->neuronas[j + 2 + red->entradas + red->ocultas].salida, 
 			data->atributos[i][data->natributos-1], data->clase[i][j]);
 
 		}
 		fprintf(fout, "\n");
 	}

 	return 0;

}
int clasificarSerieRetroalimentado(datos* data, redNeuronal* red,
			int (*fsalida) (redNeuronal*, double (*fActualizacion)(neurona*), double*),
			double (*fActualizacion)(neurona*), FILE* fout){

 	int i=0, j=0;
 	double* t = NULL;
 	/*Por ahora esto es numero magico*/
 	int iteraciones = nf;
 	if(fout ==NULL || red==NULL || data==NULL){
 		printf("fallo\n");
 		return 1;
 	}
 
 	t = malloc(sizeof(double) * data->natributos);
 	for(i = 0; i < data->natributos; i++){
 		t[i] = data->atributos[0][i];
 	}

 	for(i=0; i<iteraciones; i++){
 		(*fsalida) (red, (*fActualizacion), t);
 		for(j=0; j < data->natributos; j++){
 			fprintf(fout, "%1.4f ", t[j]);
 		}
 		for(j=0; j< data->nclases; j++){
 			fprintf(fout, "%1.4f ", red->neuronas[j + 2 + red->entradas + red->ocultas].salida);
 
 		}
 		fprintf(fout, "%1.4f\n", data->clase[i][0]);
 		for(j = 0; j < data->natributos; j++){
 			t[j]=t[j+1];
 		}
 		for(j= 0; j< red->salidas; j++){

 			t[j +red->entradas - red->salidas] = red->neuronas[j + 2 + red->entradas + red->ocultas].salida;
 		}
 	}
 	free(t);
 	return 0;

}					



void printSalidas(redNeuronal* red){

	int i=0;
	printf("salida ocultas:\n");
	for(i=1+red->entradas; i< 1+red->entradas+ red->ocultas; i++){
		printf("%1.4f ", red->neuronas[i].salida);
	}
	printf("\nsalida de la red:\n");
	for(i=2+red->entradas+ red->ocultas; i< 2+red->entradas+ red->ocultas+red->salidas; i++){
		printf("%1.4f ", red->neuronas[i].salida);
	}
	printf("\n");
}



void printPesos(redNeuronal * red){
	int i=0, j=0;
	neurona n;
	printf("entradas %d\n", red->entradas);
	printf("salidas %d\n", red->salidas);
	printf("ocultas %d\n", red->ocultas);
	printf("pesos\n");
	printf("ocultas:\n");
	for(i=0; i< red->ocultas; i++){
		n=red->neuronas[red->entradas+1 +i];
		for(j=0; j<n.nentradas; j++){
			printf("%1.4f ", n.pesos[j]);
		}
		printf("\n");
	}

	printf("salidas:\n");
	for(i=0; i< red->salidas; i++){
		if(red->ocultas==0)
			n=red->neuronas[red->entradas+1 +i];
		else
			n=red->neuronas[red->entradas+ red->ocultas +2 +i];
		for(j=0; j<n.nentradas; j++){
			printf("%1.4f ", n.pesos[j]);
		}
		printf("\n");
	}
	printf("\n");
}
