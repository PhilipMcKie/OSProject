
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>








//TODO: Looping command line, have version inherent in program
//TODO: Formatted I/O
//TODO: Pipe and rewrite (possibly here)



void main(){
  printf("Welcome to Tech OS\n>");
  char string[256];
  scanf("%s", string);
  printf("%s, Goodbye!\n", string);
}

//TODO: Forking and program execution
//TODO: replacing stdin of new program with pipe of this program (Possibly)!
//TODO: Error handle here if exec not found, but send error message to main thread for I/O handling
//TODO: Retrieving output of program
int parse(char* str){

}
