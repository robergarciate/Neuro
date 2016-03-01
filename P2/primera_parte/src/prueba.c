#include "../includes/redNeuronal.h"

int maxEtapas =0, aleat=0;;
double maxTolerancia=0.0;
datos* adapt=NULL;
int main(){
	redNeuronal* r1=NULL;
	redNeuronal* r2=NULL;
	FILE* f=NULL;
	datos* d =NULL;
	f=fopen("bases-de-datos-p1/problema-real4.txt", "r");
	d=leerDatos(f);
	escribeDatos(d, "problema-real4.txt");

	fclose(f);
}