#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main(int argc, char **argv)
{
  FILE *fd = fopen("/home/brendan/ssd/AoC/AoC-2021/Dec-7/input.txt", "r");
  char buff[5000];
  fgets(buff, 5000, fd);
  char *token = strtok(buff, ",");
  int count = 0;
  int sum = 0;
  int average;
  int array[1000];
  int minimize[800];
  int running_sum = 0;

  do{
    sum += atoi(token);
    array[count] = atoi(token);
    count++;
  }while((token = strtok(NULL,",")) != NULL);
  average = sum/count;

  for (int i = 0; i < 800; ++i) {
    int value = average -400 + i;
    for (int j = 0; j < 1000; ++j) {
      for (int k = 0; k < abs(array[j] - value); ++k) {
        running_sum += k+1;
      }
    }
    minimize[i] = running_sum;
    running_sum = 0;
  }

  int lowest = minimize[0];
  int value = average - 400;
  for (int i = 0; i < 800; ++i) {
    if(minimize[i] < lowest){
      lowest = minimize[i];
      value = average - 400 + i;
    }
  }

  printf("Lowest: %d, Average: %d\n", lowest, value);

  fclose(fd);
  return 0;
}
