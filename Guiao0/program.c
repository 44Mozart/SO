#include <stdio.h>
#include "guiao0.h"
#define value 40

int main(int argc, char* agrv[]){
  int *vector = malloc(sizeof(int))
  fill(vector,size,value);
  printf("%d\n", find(vector,size,value));
  return 0;
}
