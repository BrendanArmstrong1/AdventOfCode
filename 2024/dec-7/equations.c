#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
  unsigned size;
  unsigned size_processed;
  long     answer;
  long    *array;
  long    *processed;
} Equation;

typedef enum
{
  COMPLETE = 0,
  IN_PROG = 1,
} Status_e;

typedef enum
{
  ORIGINAL  = 0,
  PROCESSED = 1,
} Printing_status;

typedef struct
{
  unsigned  size;
  unsigned  curr;
  Equation *eqs;
} Equation_array;

typedef long (*Operation)(long a, long b);

typedef struct
{
  size_t     size;
  size_t     index;
  Operation *op;
} Operation_list;

Status_e equation_perform_operation(Equation *eq, Operation op)
{
  unsigned size;
  unsigned i;

  size = eq->size_processed;
  if (size == 1)
    return COMPLETE;

  /*Function gets used here*/
  eq->processed[0] = op(eq->processed[0], eq->processed[1]);

  if (size == 2) {
    eq->size_processed--;
    return COMPLETE;
  }

  for (i = 1; i < size; i++) {
    eq->processed[i] = eq->array[i + 1];
  }
  eq->size_processed--;
  return IN_PROG;
}

void equation_reset_processed(Equation *eq)
{
  unsigned i;
  for (i = 0; i < eq->size; i++)
    eq->processed[i] = eq->array[i];
}

void equation_free_equations(Equation_array *equations)
{
  unsigned i;

  if (!equations || !equations->eqs)
    return;

  for (i = 0; i < equations->size; i++) {
    if (equations->eqs[i].array) {
      free(equations->eqs[i].processed);
      equations->eqs[i].processed = NULL;
    }
    if (equations->eqs[i].array) {
      free(equations->eqs[i].array);
      equations->eqs[i].array  = NULL;
      equations->eqs[i].answer = 0;
      equations->eqs[i].size   = 0;
    }
  }
  free(equations->eqs);

  // Optionally, zero out the pointers to prevent use-after-free
  equations->eqs  = NULL;
  equations->size = 0;
  equations->curr = 0;
}

void equation_generate_equations_from_file(FILE *input, Equation_array *equations)
{
  char  *line = 0;
  size_t n    = 0;
  char  *temp;

  unsigned lines = 0;
  unsigned curr  = 0;

  unsigned i;

  int temp_array[200];

  while (getline(&line, &n, input) != -1)
    lines++;
  fseek(input, 0, SEEK_SET);

  equations->size = lines;
  equations->curr = 0;
  equations->eqs  = malloc(lines * sizeof(Equation));
  if (!equations->eqs) {
    fprintf(stderr, "Failed allocating all Equations!\n");
    equation_free_equations(equations);
    exit(EXIT_FAILURE);
  }

  while (getline(&line, &n, input) != -1) {
    lines = 0;
    temp  = strtok(line, ":");

    equations->eqs[curr].answer = strtol(temp, NULL, 10);
    while ((temp = strtok(NULL, " "))) {
      temp_array[lines] = atoi(temp);
      lines++;
    }

    equations->eqs[curr].array     = malloc(lines * sizeof(*equations->eqs[curr].array));
    equations->eqs[curr].processed = malloc(lines * sizeof(*equations->eqs[curr].processed));
    if (!equations->eqs[curr].array) {
      fprintf(stderr, "Failed allocating the %u array!\n", curr);
      equation_free_equations(equations);
      exit(EXIT_FAILURE);
    }
    for (i = 0; i < lines; i++) {
      equations->eqs[curr].array[i] = temp_array[i];
    }
    equations->eqs[curr].size           = lines;
    equations->eqs[curr].size_processed = lines;
    equation_reset_processed(&equations->eqs[curr]);
    curr++;
  }
}

int equation_print_equation(Equation *eq, Printing_status stat)
{
  unsigned long i;

  printf("answer: %ld, array: ", eq->answer);
  if (stat == PROCESSED) {
    for (i = 0; i < eq->size_processed; i++)
      printf("%ld ", eq->processed[i]);
  } else {
    for (i = 0; i < eq->size; i++)
      printf("%ld ", eq->array[i]);
  }
  if (stat == PROCESSED)
    printf(" Processed\n");
  else
    printf("\n");
  return 1;
}
