#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
  char **matrix;
  int    rows;
  int    cols;
} Xmas_map;

Xmas_map xmas_generate(FILE *input)
{
  Xmas_map map = {0, 0, 0};

  char  *buffer = 0;
  char  *temp   = 0;
  size_t length;
  int    i;

  fseek(input, 0, SEEK_END);
  length = ftell(input);
  fseek(input, 0, SEEK_SET);

  buffer = malloc((length + 1) * sizeof(*buffer));
  if(!buffer) {
    fprintf(stderr, "Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }

  fread(buffer, sizeof(*buffer), length, input);
  buffer[length] = '\0';

  temp = buffer;
  while(*temp) {
    if(*temp == '\n') {
      map.rows++;
    } else if(map.rows == 0) {
      map.cols++;
    }
    temp++;
  }

  if(map.rows == 0 || map.cols == 0) {
    fprintf(stderr, "Invalid file format.\n");
    free(buffer);
    exit(EXIT_FAILURE);
  }

  map.matrix = malloc(map.rows * sizeof(char *));
  if(!map.matrix) {
    fprintf(stderr, "Matrix memory allocation failed.\n");
    free(buffer);
    exit(EXIT_FAILURE);
  }

  temp = buffer;
  for(i = 0; i < map.rows; i++) {
    map.matrix[i] = malloc((map.cols) * sizeof(char));
    if(!map.matrix[i]) {
      fprintf(stderr, "Row memory allocation failed.\n");
      free(buffer);
      exit(EXIT_FAILURE);
    }
    strncpy(map.matrix[i], temp, map.cols);
    map.matrix[i][map.cols] = '\0';
    temp += map.cols + 1;
  }

  free(buffer);

  return map;
}

void xmas_print(Xmas_map *map)
{
  int i;
  for(i = 0; i < map->rows; i++) { printf("%c", map->matrix[i][i]); }
  printf("\n");
  printf("\n");
}

void xmas_free(Xmas_map *map)
{
  for(int i = 0; i < map->rows; i++) { free(map->matrix[i]); }
}

char xmas_get(Xmas_map *map, int i, int j)
{
  if(i < 0 || i > map->cols - 1) return 'G';
  if(j < 0 || j > map->rows - 1) return 'G';
  return map->matrix[i][j];
}
unsigned long xmas_scan_direction(
  Xmas_map *map, int i, int j, int ii, int jj, char *str, int str_idx)
{
  int iii;
  int jjj;
  int delta_i;
  int delta_j;

  if(str[str_idx] == 0) { return 1; }
  if(xmas_get(map, ii, jj) == str[str_idx]) {
    str_idx++;
    delta_i = ii - i;
    delta_j = jj - j;
    iii     = ii + delta_i;
    jjj     = jj + delta_j;
    return xmas_scan_direction(map, ii, jj, iii, jjj, str, str_idx);
  }

  return 0;
}

/*Part 1*/
unsigned int xmas_find_xmas(Xmas_map *map)
{
  int  i;
  int  j;
  int  ii;
  int  jj;
  int  str_idx = 0;
  char str[]   = "XMAS";

  unsigned int val = 0;

  for(i = 0; i < map->cols; i++) {
    for(j = 0; j < map->rows; j++) {
      str_idx = 0;
      if(xmas_get(map, i, j) == str[str_idx]) {
        str_idx++;
        for(ii = i - 1; ii <= i + 1; ii++) {
          for(jj = j - 1; jj <= j + 1; jj++) {
            if(ii == i && jj == j) continue;
            val += xmas_scan_direction(map, i, j, ii, jj, str, str_idx);
          }
        }
      }
    }
  }

  return val;
}

/*Part 2*/
unsigned int xmas_find_x_mas(Xmas_map *map)
{
  int i;
  int j;
  int x;
  int mas;

  unsigned int val = 0;

  for(i = 0; i < map->cols; i++) {
    for(j = 0; j < map->rows; j++) {
      if(xmas_get(map, i, j) == 'A') {
        /*Found an A, I fuckin Love this solution*/
        x   = 0;
        mas = 0;

        if(xmas_get(map, i - 1, j - 1) == 'S')
          if(xmas_get(map, i + 1, j + 1) == 'M') x = 1;

        if(xmas_get(map, i - 1, j - 1) == 'M')
          if(xmas_get(map, i + 1, j + 1) == 'S') x = 1;

        if(xmas_get(map, i + 1, j - 1) == 'S')
          if(xmas_get(map, i - 1, j + 1) == 'M') mas = 1;

        if(xmas_get(map, i + 1, j - 1) == 'M')
          if(xmas_get(map, i - 1, j + 1) == 'S') mas = 1;

        val += x * mas;
        /*End of Found an A*/
      }
    }
  }

  return val;
}

void test1(char *path);

void part1(char *path);
void part2(char *path);


void test1(char *path)
{
  FILE    *input;
  Xmas_map map;

  unsigned int number;

  input = fopen(path, "r");
  if(!input) { exit(1); }

  map = xmas_generate(input);

  number = xmas_find_x_mas(&map);

  printf("\nNumber of XMAS = %d\n", number);

  xmas_free(&map);

  fclose(input);
}

void part1(char *path)
{
  FILE    *input;
  Xmas_map map;

  unsigned int number;

  input = fopen(path, "r");
  if(!input) { exit(1); }

  map = xmas_generate(input);

  number = xmas_find_xmas(&map);

  printf("\nNumber of XMAS = %d\n", number);

  xmas_free(&map);

  fclose(input);
}

void part2(char *path)
{
  FILE    *input;
  Xmas_map map;

  unsigned int number;

  input = fopen(path, "r");
  if(!input) { exit(1); }

  map = xmas_generate(input);

  number = xmas_find_x_mas(&map);

  printf("\nNumber of XMAS = %d\n", number);

  xmas_free(&map);

  fclose(input);
}

int main(void)
{
  test1("./test.txt");
  part1("./input.txt");
  part2("./input.txt");
  return 0;
}
