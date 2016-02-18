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
        {"a", optional, , '2'},
        {"p", optional, , '3'},
        {"a", no_args, , '2'},
        {"a", no_args, , '2'},
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
}