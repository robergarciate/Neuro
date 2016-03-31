#include <stdlib.h>
#include <stdio.h>
double main(int argc, char ** argv) {
	double var1=0.0, var2=0.0;
	if (argc<3){
		return 0.0;
	}
	printf("%1.6f",atof(argv[1])+atof(argv[2]));
}