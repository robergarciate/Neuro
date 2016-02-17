#include "../includes/neurona.h"

neurona* iniNeurona(){
	neurona* n= (neurona*) malloc(sizeof(neurona));
	n->sigma=0.0;
	n->nentradas=0;
	n->pesos=NULL;
	n->entradas=NULL;
	n->salida=0.0;
	return n;
}
int iniNeurona2(neurona* n){
	n->sigma=0.0;
	n->nentradas=0;
	n->pesos=NULL;
	n->entradas=NULL;
	n->salida=0.0;
	return 0;
}

void destroyNeurona(neurona* n){
	free(n->pesos);
	free(n->entradas);
	free(n);
	n=NULL;
}

int setNeurona(neurona* n, double sigma, int nentradas, double* pesos, double** entradas){
	int i=0;
	n->sigma=sigma;
	n->nentradas=nentradas;

	n->pesos= (double*) malloc(sizeof(double)*nentradas);
	n->entradas= (double**) malloc(sizeof(double*)*(nentradas));
	
	for(i=0; i< nentradas; i++){
		n->pesos[i]=pesos[i];
		n->entradas[i]=entradas[i];
	}
	return 0;
}

double getSalida(neurona* n){
	return n->salida;
}

double actualizaNeurona(neurona* n){
	int i=0;
	double val=0.0;
	for(i=0; i< n->nentradas; i++){
		val+=n->pesos[i] * (*n->entradas[i]);
	}
	if (val >= n->sigma){
		n->salida=1.0;
	}
	else{
		n->salida=0.0;	
	}
	return 0;
}

double actualizaNeuronaPerceptron(neurona* n){
	int i=0;
	double val=0.0;
	for(i=0; i< n->nentradas; i++){
		val+=n->pesos[i] * (*n->entradas[i]);
	}
	if (val >= n->sigma){
		n->salida=1.0;
	}
	else if(val < -n->sigma){
		n->salida=-1.0;	
	}
	else{
		n->salida=0.0;	
	}
	return 0;

}


double actualizaNeuronaAdaline(neurona* n){
	int i=0;
	double val=0.0;
	for(i=0; i< n->nentradas; i++){
		val+=n->pesos[i] * (*n->entradas[i]);
	}
	n->salida=val;
	return 0;
}

double actualizaNeuronaEntrada(neurona* n, double valor){
	n->salida=valor;
	return 0.0;
}

void entradasNeurona(neurona* n, double** entradas){
	n->entradas=entradas;
}

void pesosNeurona(neurona* n, double* pesos){
	n->pesos=pesos;
}

void printNeurona(neurona* n){
	int i=0;
	printf("\nsigma=%0.1f\n", n->sigma);
	printf("nentradas=%d\n", n->nentradas);
	printf("salida=%0.1f\n", n->salida);
	printf("pesos:");
	for(i=0; i< n->nentradas; i++){
		printf("%0.1f ", n->pesos[i]);
	}
	printf("\nentradas:");
	for(i=0; i< n->nentradas; i++){
		printf("%0.1f ", *n->entradas[i]);
	}
	printf("\n\n");
	
}

