#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char** argv){

	//Abrir novos file descriptors
	int input_fd = open("/etc/passwd", O_RDONLY);
	int output_fd = open("saida.txt", O_WRONLY | O_CREAT | O_TRUNC | 0644);
	int error_fd = open("erro.txt", O_WRONLY | O_CREAT | O_TRUNC | 0644);
	
	//Guardar refernecias do stdin, stdout, stderror
	int stdin_fd = dup2(input_fd,0);
	int fdout = dup2(output_fd,1);
	int fderror = dup2(error_fd,2);
	
	//Fechar os novos file descriptors
	close(input_fd);
	close(output_fd);
	close(error_fd);
	
	// 0 => /etc/passwd
	// 1 => saida.txt
	// 2 => erro.txt
 	if(execlp("wc", "wc", NULL) < 0)
		_exit(1);
	return 0;
} 
