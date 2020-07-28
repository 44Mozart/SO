#include <string.h>
#include <stdio.h>
#include <unistd.h>
int main(){
	execlp("ls","ls","-1",NULL);
	printf("KO\n");
	return 0;
}

