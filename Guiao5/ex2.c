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
		close(pipe_fd[1]); //Descritor de escrita do processo-filho. (Nao utilizado)
		
		//Temos extremidade de leitura do pipe

		char buf[10] = "teste";
		int bytes = 0;
		while((bytes = read(pipe_fd[0],buf,10)) > 0){
			write(1,buf,bytes);
		}
		_exit(0);
	}
	else{
		close(pipe_fd[0]);//Descritor de leitura do processo-pai (Nao utilizado)	
		//Temos extremidade de escrita do pipe
		char* str = "teste";
		// sleep(15); //Vai esperar 15 segundos antes de enviar os dados
		
		for(int i = 0; i < 3; i++)		
			write(pipe_fd[1],str,strlen(str)+1);

		close(pipe_fd[1]); //A unica maneira de desbloquear o processo-filho
		//Processo-filho está a espera de dados do pai, e pai a espera do filho.
		wait(NULL);
	}
	return 0;
}

