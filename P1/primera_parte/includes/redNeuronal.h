#include "neurona.h"
#include "datos.h"

#define ADALINE 0
#define PERCEPTRON 1

typedef struct{
	int entradas;		/*Neuronas en la capa de entrada*/
	int salidas;		/*Neuronas en la capa de salida*/
	int ocultas;		/*Neuronas en la capa oculta*/
	double tasa;		/*tasa de aprendizaje*/
	neurona* neuronas; 	/*QUE NO SE NOS PASE QUE AQUI ESTA LA NEURONA DE SESGO*/
}redNeuronal;

extern int maxEtapas;
extern int aleat;
extern double maxTolerancia;
/**
***	No hay mucha diferencia entre una inicializacion y otra.
***	Si despues hacemos graficas sobre la valocidad con la 
***	que aprende una red y otra probar si alguna inicializacion
***	es mejor.
**/

/**
***
***	Inicializa toda la red y da valores a los pesos iniciales y a los sesgos
***	En las traspas pone que inicializa a cero.
***
***
**/
redNeuronal* iniRedPerceptron(int entrada, int oculta, int salida, double tasa);



/**
***
***	Inicializa toda la red y da valores a los pesos iniciales y a los sesgos
***	En las traspas pone que inicializa aleatorio con valores pequeños.
***
***
**/
redNeuronal* iniRedAdaline( int entrada, int salida, int oculta, double tasa);

void destRed1(redNeuronal* red);

void destRed2(redNeuronal* red);

int copiaRed(redNeuronal* redIn, redNeuronal* redOut);

/**
***
***
***	El segundo argumento es un puntero a funcion, no se si esta bien escrito,
***	en concreto se usan las distintas funciones de actualizacion de neurona.
***
***	Esta funcion tiene que actualizar desde las neuronas de entrada
***	hasta las de salida, lo contrario es para los pesos.
***
***
***
**/
int actualizaSalida(redNeuronal* red, double (*fActualizacion)(neurona*), double* entrada);

/**
***
***	Tener ojo con usar una actulizacion bipolar
***
**/
int actualizaPesosPerceptron(redNeuronal* red, int* t);

int actualizaPesosAdaline(redNeuronal* red, int* t);


/**
***
***	Funciona con 2 cosas
***	una variable global que guarda el estado de la red anterior
***	el numero de etaps que han transcurrido
***
***
**/

int paradaPerceptron(redNeuronal* red);

int paradaAdaline(redNeuronal* red);
/**
***
***	Esta funcion devuelve la red ya entrenada
***	El primer argumento indica el tipo de entrada
***
**/

redNeuronal* redTrain(int tentrada,datos* data,
					redNeuronal* (*fini)(int, int, int, double),
					int (*fsalida) (redNeuronal*, double (*fActualizacion)(neurona*), double*),
					int (*fParada) (redNeuronal*),
					int (*fPesos) (redNeuronal*, int*),
					double (*fActualizacion)(neurona*),					
					int nentreada, int nsalida, int noculta, double tasa);
/**1
***
***	Esta funcion devuelve las salidas esperadas de unos datos.
***
***
**/
int redTest(datos* data, redNeuronal* red,
			int (*fsalida) (redNeuronal*, double (*fActualizacion)(neurona*), double*),
			double (*fActualizacion)(neurona*));
					

int clasificar(datos* data, redNeuronal* red,
			int (*fsalida) (redNeuronal*, double (*fActualizacion)(neurona*), double*),
			double (*fActualizacion)(neurona*), FILE* fout);
					

void printSalidas(redNeuronal* red);