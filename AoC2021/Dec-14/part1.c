#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bintree{
  char *name;
  unsigned long stependamount;
  unsigned long stepstartamount;
  struct bintree *left;
  struct bintree *right;
}bintree;

#define TREENUM 100

void initialize(bintree tree[TREENUM], char *seed, int len, unsigned long charactercount[26]);
void updateTree(bintree tree[TREENUM]);
void stepTree(bintree tree[TREENUM], unsigned long charactercount[26], unsigned long *poly_length);

int main(int argc, char **argv)
{

  FILE *fd = fopen("/home/brendan/S/AoC/AoC-2021/Dec-14/input.txt", "r");
  char buff[200];
  char start[200];
  char *token;
  char *insert;
  char left[3];
  char right[3];
  char log[2000];
  unsigned long charactercount[26] = {};
  unsigned long highest = 0;
  unsigned long lowest = 9999999999999;
  unsigned long poly_length = 0;
  memset(log, 0, 2000);
  fgets(start,200,fd);// start
  fgets(buff,200,fd);// empty line
  bintree tree[TREENUM];

  for (int i = 0; i < TREENUM; ++i) {
    tree[i].stependamount = 0;
    tree[i].stepstartamount = 0;
    tree[i].name = malloc(10);
  }

  int index = 0;
  while(fgets(buff,200,fd) != NULL){
    token = strtok(buff, " ->\n");
    insert = strtok(NULL, " ->\n");
    sprintf(left, "%c%c", token[0],insert[0]);
    sprintf(right, "%c%c", insert[0], token[1]);
    if(!strstr(log, token)){
      strcpy(tree[index].name, token);
      strcat(log, token);
      strcat(log, " ");
      index += 1;
    }
    if(!strstr(log, left)){
      strcpy(tree[index].name, left);
      strcat(log, left);
      strcat(log, "| ");
      index += 1;
    }
    if(!strstr(log, right)){
      strcpy(tree[index].name, right);
      strcat(log, right);
      strcat(log, " |");
      index += 1;
    }
    for (int i = 0; i < index; ++i) {
      if(!strcmp(tree[i].name, token)){
        for (int j = 0; j < index; ++j) {
          if(!strcmp(tree[j].name, left)){
            for (int k = 0; k < index; ++k) {
              if(!strcmp(tree[k].name, right)){
                tree[i].left = &tree[j];
                tree[i].right = &tree[k];
              }
            }
          }
        } 
      }
    }
  }

  poly_length = strlen(start) - 1;
  initialize(tree, start, strlen(start),charactercount);
    
  for (int i = 0; i < 40; ++i) {
    stepTree(tree, charactercount, &poly_length);
    updateTree(tree);
  }

  printf("\n");
  for (int i = 0; i < 26; ++i) {
    if(charactercount[i] < lowest && charactercount[i] != 0)
      lowest = charactercount[i];
    if(charactercount[i] > highest)
      highest = charactercount[i];  
    printf("%c -> %lu\n",'A' + i, charactercount[i]);
  }

  printf("\nHighest: %lu\nLowest: %lu\nDifference: %lu\nStrlen: %lu\n",highest, lowest, highest-lowest, poly_length);
  
  for (int i = 0; i < TREENUM; ++i) {
    free(tree[i].name);
  }
  fclose(fd);
  return 0;
}

void initialize(bintree tree[TREENUM], char *seed, int len, unsigned long charactercount[26])
{
  char startarray[len-1][10];
  for (int i = 1; i < len; ++i) {
    charactercount[seed[i-1]-'A'] += 1;
    sprintf(startarray[i], "%c%c", seed[i-1],seed[i]);
  }
  charactercount[seed[len] - 'A'] += 1;

  for (int i = 0; i < TREENUM; ++i) {
    for (int j = 0; j < len-1; ++j) {
      if(!strcmp(tree[i].name,startarray[j])){
        tree[i].stependamount += 1;
      }
    }
  }
}

void stepTree(bintree tree[TREENUM], unsigned long charactercount[26], unsigned long *poly_length)
{
  for (int i = 0; i < TREENUM; ++i) {
    tree[i].left->stepstartamount += tree[i].stependamount;
    tree[i].right->stepstartamount += tree[i].stependamount;
    charactercount[tree[i].left->name[1] - 'A'] += tree[i].stependamount;
    *poly_length += tree[i].stependamount;
    tree[i].stependamount = 0;
  }  
}

void updateTree(bintree tree[TREENUM])
{
  for (int i = 0; i < TREENUM; ++i) {
    tree[i].stependamount = tree[i].stepstartamount; 
  } 
  for (int i = 0; i < TREENUM; ++i) {
    tree[i].left->stepstartamount = 0;
    tree[i].right->stepstartamount = 0;
  }
}
