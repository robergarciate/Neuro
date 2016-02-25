#include "../includes/redNeuronal.h"

int maxEtapas =0, aleat=0;;
double maxTolerancia=0.0;
int main(){
	redNeuronal* r1=NULL;
	redNeuronal* r2=NULL;
	FILE* f=NULL;
	datos* d =NULL;
	f=fopen("bases-de-datos-p1/problema_real1.txt", "r");
	d=leerDatos(f);
	freeDatos(d);
	fclose(f);
	f=fopen("bases-de-datos-p1/problema_real2_no_etiquetados.txt", "r");
	leerDatos(f);

	freeDatos(d);	

	fclose(f);
}