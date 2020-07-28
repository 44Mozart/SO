#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int mysystem(char* comando){
	pid_t pid;
	int exec_ret,status,return_value;
	char* exec_args[20], string;
	int i;
	string = strtok(comando," ");
	for(i = 0; string != NULL; i++){
		exec_args[i] = string;
		string = strtok(NULL, " ");
	}
	exec_args[i] = NULL;
	pid = fork();
	if(pid == 0){
		exec_ret = execvp(exec_args[0],exec_args);
		_exit(exec_ret);
	} 
	if( pid != -1){
		pid_t t_p = wait(&status);
		if(WIFEXITED(status))	
			return_value = WEXITSTATUS(status);
		else
			return_value = -1;
	}
	return return_value;
}

int main (int argc, char** argv){
	int ret;
	char comando[128];
	strcat(comando,argv[1]);
	for(int i = 2; i < argc; i++){
		strcat(comando," ");
		strcat(comando,argv[i]);
	}
	printf("Vou executar o comando %s\n", comando);
	ret = mysystem(comando);
	printf("Valor do retorno: %d\n", ret);
	return 0;
}
