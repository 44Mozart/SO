#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	
	int pipe_fd[3][2];

	if(pipe(pipe_fd[0]) < 0){
		perror("pipe");
		exit(1);
	}
	

	//criar fork para grep -v ^# /etc/passwd
	if(fork() == 0){
		
		// 0 -> stdin
		// 1 -> stdout
		// pipe_fd[0][0] -> leitura pipe
		// pipe_fd[0][1] -> escrita pipe
		
		close(pipe_fd[0][0]); //Não precisamos do de leitura.

		dup2(pipe_fd[0][1],1);
		close(pipe_fd[0][1]);

		//executar grep -v ^# /etc/passwd
		execlp("grep","grep","-v","^#","/etc/passwd",NULL);

		_exit(1);
	}

	close(pipe_fd[0][1]);

	if(pipe(pipe_fd[1]) < 0){
                perror("pipe");
                exit(1);
        }

	//criar fork para cut -f7 -d:	
	if(fork() == 0)	{
		// 0 -> stdin
		// 1 -> stdout
		// pipe_fd[0][0] -> leitura pipe		
		// pipe_fd[1][0] -> leitura pipe
		// pipe_fd[1][1] -> escrita pipe
		
		close(pipe_fd[1][0]); //Não precisamos do de leitura

		dup2(pipe_fd[0][0],0);
		dup2(pipe_fd[1][1],1);
		close(pipe_fd[0][0]);
		close(pipe_fd[1][1]);

		//executar cut -f7 -d:
		execlp("cut", "cut", "-f7","-d:", NULL);

		_exit(1);
	}
	
	close(pipe_fd[0][0]);
	close(pipe_fd[1][1]);
	
 	if(pipe(pipe_fd[2]) < 0){
                perror("pipe");
                exit(1);
        }

", "cut", "-f7","-d:",	//criar fork para uniq
	if(fork() == 0){
		// 0 -> stdin
                // 1 -> stdout
                // pipe_fd[1][0] -> leitura pipe
            	// pipe_fd[2][0] -> leitura pipe
               	// pipe_fd[2][1] -> escrita pipe

		close(pipe_fd[2][0]);
			
		dup2(pipe_fd[1][0],0);
                dup2(pipe_fd[2][1],1);
                close(pipe_fd[1][0]);
                close(pipe_fd[2][1]);
			
		//executar uniq
		execlp("uniq","uniq",NULL);
		_exit(1);
	}
	close(pipe_fd[2][1]);
	close(pipe_fd[1][0]);

	//executar wc -l
	if(fork() == 0){
		// 0 -> stdin
               	// 1 -> stdout
              	// pipe_fd[2][0] -> leitura pipe
            	

                dup2(pipe_fd[2][0],0);
                close(pipe_fd[2][0]);
                                
                //executar wc -l
               	execlp("wc","wc","-l",NULL);
		_exit(1);
	}
	else {
		close(pipe_fd[2][0]);
		wait(NULL);
	}
	return 0;
}
