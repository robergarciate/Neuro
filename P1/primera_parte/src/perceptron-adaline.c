#include "../includes/redNeuronal.h"

int main(int argc, char** argv) {
	FILE * fin,* fout= NULL;
    int flagf=0, long_index=0;
    double* pesos; /*pesos de neuronas entre neuronas*/
    double** salidas; /*valores de salida de las neuronas*/
    int* entradas; /*valorede entrada de fichero*/
    char* buffer, opt;
    int i=0, sz, j;
    double ptrain=0.0, ptest=0.0;
    redNeuronal* red=NULL;
    datos* data=NULL,* train=NULL,* test=NULL;
    static int flagPerceptron=0, flagAdaline=0;
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
        printf("asdas\n");
        return 1; 

    }
    if(fout==NULL)
        fout=stdout;
    data = leerDatos(fin);
    printDatos(data);
    train=iniDatos();
    test=iniDatos();
    bipolarizar(data);
   if( ptrain+ptest ==1.0){
        particionado(data, train, test, ptest);

        printf("ndatos:%d\n",train->ndatos );

        printf("ndatos:%d\n",test->ndatos );

        red=redTrain(0, train, iniRedPerceptron, actualizaSalida,
         paradaPerceptron, actualizaPesosPerceptron, actualizaNeuronaPerceptron,
         data->natributos, data->nclases, 0, 0.1);

    }
    else{
        printf("por hacer\n");
        return 0;
    }

    if(red==NULL){
        printf("sada\n");
    }


    printf("ndatos:%d\n",data->ndatos );
    if(fout!=stdout){
        free(fout);
    }
    fclose(fin);
    freeDatos(data);
    freeDatos(train);
    freeDatos(test);


}