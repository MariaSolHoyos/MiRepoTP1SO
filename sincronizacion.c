#include <pthread.h>
#include <stdio.h>
#include <stdlib.h> 	
#include <unistd.h> 	
#include <semaphore.h>

#define ESPERA 200000
#define REPETICIONES 10

pthread_attr_t attr;
struct sched_param param;

sem_t jugar;
sem_t ganar_perder;
sem_t descansar;
sem_t terminar;

void ejecutarCiclo (sem_t* sem1, sem_t* sem2, char* evento){
	for(int i=0; i<REPETICIONES; i++){
		sem_wait(sem1);
		printf("%s", evento);
		fflush(stdout);
		usleep(ESPERA);
		sem_post(sem2);
	}
}

void ejecutarUnicaVez (sem_t* sem1, char* evento){
		sem_wait(sem1);
		printf("%s", evento);
		//fflush(stdout);
		//usleep(ESPERA);
}

void* funcionJugar(void* param){
	ejecutarCiclo(&jugar, &ganar_perder,"JUGAR, ");
	pthread_exit(NULL);
}

void* funcionGanar(void* param){
	ejecutarCiclo(&ganar_perder, &descansar,"GANAR, ");
	pthread_exit(NULL);
}

void* funcionPerder(void* param){
	ejecutarCiclo(&ganar_perder, &descansar,"PERDER, ");
	pthread_exit(NULL);
}

void* funcionDescansar(void* param){
	ejecutarCiclo(&descansar, &jugar,"DESCANSAR. \n");
	sem_post(&terminar);
	pthread_exit(NULL);
}

void* funcionTerminar(void* param){
	sem_wait(&terminar);
	ejecutarUnicaVez(&jugar,"TERMINAR! \n");
	pthread_exit(NULL);
}

void* main(){
	/*printf("Inicia el juego:\n");
	printf("Seleccione el modo:\n");
	printf("1. Modo normal.\n2. Modo jugar bien.\n > ");
	char cmd[1];
	scanf("\n%[^\n]",cmd);*/

	pthread_t thJugar;
	pthread_t thGanar;
	pthread_t thPerder;
	pthread_t thDescansar;
	pthread_t thTerminar;

	//SEMAFOROS
	int res=sem_init(&jugar,0,1);
	if (res!=0){
		printf("Error: no se puede inicializar el semaforo Jugar");
		exit(EXIT_FAILURE);
	}

	res=sem_init(&ganar_perder,0,0);
	if (res!=0){
		printf("Error: no se puede inicializar el semaforo Ganar-Perder");
		exit(EXIT_FAILURE);
	}

	res=sem_init(&descansar,0,0);
	if (res!=0){
		printf("Error: no se puede inicializar el semaforo Descansar");
		exit(EXIT_FAILURE);
	}

	res=sem_init(&terminar,0,0);
	if (res!=0){
		printf("Error: no se puede inicializar el semaforo Terminar");
		exit(EXIT_FAILURE);
	}

	//ASIGNAR PRIORIDAD
	pthread_attr_init (&attr);
	pthread_attr_getschedparam (&attr, &param);
	(param.sched_priority)++;
	pthread_attr_setschedparam (&attr, &param);

	//EJECUTAR THREADS
	res=pthread_create(&thJugar,NULL,&funcionJugar,NULL);
	if(res!=0){
		printf("Error: no se puede ejecutar el thread Jugar");
		exit(-1);
	}

	res=pthread_create(&thGanar,&attr,&funcionGanar,NULL);
	if(res!=0){
		printf("Error: no se puede ejecutar el thread Ganar");
		exit(-1);
	}

	res=pthread_create(&thPerder,NULL,&funcionPerder,NULL);
	if(res!=0){
		printf("Error: no se puede ejecutar el thread Perder");
		exit(-1);
	}

	res=pthread_create(&thDescansar,NULL,&funcionDescansar,NULL);
	if(res!=0){
		printf("Error: no se puede ejecutar el thread Descansar");
		exit(-1);
	}

	res=pthread_create(&thTerminar,NULL,&funcionTerminar,NULL);
	if(res!=0){
		printf("Error: no se puede ejecutar el thread Terminar");
		exit(-1);
	}

	pthread_join(thJugar,NULL);
	pthread_join(thGanar,NULL);
	pthread_join(thPerder,NULL);
	pthread_join(thDescansar,NULL);
	pthread_join(thTerminar,NULL);

	sem_destroy(&jugar);
	sem_destroy(&ganar_perder);
	sem_destroy(&descansar);
	sem_destroy(&terminar);

	pthread_exit(NULL);
}
