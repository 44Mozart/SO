#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	int f = fork();
	if(f == 0){
		execlp("ls","ls","-1",NULL);
		exit(-1);
	}
	else {
		wait(&f);
		printf("OK\n");
	}
	return 0;
}
