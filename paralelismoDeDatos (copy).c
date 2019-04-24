#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> 


int primerSuma=0;
int segundaSuma=0;
int tercerSuma=0;
int cuartaSuma=0;

int digitosDePi[10000]; 

void* sumarPrimerArray (){
	for(int i=0; i<2500; i++){
		primerSuma += digitosDePi[i];
	}
}

void* sumarSegundoArray (){	
	for(int i=2500; i<5000; i++){
		segundaSuma += digitosDePi[i];
	}
}

void* sumarTercerArray (){
	for(int i=5000; i<7500; i++){
		tercerSuma += digitosDePi[i];
	}
}

void* sumarCuartoArray (){
	for(int i=7500; i<10000; i++){
		cuartaSuma += digitosDePi[i];
	}
}


int main(){
	int sumaTotal =0;

	FILE *myFile;//idem
	myFile = fopen("10milDigitosDePi.txt", "r"); 
	  
	if (myFile == NULL){
		printf("Error en la lectura\n");
		exit (0);
	}

	for (int i = 0; i < 10000; i++){
		fscanf(myFile, "%d,", &digitosDePi[i] );
	}

	//UN HILO POR CADA ARRAY
	pthread_t primerHilo;
	pthread_t segundoHilo;
	pthread_t tercerHilo;	
	pthread_t cuartoHilo;

	pthread_create(&primerHilo, NULL, sumarPrimerArray, NULL);
	pthread_create(&segundoHilo, NULL, sumarSegundoArray, NULL);
	pthread_create(&tercerHilo, NULL, sumarTercerArray, NULL);
	pthread_create(&cuartoHilo, NULL, sumarCuartoArray, NULL);

	pthread_join(primerHilo, NULL);
	pthread_join(segundoHilo, NULL);
	pthread_join(tercerHilo, NULL);
	pthread_join(cuartoHilo, NULL);
	
	sumaTotal = primerSuma + segundaSuma + tercerSuma + cuartaSuma;
	printf("La suma total de los primeros 10.000 digitos de Pi es: ");
	printf( "%i", sumaTotal);
	printf(".\n");

	fclose(myFile);
	return 0;
}
