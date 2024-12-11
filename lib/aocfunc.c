#include <stdio.h>
#include <stdlib.h>

#include "aocfunc.h"

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

  string = malloc((length + 1) * sizeof(char));
  if (string) {
    length         = fread(string, sizeof(char), length, input);
    string[length] = '\0';
  }

  fclose(input);

  return string;
}

unsigned count_char_single(char *string, char countable_char)
{
  char     character_to_count;
  unsigned count;
  char    *temp;

  if (!countable_char)
    character_to_count = '\n';
  else
    character_to_count = countable_char;
  count = 0;

  temp = string;
  while (*temp) {
    if (*temp == character_to_count) {
      count += 1;
    }
    temp++;
  }
  return count;
}

Matrix_char matrix_char_create_from_filename(char *filename)
{
  Matrix_char return_value;

  FILE    *input;
  long     length;
  char    *string;
  char    *temp;
  unsigned i;
  unsigned j;

  input = fopen(filename, "r");
  if (!input)
    exit(1);

  fseek(input, 0, SEEK_END);
  length = ftell(input);
  fseek(input, 0, SEEK_SET);

  string = malloc((length + 1) * sizeof(char));
  if (!string) {
    fprintf(stderr, "Memory allocation for file failed.\n");
    free(string);
    exit(EXIT_FAILURE);
  }

  length         = fread(string, sizeof(char), length, input);
  string[length] = '\0';
  fclose(input);

  return_value.rows = 0;
  return_value.cols = 0;

  temp = string;
  while (*temp)
    if (*temp++ == '\n')
      return_value.rows++;
    else if (return_value.rows == 0)
      return_value.cols++;
  temp = string;

  return_value.body = malloc(return_value.rows * sizeof(*return_value.body));
  if (!return_value.body) {
    fprintf(stderr, "Memory allocation in.body col failed.\n");
    exit(EXIT_FAILURE);
  }
  for (i = 0; i < return_value.rows; i++) {
    return_value.body[i] = malloc(return_value.cols * sizeof(*return_value.body[0]));
    if (!return_value.body[i]) {
      fprintf(stderr, "Memory allocation in.body row failed.\n");
      exit(EXIT_FAILURE);
    }
    for (j = 0; j < return_value.cols; j++)
      return_value.body[i][j] = *temp++;
    temp++; /*skip the newlines*/
  }

  free(string);

  return return_value;
}

char matrix_char_get_ii(Matrix_char *mat, int i, int j)
{
  if (i < 0 || i >= (int)mat->cols)
    return 0;
  if (j < 0 || j >= (int)mat->rows)
    return 0;
  return mat->body[j][i];
}

void matrix_char_print(Matrix_char *mat)
{
  unsigned i;
  unsigned j;
  for (i = 0; i < mat->rows; i++) {
    for (j = 0; j < mat->cols; j++)
      printf("%c", mat->body[i][j]);
    printf("\n");
  }
  printf("\n");
}

void matrix_char_free(Matrix_char *mat)
{
  unsigned i;
  if (!mat || !mat->body)
    return;

  for (i = 0; i < mat->rows; i++) {
    if (mat->body[i])
      free(mat->body[i]);
  }
  free(mat->body);

  // Optionally, zero out the pointers to prevent use-after-free
  mat->body = NULL;
  mat->cols = 0;
  mat->rows = 0;
}

/*int main(void)*/
/*{*/
/*  char       *string;*/
/*  unsigned    count;*/
/*  Matrix_char matrix;*/
/**/
/*  string = get_input("./test.txt");*/
/*  count  = count_char_single(string, 'A');*/
/*  printf("%s\n%u\n", string, count);*/
/**/
/*  matrix = matrix_char_create_from_filename("./test.txt");*/
/*  matrix_char_print(&matrix);*/
/*  matrix_char_free(&matrix);*/
/**/
/*  return 0;*/
/*}*/
