#include "../includes/redNeuronal.h"

int main(int argc, char** argv) {
	FILE * fin,* fout= NULL;
    int flagf=0, long_index=0;
    double* pesos; /*pesos de neuronas entre neuronas*/
    double** salidas; /*valores de salida de las neuronas*/
    int* entradas; /*valorede entrada de fichero*/
    char* buffer, opt;
    int i=0, sz, j, fallos=0;
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
        printf("red entrenada\n");
        fallos=redTest(test, red, actualizaSalida, actualizaNeuronaPerceptron);
        printf("tasa de fallo: %3.2f %%\n", ((double)fallos/(double)test->ndatos) *100);
        printf("fallos:%d\n",fallos );
    }
    else if( ptrain ==1.0 && ptest==1.0){
        red=redTrain(0, data, iniRedPerceptron, actualizaSalida,
         paradaPerceptron, actualizaPesosPerceptron, actualizaNeuronaPerceptron,
         data->natributos, data->nclases, 0, 1);
        printf("red entrenada\n");
        fallos=redTest(data, red, actualizaSalida, actualizaNeuronaPerceptron);
        printf("tasa de fallo: %3.2f %%\n", ((double)fallos/(double)data->ndatos) *100);
        printf("fallos:%d\n",fallos );
        
    }
    else{
        printf("por hacer\n");
        return 0;
    }

    if(red==NULL){
        printf("sada\n");
    }

    for(i=0; i<red->salidas; i++){
        printf("pesos:");
        for(j=0; j<red->entradas+1; j++){
            printf("%2.4f ", red->neuronas[i+1+red->entradas].pesos[j]);
        }
        printf("\n");
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