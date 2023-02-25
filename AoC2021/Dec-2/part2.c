#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {

  FILE *fd = fopen("/home/brendan/S/AoC/AoC-2021/Dec-2/input.txt", "r");

  char buff[100];
  int depth = 0;
  int aim = 0;
  int pos = 0;

  // forward 10
  // down 13
  // up 12

  while (fgets(buff, 100, fd) != NULL) {
    if (buff[0] == 'f') {
      pos += atoi(&buff[8]);
      depth += aim * atoi(&buff[8]);
    }
    if (buff[0] == 'u') {
      aim -= atoi(&buff[3]);
    }
    if (buff[0] == 'd') {
      aim += atoi(&buff[5]);
    }
  }
  printf("depth: %d\npos: %d\nproduct: %d\n", depth, pos, depth * pos);

  fclose(fd);
  return 0;
}
