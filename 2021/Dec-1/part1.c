#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

  FILE *fd = fopen("/home/brendan/S/AoC/2021/Dec-1/input.txt", "r");
  char buff[100];
  int previous = 999999;
  int measurement;
  int count = 0;
  while (fgets(buff, 100, fd)) {
    measurement = atoi(buff);
    if (measurement > previous) {
      count += 1;
    }
    previous = measurement;
  }

  printf("%d\n", count);
  fclose(fd);
  return 0;
}
