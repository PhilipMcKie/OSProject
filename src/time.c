#include <stdio.h>
#include <time.h>


int main()
{
time_t rawtime;
struct tm * timer;
char buffer[100];

time (&rawtime);
  timer = localtime (&rawtime);

  strftime(buffer,100,"The time is currently %I:%M:%S %p", timer);
  puts(buffer);

  return 0;
}
