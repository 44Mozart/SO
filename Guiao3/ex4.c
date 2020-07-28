#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>


int main(int argc, char const *argv[]){
	argv[0] = "ex3.c";	
	execvp("./ex3.c",argv);
	return 0;
}

