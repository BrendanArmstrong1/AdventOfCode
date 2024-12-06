#include <stdio.h>
#include <stdlib.h>

void test1(char *path)
{
  FILE  *input;
  char  *line = 0;
  size_t n    = 0;

  input = fopen(path, "r");
  if (!input)
    exit(1);

  while (getline(&line, &n, input) != -1)
    printf("%s", line);
}

void part1(char *_)
{
  printf("Part 1\n");
}

void part2(char *_)
{

  printf("Part 2\n");
}

int main(void)
{
  test1("./test.txt");
  /*part1("./input.txt");*/
  /*part2("./input.txt");*/
  return 0;
}
