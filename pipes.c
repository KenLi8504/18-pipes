#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1

int main(){
  int parent2child[2];
  int child2parent[2];
  char input [10000];
  char output[10000];
  pipe(parent2child);
  pipe(child2parent);
  int f = fork();
  while(1){
    if (f != 0){
      close(child2parent[WRITE]);
      close(parent2child[READ]);
      printf("Enter a string: ");
      fgets(input,10000,stdin);
      //printf("The string was %s",input);
      write(parent2child[WRITE],input,strlen(input));
      read(child2parent[READ],output,strlen(output));
      printf("The output was %s",output);
    }
    else{
      strcpy(output,"Received!\n");
      close(child2parent[READ]);
      close(parent2child[WRITE]);
      read(parent2child[READ],input,strlen(input));
      write(child2parent[WRITE],output,strlen(output));
    }
  }
  return 0;
}
