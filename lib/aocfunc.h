#ifndef AOC_CUSTOM_H
#define AOC_CUSTOM_H

typedef struct
{
  unsigned cols;
  unsigned rows;
  char   **body;
} Matrix_char;

char *get_input(char *path);
unsigned count_char_single(char *string, char countable_char);

void matrix_char_free(Matrix_char *mat);
void matrix_char_print(Matrix_char *mat);
char matrix_char_get_ii(Matrix_char *mat, int i, int j);
Matrix_char matrix_char_create_from_filename(char *filename);

#endif
