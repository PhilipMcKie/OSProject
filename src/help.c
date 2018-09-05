#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
//++++++++++++++++++++++++++++++++++++++++++
// begin main
int checkHelp(char A[])
{
    DIR *d;
    struct dirent *dir;
    d = opendir("../etc/help");
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

int main(int argc, char* A[])
{
     FILE *fptr;

    char filename[100], c;
    //scanf("%s", filename);

    // Open file
    // if(checkHelp(A[1]) == 0 ){
    //   printf("Unable to locate help file! Please read documentation!11!!1");
    //   return -1;
    // }
     char file[100];
     char* dir = "etc/help/";
     if(A[1] == NULL){
       
       strncpy(file, "etc/help/help", 100);
     }
     else{
     strncpy(file, dir, 100);
     strncat(file, A[1], 100);
   }

    fptr = fopen(file, "r");
    if (fptr == NULL)
    {
        printf("Cannot find file! Please find the closest fire extinguisher.\n");
        exit(0);
    }

    // Read contents from file
    c = fgetc(fptr);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(fptr);
    }

    fclose(fptr);
    return 0;


}
//end of main
//-----------------------------------------
