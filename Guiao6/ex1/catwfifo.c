#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h> 

int main(int argc, char * agrv[]){
	int fd;	
	if((fd  = open("fifo",O_WRONLY)) < 0){
		perror("open");
		exit(1);
	}
	
	printf("open is done.\n");
	int pid  = -1;
	
	//Fazer fork para cat
	if((pid = fork()) == 0){
		dup2(fd,1);
		close(fd);

		execlp("cat","cat",NULL);
		exit(1);	
	}
	int status = 0;
	wait(&status);
	

	//close(fd);
	return 0;
}
