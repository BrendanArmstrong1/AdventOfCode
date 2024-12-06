#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMBER       100
#define MAX_NUMBER_PAGES 200

void test1(char *path);
void part1(char *path);
void part2(char *path);

typedef struct
{
  int before[MAX_NUMBER];
  int after[MAX_NUMBER];
} number_rules;

void page_ordering_generate(FILE *input, number_rules number_list[MAX_NUMBER])
{
  char  *line = 0;
  size_t n    = 0;
  char  *temp;
  int    first;
  int    second;

  while (getline(&line, &n, input) != -1) {
    if (!strcmp(line, "\n\0"))
      break;

    temp  = line;
    first = atoi(temp);
    while (*temp++ != '|')
      temp++;
    second = atoi(temp);

    number_list[first].before[second] = 1;
    number_list[second].after[first]  = 1;
  }
}

int page_ordering_check(FILE *input, number_rules number_list[MAX_NUMBER], int swap)
{
  int return_value;

  char  *line = 0;
  char  *temp;
  size_t n = 0;

  int size;
  int page_array[MAX_NUMBER_PAGES] = {0};

  int i;
  int j;
  int item;
  int other;
  int found;

  return_value = 0;

  while (getline(&line, &n, input) != -1) {
    size = 0;
    temp = strtok(line, ",");

    while (temp) {
      page_array[size] = atoi(temp);
      temp             = strtok(NULL, ",");
      size++;
    }

    /*Here I am iterating through the page list and comparing it to the ordered list*/
    found = swap;
    for (i = 0; i < size; i++) {
      for (j = 0; j < size; j++) {
        if (j == i)
          continue;

        item  = page_array[i];
        other = page_array[j];

        if (j < i)
          if (number_list[item].before[other]) {
            found = !swap;
            if (swap) {
              page_array[i] = other;
              page_array[j] = item;

              i = 0;
              j = 0;
            }
          }

        if (j > i)
          if (number_list[item].after[other]) {
            found = !swap;
            if (swap) {
              page_array[i] = other;
              page_array[j] = item;

              i = 0;
              j = 0;
            }
          }
      }
    }
    if (!found) {
      for (i = 0; i < size; i++)
        printf("%d,", page_array[i]);
      printf("-> %d  ", page_array[size / 2]);
      return_value += page_array[size / 2];
    }

    printf("---\n");
  }

  return return_value;
}

void test1(char *path)
{
  FILE *input;
  int   i;
  int   j;
  int   value;

  number_rules number_list[MAX_NUMBER] = {0};
  for (i = 0; i < MAX_NUMBER; i++) {
    for (j = 0; j < MAX_NUMBER; j++) {
      number_list[i].before[j] = 0;
      number_list[i].after[j]  = 0;
    }
  }

  input = fopen(path, "r");
  if (!input)
    exit(1);

  page_ordering_generate(input, number_list);
  value = page_ordering_check(input, number_list, 1);

  printf("Returned Value: %d\n", value);

  fclose(input);
}

void part1(char *path)
{
  FILE *input;
  int   i;
  int   j;
  int   value;

  number_rules number_list[MAX_NUMBER] = {0};
  for (i = 0; i < MAX_NUMBER; i++) {
    for (j = 0; j < MAX_NUMBER; j++) {
      number_list[i].before[j] = 0;
      number_list[i].after[j]  = 0;
    }
  }

  input = fopen(path, "r");
  if (!input)
    exit(1);

  page_ordering_generate(input, number_list);
  value = page_ordering_check(input, number_list, 0);

  printf("Returned Value: %d\n", value);

  fclose(input);
}

void part2(char *path)
{
  FILE *input;
  int   i;
  int   j;
  int   value;

  number_rules number_list[MAX_NUMBER] = {0};
  for (i = 0; i < MAX_NUMBER; i++) {
    for (j = 0; j < MAX_NUMBER; j++) {
      number_list[i].before[j] = 0;
      number_list[i].after[j]  = 0;
    }
  }

  input = fopen(path, "r");
  if (!input)
    exit(1);

  page_ordering_generate(input, number_list);
  value = page_ordering_check(input, number_list, 1);

  printf("Returned Value: %d\n", value);

  fclose(input);
}

int main(void)
{
  /*test1("./test.txt");*/
  /*part1("./input.txt");*/
  part2("./input.txt");
  return 0;
}
