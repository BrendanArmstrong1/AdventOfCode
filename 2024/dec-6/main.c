#include <stdio.h>
#include <stdlib.h>

#include "matrix_stuff.c"

int matrix_running_the_loop(Matrix *mat, Location *loc1, Location *loc2, Matrix_account *acct)
{
  int           i;
  unsigned long index;
  int           limit;

  index = 0;
  limit = 0;
  while (matrix_get(mat, loc1->col + loc1->dir.x, loc1->row + loc1->dir.y)) {
    while (matrix_get(mat, loc1->col + loc1->dir.x, loc1->row + loc1->dir.y) == '#') {
      /*printf("Rotating loc1 %d\n", limit);*/
      location_rotate(loc1);
    }

    /*jump the second location by 2 points*/
    for (i = 0; i < 2; i++) {
      while (matrix_get(mat, loc2->col + loc2->dir.x, loc2->row + loc2->dir.y) == '#') {
        /*printf("Rotating loc2 %d\n", limit);*/
        location_rotate(loc2);
      }

      location_increment(loc2);
      if (loc2->col == loc1->col && loc2->row == loc1->row) {
        limit++;
        /*printf("Found on %d jump match 1x%d, 1y%d, 2x%d, 2y%d\n",*/
        /*       i,*/
        /*       loc1->col,*/
        /*       loc1->row,*/
        /*       loc2->col,*/
        /*       loc2->row);*/
        /*printf("             direction 1x%d, 1y%d, 2x%d, 2y%d\n",*/
        /*       loc1->dir.x,*/
        /*       loc1->dir.y,*/
        /*       loc2->dir.x,*/
        /*       loc2->dir.y);*/
        if (limit > 100)
          return 1;
        if (loc2->dir.x == loc1->dir.x && loc2->dir.y == loc1->dir.y) {
          return 1;
        }
      }
    }

    if (matrix_get(mat, loc1->col, loc1->row) != 'X') {
      acct->spaces += 1;
      acct->coords[index].x = loc1->col;
      acct->coords[index].y = loc1->row;
      index++;
    }

    mat->matrix[loc1->row][loc1->col] = 'X';
    location_increment(loc1);
    while (matrix_get(mat, loc1->col + loc1->dir.x, loc1->row + loc1->dir.y) == '#') {
      /*printf("Rotating loc1 %d\n", limit);*/
      location_rotate(loc1);
    }
  }
  mat->matrix[loc1->row][loc1->col] = 'X';
  acct->spaces += 1;
  acct->coords[index].x = loc1->col;
  acct->coords[index].y = loc1->row;
  return 0;
}

int matrix_find_path(Matrix *mat, Matrix_account *acct)
{
  Location loc1 = {0};
  Location loc2 = {0};

  /*Finding the Guard with his orientation*/
  acct->spaces = 0;
  matrix_finding_start(mat, &loc1, &loc2, acct);
  if (!acct->spaces) {
    fprintf(stderr, "Couldn't find starting point in matrix\n");
    exit(EXIT_FAILURE);
  }

  return matrix_running_the_loop(mat, &loc1, &loc2, acct);
}

void test1(char *path)
{
  FILE          *input;
  Matrix         mat;
  Matrix         mat_backup;
  Matrix_account acct  = {0};
  Matrix_account acct2 = {0};

  unsigned long number_of_loops;
  unsigned long length;
  unsigned long i;
  unsigned long loop_found;

  int x, y;

  input = fopen(path, "r");
  if (!input)
    exit(1);

  matrix_generate_mat(input, &mat);
  matrix_generate_copy(&mat, &mat_backup);
  matrix_find_path(&mat, &acct);

  length          = acct.spaces;
  number_of_loops = 2;
  for (i = 0; i < length; i++) {
    matrix_generate_copy(&mat_backup, &mat);
    loop_found = 0;

    x = acct.coords[i].x;
    y = acct.coords[i].y;

    mat.matrix[y][x] = '#';
    loop_found       = matrix_find_path(&mat, &acct2);
    number_of_loops += loop_found;
  }

  matrix_free(&mat);
  matrix_free(&mat_backup);

  printf("spaces walked: %lu\n", acct.spaces);
  printf("loops found walked: %lu\n", number_of_loops);
}

void part1(char *path)
{
  FILE          *input;
  Matrix         mat;
  Matrix_account acct = {0};

  input = fopen(path, "r");
  if (!input)
    exit(1);

  matrix_generate_mat(input, &mat);
  matrix_find_path(&mat, &acct);
  matrix_free(&mat);

  printf("spaces walked: %lu\n", acct.spaces);
}

void part2(char *path)
{
  FILE          *input;
  Matrix         mat;
  Matrix         mat_backup;
  Matrix_account acct  = {0};
  Matrix_account acct2 = {0};

  unsigned long number_of_loops;
  unsigned long length;
  unsigned long i;
  unsigned long loop_found;

  int x, y;

  input = fopen(path, "r");
  if (!input)
    exit(1);

  matrix_generate_mat(input, &mat);
  matrix_generate_copy(&mat, &mat_backup);
  matrix_find_path(&mat, &acct);

  length = acct.spaces;

  number_of_loops = 0;
  for (i = 0; i < length; i++) {
    matrix_generate_copy(&mat_backup, &mat);
    mat.matrix[y][x] = '#';
    loop_found       = 0;

    x = acct.coords[i].x;
    y = acct.coords[i].y;

    loop_found = matrix_find_path(&mat, &acct2);
    number_of_loops += loop_found;
  }

  matrix_free(&mat);
  matrix_free(&mat_backup);

  printf("loops found walked: %lu\n", number_of_loops);
}

int main(void)
{
  /*test1("./test.txt");*/
  printf("Part1 solution:\n");
  part1("./input.txt");
  printf("Part2 solution:\n");
  part2("./input.txt");
  return 0;
}
