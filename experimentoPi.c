#include <stdio.h>
#include <stdlib.h>

//compilar con gcc experimentoPi.c -o ejecutable
//ejecutar con  ./ejecutable

int main(){

 /* FILE *myFile;
  myFile = fopen("10milDigitosDePi_separados.txt", "r");

  //leer archivo en un array
  int numberArray[10000];
  int i;*/

  /*if (myFile == NULL){
    printf("Error en la lectura\n");
    exit (0);
  }*/

  /*for (i = 0; i < 10000; i++){
    fscanf(myFile, "%d,", &numberArray[i] );
  }*/

  printf("Los primeros digitos son\n\n");
  for (i = 0; i < 8; i++){
    printf("Numero es: %d\n\n", numberArray[i]);
  }
  printf("El ultimo numero es: %d\n\n", numberArray[9999]);

  fclose(myFile);

  return 0;
}
