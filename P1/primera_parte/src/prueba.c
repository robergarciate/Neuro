#include "../includes/redNeuronal.h"


int maxEtapas =0, aleat=0;;
double maxTolerancia=0.0;
int main(){
	redNeuronal* r1=NULL;
	redNeuronal* r2=NULL;
	FILE* f=NULL;
	f=fopen("bases-de-datos-p1/problema_real1.txt", "r");
	leerDatos(f);

	f=fopen("bases-de-datos-p1/problema_real2.txt", "r");

	leerDatos(f);
	

}