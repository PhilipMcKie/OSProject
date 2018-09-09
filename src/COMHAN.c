
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include "stringlib.h"

typedef struct pthread_information{
  char* COMNAME;
  char pipename;
  char** COMLINE;
}pinf;

char A[] = "Version R1.1\n09/09/2018\nBrandon Dale\nJoshua Ellison\nPhilip McKie\n\nTechOS>";

void Version(){
  printf("%s", A);
}

int checkBin(char A[])
{
    DIR *d;
    struct dirent *dir;
    d = opendir("./bin");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
          if(dir->d_name[0] != '.'){
            if(strcmp(A, dir->d_name) == 0)
            return 1;
          }
        }
        closedir(d);
    }
    return(0);
}






int menu(){
  pinf* p1 =(pinf*) malloc(sizeof(pinf));
  int flag = 1;
  DIR *d;
  struct dirent *dir;
  d = opendir(".");

  printf("Welcome to Tech OS\nTechOS>");
  char input[50];
  char** inputArray;
  do{
  fgets(input, 50, stdin);
  int argsc = split(input, &inputArray);
  if(argsc == -1){
    printf("\nTechOS>");
    continue;
  }
  if((strcmp(inputArray[0], "terminate")) == 0){
    printf("G o o d b y e!\n");
    break;
  }
  if((strcmp(inputArray[0], "version")) == 0){
    Version();
    continue;
  }

  if(checkBin(inputArray[0]) != 1){
    printf("Command not found! Please check the documentation!\nTechOS>");
    continue;
  }
  char COMNAME[100];
  strcpy(COMNAME, "./bin/");
  strncat(COMNAME, inputArray[0], 100);
  p1->COMNAME = COMNAME;
  p1->COMLINE = inputArray;



  pid_t pid = fork();
    if(pid == 0){
      int i = execv((p1->COMNAME), p1->COMLINE);
    }
    else{
      waitpid(pid, 0, 0);
    }

  printf("\nTechOS>");
}while(1);

}

int main(){
  menu();
}
