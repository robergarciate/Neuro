#include "../includes/neurona.h"


int main(int argc, char** argv) {
	FILE * fin;
    int flagf=0, long_index=0;
    double* pesos; /*pesos de neuronas entre neuronas*/
    double** salidas; /*valores de salida de las neuronas*/
    int* entradas; /*valorede entrada de fichero*/
    char* buffer, opt;
    int i=0, sz, j;
    neurona** redNeuronal;
    static struct option options[] = {
        {"f",required_argument,0,'1'},
        {0,0,0,0}
    };
 
    while ((opt = getopt_long_only(argc, argv,"1:", options, &long_index )) != -1){
        switch(opt){
            case '1':
                fin=fopen (optarg, "r");
           		flagf=1;
            break;
            case'?':
        		printf("ERROR1: se esperaba ./maCulloch-Pits {-f fin } \n");

            break;
 
        }
    }
    if (flagf == 0){
        printf("ERROR2: se esperaba ./maCulloch-Pits {-f fin } \n");
        return 0;
    }
    /*LECTURA DEL FICHERO*/
    printf("LECTURA DEL FICHERO\n");

    fseek(fin, 0L, SEEK_END);
    sz = ftell(fin);
    fseek(fin, 0L, SEEK_SET);
    
    sz+=6;
    buffer= (char*) malloc(sizeof(char));
    entradas= (int*) calloc(sz, sizeof(int));

    while (!feof(fin)){
    	fread(buffer, 1, 1, fin);
        entradas[i++]=atoi(buffer);
    }
    entradas[i-1]=0;

    /*INICIALIZACION DE LA RED NEURONAL*/
    printf("INICIALIZACION DE LA RED NEURONAL\n");
    
    redNeuronal= (neurona**) malloc(sizeof(neurona*)*14);
    for(i=0; i< 14; i++){
        redNeuronal[i]= iniNeurona();
    }

    /*ESTABLECIMIENTO DE LA RED NEURONAL*/
    printf("ESTABLECIMIENTO DE LA RED NEURONAL\n");

    /*0 1 2 son las neuronas de entrada*/
    
    for(i=0; i<3 ; i++){
        setNeurona(redNeuronal[i], 0.1, 0, NULL, NULL);
    }

    /*3 4 5 son las neuronas de de la primera capa oculta*/

    pesos= (double*) malloc(sizeof(double));
    pesos[0]=1;
    salidas= (double**) malloc(sizeof(double*));

	
    for(i=0; i<3 ; i++){
        salidas[0]=&(redNeuronal[i]->salida);
        setNeurona(redNeuronal[i+3], 0.1, 1, pesos, salidas);
    }
    /*6 7 8 son las neuronas de la segunda capa oculta 
    **para la salida que indica arriba*/

    pesos= (double*) realloc(pesos, sizeof(double)*2);
    pesos[1]=1;
    salidas= (double**) realloc(salidas, sizeof(double*)*2);
    
    salidas[0]=&redNeuronal[2]->salida;
    salidas[1]=&redNeuronal[3]->salida;
    setNeurona(redNeuronal[6], 2.0, 2, pesos, salidas);
    
    salidas[0]=&redNeuronal[0]->salida;
    salidas[1]=&redNeuronal[4]->salida;
    setNeurona(redNeuronal[7], 2.0, 2, pesos, salidas);
    
    salidas[0]=&redNeuronal[1]->salida;
    salidas[1]=&redNeuronal[5]->salida;
    setNeurona(redNeuronal[8], 2.0, 2, pesos, salidas);
    
    /*9 10 11 son las neuronas de la segunda capa oculta 
    **para la salida que indica abajo*/

    salidas[0]=&redNeuronal[1]->salida;
    salidas[1]=&redNeuronal[3]->salida;
    setNeurona(redNeuronal[9], 2.0, 2, pesos, salidas);
    
    salidas[0]=&redNeuronal[2]->salida;
    salidas[1]=&redNeuronal[4]->salida;
    setNeurona(redNeuronal[10], 2.0, 2, pesos, salidas);
    
    salidas[0]=&redNeuronal[0]->salida;
    salidas[1]=&redNeuronal[5]->salida;
    setNeurona(redNeuronal[11], 2.0, 2, pesos, salidas);
    
    /*12 13 son las neuronas la capa de salida*/

    pesos= (double*) realloc(pesos, sizeof(double)*3);
    pesos[2]=1;
    salidas= (double**) realloc(salidas, sizeof(double*)*3);
    

    salidas[0]=&redNeuronal[6]->salida;
    salidas[1]=&redNeuronal[7]->salida;
    salidas[2]=&redNeuronal[8]->salida;
    setNeurona(redNeuronal[12], 1.0, 3, pesos, salidas);

    salidas[0]=&redNeuronal[9]->salida;
    salidas[1]=&redNeuronal[10]->salida;
    salidas[2]=&redNeuronal[11]->salida;
    setNeurona(redNeuronal[13], 1.0, 3, pesos, salidas);


   

    /*EVOLUCION DE LA NEURONA*/
    printf("EVOLUCION DE LA NEURONA\n");

    for(i=0; i< sz; i++){
    	if(i%3==0)
    		printf(" ");
    	printf("%d", entradas[i]);
    }
    printf("\n");
    /*Entrada inicial*/
    actualizaNeuronaEntrada(redNeuronal[0], entradas[0]);
    actualizaNeuronaEntrada(redNeuronal[1], entradas[1]);
    actualizaNeuronaEntrada(redNeuronal[2], entradas[2]);

    printf("%01.f\t %01.f\t %01.f\n", getSalida(redNeuronal[0]), getSalida(redNeuronal[3]), getSalida(redNeuronal[6]));
    printf("%01.f\t %01.f\t %01.f\n", getSalida(redNeuronal[1]), getSalida(redNeuronal[4]), getSalida(redNeuronal[7]));
    printf("%01.f\t %01.f\t %01.f\t%01.f:Arriba\n", getSalida(redNeuronal[2]), getSalida(redNeuronal[5]), getSalida(redNeuronal[8]), getSalida(redNeuronal[12]));
    printf("\t\t %01.f\n", getSalida(redNeuronal[9]));
    printf("\t\t %01.f\n", getSalida(redNeuronal[10]));
    printf("\t\t %01.f\t%01.f:Abajo\n", getSalida(redNeuronal[11]), getSalida(redNeuronal[13]));

    for(i=3; i< sz;){
        /*Actualizamos las neuronas desde la salida hasta la entrada*/
       
    	for(j=13; j>2 ; j--){
    		actualizaNeurona(redNeuronal[j]);
    	}

        /*Actualizamos las neuronas de entrada*/
        printf("entrada:%d%d%d\n", entradas[i], entradas[i+1], entradas[i+2]);
        printf("valores de i:%d %d %d\n", i, i+1, i+2);
        actualizaNeuronaEntrada(redNeuronal[0], entradas[i++]);
        actualizaNeuronaEntrada(redNeuronal[1], entradas[i++]);
        actualizaNeuronaEntrada(redNeuronal[2], entradas[i++]);

   		printf("%01.f\t %01.f\t %01.f\n", getSalida(redNeuronal[0]), getSalida(redNeuronal[3]), getSalida(redNeuronal[6]));
    	printf("%01.f\t %01.f\t %01.f\n", getSalida(redNeuronal[1]), getSalida(redNeuronal[4]), getSalida(redNeuronal[7]));
	   	printf("%01.f\t %01.f\t %01.f\t%01.f:Arriba\n", getSalida(redNeuronal[2]), getSalida(redNeuronal[5]), getSalida(redNeuronal[8]), getSalida(redNeuronal[12]));
	    printf("\t\t %01.f\n", getSalida(redNeuronal[9]));
	    printf("\t\t %01.f\n", getSalida(redNeuronal[10]));
	    printf("\t\t %01.f\t%01.f:Abajo\n", getSalida(redNeuronal[11]), getSalida(redNeuronal[13]));

    }
    for(i=13; i>=0; i--){
        destroyNeurona(redNeuronal[i]);
    }
    free(redNeuronal);
    free(pesos);
    free(entradas);
    free(salidas);
    free(buffer);
    fclose(fin);
    printf("%lu\n",sizeof(neurona));
    return 0;
}