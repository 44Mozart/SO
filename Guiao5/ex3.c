#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char* argv[]){
		
	//criar pipe
	//fork
	//	filho : executar wc.
	//	pai : ler stdin e enviar para o processo filho.
	//

	int pipe_fd[2];
	if(pipe(pipe_fd) < 0){
		perror("pipe");
		exit(1);
	}
	
	int pid = -1;
	if((pid = fork()) == 0){
		// 0 -> stdin
		// 1 -> stdout	
		// pipe_fd[0] -> leitura pipe
		// pipe_fd[1] -> escrita pipe
		close(pipe_fd[1]);
		
		dup2(pipe_fd[0], 0);
		// 0, pipe_fd[0] -> leitura pipe
                // 1 -> stdout  

		close(pipe_fd[0]);
		//0 -> leitura pipe
		//1 ->stdout

		execlp("wc","wc",NULL);
		
		_exit(1);
			
	}
	else {
		// 0 -> stdin
                // 1 -> stdout  
                // pipe_fd[0] -> leitura pipe
                // pipe_fd[1] -> escrita pipe
		close(pipe_fd[0]);

		int bytes = 0;
		char buf[10];
		while((bytes = read(0,buf,10)) > 0)
			write(pipe_fd[1],buf,bytes);
		
		close(pipe_fd[1]);
		wait(NULL);
	}
	return 0;
}
