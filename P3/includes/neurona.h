
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <math.h>

typedef struct {
	double umbral;
	int nentradas;
	double* pesos;
	double** entradas;
	double salida;
	double delta;
}neurona;

neurona* iniNeurona();

int iniNeurona2(neurona* n);

void destroyNeurona(neurona* n);

void copiaNeurona(neurona* n1, neurona* n2);

int setNeurona(neurona* n, double umbral, int nentradas, double* pesos, double** entradas);

double getSalida(neurona* n);


double actualizaNeurona(neurona* n);

double actualizaNeuronaPerceptron(neurona* n);

double actualizaNeuronaAdaline(neurona* n);

double actualizaNeuronaEntrada(neurona* n, double valor);

double actualizaNeuronaSigmoidalBipolar(neurona* n);

double actualizaNeuronaLineal(neurona* n);

void entradasNeurona(neurona* n, double ** entradas);

void pesosNeurona(neurona* n, double* pesos);

int copiaPesos(neurona* n1, neurona* n2);

void printNeurona(neurona* n);