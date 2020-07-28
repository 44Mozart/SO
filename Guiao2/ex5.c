#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

void criaProcessos(int n){
	if(n == 10) exit(-1);
	int f = fork();
	if(f == 0){
		printf("Eu sou o processo nr: %d\n", n+1);
		printf("Identificador do processo: %d\n", getpid());
		printf("Identificador do processo pai: %d\n", getppid());
		criaProcessos(n+1);
	}
	else {
		wait(&f);
		exit(f);
	}
}

int main(){
	for(int i = 0; i < 10; i++){
		criaProcessos(i);
	}
}

