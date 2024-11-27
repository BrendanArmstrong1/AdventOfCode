#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

  FILE *fd = fopen("/home/brendan/ssd/AoC/AoC-2021/Dec-1/input.txt", "r");
  char buff[100];
  int array[2000];
  int index = 0;
  int count = 0;
  while (fgets(buff, 100, fd) != NULL) {
    array[index++] = atoi(buff);
  }
  for (int i = 3; i < 2000; ++i) {
    if (array[i] - array[i - 3] > 0) {
      count += 1;
    }
  }
  printf("%d\n", count);
  fclose(fd);
  return 0;
}
