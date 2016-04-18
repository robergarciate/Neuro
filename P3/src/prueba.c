#include "../includes/redNeuronal.h"


int maxEtapas =0, aleat=0;;
double maxTolerancia=0.0;
datos* adapt=NULL;
int main(int argc, char** argv){
	int i=0;
	//int* cols= columnasRuidosas(10, 3);

	
	datos* data=NULL;
	FILE *f= fopen(argv[1], "r");
	printf("cosa\n");

	data=lectorSerie(f, 2, 2);
	//bipolarizar(data);
	printf("cosa\n");
	//printDatos(data);
	freeDatos(data);
	free(data);
	fclose(f);
}