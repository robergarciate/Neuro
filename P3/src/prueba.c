#include "../includes/redNeuronal.h"

int maxEtapas =0, aleat=0;;
double maxTolerancia=0.0;
datos* adapt=NULL;
int main(int argc, char** argv){
	datos* data=NULL;
	FILE *f= fopen(argv[1], "r");

	data=leerDatos(f);
	normalizarDatos(data);
	escribeDatos(data, "cosa.txt"); 
	freeDatos(data);
	fclose(f);
	liberarLex();
	/*red=iniRedRetropropagacion(2, 1, 2, 0.5);
	

	actualizaSalida( red, actualizaNeuronaSigmoidalBipolar, res);
	printPesos(red);
	printSalidas(red);
	
	for(i=0; i< 1000; i++){
		actualizaPesosRetropropagacion(red, ret);
		actualizaSalida( red, actualizaNeuronaSigmoidalBipolar, res);
	}
	printPesos(red);*/
	
}