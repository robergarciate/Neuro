#include "../includes/redNeuronal.h"

int maxEtapas =0, aleat=0;;
double maxTolerancia=0.0;
datos* adapt=NULL;
int main(int argc, char** argv){
	double res[2]={0.5,0.5};
	int ret[2]={1.0,-1.0};
	redNeuronal* red=NULL;
	int i=0;
	printf("inicialzacion\n");
	red=iniRedRetropropagacion(2, 1, 2, 0.5);
	

	actualizaSalida( red, actualizaNeuronaSigmoidalBipolar, res);
	printPesos(red);
	printSalidas(red);
	
	for(i=0; i< 1000; i++){
		actualizaPesosRetropropagacion(red, ret);
		actualizaSalida( red, actualizaNeuronaSigmoidalBipolar, res);
	}
	printPesos(red);
	
}