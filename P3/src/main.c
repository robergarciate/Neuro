#include "../includes/redNeuronal.h"

int maxEtapas =0, aleat=0;
double maxTolerancia=0.0;

datos* adapt=NULL;

int main(int argc, char** argv) {
	FILE * fin=NULL,* fout= NULL,* fclasf=NULL;
    int long_index=0;
    char opt;
    double fallos=0;
    double ptrain=0.0, ptest=0.0, tasa=0.0;
    redNeuronal* red=NULL;
    FILE * ferr= fopen("err.data", "w");


    redNeuronal* (*fini)(int, int, int, double)=NULL;
    int (*fsalida) (redNeuronal*, double (*fActualizacion)(neurona*), double*)=NULL;
    int (*fParada) (redNeuronal*)=NULL;
    double (*fPesos) (redNeuronal*, double*)=NULL;
    double (*fActualizacion)(neurona*)=NULL;
    int ocultas=0, na=0, ns=0;



    datos* data=NULL,* train=NULL,* test=NULL;
    static int flagPerceptron=0, flagAdaline=0, flagClasf, flagBP, falgAlf, falgSerie;
    static int interSum=0, interPrd=0, interMed=0, norm=0;
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
		{"interMed", no_argument, &interMed, 'o'},
        {"norm", no_argument, &norm, 'p'},
        {"bp", no_argument, &flagBP, 'r'},
        {"ocultas", required_argument, 0, 's'},
        {"alf", no_argument, &falgAlf, 't'},
        {"serie", no_argument, &falgSerie, 'u'},
        {"na", required_argument, 0, 'v'},
        {"ns", required_argument, 0, 'w'},

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
            case 's':
                ocultas=atoi(optarg);
            break;
            case 'v':
                na=atoi(optarg);
                if(na<0){
                    printf("%d no es un tamaño valido para na, debe ser mayor que 0\n", na);
                    return 1;
                }
            break;
            case 'w':
                
                ns=atoi(optarg);
                if(ns<0){
                    printf("%d no es un tamaño valido para ns, debe ser mayor que 0\n", na);
                    return 1;
                }
            break;
            
            case'?':
                printf("ERROR1: parametro no reconocido\n"
                	"se esperaba:\n"
                    "./main {-fin file } [-alf] [-serie -na numero -ns numero]"
                    "{-a | -p | -bp -ocultas num}"
                    " {-train num} {-test num} {-tasa num} {-etapas num}" 
                    "[-clasificar -fclasf file [-fout file]] [-norm]"
                    "[-tolerancia num] [-iniAleat] [-interPrd | -interSum | -interMed]\n");
                return 0;
            break;
 
        }
    }

    if(fin==NULL || ptrain>1 || ptest>1 
      || (flagPerceptron==0 && flagAdaline==0 && flagBP==0)
      || (flagPerceptron!=0 && flagAdaline!=0)
      || (interPrd!=0 && interSum!=0 && interMed!=0) || (flagClasf!=0 && fclasf==NULL) ){
        printf("se esperaba:\n"
                    "./main {-fin file } [-alf] [-serie -na numero -ns numero]"
                    "{-a | -p | -bp -ocultas num}"
                    " {-train num} {-test num} {-tasa num} {-etapas num}" 
                    "[-clasificar -fclasf file [-fout file]] [-norm]"
                    "[-tolerancia num] [-iniAleat] [-interPrd | -interSum | -interMed]\n");
        return 0; 

    }

    if(fout==NULL)
        fout=stdout;
    if(tasa== 0.0){
    	tasa=0.01;
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
    	maxTolerancia =0.0000001;
    	printf("tolerancia no especificada se establece en %1.4f\n", maxTolerancia);
    }

    /**
    * Leemos los datos segun el tipo que sean
    **/
    if(falgAlf)
        data= lectorAlfabetico(fin);
    else if(falgSerie)
        data=lectorSerie(fin, na, ns);
    
    else
        data = leerDatos(fin);
    
    if(interSum!=0){
    	train= interpolarSuma(data);
    	freeDatos(data);
    	data=train;
    	train=NULL;
    }

    else if(interPrd!=0){
    	train= interpolarProducto(data);
    	freeDatos(data);
    	data=train;
    	train=NULL;
    }

    else if(interMed!=0){
    	train= interpolarMedia(data);
    	freeDatos(data);
    	data=train;
    	train=NULL;
    }

    if(norm!=0){
        normalizarDatos(data);
    }

    bipolarizar(data);

    if(flagPerceptron){
    	printf("Perceptron\n");
        fini=iniRedPerceptron;
        fsalida=actualizaSalida;
        fParada=paradaPerceptron;
        fPesos=actualizaPesosPerceptron;
        fActualizacion=actualizaNeuronaPerceptron;
    }
    else if(flagAdaline){
    	printf("Adaline\n");
        fini=iniRedPerceptron;
        fsalida=actualizaSalida;
        fParada=paradaAdaline;
        fPesos=actualizaPesosAdaline;
        fActualizacion=actualizaNeuronaAdaline;
    }
    else if(flagBP){
    	printf("Retropropagacion\n");
        if(ocultas==0){
           ocultas=data->natributos*2;
        }
        fini=iniRedRetropropagacion;
        fsalida=actualizaSalida;
        fParada=paradaRetropropagacion;
        /*fParada=paradaRetropropagacion2;
        */fPesos=actualizaPesosRetropropagacion;
        fActualizacion=actualizaNeuronaSigmoidalBipolar;
    }
    else{
        return 0;
    }
    
    if(ptrain+ptest ==1.0){
        train=iniDatos();
        test=iniDatos();
       if(falgSerie)
            particionado2(data, train, test, ptest);
        else
            particionado(data, train, test, ptest);
        adapt=train;
    }
    else if(ptrain ==1.0){
        train=data;
        test=data;
        adapt=data;

    }
    else{
        return 1;
    }


    /*ruidoDatos(train, 5, 11.0);
*/
    red=redTrain(0, train, fini, fsalida,
    	fParada, fPesos, fActualizacion,
        data->natributos, data->nclases, ocultas, tasa);
    printf("red entrenada\n");



    printPesos(red);

    if(flagClasf!=0){
		clasificar(test, red, fsalida, fActualizacion, fout);
    }
    else{
        ruidoDatos(train, 5, 1.0);
        fallos=redTest(test, red, fsalida, fActualizacion);
        printf("tasa de fallo: %3.2f %%\n", ((double)fallos/(double)test->ndatos) *100);
    	printf("fallos:%1.2f datos:%d\n",fallos, test->ndatos );
        fprintf(ferr, "%1.4f", (double)fallos/(double)test->ndatos);
    }

    if(red==NULL){
        printf("sada\n");
    }

    
    destRed1(red);

    if (fclasf!=NULL)
    	fclose(fclasf);

    if(fout!=stdout)
        free(fout);
    

    if(flagAdaline| flagBP)
    	printf("tasa %1.4f train %1.4f test %1.4f tolerancia %1.16f etapas %d\n",
    			tasa, ptrain, ptest, maxTolerancia, maxEtapas);
    if(flagPerceptron )
    	printf("tasa %1.4f train %1.4f  test %1.4f  etapas %d\n",
    			tasa, ptrain, ptest, maxEtapas);

    fclose(fin);
    if(ptrain ==1.0)
        freeDatos(data);
    else{
        freeDatos(data);
        freeDatos(train);
        freeDatos(test);
    }
    fclose(ferr);
    liberarLex();
    return 0;
}