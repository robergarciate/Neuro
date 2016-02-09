#include "../includes/datos.h"

datos* iniDatos(){
	datos* data;
	data=malloc(sizeof(datos));
	data->nclases=0;
	data->natributos=0;
	data->ndatos=0;
	return data;
	
}

int reservarTupla(datos* data){
	int i=0, j=0, k=0, l=0;
	int* clase= NULL;
	double* atributos=NULL;
	//printf("reservarTupla\n");
	if(data==NULL)
		return 1;

	if(data->ndatos==1){
		printf("%d\n",data->clase[0][0]);
		for(l=0; l<data->ndatos; l++){
			clase= data->clase[l];
			atributos= data->atributos[l];	
		}
	}
	i=data->ndatos;
	j=data->natributos;
	k=data->nclases;

	data->atributos=realloc(data->atributos, sizeof(double*)*(i+1));
	data->atributos[i]=malloc(sizeof(double)*j);

	data->clase=realloc(data->clase, sizeof(int*)*(i+1));
	data->clase[i]=malloc(sizeof(int)*k);

	if(data->ndatos==1){
		for(l=0; l<data->ndatos; l++){
			clase= data->clase[l];
			atributos= data->atributos[l];	
		}
		printf("%d\n",data->clase[0][0] );	
	}
	data->ndatos++;
	return 0;
}
int printDatos(datos* data){
	int i=0, j=0;
	printf("natributos:%d\n",data->natributos);
	printf("nclases:%d\n",data->nclases);
	printf("ndatos:%d\n",data->ndatos);
	printf("tuplas\n");
		for(i=0; i<data->ndatos; i++){

		for(j=0; j<data->natributos; j++){
			printf(" [%1.1f]", data->atributos[i][j]);
		}

		for(j=0; j<data->natributos; j++){
			printf(" [%d]", data->clase[i][j]);
		}
		printf("\n");
	}

}
