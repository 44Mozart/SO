
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#define SIZE 1024



void copiaBF (char buffer[] ,int fd){
  int i;
  for (i = 0; i < SIZE/2; i++){
    buffer[i] = 'a';
  }
  buffer[i] = '\n';
  i++;
  for (; i < SIZE; i++){
    buffer[i] = 'a';
  }
  ssize_t res = write(fd,buffer,SIZE);
}

/*
void mycat(){
  char buffer[SIZE];
  int res = 0;
  while((res = read(0,buffer,SIZE))!= 0){
    ssize_t c = write(0,buffer,SIZE);
  }
}
*/

void mycp (){
  int fd = open("foo.txt",O_RDONLY,0600);
  int nFd = open("foo_c.txt",O_CREAT|O_TRUNC|O_WRONLY,0600);
  ssize_t res;
  char buffer[SIZE];
  while ((res = read(fd,buffer,SIZE))){
    ssize_t c = write(nFd,buffer,SIZE);
  }
  close(nFd);
}

int readc(int fd, char* c){
  return read(fd,c,1);
}

ssize_t readln(int fd, char *buf, size_t size){
  int res = 0;
  int i = 0;

  while (i < size && (res = readc(fd,&buf[i])>0)){
    i++;
    if (((char*) buf)[i-1]  == '\n'){
      return i;
    }
  }
  return i;
}




int main(){
  int fd = open("foo.txt",O_CREAT|O_TRUNC|O_RDWR,0600);
  char buffer[SIZE];
  copiaBF (buffer,fd);
  mycp();
  mycat();
  lseek(fd,0,SEEK_SET);
  ssize_t i = readln(fd,buffer,SIZE);
  snprintf(buffer,SIZE,"%ld\n",i);
  write (0,buffer,SIZE);
  close(fd);

  return 0;
}
