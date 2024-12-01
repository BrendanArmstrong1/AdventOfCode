#include <stdio.h>
#include <stdlib.h>

typedef struct Lists
{
  int **list1;
  int **list2;
  int   size;
  int   offset;
} lists;

lists generate_lists(char *content);
void  sort_lists(lists *separate_lists);
void  find_distance(lists *separate_lists);
void  free_lists(lists *separate_lists);

void part1(void);
void part2(void);

int main(void)
{
  part1();
  return 0;
}

void part1(void)
{
  FILE *input;
  char *contents;
  long  fsize;
  lists separate_lists;

  input = fopen("input.txt", "r");
  if(!input) { exit(1); }

  fseek(input, 0, SEEK_END);
  fsize = ftell(input);
  fseek(input, 0, SEEK_SET);

  contents = malloc(fsize + 1);
  fread(contents, fsize, 1, input);

  separate_lists = generate_lists(contents);
  sort_lists(&separate_lists);
  find_distance(&separate_lists);

  free(contents);
  free_lists(&separate_lists);
  fclose(input);
}

lists generate_lists(char *content)
{
  lists result    = {0};
  int   max_lines = 1000;

  result.list1 = malloc(max_lines * sizeof(*result.list1));
  result.list2 = malloc(max_lines * sizeof(*result.list2));

  char *line = content;
  while(*line) {
    int num1 = atoi(line);
    while(*line && *line != ' ') line++;
    int num2 = atoi(line);

    result.list1[result.size] = malloc(sizeof(**result.list1));
    result.list2[result.size] = malloc(sizeof(**result.list2));

    *result.list1[result.size] = num1;
    *result.list2[result.size] = num2;

    while(*line && *line != '\n') line++;
    if(*line == '\n') line++;

    result.size++;
    if(*line == '\0') break;
  }
  return result;
}

int compare_ints(const void *a, const void *b)
{
  return (*(int *)a - *(int *)b);
}

void sort_lists(lists *separate_lists)
{
  int  i;
  int *temp_list1 =
    malloc(separate_lists->size * sizeof(**separate_lists->list1));
  int *temp_list2 =
    malloc(separate_lists->size * sizeof(**separate_lists->list2));

  for(i = 0; i < separate_lists->size; i++) {
    temp_list1[i] = *separate_lists->list1[i];
    temp_list2[i] = *separate_lists->list2[i];
  }

  qsort(temp_list1,
        separate_lists->size,
        sizeof(**separate_lists->list1),
        compare_ints);
  qsort(temp_list2,
        separate_lists->size,
        sizeof(**separate_lists->list2),
        compare_ints);

  for(i = 0; i < separate_lists->size; i++) {
    *separate_lists->list1[i] = temp_list1[i];
    *separate_lists->list2[i] = temp_list2[i];
  }

  free(temp_list1);
  free(temp_list2);
}

void find_distance(lists *separate_lists)
{
  int  i;
  int  difference;
  long sum = 0;
  for(i = 0; i < separate_lists->size; i++) {
    if(*separate_lists->list1[i] > *separate_lists->list2[i]) {
      difference = *separate_lists->list1[i] - *separate_lists->list2[i];
    } else {
      difference = *separate_lists->list2[i] - *separate_lists->list1[i];
    }
    sum = sum + difference;
  }
  printf("%lu\n", sum);
}

void free_lists(lists *separate_lists)
{
  int i;

  for(i = 0; i < separate_lists->size; i++) {
    free(separate_lists->list1[i]);
    free(separate_lists->list2[i]);
  }
  free(separate_lists->list1);
  free(separate_lists->list2);
}
