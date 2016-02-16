#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
typedef struct {
	int natributos;
	int nclases;
	int ndatos;
	double** atributos;
	int** clase;
	
}datos;



datos* iniDatos();

void freeDatos(datos* data);

/**
***	Como me parecia feo reservar mas memoria de la que
***	necesitas en particionado he añadido que las ultimas
***	posiciones +1 de clase y atributos sean NULL, despues
***	voy liberando desde el tamaño de los datos hasta NULL 
***	y asi no perdemos memoria a la hora de liberar ni
***	resrvamos de mas
***
***	Entrada:
***		data-> los datos a ajutar 
***
**/
void liberaEspacioLibre(datos* data);
/**
***	Dados unos datos los divide en particion
***	de entrenamiento y de clasificacion
***	
***	Entradas:
***		data-> los datos de entrada
***		train-> datos donde devolveremos train
***		test-> datos donde devolveremos test
***		porcentaje-> cantidad de datos que iran a train
***	
***	Devuelve:
***		error, exito y esas cosas
***	
**/
int particionado(datos* data, datos* train, datos* test, double porcentaje);

/**
***	Reserva una tupla mas para los datos
***	
***	Entrada:
***		data->datos donde ampliamos la tupla
***	
***	Devuelve:
***		Error, acierto y esas cosas
***	
**/
int reservarTupla(datos* data);

int printDatos(datos* data);

int escribeDatos(datos* data, char* fichero); 
