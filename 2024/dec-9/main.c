#include <stdio.h>
#include <stdlib.h>

#include "utility.c"

#define SPACE     200000
#define MAX_EMPTY 3000

unsigned *create_unzipped(unsigned sum, char *string, unsigned **empty_index)
{
  unsigned *unzipped;
  char     *temp;
  char      temp2[2];
  int       i;
  int       number;
  unsigned  file_index;
  unsigned  unzipped_index;
  unsigned  empty_sub_index;

  char file = 1;

  unzipped = malloc(sum * sizeof(*unzipped));

  file_index     = 0;
  unzipped_index = 0;
  temp           = string;
  temp2[1]       = 0;

  while (*temp) {
    temp2[0] = temp[0];
    number   = atoi(temp2);
    if (file) { /*this is a file*/
      if (!number)
        printf("Found a 0 size file\n");
      for (i = 0; i < number; i++)
        unzipped[unzipped_index++] = file_index;
      file = 0;
      file_index++;
    } else { /*this is empty space*/
      empty_sub_index = 0;
      while (empty_sub_index < MAX_EMPTY && empty_index[number][empty_sub_index] != 0)
        empty_sub_index++;
      if (empty_sub_index < MAX_EMPTY)
        empty_index[number][empty_sub_index] = unzipped_index;

      for (i = 0; i < number; i++)
        unzipped[unzipped_index++] = SPACE;
      file = 1;
    }
    temp++;
  }

  return unzipped;
}

void get_sum(char *string, unsigned *sum)
{
  char *temp;
  char  temp2[2];

  *sum     = 0;
  temp     = string;
  temp2[1] = 0;
  while (*temp) {
    temp2[0] = temp[0];
    *sum += atoi(temp2);
    temp++;
  }
}

void two_pointer_swap(unsigned *unzipped, unsigned sum)
{
  unsigned start;
  unsigned end;

  start = 0;
  end   = sum - 1;
  while (start < end) {
    while (unzipped[end] == SPACE) {
      end--;
    }

    if (unzipped[start] == SPACE) {
      unzipped[start] = unzipped[end];
      unzipped[end]   = SPACE;
      end--;
    }
    start++;
  }
}

unsigned find_min_empty(unsigned **empty_index, unsigned *index)
{
  unsigned i;
  unsigned return_value;

  return_value = 99999999;

  for (i = *index; i < 10; i++) {
    if (empty_index[i][0]) {
      if (empty_index[i][0] < return_value) {
        return_value = empty_index[i][0];
        *index       = i;
      }
    }
  }
  return return_value;
}

unsigned get_empty_index(unsigned **empty_index, unsigned index)
{
  unsigned return_value;
  unsigned i;
  unsigned difference;
  unsigned new_empty;
  unsigned initial_length;

  i          = 0;
  difference = 0;

  initial_length = index;
  /*I need to iterate from right to left instead of left to right*/
  return_value = find_min_empty(empty_index, &index);
  difference   = index - initial_length;

  while (empty_index[index][i]) {
    empty_index[index][i] = empty_index[index][i + 1];
    i++;
  }

  new_empty = return_value + initial_length;
  if (difference) {
    i = 0;
    while (empty_index[difference][i]) {
      i++;
    }

    while (i > 0 && empty_index[difference][i - 1] >= new_empty) {
      empty_index[difference][i] = empty_index[difference][i - 1];
      i--;
    }
    empty_index[difference][i + 1] = empty_index[difference][i];
    empty_index[difference][i]     = new_empty;
  }
  return return_value;
}

void two_pointer_swap_part2(unsigned *unzipped, unsigned sum, unsigned **empty_index)
{
  unsigned end;
  unsigned length;
  unsigned value;
  unsigned index;
  unsigned i;

  end = sum - 1;
  while (end > 0) {
    length = 0;
    while (unzipped[end] == SPACE) {
      end--;
    }
    value = unzipped[end];
    if (value == 0) {
      end = 0;
      break;
    }

    while (unzipped[end] == value) {
      length++;
      end--;
    }

    end++;
    index = get_empty_index(empty_index, length);

    if (index == 0) {
      end--;
      continue;
    }

    if (index <= end) {
      for (i = 0; i < length; i++) {
        unzipped[index + i] = unzipped[end + i];
        unzipped[end + i]   = SPACE;
      }
    }
    end--;
  }
}

