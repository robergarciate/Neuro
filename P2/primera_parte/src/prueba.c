#include "../includes/redNeuronal.h"

int maxEtapas =0, aleat=0;;
double maxTolerancia=0.0;
datos* adapt=NULL;
int main(){
	redNeuronal* r1=NULL;

	r1=iniRedRetropropagacion( 5, 2, 2, 0.2);
	destRed2(r1);
}