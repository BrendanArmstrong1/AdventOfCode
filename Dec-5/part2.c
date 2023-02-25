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
    if(collection[i].x1 == collection[i].x2){ // linear component
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
    } else if(collection[i].y1 == collection[i].y2){ // linear component
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
    } else {                                       // Diagonal Components
      int len = abs(collection[i].x1 - collection[i].x2);
      int row1 = collection[i].y1;
      int col1 = collection[i].x1;
      int row2 = collection[i].y2;
      int col2 = collection[i].x2;
      if(col2 > col1){
        if(row2 > row1){
          for(int l=0;l<len+1;++l) // upper right
            grid[row1+l][col1+l] += 1;
        } else {
          for(int l=0;l<len+1;++l) // lower right
            grid[row1-l][col1+l] += 1;
        }
      } else {
        if(row2 > row1){
          for(int l=0;l<len+1;++l) // upper left
            grid[row1+l][col1-l] += 1;
        } else {
          for(int l=0;l<len+1;++l) // lower left
            grid[row1-l][col1-l] += 1;
        }
      }
    }
  }
  count = 0;
  for(int i=0; i<1000;i++){
    for(int j=0;j<1000;j++){
      if(grid[i][j] >= 2)
        count++;
    }
  } 
  printf("%d\n", count);

  /*
  for(int i=0; i<1000;i++){
    for(int j=0;j<1000;j++){
      if(grid[i][j] >= 2)
        printf("\033[44m2\033[0m");
      if(grid[i][j] == 1)
        printf("\033[42m1\033[0m");
      if(grid[i][j] == 0)
        printf("%d",grid[i][j]);
    }
    printf("\n");
  } 
  */

  fclose(fd);
  return 0;
}
