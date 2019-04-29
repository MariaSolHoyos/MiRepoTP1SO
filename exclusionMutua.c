#include <stdio.h>
#include <stdlib.h>    
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> 

int repeticionesEscritor = 10;
int repeticionesLector = 1;
int hoja = 0;
pthread_mutex_t mi_mutex;

void* funcionEscribir (){
	for(int i=0; i<repeticionesEscritor; i++){
		pthread_mutex_lock(&mi_mutex);
		
		hoja+=1;
		printf("Escribe %d \n", hoja);

		pthread_mutex_unlock(&mi_mutex);
     }
}

void* funcionLeer(){
	for(int i=0; i<repeticionesLector; i++){
		pthread_mutex_lock(&mi_mutex);

		printf("Lee  %d \n", hoja);

		pthread_mutex_unlock(&mi_mutex);
     } 
}

int main(){
	//identificador de los hilos
	pthread_t thEscribir;
	pthread_t thLeer;
	pthread_mutex_init ( &mi_mutex, NULL);

	//creo los hilos
	int res = pthread_create(&thLeer, NULL, &funcionLeer, NULL);  
	if(res != 0){
		printf("Error: no se puede ejecutar el thread, %d \n", res);
		exit(-1);
	}	
   
	res = pthread_create(&thEscribir, NULL, &funcionEscribir, NULL);
	if(res != 0){
		printf("Error: no se puede ejecutar el thread, %d \n", res);
		exit(-1);
	}

	//espero que terminen los hilos
	pthread_join(thEscribir, NULL);
	pthread_join(thLeer, NULL);

	pthread_mutex_destroy(&mi_mutex);

	return 0;
}
