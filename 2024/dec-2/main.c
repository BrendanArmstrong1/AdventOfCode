#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
  SAFE     = 0,
  NOT_SAFE = 1,
} Reactor_status;

int            parse_reactor_levels(int *reactor_levels, char *line);
Reactor_status process_reactor_levels(int *reactor_levels, int count);
void           remove_reactor_level(int *reactor_levels, int idx, int count);

void part1(void);
void part2(void);

int main(void)
{
  part1();
  part2();
  return 0;
}

int parse_reactor_levels(int *reactor_levels, char *line)
{
  char *token;
  int   count;

  count = 0;
  token = strtok(line, " ");

  while(token != 0 && count < 100) {
    reactor_levels[count] = atoi(token);
    count++;
    token = strtok(0, " ");
  }
  return count;
}

Reactor_status process_reactor_levels(int *reactor_levels, int count)
{
  int i;
  int increasing;
  int jump_level;

  jump_level = 0;

  for(i = 0; i < count; i++) {
    if(i == 0) { /*First number*/
      jump_level = (reactor_levels[i + 1] - reactor_levels[i]);
      if(jump_level == 0) { return NOT_SAFE; }

      if(jump_level > 0) {
        increasing = 1;
      } else {
        increasing = 0;
      }
      jump_level = (reactor_levels[i + 1] - reactor_levels[i]);
      if(abs(jump_level) > 3) { return NOT_SAFE; }
    } else { /*Rest of the numbers*/
      jump_level = (reactor_levels[i] - reactor_levels[i - 1]);
      if(jump_level == 0) { return NOT_SAFE; }

      if(increasing) {
        if(jump_level < 0) { return NOT_SAFE; }
      } else {
        if(jump_level > 0) { return NOT_SAFE; }
      }
      if(abs(jump_level) > 3) { return NOT_SAFE; }
    }
  }
  return SAFE;
}

void remove_reactor_level(int *reactor_levels, int idx, int count)
{
  for(; idx < count - 1; idx++) {
    reactor_levels[idx] = reactor_levels[idx + 1];
  }
}

void part1(void)
{
  FILE          *input;
  char          *line = 0;
  size_t         n    = 0;
  ssize_t        read;
  int            count;
  int            safe_count;
  int            not_safe_count;
  Reactor_status status;

  int reactor_levels[100];

  input = fopen("input.txt", "r");
  if(!input) { exit(1); }

  safe_count     = 0;
  not_safe_count = 0;

  while((read = getline(&line, &n, input)) != -1) {
    count  = parse_reactor_levels(reactor_levels, line);
    status = process_reactor_levels(reactor_levels, count);

    switch(status) {
    case SAFE:
      safe_count += 1;
      break;
    case NOT_SAFE:
      not_safe_count += 1;
      break;
    }
  }
  printf("safe: %d\n", safe_count);
  printf("not safe: %d\n", not_safe_count);
}

void part2(void)
{
  FILE          *input;
  char          *line = 0;
  size_t         n    = 0;
  ssize_t        read;
  int            count;
  int            safe_count;
  int            not_safe_count;
  int            idx;
  Reactor_status status;

  int reactor_levels[100];
  int reactor_levels_backup[100];

  input = fopen("input.txt", "r");
  if(!input) { exit(1); }

  safe_count     = 0;
  not_safe_count = 0;

  while((read = getline(&line, &n, input)) != -1) {
    count  = parse_reactor_levels(reactor_levels, line);
    status = process_reactor_levels(reactor_levels, count);
    if(status == NOT_SAFE) {
      idx = 0;
      while(status == NOT_SAFE) {
        memcpy(reactor_levels_backup, reactor_levels, sizeof(reactor_levels));
        remove_reactor_level(reactor_levels_backup, idx, count);
        status = process_reactor_levels(reactor_levels_backup, count - 1);
        if(status == SAFE) {
          break;
        }

        idx += 1;
        if(idx >= count) { break; }
      }
    }

    switch(status) {
    case SAFE:
      safe_count += 1;
      break;
    case NOT_SAFE:
      not_safe_count += 1;
      break;
    }
  }
  printf("safe: %d\n", safe_count);
  printf("not safe: %d\n", not_safe_count);
}
