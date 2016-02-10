#include "../includes/datos.h"

datos* iniDatos(){
	datos* data;
	data=malloc(sizeof(datos));
	data->nclases=0;
	data->natributos=0;
	data->ndatos=0;
	return data;
	
}

/**
***	Dados unos datos los divide en particion
***	de entrenamiento y de clasificacion
***	
***	Entradas:
***		data-> los datos de entrada
***		train-> datos donde devolveremos train
***		test-> datos donde devolveremos test
***		porcentaje-> cantidad de datos que iran a train
***	
**/
int particionado(datos* data, datos* train, datos* test, double porcentaje){
	int i = 0, j=0, k=0, l=0;
	double r;
	if((data==NULL) || (train==NULL) ||(test==NULL) || (porcentaje <= 0.0) || (porcentaje > 1.0))
		return 1;
   
	srand(time(NULL));
	
	train->nclases = data->nclases;
	train->natributos = data->natributos;

	test->nclases = data->nclases;
	test->natributos = data->natributos;

	for(i=0; i < data->ndatos; ++i){
		/*for(l=0; l < data->ndatos; l++){
			printf("[%d]",data->clase[l][0] );
		}
		printf("\n");*/
		r=(double)rand()/(double)RAND_MAX;
		if( r<porcentaje){
			reservarTupla(test);
			test->atributos[k] = data->atributos[i];
			test->clase[k++] = data->clase[i];
			printf("test %d %d\n",test->ndatos, i);
		}else{
			reservarTupla(train);
			train->atributos[j] = data->atributos[i];
			train->clase[j++] = data->clase[i];
			printf("train %d %d\n",train->ndatos, i);
		}
	}

	return 0;
}

/*
int particionadoSeguido(datos* data, datos* train, datos* test, double porcentaje){
	if((data==NULL) || (train==NULL) || (test==NULL) || (porcentaje <= 0) || (porcentaje > 1))
		return 1;

	int i = 0;
	seleccion = floor(data->ndatos * porcentaje);

	train->nclases = data->nclases;
	train->natributos = data->natributos;

	for(i=0;i<seleccion;++i){
		if(reservarTupla(train) == 1)
			return 1;
		train->atributos[i] = data->atributos[i];
		train->clase[i] = data->clase[i];
	}

	test->nclases = data->nclases;
	test->natributos = data->natributos;

	for(i=0;i<data->ndatos - seleccion;++i){
		if(reservarTupla(test) == 1)
			return 1;
		test->atributos[i] = data->atributos[i];
		test->clase[i] = data->clase[i];
	}
	
	return 0;
}
*/
int reservarTupla(datos* data){
	int i=0, j=0, k=0;
	if(data==NULL)
		return 1;

	i=data->ndatos;
	j=data->natributos;
	k=data->nclases;

	data->atributos=realloc(data->atributos, sizeof(double*)*(i+1));
	data->atributos[i]=malloc(sizeof(double)*j);

	data->clase=realloc(data->clase, sizeof(int*)*(i+1));
	data->clase[i]=malloc(sizeof(int)*k);

	data->ndatos++;
	return 0;
}
int printDatos(datos* data){
	int i=0, j=0;
	if(data==NULL)
		return 1;
	printf("natributos:%d\n",data->natributos);
	printf("nclases:%d\n",data->nclases);
	printf("ndatos:%d\n",data->ndatos);
	printf("tuplas\n");
	for(i=0; i<data->ndatos; i++){

		for(j=0; j<data->natributos; j++){
			printf(" [%1.4f]", data->atributos[i][j]);
		}

		for(j=0; j<data->nclases; j++){
			printf(" [%d]", data->clase[i][j]);
		}
		printf("\n");
	}
	return 0;
}
