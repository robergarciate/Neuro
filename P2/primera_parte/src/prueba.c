#include "../includes/redNeuronal.h"

int maxEtapas =0, aleat=0;;
double maxTolerancia=0.0;
datos* adapt=NULL;
int main(){
	redNeuronal* r1=NULL;
	double cosa[5]={1.0, 1.0, 1.0, 1.0, 1.0};
	int cosa1[2]={1, 1};
	r1=iniRedRetropropagacion( 5, 2, 2, 0.2);
	actualizaSalida(r1, actualizaNeuronaSigmoidalBipolar, cosa);
	actualizaPesosRetropropagacion(r1, cosa1);
	actualizaPesosRetropropagacion(r1, cosa1);

	destRed2(r1);
}