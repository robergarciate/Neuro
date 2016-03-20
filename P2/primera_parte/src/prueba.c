#include "../includes/redNeuronal.h"

int maxEtapas =0, aleat=0;;
double maxTolerancia=0.0;
datos* adapt=NULL;
int main(int argc, char** argv){
	FILE * f;
	datos* data=NULL;
	f=fopen(argv[1], "r");
	data= leerDatos(f);
	normalizarDatos(data);
	printDatos(data);
}