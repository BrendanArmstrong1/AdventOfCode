#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdint.h>


int main(int argc, char **argv)
{
  FILE *fd=fopen("/home/brendan/ssd/AoC/AoC-2021/Dec-6/input.txt", "r");
  char *token;
  char buff[2000];
  fgets(buff,2000,fd);
  long long hist[9] = {};
  int entry = 0;
  token = strtok(buff,",");
  do{
    entry = atoi(token);
    hist[entry]++;
  }while(( token = strtok(NULL,",") ) != NULL);


  long long temp;
  for (int i = 0; i < 256; ++i) {
    temp = hist[0];
    for (int j = 1; j < 9; ++j) {
      hist[j-1] = hist[j];
      if(j == 8){
        hist[j] = 0;
      }
    }
    hist[8] += temp;
    hist[6] += temp;
  }

  long long sum = 0;
  for (int i = 0; i < 9; ++i) {
    sum += hist[i];
  }
  printf("%lld\n", sum);

  fclose(fd);
  return 0;
}





