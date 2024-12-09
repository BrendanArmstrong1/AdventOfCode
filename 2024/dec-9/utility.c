#include <stdio.h>
#include <stdlib.h>

char *get_input(char *path)
{
  FILE *input;
  long  length;
  char *string;

  input = fopen(path, "r");
  if (!input)
    exit(1);

  fseek(input, 0, SEEK_END);
  length = ftell(input);
  fseek(input, 0, SEEK_SET);

  string = malloc(length * sizeof(char));
  if (string) {
    length = fread(string, sizeof(char), length, input);
  }
  string[length - 1] = '\0';

  fclose(input);

  return string;
}
