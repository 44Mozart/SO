#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	int i,f;
	for(i = 0; i < 10; i++){
		f = fork();
		printf("Identificador do filho: %d\n", getpid());
		printf("Identificador do pai: %d\n", getppid());
		exit(0);
	}
	for(i = 0; i < 10; i++){
		wait(&f);
		printf("%d\n", WEXITSTATUS(f));
	}
}

