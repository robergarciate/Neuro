#include "../includes/neurona.h"

neurona* iniNeurona(){
	neurona* n= (neurona*) malloc(sizeof(neurona));
	n->umbral=0.0;
	n->nentradas=0;
	n->pesos=NULL;
	n->entradas=NULL;
	n->salida=0.0;
	return n;
}
int iniNeurona2(neurona* n){
	n->umbral=0.0;
	n->nentradas=0;
	n->pesos=NULL;
	n->entradas=NULL;
	n->salida=0.0;
	return 0;
}

void destroyNeurona(neurona* n){
	free(n->pesos);
	free(n->entradas);
}
void copiaNeurona(neurona* n1, neurona* n2){
	int i=0;
	if(n1==NULL || n2==NULL){
		return;
	}
	free(n2->pesos);
	free(n2->entradas);
	n2->umbral= n1->umbral;
	n2->nentradas= n1->nentradas;
	n2->salida= n1->salida;
	n2->pesos=malloc(sizeof(double)*n1->nentradas);
	n2->entradas=malloc(sizeof(double*)*n1->nentradas);
	for(i=0; i< n1->nentradas; i++){
		n2->pesos[i]=n1->pesos[i];
		n2->entradas[i]=n1->entradas[i];
	}
}

int setNeurona(neurona* n, double umbral, int nentradas, double* pesos, double** entradas){
	int i=0;
	n->umbral=umbral;
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
	if (val >= n->umbral){
		n->salida=1.0;
	}
	else{
		n->salida=0.0;	
	}
	return val;
}

double actualizaNeuronaPerceptron(neurona* n){
	int i=0;
	double val=0.0;
	if(n->entradas==0)
		return n->salida;
	for(i=0; i< n->nentradas; i++){
		/*printf("\ti:%d %1.4f * %1.4f\n", i, n->pesos[i], *n->entradas[i]);
		*/val+=n->pesos[i] * (*n->entradas[i]);
	}
	/*printf("val:%1.4f umbral:%1.4f", val, n->umbral);
	*/if (val > n->umbral){
		n->salida=1.0;
	}
	else 
		n->salida=-1.0;	
	
	/*printf("salida: %1.4f\n", n->salida);
	*/return val;

}


double actualizaNeuronaAdaline(neurona* n){
	int i=0;
	double val=0.0;
	if(n->entradas==0)
		return n->salida;
	for(i=0; i< n->nentradas; i++){
		val+=n->pesos[i] * (*n->entradas[i]);
	}
	n->salida=val;
	return val;
}

double actualizaNeuronaSigmoidalBipolar(neurona* n){
	int i=0;
	double val=0.0;
	if(n->nentradas==0){
		return n->salida;	
	}
	for(i=0; i< n->nentradas; i++){
		val+=n->pesos[i] * (*n->entradas[i]);
	}
	val = 2 / (1 + exp(-val)) - 1;
	n->salida = val;
	return val; 
}
double actualizaNeuronaLineal(neurona* n){
	int i=0;
	double val=0.0;
	if(n->nentradas==0){
		return n->salida;	
	}
	for(i=0; i< n->nentradas; i++){
		val+=n->pesos[i] * (*n->entradas[i]);
	}
	n->salida = val;
	return val; 
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
	printf("\numbral=%1.4f\n", n->umbral);
	printf("nentradas=%d\n", n->nentradas);
	printf("salida=%1.4f\n", n->salida);
	printf("pesos:");
	for(i=0; i< n->nentradas; i++){
		printf("%d", i);
		printf(" %1.4f\n", n->pesos[i]);
	}
	printf("\nentradas:");
	for(i=0; i< n->nentradas; i++){
		printf("%1.4f ", *n->entradas[i]);
	}
	printf("\n\n");
	
}

