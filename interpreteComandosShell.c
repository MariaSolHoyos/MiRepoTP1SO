#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_NUMBER_OF_PARAMS 10

int main( ) {
	while (1){
		//leer un comando input:
		printf("\nInterprete de Comandos:\n");
		char cmd[MAX_COMMAND_LENGTH];
		scanf("\n%[^\n]",cmd);
		int pid = fork();

		//remover el enter de tu comando
		if(cmd[strlen(cmd)-1] == '\n'){
  			cmd[strlen(cmd)-1] = '\0';
		}

		void parsecmd(char* cmd, char** params){
			for(int i = 0; i < MAX_NUMBER_OF_PARAMS; i++) {
				params[i] = strsep(&cmd, " ");		
				if(params[i] == NULL) break;
		  	}
		}

		//dividir el comando en un array de parametros
		char* params[MAX_NUMBER_OF_PARAMS + 1];
		parsecmd(cmd, params);

		//ejecutar los parametros
		if (pid==0){
			execvp(params[0], params);	
		}
	}
	return 0;
}
