#include <aocfunc.h>
#include <stdio.h>

void test1(char *path)
{
  Matrix_char matrix;

  matrix = matrix_char_create_from_filename(path);

  matrix_char_print(&matrix);
}

void part1(char *_) {}
void part2(char *_) {}

int main(void)
{
  test1("./test.txt");
  /*part1("./input.txt");*/
  /*part2("./input.txt");*/
  return 0;
}
