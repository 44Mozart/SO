#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){
	//criar pipe
	int pipe_fd[2];
	
	if(pipe(pipe_fd) < 0){
		perror("pipe");
		exit(1);
	} 


//Se fecharmos aqui, p.exemplo o descritor de leitura do pai, o processo filho ao ser criado, vai herdar os descritores do pai. Logo não tera o de leitura.


	//criar processo filho
	int pid = -1;
	//Comunicacao pai -> filho
	if((pid = fork()) == 0){
		//Processo-filho herda descritores do pipe.
		
		//Fechamos descritores que não são utilizados no processo-filho.
		close(pipe_fd[0]); //Descritor de leitura do processo-filho. (Nao utilizado)
		
		//Temos extremidade de escrita do pipe

		char* str = "teste";
                write(pipe_fd[1],str,strlen(str)+1);
		_exit(0);
	}
	else{
		close(pipe_fd[1]);//Descritor de escritura do processo-pai (Nao utilizado)	
		//Temos extremidade de leitura do pipe

		char buf[10] = "teste";
                int bytes = read(pipe_fd[0],buf,10);

                printf("Li %d bytes: %s\n",bytes,buf);

		wait(NULL);
	}
	return 0;
}
