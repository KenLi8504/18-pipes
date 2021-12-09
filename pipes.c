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
  char intermediate[10000];
  pipe(parent2child);
  pipe(child2parent);
  int f = fork();

  //child
  while (1){
    if (f == 0){
      close(child2parent[READ]);
      close(parent2child[WRITE]);
      read(parent2child[READ],input,10000);
      strcpy(intermediate,input);
      //printf("The child here received here was %s\n",input);
      //printf("The output here was %s\n",intermediate);
      int counter = 0;
      for (int i = 0; intermediate[i]!='\0'; i++) {
        //printf("This char is %c\n",intermediate[i]);
        //printf("The counter is %d",counter);
        if (counter == 0){
          if(intermediate[i] >= 'a' && intermediate[i] <= 'z') {
            intermediate[i] = intermediate[i] - 32;
            counter = counter + 1;
            //printf("OPTION 1");
          }
          else if (intermediate[i] >= 'A' && intermediate[i] <= 'Z'){
            counter = counter + 1;
            //printf("OPTION 2");
          }
        }
        else if (counter == 1){
          if (intermediate[i] >= 'a' && intermediate[i] <= 'z') {
            counter = counter - 1;
            //printf("OPTION 3");
          }
          else if (intermediate[i] >= 'A' && intermediate[i] <= 'Z'){
            intermediate[i] = intermediate[i] + 32;
            counter = counter - 1;
            //printf("OPTION 4");
          }
        }
      //printf("The new string is %s",intermediate);
      }
      strcpy(output,intermediate);
      // printf("The length of the input is %ld\n",strlen(input));
      //printf("The output here was %s\n",intermediate);
      write(child2parent[WRITE],output,10000);
    }

    //parent
    else{
      close(child2parent[WRITE]);
      close(parent2child[READ]);
      printf("Enter a string: ");
      fgets(input,10000,stdin);
      char input_length_adjusted [strlen(input)];
      strcpy(input_length_adjusted,input);
      // //printf("The string was %s",input);
      write(parent2child[WRITE],input_length_adjusted,10000);
      read(child2parent[READ],output,10000);
      printf("The output from the child was %s\n",output);
    }
  }
  return 0;
}
