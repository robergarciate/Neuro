#include "../includes/redNeuronal.h"


int maxEtapas =0, aleat=0;;
double maxTolerancia=0.0;
datos* adapt=NULL;
int nf=0;
int main(int argc, char** argv){
	int i=0;
	//int* cols= columnasRuidosas(10, 3);

	
	datos* data=NULL;
	datos* test=NULL;
	FILE *f= fopen(argv[1], "r");
	data =lectorAlfabetico(f);
	test=copiarDatos(data);
	printDatos(test);
	freeDatos(data);
	freeDatos(test);
	free(data);
	free(test);
	fclose(f);
	liberarLex();
}
