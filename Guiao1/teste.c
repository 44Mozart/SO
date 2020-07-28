#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdlib.h>
#include <stdio.h>

int readln (int fildes, void *buf, int nbyte){
  char c;
  int i = 0;
  int x;
  while (c !='\n' && i<nbyte){
    x = read(fildes, (buf+i), 1); // como é 1 aqui, a seguir é i++; se fosse outro nr tinha que ser i = x+i
    c = *((char*) buf + i);
    i++;
  }
  return i;
}


// nl numbers the lines in a file
int main(int argc, char * argv[]) {
  int fd = open("teste.txt",O_RDWR,0600);
  char c[20];
  int n;
  int i = 1;
  while((n = readln(fd,c,10)) > 0){
    if (c[n-1] == '\n') printf("%d -> %s\n",i++,c);
  }
  return 0;
}
