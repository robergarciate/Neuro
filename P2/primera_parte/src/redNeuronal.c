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
void destRed1(redNeuronal* red){
	int i=0, n=0;
	n= 1+ red->entradas + red->salidas +red->ocultas ;
	for(i=0; i<n; i++){
		destroyNeurona(&red->neuronas[i]);		
	}
	free(red->neuronas);
	free(red);
}

void destRed2(redNeuronal* red){
	int i=0, n=0;
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


int actualizaPesosAdaline(redNeuronal* red, int* t){
	int i=0, j=0;
	double val=0;
	if(red==NULL || t==NULL){
		return 1;
	}
	for(i=0; i<red->salidas; i++){		
		val=actualizaNeuronaAdaline(&red->neuronas[i+1+red->entradas]);
		/*printf("se reajusta la salida %d\n", i);
		*/for(j=0; j<red->entradas; j++){
			(&red->neuronas[i+1+red->entradas])->pesos[j]+= red->tasa*
						(t[i] - val)*red->neuronas[j].salida;
			/*printf("j=%d %2.4f ", j, (&red->neuronas[i+1+red->entradas])->pesos[j]);
			*/
		}

		(&red->neuronas[i+1+red->entradas])->pesos[j]+= red->tasa*(t[i] - val);
		/*printf("j=%d %2.4f\n", j, (&red->neuronas[i+1+red->entradas])->pesos[j]);
		*/
	
		
	} 
	return 0;
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
		actualizaNeuronaEntrada(&(red->neuronas[i]), entrada[i]);

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
	int i=0, fallos=0;
	FILE * f=NULL;
	if(data==NULL || nentreada==0 || nsalida==0){
		return NULL;
	}
	red =(*fini)(nentreada, noculta, nsalida, tasa);


	if(red==NULL){
		return NULL;
	}
	f=fopen("adaptacion.data", "w");
	while((*fParada)(red)){
		/*QUITAR ESO PARA LA ENTREGA*/
		fallos=redTest(adapt, red,fsalida, fActualizacion);
		fprintf(f, "%2.4f\n", (double)fallos/(double)data->ndatos);
		/**/
		for(i=0; i<data->ndatos; i++){
			(*fsalida) (red, (*fActualizacion), data->atributos[i]);
			(*fPesos) (red, data->clase[i]);
		}
	}
	fclose(f);
	return red;
}

double redTest(datos* data, redNeuronal* red,
			int (*fsalida) (redNeuronal*, double (*fActualizacion)(neurona*), double*),
			double (*fActualizacion)(neurona*)){

 	int i=0, j=0;
 	double res=0;
 	/*double aux=0;*/
 	for(i=0; i<data->ndatos; i++){
 		(*fsalida) (red, (*fActualizacion), data->atributos[i]);
 		for(j=0; j<data->nclases; j++){
 			/*aux=(*fActualizacion)(&red->neuronas[j + 1 + red->entradas]) - (double)data->clase[i][j];
 			res+=aux*aux;*/
 			
 			if((double)data->clase[i][j] != red->neuronas[j + 1 + red->entradas].salida){
 				res++;
 				break;
 			}
 		}
 	}
 	/*res= res/data->nclases;*/
 	return res;

}


int clasificar(datos* data, redNeuronal* red,
			int (*fsalida) (redNeuronal*, double (*fActualizacion)(neurona*), double*),
			double (*fActualizacion)(neurona*), FILE* fout){

 	int i=0, j=0, n=0, k=0;
 	char s[32]="";
 	if(fout ==NULL || red==NULL || data==NULL)
 		return 1;
 	n=red->entradas+1+red->salidas+red->ocultas;
 	for(i=0; i<data->ndatos; i++){
 		(*fsalida) (red, (*fActualizacion), data->atributos[i]);
 		for(j= n- red->salidas, k=0; j<n; j++,k=0){

 			sprintf(s, "%1.1f ", red->neuronas[j].salida);
 			while(s[k]!='\0'){
 				fwrite(&s[k++], 1,1, fout); 			
 			}
 		}
 		s[0]='\n';
 		fwrite(&s[0], 1,1, fout);
 	}

 	return 0;

}
					
