#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	
	int pipe_fd[2];

	if(pipe(pipe_fd) < 0){
		perror("pipe");
		exit(1);
	}
	

	//criar fork para ls /etc
	if(fork() == 0){
		
		// 0 -> stdin
		// 1 -> stdout
		// pipe_fd[0] -> leitura pipe
		// pipe_fd[1] -> escrita pipe
		
		close(pipe_fd[0]); //Não precisamos do de leitura.

		dup2(pipe_fd[1],1);
		close(pipe_fd[1]);

		//executar ls /etc
		execlp("ls","ls","/etc",NULL);

		_exit(1);
	}
	else{
		
		//criar fork para wc -l
		if(fork() == 0)	{
			// 0 -> stdin
			// 1 -> stdout
			// pipe_fd[0] -> leitura pipe
			// pipe_fd[1] -> escrita pipe

			close(pipe_fd[1]); //Não precisamos do de escrita

			dup2(pipe_fd[0],0);
			close(pipe_fd[0]);

			//executar ls/etc
			execlp("wc", "wc", "-l", NULL);

			_exit(1);
		}
		else{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			wait(NULL);
			wait(NULL);
		}
	}
	return 0;
}
