#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> 

int digitosDePi[10000]; 

int primerArray[2500];
int segundoArray[2500];
int tercerArray[2500];
int cuartoArray[2500];


void* primerSubArray (){
	for(int i=0; i<2500; i++){
		primerArray[i] = digitosDePi[i];
	}
}

void* segundoSubArray (){	
	for(int i=2500; i<5000; i++){
		segundoArray[i-2500] = digitosDePi[i];
	}
}

void* tercerSubArray (){
	for(int i=5000; i<7500; i++){
		tercerArray[i-5000] = digitosDePi[i];
	}
}

void* cuartoSubArray (){
	for(int i=7500; i<10000; i++){
		cuartoArray[i-7500] = digitosDePi[i];
	}
}

int main(){
	FILE *myFile;
	myFile = fopen("10milDigitosDePi.txt", "r"); 
	  
	if (myFile == NULL){
		printf("Error en la lectura\n");
		exit (0);
	}

	for (int i=0; i<10000; i++){
		fscanf(myFile, "%d,", &digitosDePi[i] );
	}

	//UN HILO POR CADA ARRAY
	pthread_t primerHilo;
	pthread_t segundoHilo;
	pthread_t tercerHilo;	
	pthread_t cuartoHilo;

	pthread_create(&primerHilo, NULL, primerSubArray, NULL);
	pthread_create(&segundoHilo, NULL, segundoSubArray, NULL);
	pthread_create(&tercerHilo, NULL, tercerSubArray, NULL);
	pthread_create(&cuartoHilo, NULL, cuartoSubArray, NULL);

	pthread_join(primerHilo, NULL);
	pthread_join(segundoHilo, NULL);
	pthread_join(tercerHilo, NULL);
	pthread_join(cuartoHilo, NULL);

	int ret = 0;
	for(int i=0; i<2500; i++){
		ret+=primerArray[i];
		ret+=segundoArray[i];
		ret+=tercerArray[i];
		ret+=cuartoArray[i];
	}
	
	printf("La suma total de los primeros 10000 digitos de Pi es: ");
	printf("%i", ret);
	printf("!\n");

	fclose(myFile);
	return 0;
}
