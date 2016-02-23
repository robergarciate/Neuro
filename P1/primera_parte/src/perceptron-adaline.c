#include "../includes/redNeuronal.h"

int maxEtapas =0;
double maxTolerancia=0.0;

int main(int argc, char** argv) {
	FILE * fin,* fout= NULL;
    int long_index=0;
    char opt;
    int i=0, j, fallos=0;
    double ptrain=0.0, ptest=0.0, tasa=0.0;
    redNeuronal* red=NULL;
    datos* data=NULL,* train=NULL,* test=NULL;
    static int flagPerceptron=0, flagAdaline=0;
    static int interSum=0, interPrd=0;
    static struct option options[] = {
        {"fin",required_argument,0, 1},
        {"fout",required_argument,0, 2},
        {"a", no_argument, &flagAdaline, 3},
        {"p", no_argument, &flagPerceptron, 4},
        {"train", required_argument, 0, 5},
        {"test", required_argument, 0, 6},
        {"tasa", required_argument, 0, 7},
        {"etapas", required_argument, 0, 8},
        {"tolerancia", required_argument, 0, 9},
        {"iniAleat", no_argument, &aleat, 10},
        {"interSum", no_argument, &interSum, 11},        
        {"interPrd", no_argument, &interPrd, 12},
        {0,0,0,0}
    };
    while ((opt = getopt_long_only(argc, argv,"1:", options, &long_index )) != -1){
        switch(opt){
            case 1:
                fin=fopen (optarg, "r");
            break;

            case 2:
                fout=fopen (optarg, "w");
            break;
            case 5:
                ptrain=atof(optarg);
            break;
            case 6:
                ptest=atof(optarg);
            break;
            case 7:
                tasa=atof(optarg);

            case 8:
                maxEtapas=atoi(optarg);
            break;
            case 9:
                maxTolerancia=atof(optarg);
            break;  
            case'?':
                printf("ERROR1: parametro no reconocido\n"
                	"se esperaba:\n"
                	"./perceptron-adaline {-fin file } [-fout file] {-a | -p}"
                	" {-train num} {-test num} {-tasa num} {-etapas num} [-tolerancia num] [-iniAleat] [-interPrd | -interSum]\n");
                return 0;
            break;
 
        }
    }

    if(fin==NULL || ptrain>1 || ptest>1 
      || (flagPerceptron==0 && flagAdaline==0)
      || (flagPerceptron!=0 && flagAdaline!=0)
      || (interPrd!=0 && interSum!=0)){
        printf("se esperaba:\n"
        "./perceptron-adaline {-fin file } [-fout file] {-a | -p}"
       	" {-train num} {-test num} {-tasa num} {-etapas num} [-tolerancia num] [-iniAleat] [-interPrd | -interSum]\n");
            
        return 0; 

    }

    if(fout==NULL)
        fout=stdout;
    if(tasa== 0.0){
    	tasa=0.1;
	   	printf("tasa de aprendizaje no especificada se estable ce en %1.4f\n", tasa);
    }
    if(ptrain==0.0){
    	ptrain=0.65;
    	printf("train no especficado se estable ce en %1.4f\n", ptrain);
    }

    if(ptest==0.0){
    	ptest=0.35;
    	printf("train no especficado se establece en %1.4f\n", ptest);
    }
    if (maxEtapas==0){
    	maxEtapas=10000;
    	printf("etapas no especificadas se establece en %d\n",maxEtapas );
    }
    if(maxTolerancia==0.0){
    	maxTolerancia =0.1*tasa;
    	printf("tolerancia no especificada se establece en %1.4f\n", maxTolerancia);
    }
    data = leerDatos(fin);
    
    if(interSum!=0){
    	train= interpolarSuma(data);
    	freeDatos(data);
    	data=train;
    	train=NULL;
    }

    if(interPrd!=0){
    	train= interpolarProducto(data);
    	freeDatos(data);
    	data=train;
    	train=NULL;
    }

    train=iniDatos();
    test=iniDatos();
    bipolarizar(data);
   if( ptrain+ptest ==1.0){
        particionado(data, train, test, ptest);

        printf("ndatos:%d\n",train->ndatos );

        printf("ndatos:%d\n",test->ndatos );
        if(flagPerceptron){
        	printf("perceptron\n");
            red=redTrain(0, train, iniRedPerceptron, actualizaSalida,
             paradaPerceptron, actualizaPesosPerceptron, actualizaNeuronaPerceptron,
             data->natributos, data->nclases, 0, tasa);
            printf("red entrenada\n");
            fallos=redTest(test, red, actualizaSalida, actualizaNeuronaPerceptron);
        }
        else{
        	printf("adaline\n");
        	red=redTrain(0, train, iniRedPerceptron, actualizaSalida,
             paradaAdaline, actualizaPesosAdaline, actualizaNeuronaAdaline,
             data->natributos, data->nclases, 0, tasa);
            printf("red entrenada\n");
            fallos=redTest(test, red, actualizaSalida, actualizaNeuronaAdaline);
        }
        printf("tasa de fallo: %3.2f %%\n", ((double)fallos/(double)test->ndatos) *100);
    	printf("fallos:%d datos:%d\n",fallos, test->ndatos );	

    }
    else if( ptrain ==1.0 && ptest==1.0){
       	printf("datos: %d\n",data->ndatos );
        if(flagPerceptron){
        	printf("perceptron\n");
            red=redTrain(0, data, iniRedPerceptron, actualizaSalida,
             paradaPerceptron, actualizaPesosPerceptron, actualizaNeuronaPerceptron,
             data->natributos, data->nclases, 0, tasa);
            printf("red entrenada\n");
            fallos=redTest(data, red, actualizaSalida, actualizaNeuronaPerceptron);
        }
        else{
        	printf("adaline\n");
        	red=redTrain(0, data, iniRedPerceptron, actualizaSalida,
             paradaAdaline, actualizaPesosAdaline, actualizaNeuronaAdaline,
             data->natributos, data->nclases, 0, tasa);
            printf("red entrenada\n");
            fallos=redTest(data, red, actualizaSalida, actualizaNeuronaAdaline);

        }
        printf("tasa de fallo: %3.2f %%\n", ((double)fallos/(double)data->ndatos) *100);
        printf("fallos:%d datos:%d\n",fallos, data->ndatos);	

        
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

    if(fout!=stdout){
        free(fout);
    }
    printDatos(data);
    destRed1(red);
    fclose(fin);
    freeDatos(data);
    freeDatos(train);
    freeDatos(test);
    if(flagAdaline)
    	printf("tasa %1.4f train %1.4f test %1.4f tolerancia %1.16f etapas %d\n",
    			tasa, ptrain, ptest, maxTolerancia, maxEtapas);
    if(flagPerceptron)
    	printf("tasa %1.4f train %1.4f  test %1.4f  etapas %d\n",
    			tasa, ptrain, ptest, maxEtapas);
    printf("interPrd %d interSum %d\n", interPrd, interSum);
    return 0;
}