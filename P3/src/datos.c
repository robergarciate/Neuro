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
	train->clase=malloc(sizeof(double*)*data->ndatos);


	test->nclases = data->nclases;
	test->natributos = data->natributos;
	test->atributos=malloc(sizeof(double*)*data->ndatos);
	test->clase=malloc(sizeof(double*)*data->ndatos);

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



int particionado2(datos* data, datos* train, datos* test, double porcentaje){
	int ntrain= data->ndatos - data->ndatos * porcentaje;
	int i=0, j=0, k=0;

	if(!(porcentaje>0 && porcentaje<1)){

		return 1;
	}
	train->ndatos = ntrain;
	train->nclases = data->nclases;
	train->natributos = data->natributos;
	train->atributos = malloc(sizeof(double*)*ntrain);
	train->clase = malloc(sizeof(double*)*ntrain);

	test->ndatos = data->ndatos - ntrain;
	test->nclases = data->nclases;
	test->natributos = data->natributos;
	test->atributos=malloc(sizeof(double*) * test->ndatos);
	test->clase=malloc(sizeof(double*) * test->ndatos);

	for(i=0; i < data->ndatos; i++){
		if(i>=ntrain){
			test->atributos[k] = malloc(sizeof(double) * test->natributos);
			test->clase[k] = malloc(sizeof(double) * test->nclases);
		}
		else{
			train->atributos[i] = malloc(sizeof(double) * train->natributos);
			train->clase[i] = malloc(sizeof(double) * train->nclases);
		}

		for(j=0; j < data->natributos; j++){
			
			if(i < ntrain)
				train->atributos[i][j] = data->atributos[i][j];
			else
				test->atributos[k][j] = data->atributos[i][j];
			
		}
		for(j=0; j < data->nclases; j++){

			if(i < ntrain)
				train->clase[i][j] = data->clase[i][j];
			else
				test->clase[k][j] = data->clase[i][j];

		}

		if(i>=ntrain){
			k++;
		}
	}

	return 0;
}


