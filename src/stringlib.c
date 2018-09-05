#include <string.h>
#include <stdio.h>
#include <stdlib.h>






int CharNo(char* arr, char* character){
  int i;
  int no = 0;
  for(i = 0; i < strlen(arr); i++){
    if(arr[i] == *character){
      no++;
    }
  }
  return 0;

}

// void removeDuplicates(char* A, char* character, int flag){
//   int startFlag = 1;
//   int f = 0;
//   while(startFlag){
//     if(A[f++])
//   }
// }

int split(char* A, char*** B){

  char * pch;
  int counter = 0;
  //Copy input string (Because strtok is destructive)
  char* cpystring = (char*)malloc(sizeof(char*) * strlen(A));
  strcpy(cpystring, A);
  if(A[0] == '\n'){
    return -1;
  }
  //Begin Splitting procedure to count how many Strings we will have
  pch = strtok (A," \n");
  //If Empty String
  if(pch == NULL){
    return -1;
  }
  while (pch != NULL)
  {
    // printf("pch is %s\n", pch);
    counter++;
    pch = strtok (NULL, " \n");
  }
  // printf("counter is %d\n", counter);
  //Allocate String array
  char** output = (char**) malloc((sizeof(char*)) * (counter+1));
  //Copy String Array
  int i = 0;
  for(i = 0; i < counter; i++){
    output[i] = i==0 ? strtok(cpystring, " \n"):strtok(NULL, " \n");
  }

  output[i] = NULL;
  *B = output;

  return counter;
}
int btrstrcmp(char* arr1, char* arr2){
  int arr1len = strlen(arr1);
  int arr2len = strlen(arr2);
  char* arr1l = (char*) malloc(sizeof(char)*arr1len);
  char* arr2l = (char*) malloc(sizeof(char)*arr2len);
  strcpy(arr1l, arr1);
  strcpy(arr2l, arr2);

  printf("%s [%d], %s [%d]\n", arr1, arr1len, arr2, arr2len);
  if ((arr1len > arr2len)) {
    return 1;
  } else if ((arr2len > arr1len)) {
    return -1;
  } else {
    int i;
    char c;
    for(i = 0; i < arr1len; i++){
      c = arr1l[i] - arr2l[i];
      if (c >= 1) {
        return 1;
      } else if (c <= -1) {
        return -1;
      }
    }

  }
  return 25;
}

// void main(){
//   char A[50];
//   char** B;
//   fgets(A, 50, stdin);
//   int s = split(A, &B);
//   if(s == -1){
//     printf("NIL");
//   }
//   printf("%d", s);
//   int i;
//   for(i = 0; i <= s; i++){
//     printf("%s", B[i]);
//   }
//
// }
