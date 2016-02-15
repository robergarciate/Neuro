#include "neurona.h"

typedef struct{
	int entradas;		/*Neuronas en la capa de entrada*/
	int salidas;		/*Neuronas en la capa de salida*/
	int ocultas			/*Neuronas en la capa oculta*/
	double tasa;		/*tasa de aprendizaje*/
	neurona* neuronas; 	/*QUE NO SE NOS PASE QUE AQUI ESTA LA NEURONA DE SESGO*/
}redNeuronal;


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
int actualizaSalida(redNeuronal* red, double (*fActualizacion)(), double* entrada);

/**
***
***	Tener ojo con esto y actulizar pesos de forma adecuada en funcion 
***	de si es un perceptron o una red de Adaline
***
**/
int actualizaPesos(redNeuronal* red);



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
int iniRedPerceptron(redNeuronal* red, int entrada, int salida, int oculta, double tasa);


/**
***
***	Inicializa toda la red y da valores a los pesos iniciales y a los sesgos
***	En las traspas pone que inicializa aleatorio con valores pequeños.
***
***
**/
int iniRedAdaline(redNeuronal* red, int entrada, int salida, int oculta, double tasa);

/**
***
***	Esta funcion devuelve la red ya entrenada
***	El primer argumento indica el tipo de entrada
***
**/
redNeuronal* redTrain(int tentrada,datos* data, int (*fini)(), int (*fsalida)(), int nentreada, int nsalida, int noculta);

/**
***
***	Esta funcion devuelve las salidas esperadas de unos datos.
***
***
**/
int* redTest(datos* data, redNeuronal* red, int (*fsalida)());