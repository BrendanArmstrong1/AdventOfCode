#include <stdio.h>
#include <stdlib.h>

typedef struct
{
  char **matrix;
  int    cols;
  int    rows;
} Matrix;

typedef struct
{
  int x;
  int y;
} Direction;

typedef struct
{
  int       col;
  int       row;
  int       startx;
  int       starty;
  Direction dir;
} Location;

typedef struct
{
  unsigned long spaces;
  Direction     coords[10000];
} Matrix_account;

void location_increment(Location *loc)
{
  loc->col += loc->dir.x;
  loc->row += loc->dir.y;
}

void location_rotate(Location *loc)
{
  if (loc->dir.y) {
    loc->dir.x = loc->dir.y * -1;
    loc->dir.y = 0;
  } else {
    loc->dir.y = loc->dir.x;
    loc->dir.x = 0;
  }
}

void matrix_print(Matrix *mat)
{
  int i;
  int j;
  for (i = 0; i < mat->rows; i++) {
    for (j = 0; j < mat->cols; j++)
      printf("%c", mat->matrix[i][j]);
    printf("\n");
  }
  printf("\n");
}

void matrix_free(Matrix *mat)
{
  int i;
  if (!mat || !mat->matrix)
    return;

  for (i = 0; i < mat->rows; i++) {
    if (mat->matrix[i])
      free(mat->matrix[i]);
  }
  free(mat->matrix);

  // Optionally, zero out the pointers to prevent use-after-free
  mat->matrix = NULL;
  mat->cols   = 0;
  mat->rows   = 0;
}

void matrix_generate_mat(FILE *input, Matrix *mat)
{
  char  *buffer = 0;
  char  *temp   = 0;
  size_t length;
  int    i;
  int    j;

  fseek(input, 0, SEEK_END);
  length = ftell(input);
  fseek(input, 0, SEEK_SET);

  buffer = malloc((length + 1) * sizeof(*buffer));
  if (!buffer) {
    fprintf(stderr, "Memory allocation in buffer failed.\n");
    free(buffer);
    exit(EXIT_FAILURE);
  }

  fread(buffer, sizeof(*buffer), length, input);
  buffer[length] = '\0';

  mat->rows = 0;
  mat->cols = 0;

  temp = buffer;
  while (*temp)
    if (*temp++ == '\n')
      mat->rows++;
    else if (mat->rows == 0)
      mat->cols++;

  temp        = buffer;
  mat->matrix = malloc(mat->rows * sizeof(*mat->matrix));
  if (!mat->matrix) {
    fprintf(stderr, "Memory allocation in matrix col failed.\n");
    matrix_free(mat);
    exit(EXIT_FAILURE);
  }
  for (i = 0; i < mat->rows; i++) {
    mat->matrix[i] = malloc(mat->cols * sizeof(*mat->matrix[0]));
    if (!mat->matrix[i]) {
      fprintf(stderr, "Memory allocation in matrix row failed.\n");
      matrix_free(mat);
      exit(EXIT_FAILURE);
    }
    for (j = 0; j < mat->cols; j++)
      mat->matrix[i][j] = *temp++;
    temp++;
  }

  free(buffer);
}

void matrix_generate_copy(Matrix *from, Matrix *to)
{
  int i;
  int j;

  if (!to->matrix) {
    to->rows = from->rows;
    to->cols = from->cols;

    to->matrix = malloc(from->rows * sizeof(*from->matrix));
    if (!to->matrix) {
      fprintf(stderr, "Memory allocation in matrix col failed.\n");
      matrix_free(to);
      exit(EXIT_FAILURE);
    }
    for (i = 0; i < to->rows; i++) {
      to->matrix[i] = malloc(to->cols * sizeof(*to->matrix[0]));
      if (!to->matrix[i]) {
        fprintf(stderr, "Memory allocation in matrix row failed.\n");
        matrix_free(to);
        exit(EXIT_FAILURE);
      }
    }
  }

  for (i = 0; i < from->cols; i++)
    for (j = 0; j < from->rows; j++)
      to->matrix[j][i] = from->matrix[j][i];
}

char matrix_get(Matrix *mat, int i, int j)
{
  if (i < 0 || i >= mat->cols)
    return 0;
  if (j < 0 || j >= mat->rows)
    return 0;
  return mat->matrix[j][i];
}

void matrix_finding_start(Matrix *mat, Location *loc1, Location *loc2, Matrix_account *acct)
{
  int i;
  int j;
  /*assume we will find it ahead of time to save typeing*/
  acct->spaces = 1;
  for (i = 0; i < mat->cols; i++)
    for (j = 0; j < mat->rows; j++) {
      if (mat->matrix[j][i] == '^') {
        loc1->col    = i;
        loc1->row    = j;
        loc1->dir.y  = -1;
        loc2->col    = i;
        loc2->row    = j;
        loc2->dir.y  = -1;
        loc1->startx = i;
        loc1->starty = j;
        loc2->startx = i;
        loc2->starty = j;

        mat->matrix[j][i] = 'X';
        return;
      }
      if (mat->matrix[j][i] == 'v') {
        loc1->col   = i;
        loc1->row   = j;
        loc1->dir.y = 1;
        loc2->col   = i;
        loc2->row   = j;
        loc2->dir.y = -1;
        loc1->startx = i;
        loc1->starty = j;
        loc2->startx = i;
        loc2->starty = j;

        mat->matrix[j][i] = 'X';
        return;
      }
      if (mat->matrix[j][i] == '<') {
        loc1->col   = i;
        loc1->row   = j;
        loc1->dir.x = -1;
        loc2->col   = i;
        loc2->row   = j;
        loc2->dir.y = -1;
        loc1->startx = i;
        loc1->starty = j;
        loc2->startx = i;
        loc2->starty = j;

        mat->matrix[j][i] = 'X';
        return;
      }
      if (mat->matrix[j][i] == '>') {
        loc1->col   = i;
        loc1->row   = j;
        loc1->dir.x = 1;
        loc2->col   = i;
        loc2->row   = j;
        loc2->dir.y = -1;
        loc1->startx = i;
        loc1->starty = j;
        loc2->startx = i;
        loc2->starty = j;

        mat->matrix[j][i] = 'X';
        return;
      }
    }
  acct->spaces = 0;
  return;
}
