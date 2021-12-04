#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {

  FILE *fd = fopen("/home/brendan/S/AoC/AoC-2021/Dec-3/input.txt", "r");
  int count[12] = {};
  char buff[20];
  memset(buff, '0', 20);
  int gamma = 0;
  int epsilon = 0;

  while (fgets(buff, 20, fd) != NULL) {
    for (int i = 0; i < 12; ++i) {
      count[i] += buff[i] - '0';
    }
  }

  for (int i = 0; i < 12; ++i) {
    gamma += (int)pow(2, 11 - i) * (count[i] > 500);
    epsilon += (int)pow(2, 11 - i) * (count[i] < 500);
  }

  printf("%d\n%d\n%d\n", gamma, epsilon, gamma * epsilon);
  fclose(fd);
  return 0;
}
