#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Line{
  int x1;
  int y1;
  int x2;
  int y2;
}Line;


int main(int argc, char **argv)
{
  FILE *fd = fopen("/home/brendan/S/AoC/AoC-2021/Dec-5/input.txt", "r");
  char buff[100];
  Line collection[500];
  char *token;
  int grid[1000][1000];
  memset(grid, 0, 1000*1000*sizeof(int));
  
  int count = 0;
  while (fgets(buff, 100, fd) != NULL) {
    token = strtok(buff, ", ->");
    collection[count].x1 = atoi(token); 
    token = strtok(NULL, ", ->");
    collection[count].y1 = atoi(token); 
    token = strtok(NULL, ", ->");
    collection[count].x2 = atoi(token); 
    token = strtok(NULL, ", ->");
    collection[count].y2 = atoi(token); 
    count++;
  }

  for(int i=0;i<500;++i){
    if(collection[i].x1 == collection[i].x2){ // linear components
      int col = collection[i].x1;
      if(collection[i].y1 > collection[i].y2){
        int len = collection[i].y1 - collection[i].y2; 
        for(int l=0;l<len+1;++l)
          grid[collection[i].y2 + l][col] += 1;
      } else {
        int len = collection[i].y2 - collection[i].y1; 
        for(int l=0;l<len+1;++l)
          grid[collection[i].y1 + l][col] += 1;
      }
    } else if(collection[i].y1 == collection[i].y2){ // linear components
      int row = collection[i].y1;
      if(collection[i].x1 > collection[i].x2){
        int len = collection[i].x1 - collection[i].x2; 
        for(int l=0;l<len+1;++l)
          grid[row][collection[i].x2 + l] += 1;
      } else {
        int len = collection[i].x2 - collection[i].x1; 
        for(int l=0;l<len+1;++l)
          grid[row][collection[i].x1 + l] += 1;
      }
    }
  }
  count = 0;
  for(int i=0; i<1000;i++){
    for(int j=0;j<1000;j++){
      if(grid[i][j] >= 2)
        count++;
     //   printf("\033[44m2\033[0m");
     // if(grid[i][j] == 1)
     //   printf("\033[42m1\033[0m");
     // if(grid[i][j] == 0)
     //   printf("%d",grid[i][j]);
    }
    //printf("\n");
  } 
  printf("%d\n", count);

  fclose(fd);
  return 0;
}
