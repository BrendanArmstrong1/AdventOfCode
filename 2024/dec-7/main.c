#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "equations.c"

// Addition operation
long operation_add(long a, long b)
{
  return a + b;
}

// Multiplication operation
long operation_mul(long a, long b)
{
  return a * b;
}

// Maximum operation
long operation_max(long a, long b)
{
  return (a > b) ? a : b;
}

void equation_generate_operation_list(Equation *eq, Operation_list *ops)
{
  Operation available_ops[] = {
    operation_add,
    operation_mul,
  };
  size_t num_ops = sizeof(available_ops) / sizeof(available_ops[0]);

  // Total combinations is num_ops raised to (size-1)
  size_t total_combinations = 1;
  for (size_t i = 0; i < eq->size - 1; i++) {
    total_combinations *= num_ops;
  }

  // Allocate space for all operations in all combinations
  ops->op = malloc(total_combinations * (eq->size - 1) * sizeof(Operation));
  if (!ops->op) {
    fprintf(stderr, "Couldn't allocate operation combinations\n");
    exit(EXIT_FAILURE);
  }

  // Generate all possible combinations
  for (size_t combo = 0; combo < total_combinations; combo++) {
    size_t temp = combo;
    for (size_t i = 0; i < eq->size - 1; i++) {
      // Select operation based on current combination
      size_t op_index                     = temp % num_ops;
      ops->op[combo * (eq->size - 1) + i] = available_ops[op_index];
      temp /= num_ops;
    }
  }

  // Set metadata for the operation list
  ops->size  = total_combinations * (eq->size - 1); // Total number of operations
  ops->index = 0;                                   // Start from the first operation
}

Status_e operations_get_next_op(Operation_list *ops, Operation *op)
{
  if (ops->index >= ops->size)
    return COMPLETE;

  *op = ops->op[ops->index++];
  return IN_PROG;
}

void equation_run_processing(Equation_array *equations)
{
  unsigned       i;
  Operation_list ops = {0};
  Equation      *eq;
  int            found_solution;

  for (i = 0; i < equations->size; i++) {
    // Point to current equation
    eq = &equations->eqs[i];

    // Generate all possible operation combinations
    equation_generate_operation_list(eq, &ops);

    // Track whether a solution was found
    found_solution = 0;

    // Try each combination of operations
    for (size_t combo = 0; combo < (ops.size / (eq->size - 1)); combo++) {
      // Reset processed array to original state
      equation_reset_processed(eq);
      equation_print_equation(eq, ORIGINAL);

      // Prepare to use this specific combination
      ops.index = combo * (eq->size - 1);

      // Temporary variables to manage operation sequence
      Operation current_op;
      Status_e  stat;

      // Try this combination of operations
      while (1) {
        // Get next operation from current combination
        if (ops.index >= (combo + 1) * (eq->size - 1)) {
          // Reached end of this combination
          break;
        }

        // Select current operation
        current_op = ops.op[ops.index++];

        // Perform the operation
        stat = equation_perform_operation(eq, current_op);
        equation_print_equation(eq, PROCESSED);

        // Check if operation sequence is complete
        if (stat == COMPLETE) {
          // Check if result matches desired answer
          if (eq->processed[0] == eq->answer) {
            printf("Solution found for equation %u!\n", i);
            printf("Final result: %ld\n", eq->processed[0]);
            found_solution = 1;
            break;
          }
          break;
        }
      }

      // If solution found, move to next equation
      if (found_solution) {
        break;
      }
    }

    // If no solution found after trying all combinations
    if (!found_solution) {
      printf("No solution found for equation %u\n", i);
    }

    // Free the operation list for this equation
    free(ops.op);
    ops.op = NULL;
  }
}

void test1(char *path)
{
  FILE          *input;
  Equation_array equations = {0};

  input = fopen(path, "r");
  if (!input)
    exit(1);

  equation_generate_equations_from_file(input, &equations);

  equation_run_processing(&equations);

  equation_free_equations(&equations);
}

void part1(char *path)
{
  FILE          *input;
  Equation_array equations = {0};

  input = fopen(path, "r");
  if (!input)
    exit(1);

  equation_generate_equations_from_file(input, &equations);

  equation_run_processing(&equations);

  equation_free_equations(&equations);
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