int reservarTupla(datos* data){
	int i=0, j=0, k=0;
	if(data==NULL)
		return 1;
	i=data->ndatos;
	j=data->natributos;
	k=data->nclases;
	data->atributos=realloc(data->atributos, sizeof(double*)*(i+1));
	data->atributos[i]=malloc(sizeof(double)*j);
	
	for(j=0; j<data->natributos; j++){
		data->atributos[i][j]=0;
	}

	data->clase=realloc(data->clase, sizeof(double*)*(i+1));
	data->clase[i]=malloc(sizeof(double)*k);

	for(j=0; j<data->nclases; j++){
		data->atributos[i][j]=0;
	}	

	data->ndatos++;
	return 0;
}
int printDatos(datos* data){
	int i=0, j=0;
	if(data==NULL){
		printf("data=NULL\n");
		return 1;
	}
	printf("natributos:%d\n",data->natributos);
	printf("nclases:%d\n",data->nclases);
	printf("ndatos:%d\n",data->ndatos);
	printf("tuplas\n");
	for(i=0; i<data->ndatos; i++){
		printf("atributos de %d", i);
		for(j=0; j<data->natributos; j++){
			if(j%5==0)
				printf("\n");

			printf(" [%1.4f]", data->atributos[i][j]);
		}

		printf("\n");

		printf("\nclase de %d", i);
		for(j=0; j<data->nclases; j++){
			if(j%5==0)
				printf("\n");
			printf(" [%1.4f]", data->clase[i][j]);
		}
		printf("\n\n");
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
		fprintf(f, "%1.4f",data->atributos[i][0] );
		for(j=1; j< data->natributos; j++){
			fprintf(f, ", %1.4f",data->atributos[i][j] );
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

datos* interpolarSuma(datos* d){
	datos* res=NULL;
	int i=0, j=0, k=0;
	if(d==NULL){
		return NULL;
	}
	res= iniDatos();

	res->natributos=d->natributos*2 -1;
	res->nclases=d->nclases;
	res->ndatos=d->ndatos;
	res->atributos=malloc(sizeof(double*)*res->ndatos);
	res->clase=malloc(sizeof(double*)*res->ndatos);
	for(i=0; i<d->ndatos; i++){
		res->atributos[i]=malloc(sizeof(double)*res->natributos);
		res->clase[i]=malloc(sizeof(double)*res->nclases);
	}

	for(i=0; i<d->ndatos; i++){
		for(j=0; j<d->natributos; j++){
			res->atributos[i][j]= d->atributos[i][j];
		}

		for(k=1, j=d->natributos; j< res->natributos; j++,k++){
			res->atributos[i][j]= d->atributos[i][k] + d->atributos[i][k-1];
		}

		for(j=0; j<d->nclases; j++){
			res->clase[i][j]= d->clase[i][j];
		}
	}
	return res;	
}	

datos* interpolarProducto(datos* d){
	datos* res=NULL;
	int i=0, j=0, k=0;
	if(d==NULL){
		return NULL;
	}
	res= iniDatos();
	
	res->natributos=d->natributos*2 -1;
	res->nclases=d->nclases;
	res->ndatos=d->ndatos;
	res->atributos=malloc(sizeof(double*)*res->ndatos);
	res->clase=malloc(sizeof(double*)*res->ndatos);
	for(i=0; i<d->ndatos; i++){
		res->atributos[i]=malloc(sizeof(double)*res->natributos);
		res->clase[i]=malloc(sizeof(double)*res->nclases);
	}

	for(i=0; i<d->ndatos; i++){
		for(j=0; j<d->natributos; j++){
			res->atributos[i][j]= d->atributos[i][j];
		}

		for(k=1, j=d->natributos; j< res->natributos; j++,k++){
			res->atributos[i][j]= d->atributos[i][k] * d->atributos[i][k-1];
		}

		for(j=0; j<d->nclases; j++){
			res->clase[i][j]= d->clase[i][j];
		}
	}
	return res;	
}	

datos* interpolarMedia(datos* d){
	datos* res=NULL;
	int i=0, j=0;
	double val=0;
	if(d==NULL){
		return NULL;
	}
	res= iniDatos();
	
	res->natributos=d->natributos+1;
	res->nclases=d->nclases;
	res->ndatos=d->ndatos;
	res->atributos=malloc(sizeof(double*)*res->ndatos);
	res->clase=malloc(sizeof(double*)*res->ndatos);
	for(i=0; i<d->ndatos; i++){
		res->atributos[i]=malloc(sizeof(double)*res->natributos);
		res->clase[i]=malloc(sizeof(double)*res->nclases);
	}

	for(i=0; i<d->ndatos; i++){
		for(j=0; j<d->natributos; j++){
			res->atributos[i][j]= d->atributos[i][j];
			val=d->atributos[i][j];
		}
		res->atributos[i][j]=val/j;

		for(j=0; j<d->nclases; j++){
			res->clase[i][j]= d->clase[i][j];
		}
	}
	return res;	
}	



void bipolarizar(datos* data){
	int i=0 , j=0;
	if(data== NULL){
		return;
	}
	for(i= 0; i< data->ndatos; i++){
		for(j=0; j<data->nclases; j++){
			if(data->clase[i][j]==0)
				data->clase[i][j]=-1;
		}
	}
}


void normalizarDatos(datos* d){
	int i=0, j=0;
	double media=0.0, varianza=0.0; 
	if(d==NULL)
		return;

	for(j=0; j<d->natributos; j++){
		printf("Se normaliza la columna:%d\n", j);
		media=0.0;
		varianza=0.0;
		for(i=0; i<d->ndatos; i++){
			media+=d->atributos[i][j];
		}
		media/=d->ndatos;
		for(i=0; i<d->ndatos; i++){
			varianza+=pow(d->atributos[i][j] -media, 2.0);
		}
		varianza/=d->ndatos;
		printf("media: %1.5f varianza: %1.4f\n\n", media, varianza);
		for(i=0; i<d->ndatos; i++){
			d->atributos[i][j]= (d->atributos[i][j]-media)/sqrt(varianza);
		}

	}
}


int * columnasRuidosas(int cols, int ruido){
	int i=0,j=0, col=0;
	int *cambiar;
	if(ruido>cols){
		ruido=cols;	
	}
	cambiar=malloc(sizeof(int)*ruido);
	srand(time(NULL));
	for(i=0; i < ruido; i++)
		cambiar[i]=-1;

	for(i=0; i < ruido; i++){
		col=rand() % cols;
		for(j=0; j < ruido; j++){

			if(col==cambiar[j]){
				j=-1;
				col=rand() % cols;
			}
		}

		cambiar[i]=col;
	}
	return cambiar;
}

int esRuidosas(int* cols, int col, int tam){
	int i=0;

	for(i=0; i< tam; i++){
		if(cols[i]==col)
			return 1;
	}
	return 0;
}

 void ruidoDatos(datos* d, int natributos, double ndatos){
	int nruido=d->ndatos*ndatos;
	int i=0, j=0;
	int* cambiar= NULL;
	srand(time(NULL));

	if(nruido!=d->ndatos){
		d->clase= (double**) realloc((void*)d->clase, sizeof(double*) * (nruido));
		d->atributos= (double**) realloc((void*)d->atributos, sizeof(double*) * (nruido));
	}
	
	if(natributos > d->natributos)
		natributos= d->natributos;

	
	if(nruido> d->ndatos){
		for(i=0; i < nruido - d->ndatos; i++){

			cambiar= columnasRuidosas(d->natributos, natributos);

			d->atributos[i + d->ndatos]= malloc(sizeof(double) * d->natributos);
			d->clase[i +d->ndatos]= malloc(sizeof(double) * d->nclases);
			for(j=0; j < d->natributos; j++){
				if(esRuidosas(cambiar, j , natributos))
					if(d->atributos[i][j]==0)
						d->atributos[i + d->ndatos][j]= 1;
					else
						d->atributos[i + d->ndatos][j]= 0;
				else
					d->atributos[i + d->ndatos][j]= d->atributos[(i+nruido) % d->ndatos][j];

			}

			for(j=0; j < d->nclases; j++){

				d->clase[i + d->ndatos][j]= d->clase[(i+nruido) % d->ndatos][j];
			}
			free(cambiar);

		}
	}
	else{
		for(i=0; i < nruido ; i++){
			cambiar= columnasRuidosas(d->natributos, natributos);
			
			for(j=0; j < d->natributos; j++){

				if(esRuidosas(cambiar, j , natributos)){
					if(d->atributos[i][j]==0)
						d->atributos[i][j]= 1;
					else
						d->atributos[i][j]= 0;

				}
			}
			free(cambiar);	

		}
	}

	printf("%d %d\n", nruido, d->ndatos);
	d->ndatos=nruido;
}

datos* copiarDatos(datos* din){
	datos* dout = iniDatos();
	int i = 0, j = 0;
	dout->ndatos = din->ndatos;
	dout->natributos = din->natributos;
	dout->nclases = din->nclases;

	dout->atributos = malloc(sizeof(double*) * dout->ndatos);

	dout->clase = malloc(sizeof(double*) * dout->ndatos);


	for( i=0 ; i < dout->ndatos; i++){
		dout->atributos[i] = malloc(sizeof(double) * dout->natributos);
		for( j=0 ; j < dout->natributos; j++){
			dout->atributos[i][j] = din->atributos[i][j]; 
		}

		dout->clase[i] = malloc(sizeof(double) * dout->nclases);

		for( j=0 ; j < dout->nclases; j++){

			dout->clase[i][j] = din->clase[i][j]; 
		}
	}
	return dout;
}


void printClases(FILE* fout, datos* data){

	int i=0;
	int j=0;
	for(i = 0; i < data->ndatos; i++){
		for(j = 0; j < data->nclases; j++){
			fprintf(fout, "%1.4f ", data->clase[i][j]);
		}		
		fprintf(fout, "\n");
	}
}
