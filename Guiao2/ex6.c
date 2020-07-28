#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int conta(int** mat, int linha, int num){
	int count =0;
	for(int i = 0; i < 1000; i++){
		if(mat[linha][i] == num)
			count++;
	}
	return count;
}

int main (int argc, char* argsv[]){
	if(argc == 0){
		perror("Erro no nr de inputs");
		exit(-1);
	}
	int** mat = malloc(4*sizeof(int*));
	for(int i = 0; i < 4; i++)
		mat[i] = malloc(1000*sizeof(int));
	int num = 0;
	if(argc > 1)
		num = atoi(argsv[1]);
	srand(time(NULL));
	int contador, a, b;
	for(a = 0; a < 4; a++){
		for(b = 0; b < 1000; b++)
			mat[a][b] = rand()%1000;
	}
	int f;
	for(int i = 0; i < 4; i++){
		f = fork();
		if(f == 0){
			contador = conta(mat,i,num);
			printf("Nesta linha ha %d ocorrencias de %d\n", contador, num);
			exit(contador);
		}
	}
	for(a = 0; a < 4; a++)
		wait(&f);
	int count = 0;
	for(a = 0; a < 4; a++){
		for(b = 0; b < 1000; b++){
			if(mat[a][b] == num)
				count++;
		}
	}
	printf("%d\n", count);
	return 0;
}
