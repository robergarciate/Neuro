#include "../includes/redNeuronal.h"

int maxEtapas =0, aleat=0;;
double maxTolerancia=0.0;
datos* adapt=NULL;
int main(int argc, char** argv){
	FILE * f;
	datos* data=NULL;
	double res=0;
	redNeuronal* red=NULL;
	f=fopen(argv[1], "r");
	data= leerDatos(f);

	printf("inicialzacion\n");
	red=iniRedRetropropagacion(data->natributos, 2, data->nclases, 0.5);
	

	printf("test\n");
	res=redTest(data, red,actualizaSalida, 
			actualizaNeuronaSigmoidalBipolar);	
	printf("res: %4.4f\n", res);
	printf("tot: %d\n", data->ndatos);
	printPesos(red);

}