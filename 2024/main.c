#include <stdio.h>
#include <stdlib.h>

void test1(char *path);

void part1(char *path);
void part2(char *path);

void test1(char *path)
{
  FILE *input;

  input = fopen(path, "r");
  if (!input) {
    exit(1);
  }
}

void part1(char *path)
{
  FILE *input;

  input = fopen(path, "r");
  if (!input) {
    exit(1);
  }
}

void part2(char *path)
{
  FILE *input;

  input = fopen(path, "r");
  if (!input) {
    exit(1);
  }
}

int main(void)
{
  test1("./test.txt");
  part1("./input.txt");
  part2("./input.txt");
  return 0;
}
