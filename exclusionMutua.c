#include <stdio.h>
#include <stdlib.h>    
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> 

int repeticionesEscritor = 10;
int repeticionesLector = 1;
int hoja = 0;
sem_t sem;

void* funcionEscribir (void* param){
	for(int i=0; i<repeticionesEscritor; i++){
		sem_wait(&sem);
		
		hoja+=1;
		printf("Escribe %d \n", hoja);

		sem_post(&sem);
     }
}

void* funcionLeer(void* param){
	for(int i=0; i<repeticionesLector; i++){
		sem_wait(&sem);

		printf("Lee  %d \n", hoja);

		sem_post(&sem);
     } 
}

int main(){
	//identificador de los hilos
	pthread_t thEscribir;
	pthread_t thLeer;

	int res = sem_init(&sem,0,1);
	if(res != 0){
		printf("Error: no se puede inicializar el thread, %d \n", res);
		exit(EXIT_FAILURE);
	}
	
	//creo los hilos
	res = pthread_create(&thLeer, NULL, &funcionLeer, NULL);  
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

	sem_destroy(&sem);

	return 0;
}
