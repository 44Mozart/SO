#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

//pid_t getpid(void) -> o meu pid
//pid_t getppid(void) -> o pid do pai

int main(){
	printf("Identificador do processo principal: %d:\n", getpid());
	int f = fork();
	if(f == 0){
		//processo-filho
		printf("Identificador do processo filho: %d\n", getpid());
		printf("Identificador do processo pai do processo filho: %d\n", getppid());
	}
	else{
		//processo-pai
		printf("Identificador do processo pai: %d\n", getpid());
		printf("Identificador do processo pai do processo pai: %d\n", getppid());
		printf("Identificador do filho: %d\n", f);
	}
}
