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
