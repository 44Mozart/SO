#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){

	int log_fd =  -1;
	if((log_fd  = open("log.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666)) < 0){
		perror("opne log");
		exit(1);
	}

	printf("log is open\n");

	int fifo_fd = -1;
	if((fifo_fd = open("fifo",O_RDONLY)) < 0){
		perror("open fifo");
		exit(1);
	}

	printf("fifo is opne\n");
	char buf[100];
	int bytes_read = 0;
	while((bytes_read = read(fifo_fd,buf,100)) > 0)
		write(log_fd, buf, bytes_read);

	close(fifo_fd);
	close(log_fd);

	return 0;

}

