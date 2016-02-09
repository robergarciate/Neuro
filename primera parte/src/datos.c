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
	int i=0, j=0, k=0;
	if(data==NULL)
		return 1;
	i=data->ndatos;
	j=data->natributos;
	k=data->nclases;
	data->atributos=realloc(data->atributos, sizeof(double*)*(i));
	data->atributos[i]=malloc(sizeof(double)*j);
	data->prediccion=realloc(data->prediccion, sizeof(int*)*(i));
	data->prediccion[i]=malloc(sizeof(int)*k);

	data->ndatos++;
	return 0;
}
int printDatos(datos* data){
	int i=0, j=0;
	printf("natributos:%d\n",data->natributos);
	printf("nclases:%d\n",data->nclases);
	printf("ndatos:%d\n",data->ndatos);

	for(i=0; i<data->ndatos; i++){
		printf("%d %d\n", i, j);
		for(j=0; j<-data->natributos; j++){
			printf("%1.8f ", data->atributos[i][j]);	
		}
		for(j=0; j<-data->nclases; j++){
			printf("%1.8f ", data->prediccion[i][j]);	
		}
		printf("\n");
	}
}
