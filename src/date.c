#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>



void printDate(){
time_t rawtime;
struct tm * date;
char buffer[100];

time (&rawtime);
  date = localtime (&rawtime);

  strftime(buffer,100,"The date is currently %x", date);
  puts(buffer);

  return ;
}

void setDate(char* dt){
  // struct tm date;
  // strptime(dt, "%d/%m/%Y", &date);
  // char buffer[100];
  // strftime(buffer, 100, "The date passed in is %x", &date);


  char x[20];
  strncpy(x, dt, 20);
  int day,month,year;
  char* parsedString = strtok(x, "/\n");
  if(parsedString == NULL){
    printf("Date format error!");
    return;
  }
  day = atoi(parsedString);
  parsedString = strtok(NULL, "/\n");
  if(parsedString == NULL){
    printf("Date format error!");
    return;
  }
  month = atoi(parsedString);
  parsedString = strtok(NULL, "/\n");
  if(parsedString == NULL){
    printf("Date format error!");
    return;
  }
  year = atoi(parsedString);

  if(day > 31 || day < 1){
    printf("Date format error!");
    return;
  }
  if(month > 12 || month < 1){
    printf("Date format error!");
    return;
    if(month == 2 && day >28 ){
      printf("Date format error!");
      return;
    }
    if(month == 4 && day >30){
      printf("Date format error!");
      return;
    }

    if(month == 6 && day >30){
      printf("Date format error!");
      return;
    }
    if(month == 9 && day >30){
      printf("Date format error!");
      return;
    }
    if(month == 11 && day >30){
      printf("Date format error!");
      return;
    }
  }

  if(year < 1900 || year >2100){
    printf("Date format error!");
    return;
  }
  struct tm* datetime;
  time_t t = time(0);

  datetime = localtime(&t);
  if(datetime){
  datetime->tm_mday = day;
  datetime->tm_mon = month -1;
  datetime->tm_year = year - 1900;
  int test = mktime(datetime);
  if(test == -1){
    printf("Error setting date! Are you the root user?");
  }
  const struct timeval tv = {mktime(datetime), 0};
  settimeofday(&tv, 0);
}
printf("Time changed!\nNew date is: ");
printDate();
}


int main(int argc ,char* argv[])
{
    if(argc == 1){
      printDate();
    }
    else if(strcmp(argv[1], "set") == 0){
    setDate(argv[2]);
  }
  else{
    printf("Date syntax error, please read documentation!\n");
  }
  //setDate(argv[1]);
}
