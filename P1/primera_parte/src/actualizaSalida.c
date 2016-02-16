#include "../includes/redNeuronal.h"

/*
typedef struct{
	int entradas;		//Neuronas en la capa de entrada
	int salidas;		//Neuronas en la capa de salida
	int ocultas			//Neuronas en la capa oculta
	double tasa;		//Tasa de aprendizaje
	neurona* neuronas; 	//QUE NO SE NOS PASE QUE AQUI ESTA LA NEURONA DE SESGO
}redNeuronal;
*/

/*
***	El segundo argumento es un puntero a funcion, no se si esta bien escrito,
***	en concreto se usan las distintas funciones de actualizacion de neurona.
***
***	Esta funcion tiene que actualizar desde las neuronas de entrada
***	hasta las de salida, lo contrario es para los pesos.
*/

int actualizaSalida(redNeuronal* red, double (*fActualizacion)(neurona*), double* entrada){

	int i = 0;

	if ((red == NULL) || (fActualizacion == NULL) || (entrada == NULL)){
		return 1;
	}

	for(i = 0 ; i < red->entradas ; i++)
		actualizaNeuronaEntrada(&(red->neuronas[i+1]), entrada[i]);

	for(i = red->entradas ; i <= (red->entradas + red->salidas) ; i++)
		(*fActualizacion)(&(red->neuronas[i]));

	return 0;

}