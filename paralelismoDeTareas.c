#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> 

int digitosDePi[10000]; 
/*PROMEDIO*/
int promedio=0;

/*CANTIDAD DE APARICIONES*/
int apariciones[10];
int cantCero=0;
int cantUno=0;
int cantDos=0;
int cantTres=0;
int cantCuatro=0;
int cantCinco=0;
int cantSeis=0;
int cantSiete=0;
int cantOcho=0;
int cantNueve=0;
int masVeces=0;

void* calcularPromedio (){// CALCULAR PROMEDIO
	for(int i=0; i<10000; i++){
		promedio += digitosDePi[i];
	}
	promedio = promedio / 10000;
}

void* calcularAparicion (){//CALCULAR APARICION DE CADA DIGITO Y CUAL APARECE MÁS VECES
	for(int i=0; i<10000; i++){
		if(digitosDePi[i]==0){
			cantCero++;
		}
		if(digitosDePi[i]==1){
			cantUno++;
		}
		if(digitosDePi[i]==2){
			cantDos++;
		}
		if(digitosDePi[i]==3){
			cantTres++;
		}
		if(digitosDePi[i]==4){
			cantCuatro++;
		}
		if(digitosDePi[i]==5){
			cantCinco++;
		}
		if(digitosDePi[i]==6){
			cantSeis++;
		}
		if(digitosDePi[i]==7){
			cantSiete++;
		}
		if(digitosDePi[i]==8){
			cantOcho++;
		}
		if(digitosDePi[i]==9){
			cantNueve++;
		}
	}
	apariciones[0]=cantCero;
	apariciones[1]=cantUno;
	apariciones[2]=cantDos;
	apariciones[3]=cantTres;
	apariciones[4]=cantCuatro;
	apariciones[5]=cantCinco;
	apariciones[6]=cantSeis;
	apariciones[7]=cantSiete;
	apariciones[8]=cantOcho;
	apariciones[9]=cantNueve;
}

/*void* tercerSubArray (){//TODO: CALCULAR CANTIDAD DE PRIMOS Y LA SUMA DE ELLOS
	for(int i=5000; i<7500; i++){
		tercerArray[i-5000] = digitosDePi[i];
	}
}*/

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
	//pthread_t tercerHilo;	

	pthread_create(&primerHilo, NULL, calcularPromedio, NULL);
	pthread_create(&segundoHilo, NULL, calcularAparicion, NULL);
	//pthread_create(&tercerHilo, NULL, tercerSubArray, NULL);

	pthread_join(primerHilo, NULL);
	pthread_join(segundoHilo, NULL);
	//pthread_join(tercerHilo, NULL);

	
	printf("El promedio de de entre los primeros 10000 digitos de Pi es: ");
	printf("%i", promedio);
	printf("\n");

	for(int i=0; i<10; i++){
		printf("\nCantidad de veces que aparece el numero %i", i);
		printf(": %i", apariciones[i]);
	}
	printf("\n");
	

	fclose(myFile);
	return 0;
}
