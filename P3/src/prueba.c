#include "../includes/redNeuronal.h"

int maxEtapas =0, aleat=0;;
double maxTolerancia=0.0;
datos* adapt=NULL;
int main(int argc, char** argv){
	datos* data=NULL;
	FILE *f= fopen(argv[1], "r");
	printf("cosa\n");

	data=lectorAlfabetico(f);
	free(data);
	printf("cosa\n");
	fclose(f);
}