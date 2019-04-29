#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> 
#include <time.h>

int digitosDePi[10000]; 
/*PROMEDIO*/
int promedio=0;

/*CANTIDAD DE APARICIONES*/
int apariciones[10] = {0,0,0,0,0,0,0,0,0,0};
int elMasRepetido;

/*SUMA DE PRIMOS*/
int cantPrimos=0;
int sumaPrimos=0;


void* calcularPromedio (){// CALCULAR PROMEDIO
	for(int i=0; i<10000; i++){
		promedio += digitosDePi[i];
	}
	promedio = promedio / 10000;
}

void* calcularAparicion (){//CALCULAR APARICION DE CADA DIGITO Y CUAL APARECE MÁS VECES
	for(int i=0; i<10000; i++){
		if(digitosDePi[i]==0){
			apariciones[0]++;
		}
		if(digitosDePi[i]==1){
			apariciones[1]++;
		}
		if(digitosDePi[i]==2){
			apariciones[2]++;
		}
		if(digitosDePi[i]==3){
			apariciones[3]++;
		}
		if(digitosDePi[i]==4){
			apariciones[4]++;
		}
		if(digitosDePi[i]==5){
			apariciones[5]++;
		}
		if(digitosDePi[i]==6){
			apariciones[6]++;
		}
		if(digitosDePi[i]==7){
			apariciones[7]++;
		}
		if(digitosDePi[i]==8){
			apariciones[8]++;;
		}
		if(digitosDePi[i]==9){
			apariciones[9]++;
		}
	}

	int max=0;
	for(int i=0; i<10; i++){
		if(apariciones[i]>max){
			max=apariciones[i];
			elMasRepetido=i;
		}
	}
}

void* obtenerPrimos (){//CALCULAR CANTIDAD DE PRIMOS Y LA SUMA DE ELLOS

	for(int i=0; i<10000; i++){
		int cont=0;
		for(int j=1; j<=digitosDePi[i]; j++){
			if(digitosDePi[i]%j==0){
				cont++;
			}
		}
		if(cont==2){//si es primo
			cantPrimos++;
			sumaPrimos+=digitosDePi[i];
		}
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
	
	calcularPromedio();obtenerPrimos();	
	printf("\nEl promedio de de entre los primeros 10000 digitos de Pi es: ");
	printf("%i", promedio);
	printf("\n");
	
	calcularAparicion();
	for(int i=0; i<10; i++){
		printf("\nCantidad de veces que aparece el número %i", i);
		printf(": %i", apariciones[i]);
	}
	printf("\n");
	printf("El dìgito que aparece más veces es: %i", elMasRepetido);
	printf("\n");
	
	obtenerPrimos();
	printf("\nCantidad de números primos que ocurren: %i", cantPrimos);
	printf("\nLa suma de ellos es: %i", sumaPrimos);
	printf("\n");

	fclose(myFile);
	return 0;
}

