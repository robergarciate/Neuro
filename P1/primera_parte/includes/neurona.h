
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

typedef struct {
	double sigma;
	int nentradas;
	double* pesos;
	double** entradas;
	double salida; 
}neurona;

neurona* iniNeurona();

void destroyNeurona(neurona* n);

int setNeurona(neurona* n, double sigma, int nentradas, double* pesos, double** entradas);

double getSalida(neurona* n);


double actualizaNeurona(neurona* n);

double actualizaNeuronaPerceptron(neurona* n);

double actualizaNeuronaAdaline(neurona* n);

double actualizaNeuronaEntrada(neurona* n, double valor);

void entradasNeurona(neurona* n, double ** entradas);

void pesosNeurona(neurona* n, double* pesos);

void printNeurona(neurona* n);