#include <aocfunc.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 4000
#define MAX_BLINKS 75

typedef struct
{
  unsigned long value;
  unsigned long count;
  unsigned      used;
} Box;

void box_put_value(Box boxes[MAX_LENGTH], unsigned long value, unsigned count)
{
  unsigned idx;
  idx = 0;
  for (idx = 0; idx < MAX_LENGTH; idx++) {
    if (boxes[idx].value == value && boxes[idx].used) {
      if ((ULONG_MAX - boxes[idx].count) < count)
        continue;
      boxes[idx].count += count;
      return;
    } else if (!boxes[idx].used) {
      boxes[idx].count = count;
      boxes[idx].used  = 1;
      boxes[idx].value = value;
      return;
    }
  }
}

void build_initial_array(char *string, Box boxes[MAX_LENGTH])
{
  unsigned long value;
  char         *token;
  token = strtok(string, " ");

  while (token) {
    value = strtoul(token, 0, 10);
    box_put_value(boxes, value, 1);
    token = strtok(0, " ");
  }
}

int check_if_even(unsigned long value, unsigned long *first, unsigned long *second)
{
  int  i;
  int  k;
  int  length;
  char temp[500];
  char temp2[500];
  for (i = 0; i < 500; i++) {
    temp[i]  = 0;
    temp2[i] = 0;
  }

  sprintf(temp, "%lu", value);

  length = 0;
  i      = 0;
  while (temp[i]) {
    length++;
    i++;
  }
  if (!(length % 2)) {
    i = length / 2;
    k = 0;
    while (temp[i])
      temp2[k++] = temp[i++];
    temp[length / 2] = 0;
    /*printf("value: %lu, length: %d\n", value, length);*/
    /*printf("temp1: %s\ntemp2: %s", temp, temp2);*/
    /*printf("\n");*/
    *first  = strtoul(temp, 0, 10);
    *second = strtoul(temp2, 0, 10);
    return 1;
  } else {
    return 0;
  }
  return 0;
}

void box_empty(Box boxes_to[MAX_LENGTH])
{
  unsigned idx;

  for (idx = 0; idx < MAX_LENGTH; idx++) {
    boxes_to[idx].value = 0;
    boxes_to[idx].count = 0;
    boxes_to[idx].used  = 0;
  }
}

void blink(Box boxes_to[MAX_LENGTH], Box boxes_from[MAX_LENGTH])
{
  unsigned      idx;
  unsigned long first;
  unsigned long second;

  for (idx = 0; idx < MAX_LENGTH; idx++) {
    if (boxes_from[idx].used) {
      if (boxes_from[idx].value == 0) {
        box_put_value(boxes_to, 1, boxes_from[idx].count);
      } else if (check_if_even(boxes_from[idx].value, &first, &second)) {
        box_put_value(boxes_to, first, boxes_from[idx].count);
        box_put_value(boxes_to, second, boxes_from[idx].count);
      } else {
        box_put_value(boxes_to, boxes_from[idx].value * 2024, boxes_from[idx].count);
      }
    }
  }
}

void test1(char *path)
{
  char         *string;
  unsigned long counter;
  unsigned      i;
  Box           boxes1[MAX_LENGTH];
  Box           boxes2[MAX_LENGTH];
  Box          *temp;

  for (i = 0; i < MAX_LENGTH; i++) {
    boxes1[i].count = 0;
    boxes1[i].used  = 0;
    boxes1[i].value = 0;
  }

  string = get_input(path);

  printf("%s\n", string);

  build_initial_array(string, boxes1);
  box_empty(boxes2);

  temp = boxes1;
  for (i = 0; i < MAX_BLINKS; i++) {
    if (!(i % 2)) {
      blink(boxes2, boxes1);
      box_empty(boxes1);
      temp = boxes2;
    } else {
      blink(boxes1, boxes2);
      box_empty(boxes2);
      temp = boxes1;
    }
  }

  counter = 0;
  for (i = 0; i < MAX_LENGTH; i++) {
    counter += temp[i].count;
    printf(
      "Box %u, value: %lu, count: %lu, used %u\n", i, temp[i].value, temp[i].count, temp[i].used);
  }
  /*150694242073*/
  /*219413718809*/
  printf("%lu\n", counter);
}

void part1(char *_) {}
void part2(char *_) {}

int main(void)
{
  test1("./input.txt");
  /*part1("./input.txt");*/
  /*part2("./input.txt");*/
  return 0;
}
