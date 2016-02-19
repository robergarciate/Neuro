#include "../includes/redNeuronal.h"

int main(int argc, char** argv) {
	FILE * fin,* fout= stdout;
    int flagf=0, long_index=0;
    double* pesos; /*pesos de neuronas entre neuronas*/
    double** salidas; /*valores de salida de las neuronas*/
    int* entradas; /*valorede entrada de fichero*/
    char* buffer, opt;
    int i=0, sz, j;
    double ptrain=0.0, ptest=0.0;
    neurona** redNeuronal;
    datos* data=NULL,* train=NULL,* test=NULL;
    static flagPerceptron=0, flagAdaline=0;
    static struct option options[] = {
        {"fin",required_argument,0,'1'},
        {"fout",required_argument,0,'6'},
        {"a", no_argument, &flagAdaline, '2'},
        {"p", no_argument, &flagPerceptron, '3'},
        {"train", required_argument, 0, '4'},
        {"test", required_argument, 0, '5'},
        {0,0,0,0}
    };

    while ((opt = getopt_long_only(argc, argv,"1:", options, &long_index )) != -1){
        switch(opt){
            case '1':
                fin=fopen (optarg, "r");
                flagf=1;
            break;

            case '6':
                fout=fopen (optarg, "w");
            break;
            case '4':
                ptrain=atof(optarg);
            break;
            case '5':
                ptest=atof(optarg);
            break;

            case'?':
                printf("ERROR1: se esperaba ./maCulloch-Pits {-f fin } \n");

            break;
 
        }
    }

    if(fin==NULL || (ptrain==0.0 && ptest==0.0) || ptrain>1 || ptest>1){
        return 1; 
    }

    data = leerDatos(fin);

    if( ptrain+ptest ==1.0){
        particionado(data, train, test, ptrain);
    }
    else{
        printf("por hacer\n");
        return 0;
    }

    printDatos(data);
    freeDatos(data);
    freeDatos(train);
    freeDatos(test);
}