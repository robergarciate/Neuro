#include "../includes/datos.h"

datos* iniDatos(){
	datos* data;
	data=malloc(sizeof(datos));
	data->nclases=0;
	data->natributos=0;
	data->ndatos=0;
	data->atributos=NULL;
	data->clase=NULL;
	return data;
	
}

void freeDatos(datos* data){
	int i=0;
	if(data==NULL)
		return;
	for (i = 0; i < data->ndatos; ++i){

		free(data->clase[i]);

		data->clase[i]=NULL;

		free(data->atributos[i]);

		data->atributos[i]=NULL;
		
		
	}
	free(data->atributos);
	data->atributos=NULL;

	free(data->clase);
	data->clase=NULL;
	free(data);
	data=NULL;

}

void liberaEspacioLibre(datos* data){
	int i=0;
	if (data== NULL)
		return;
	while(data->atributos[data->ndatos+i]==NULL){
		free(data->atributos[data->ndatos+i++]);
	}

	while(data->clase[data->ndatos+i]==NULL){
		free(data->clase[data->ndatos+i++]);
	}
}

int particionado(datos* data, datos* train, datos* test, double porcentaje){
	int i = 0, j=0, k=0, l=0;
	double r;
	if((data==NULL) || (train==NULL) ||(test==NULL) || (porcentaje <= 0.0) || (porcentaje > 1.0))
		return 1;
   
	srand(time(NULL));
	
	train->nclases = data->nclases;
	train->natributos = data->natributos;
	train->atributos=malloc(sizeof(double*)*data->ndatos);
	train->clase=malloc(sizeof(int*)*data->ndatos);


	test->nclases = data->nclases;
	test->natributos = data->natributos;
	test->atributos=malloc(sizeof(double*)*data->ndatos);
	test->clase=malloc(sizeof(int*)*data->ndatos);

	for(i=0; i< data->ndatos; i++){
		train->atributos[i]=NULL;
		train->clase[i]=NULL;
		test->atributos[i]=NULL;
		test->clase[i]=NULL;

	}

	for(i=0; i < data->ndatos; ++i){
		r=(double)rand()/(double)RAND_MAX;
		if( r<porcentaje){
			test->atributos[k]=malloc(sizeof(double)*test->natributos);
			for(l=0; l<test->natributos; l++){
				test->atributos[k][l]=	data->atributos[i][l];
			}

			test->clase[k]=malloc(sizeof(double)*test->nclases);
			for(l=0; l<test->nclases; l++){
				test->clase[k][l]=	data->clase[i][l];
			}
			k++;
			test->ndatos++;
		}else{

			train->atributos[j]=malloc(sizeof(double)*train->natributos);
			for(l=0; l<train->natributos; l++){
				train->atributos[j][l]=	data->atributos[i][l];
			}
			train->clase[j]=malloc(sizeof(double)*train->nclases);
			for(l=0; l<train->nclases; l++){
				train->clase[j][l]=	data->clase[i][l];
			}
			j++;
			train->ndatos++;
		}
	}
	return 0;
}

/*
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
		for(l=0; l < data->ndatos; l++){
			printf("[%d]",data->clase[l][0] );
		}
		printf("\n");
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
*/
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
	data->atributos[i]=calloc(j ,sizeof(double));

	data->clase=realloc(data->clase, sizeof(int*)*(i+1));
	data->clase[i]=calloc(k ,sizeof(int));
	
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


int escribeDatos(datos* data, char* fichero){
	FILE* f=NULL;
	int i=0, j=0, wr=0;
	f=fopen(fichero, "w");
	fprintf(f, "%d\n", data->ndatos);
	fprintf(f, "A1");
	for (i= 1; i < data->natributos; ++i){
		fprintf(f, ",A%d",i+1);
	}

	fprintf(f, ",Class\nContinuo");
	for (i= 1; i < data->natributos; ++i){
		fprintf(f, ",Continuo");
	}
	fprintf(f, ",Continuo\n");

	for (i= 0; i < data->ndatos; ++i){
		fprintf(f, "%1.1f",data->atributos[i][0] );
		for(j=1; j< data->natributos; j++){
			fprintf(f, ", %1.1f",data->atributos[i][j] );
		}

		for(j=0, wr=0; j<data->nclases; j++){
			if(data->clase[i][j]==1){
				fprintf(f, ", %d\n",j+1);
				wr=1;
				break;
			}

		}
		if(wr==0){
			fprintf(f, ", 0\n");
		}
	}

	fclose(f);
	return 0;

}
