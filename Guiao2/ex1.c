#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	printf("Identificador do processo: %d\n",getpid());
	printf("Indentiicador do pai do processo: %d\n", getppid());
}
