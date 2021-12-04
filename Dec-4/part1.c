#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {

  FILE *fd = fopen("input.txt", "r");
  char buff[1000];
  char *token;

  fgets(buff, 1000, fd);
  printf("%s\n", buff);
  token = strtok(buff, ",");
  do {
    // Send token and file handler into matching function here
    printf("%s\n", token);
  } while ((token = strtok(NULL, ",")) != NULL);

  fclose(fd);
  return 0;
}
