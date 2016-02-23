#include "../includes/redNeuronal.h"


int maxEtapas =0;
double maxTolerancia=0.0;
int main(){
	redNeuronal* r1=NULL;
	redNeuronal* r2=NULL;
		
	r1=iniRedPerceptron(9, 0, 2, 2);
	r2= malloc(sizeof(redNeuronal));
	copiaRed(r1, r2);
	printf("1\n");
	destRed2(r2);
	printf("2\n");
	copiaRed(r1, r2);
	destRed2(r2);
	destRed1(r1);

	

}