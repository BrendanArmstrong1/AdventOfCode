#include <aocfunc.h>
#include <stdio.h>
#include <stdlib.h>

#define NODE_SIZE 100

void find_paths_part2(Matrix_char *matrix, int i, int j, unsigned *visited)
{
  int new_value;
  int value;
  int d;
  int ni;
  int nj;

  value = matrix_char_get_ii(matrix, i, j) - '0';
  if (value == 9) {
    *visited += 1;
  }

  int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

  for (d = 0; d < 4; d++) {
    ni = i + directions[d][0];
    nj = j + directions[d][1];

    if (matrix_char_get_ii(matrix, ni, nj)) {
      new_value = matrix_char_get_ii(matrix, ni, nj) - '0';
      if (new_value - value == 1) {
        find_paths_part2(matrix, ni, nj, visited);
      }
    }
  }
}

unsigned find_paths(Matrix_char *matrix, int i, int j, unsigned **visited)
{
  int      new_value;
  int      value;
  int      d;
  int      ni;
  int      nj;
  unsigned sum = 0;

  visited[i][j] = 1;

  value = matrix_char_get_ii(matrix, i, j) - '0';
  if (value == 9) {
    return 1;
  }

  int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

  for (d = 0; d < 4; d++) {
    ni = i + directions[d][0];
    nj = j + directions[d][1];

    if (matrix_char_get_ii(matrix, ni, nj) && !visited[ni][nj]) {
      new_value = matrix_char_get_ii(matrix, ni, nj) - '0';
      if (new_value - value == 1) {
        sum += find_paths(matrix, ni, nj, visited);
      }
    }
  }

  return sum;
}

void scan_matrix_part2(Matrix_char *matrix)
{
  int      i;
  int      j;
  unsigned value;
  unsigned visited;

  value = 0;

  for (j = 0; j < (int)matrix->rows; j++) {
    for (i = 0; i < (int)matrix->cols; i++) {
      if (matrix_char_get_ii(matrix, i, j) == '0') {
        visited = 0;
        find_paths_part2(matrix, i, j, &visited);
        value += visited;
      }
    }
  }

  printf("%u\n", value);
}

void scan_matrix(Matrix_char *matrix)
{
  int      i;
  int      j;
  int      k;
  int      y;
  unsigned value;

  value = 0;

  unsigned **visited = (unsigned **)malloc(matrix->rows * sizeof(unsigned *));
  for (i = 0; i < (int)matrix->rows; i++) {
    visited[i] = (unsigned *)calloc(matrix->cols, sizeof(unsigned));
  }

  for (j = 0; j < (int)matrix->rows; j++) {
    for (i = 0; i < (int)matrix->cols; i++) {
      if (matrix_char_get_ii(matrix, i, j) == '0') {
        for (k = 0; k < (int)matrix->rows; k++) {
          for (y = 0; y < (int)matrix->cols; y++) {
            visited[k][y] = 0;
          }
        }
        value += find_paths(matrix, i, j, visited);
      }
    }
  }

  printf("%u\n", value);

  for (int i = 0; i < (int)matrix->rows; i++) {
    free(visited[i]);
  }
  free(visited);
}

void test1(char *path)
{
  Matrix_char matrix;

  matrix = matrix_char_create_from_filename(path);

  /*scan_matrix(&matrix);*/
  scan_matrix_part2(&matrix);

  matrix_char_free(&matrix);
}

void part1(char *path)
{
  Matrix_char matrix;

  matrix = matrix_char_create_from_filename(path);

  scan_matrix(&matrix);

  matrix_char_free(&matrix);
}

void part2(char *path)
{
  Matrix_char matrix;

  matrix = matrix_char_create_from_filename(path);

  scan_matrix_part2(&matrix);

  matrix_char_free(&matrix);
}

int main(void)
{
  /*test1("./test.txt");*/
  /*part1("./input.txt");*/
  part2("./input.txt");
  return 0;
}
