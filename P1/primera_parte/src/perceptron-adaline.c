#include "../includes/redNeuronal.h"

int maxEtapas =0, aleat=0;
double maxTolerancia=0.0;

int main(int argc, char** argv) {
	FILE * fin,* fout= NULL,* fclasf;
    int long_index=0;
    char opt;
    int i=0, j, fallos=0;
    double ptrain=0.0, ptest=0.0, tasa=0.0;
    redNeuronal* red=NULL;
    datos* data=NULL,* train=NULL,* test=NULL;
    static int flagPerceptron=0, flagAdaline=0, flagClasf;
    static int interSum=0, interPrd=0;
    static struct option options[] = {
        {"fin",required_argument,0, 'a'},
        {"fout",required_argument,0, 'b'},
        {"a", no_argument, &flagAdaline, 'c'},
        {"p", no_argument, &flagPerceptron, 'd'},
        {"train", required_argument, 0, 'e'},
        {"test", required_argument, 0, 'f'},
        {"tasa", required_argument, 0, 'g'},
        {"etapas", required_argument, 0, 'h'},
        {"tolerancia", required_argument, 0, 'i'},
        {"iniAleat", no_argument, 0, 'j'},
        {"interSum", no_argument, &interSum, 'k'},        
        {"interPrd", no_argument, &interPrd, 'l'},    
        {"clasificar", no_argument, &flagClasf, 'm'},    
        {"fclasf", required_argument, 0, 'n'},
        {0,0,0,0}
    };
    while ((opt = getopt_long_only(argc, argv,"1:", options, &long_index )) != -1){
        switch(opt){
            case 'a':
                fin=fopen (optarg, "r");
            break;

            case 'b':
                fout=fopen (optarg, "w");
            break;
            case 'e':
                ptrain=atof(optarg);
            break;
            case 'f':
                ptest=atof(optarg);
            break;
            case 'g':
                tasa=atof(optarg);

            case 'h':
                maxEtapas=atoi(optarg);
            break;
            case 'i':
                maxTolerancia=atof(optarg);
            break;
            case 'j':
            	aleat =1;
            break;
            case 'n':
            	fclasf=fopen (optarg, "r");
            break;
            case'?':
                printf("ERROR1: parametro no reconocido\n"
                	"se esperaba:\n"
			        "./perceptron-adaline {-fin file }  {-a | -p}"
			    	" {-train num} {-test num} {-tasa num} {-etapas num}" 
			    	"[-clasificar -fclasf file [-fout file]]"
			    	"[-tolerancia num] [-iniAleat] [-interPrd | -interSum]\n");
                return 0;
            break;
 
        }
    }

    if(fin==NULL || ptrain>1 || ptest>1 
      || (flagPerceptron==0 && flagAdaline==0)
      || (flagPerceptron!=0 && flagAdaline!=0)
      || (interPrd!=0 && interSum!=0) || (flagClasf!=0 && fclasf==NULL) ){
        printf("se esperaba:\n"
        "./perceptron-adaline {-fin file }  {-a | -p}"
    	" {-train num} {-test num} {-tasa num} {-etapas num}" 
    	"[-clasificar -fclasf file [-fout file]]"
    	"[-tolerancia num] [-iniAleat] [-interPrd | -interSum]\n");
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
            if(flagClasf!=0){
            	freeDatos(test);
            	test=leerDatos(fclasf);
            	clasificar(test, red, actualizaSalida, actualizaNeuronaPerceptron, fout);
            }
            else
            	fallos=redTest(test, red, actualizaSalida, actualizaNeuronaPerceptron);
        }
        else{
        	printf("adaline\n");
        	red=redTrain(0, train, iniRedPerceptron, actualizaSalida,
             paradaAdaline, actualizaPesosAdaline, actualizaNeuronaAdaline,
             data->natributos, data->nclases, 0, tasa);
            printf("red entrenada\n");
             if(flagClasf!=0){
            	freeDatos(test);
            	test=leerDatos(fclasf);
            	clasificar(test, red, actualizaSalida, actualizaNeuronaPerceptron, fout);
            }
            else
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
            if(flagClasf!=0){
            	freeDatos(test);
            	test=leerDatos(fclasf);
            	clasificar(test, red, actualizaSalida, actualizaNeuronaPerceptron, fout);
            }
            else
            	fallos=redTest(data, red, actualizaSalida, actualizaNeuronaPerceptron);
        }
        else{
        	printf("adaline\n");
        	red=redTrain(0, data, iniRedPerceptron, actualizaSalida,
             paradaAdaline, actualizaPesosAdaline, actualizaNeuronaAdaline,
             data->natributos, data->nclases, 0, tasa);
            printf("red entrenada\n");
            if(flagClasf!=0){
            	freeDatos(test);
            	test=leerDatos(fclasf);
            	clasificar(test, red, actualizaSalida, actualizaNeuronaPerceptron, fout);
            }
            else
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
    destRed1(red);
    fclose(fin);
    freeDatos(data);
    freeDatos(train);
    freeDatos(test);
    liberarLex();
    if(flagAdaline)
    	printf("tasa %1.4f train %1.4f test %1.4f tolerancia %1.16f etapas %d\n",
    			tasa, ptrain, ptest, maxTolerancia, maxEtapas);
    if(flagPerceptron)
    	printf("tasa %1.4f train %1.4f  test %1.4f  etapas %d\n",
    			tasa, ptrain, ptest, maxEtapas);
    return 0;
}