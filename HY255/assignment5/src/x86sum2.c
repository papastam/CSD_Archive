#include <stdio.h> 
#include <stdlib.h> 

#define N 1000

int i = N;
int S = 0;

int main (void) 
{

  while (i >= 0) { S += i; i--;}

  printf("The sum from 0 to %d is %d\n", N, S);

  return 0;
}