unsigned long get_checksum(unsigned *unzipped, unsigned sum)
{
  unsigned long checksum;
  unsigned      index;
  unsigned     *temp;

  checksum = 0;
  index    = 0;
  temp     = unzipped;

  while (index < sum) {
    if (temp[0] != SPACE)
      checksum += index * temp[0];
    index++;
    temp++;
  }
  return checksum;
}

void print_unzipped(unsigned *unzipped, unsigned sum)
{

  unsigned i;
  for (i = 0; i < sum; i++)
    if (unzipped[i] == SPACE)
      printf(".");
    else
      printf("%u", unzipped[i]);
  printf("\n");
}

void test1(char *path)
{
  char     *string;
  unsigned *unzipped;

  int           i;
  int           j;
  unsigned      sum;
  unsigned long checksum;
  unsigned    **empty_index;

  empty_index = malloc(10 * sizeof(*empty_index));
  for (i = 0; i < 10; i++) {
    empty_index[i] = malloc(MAX_EMPTY * sizeof(*empty_index[0]));
    for (j = 0; j < MAX_EMPTY; j++)
      empty_index[i][j] = 0;
  }

  string = get_input(path);
  get_sum(string, &sum);
  unzipped = create_unzipped(sum, string, empty_index);

  print_unzipped(unzipped, sum);
  /*two_pointer_swap(unzipped, sum);*/
  two_pointer_swap_part2(unzipped, sum, empty_index);
  checksum = get_checksum(unzipped, sum);
  print_unzipped(unzipped, sum);

  printf("%lu\n", checksum);

  for (i = 0; i < 10; i++)
    free(empty_index[i]);
  free(empty_index);
  free(unzipped);
  free(string);
}

void part1(char *path)
{
  char     *string;
  unsigned *unzipped;

  int           i;
  int           j;
  unsigned      sum;
  unsigned long checksum;
  unsigned    **empty_index;

  empty_index = malloc(10 * sizeof(*empty_index));
  for (i = 0; i < 10; i++) {
    empty_index[i] = malloc(MAX_EMPTY * sizeof(*empty_index[0]));
    for (j = 0; j < MAX_EMPTY; j++)
      empty_index[i][j] = 0;
  }

  string = get_input(path);
  get_sum(string, &sum);
  unzipped = create_unzipped(sum, string, empty_index);
  two_pointer_swap(unzipped, sum);
  checksum = get_checksum(unzipped, sum);

  printf("%lu\n", checksum);

  for (i = 0; i < 10; i++)
    free(empty_index[i]);
  free(empty_index);
  free(unzipped);
  free(string);
}

void part2(char *path)
{
  char     *string;
  unsigned *unzipped;

  int           i;
  int           j;
  unsigned      sum;
  unsigned long checksum;
  unsigned    **empty_index;

  empty_index = malloc(10 * sizeof(*empty_index));
  for (i = 0; i < 10; i++) {
    empty_index[i] = malloc(MAX_EMPTY * sizeof(*empty_index[0]));
    for (j = 0; j < MAX_EMPTY; j++)
      empty_index[i][j] = 0;
  }

  string = get_input(path);
  get_sum(string, &sum);
  unzipped = create_unzipped(sum, string, empty_index);

  /*print_unzipped(unzipped, sum);*/
  /*two_pointer_swap(unzipped, sum);*/
  two_pointer_swap_part2(unzipped, sum, empty_index);
  checksum = get_checksum(unzipped, sum);
  /*print_unzipped(unzipped, sum);*/

  printf("%lu\n", checksum);

  for (i = 0; i < 10; i++)
    free(empty_index[i]);
  free(empty_index);
  free(unzipped);
  free(string);
}

int main(void)
{
  test1("./test.txt");
  part1("./input.txt");
  part2("./input.txt");
  return 0;
}
