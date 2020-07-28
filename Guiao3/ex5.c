#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char** argv){
	pid_t f;
	int status;
	for(int i =0 ; i < argc; i++){
		f = fork();		
		if(f == 0){
			printf("[filho] process %d a executar o comando %s\n", getpid(),argv[i]);
			execvp(argv[i],argv+i);
			_exit(0);
		}
	}
	for(int i = 0; i < argc-1; i++){
		pid_t t_p = wait(&status);
		printf("[pai] process %d exited with %d\n", t_p, WEXITSTATUS(status));
	}
	return 0;
}
