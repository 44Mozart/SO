#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>


int main(){
	int i;
	for(i = 1; i <= 10; i++){
		int f = fork();
		if(f == 0){
			printf("Identificador do filho: %d\n",getpid());
			printf("Identificador do pai: %d\n", getppid());
			exit(i);
		}
		else{
			wait(&f);
			printf("Eu sou o filho nr: %d\n",WEXITSTATUS(f));
		}
	}
}
