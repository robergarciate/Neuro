#include "../includes/redNeuronal.h"


int maxEtapas =0, aleat=0;;
double maxTolerancia=0.0;
datos* adapt=NULL;
int main(int argc, char** argv){
	int i=0;
	//int* cols= columnasRuidosas(10, 3);

	
	datos* data=NULL;
	datos* train=NULL;
	datos* test=NULL;
	FILE *f= fopen(argv[1], "r");
	FILE * fout= fopen("clases.txt", "w");
	printf("cosa\n");

	data=lectorSerie(f, 20, 1);
	//bipolarizar(data);
	train = iniDatos();
	test = iniDatos();
	printf("%d\n", particionado2(data, train, test, 0.5));
	
	printDatos(train);
	printDatos(test);
	freeDatos(data);
	freeDatos(test);
	freeDatos(train);
	free(data);
	free(test);
	free(train);
	fclose(f);
}