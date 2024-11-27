#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define ROWS 100
#define COLS 100

void DFS(int seen[ROWS][COLS], int matrix[ROWS][COLS], int i, int j, int *size);
int CalcBasinSize(int seen[ROWS][COLS], int matrix[ROWS][COLS], int,int);

int main(int argc, char **argv)
{

  FILE *fd = fopen("/home/brendan/ssd/AoC/AoC-2021/Dec-9/input.txt", "r");
  char buff[200];
  int matrix[ROWS][COLS];
  int seen[ROWS][COLS] = {};


  int i = 0;
  while(fgets(buff,200,fd) != NULL){
    for (int j = 0; j < COLS; ++j) {
      matrix[i][j] = buff[j] - '0';
    }
    i++;
  }

  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      if( i == 0 ){
        if(j == 0){ // top left corner
          if(matrix[i+1][j] > matrix[i][j] && matrix[i][j+1] > matrix[i][j]){
            CalcBasinSize(seen, matrix, i, j);
          }
        } else if(j == COLS - 1){ // top right corner
          if(matrix[i+1][j] > matrix[i][j] && matrix[i][j-1] > matrix[i][j]){
            CalcBasinSize(seen, matrix, i, j);
          }
        } else { // top row
          if(matrix[i+1][j] > matrix[i][j] && matrix[i][j+1] > matrix[i][j] && matrix[i][j-1] > matrix[i][j]){
            CalcBasinSize(seen, matrix, i, j);
          }
        }
      } else if(i == ROWS - 1){
        if(j == 0){ // bottom left corner
          if(matrix[i-1][j] > matrix[i][j] && matrix[i][j+1] > matrix[i][j]){
            CalcBasinSize(seen, matrix, i, j);
          }
        } else if(j == COLS - 1){ // bottom right corner
          if(matrix[i-1][j] > matrix[i][j] && matrix[i][j-1] > matrix[i][j]){
            CalcBasinSize(seen, matrix, i, j);
          }
        } else { // bottom row
          if(matrix[i-1][j] > matrix[i][j] && matrix[i][j+1] > matrix[i][j] && matrix[i][j-1] > matrix[i][j]){
            CalcBasinSize(seen, matrix, i, j);
          }
        }
      } else if(j == 0){ // left column
        if(matrix[i+1][j] > matrix[i][j] && matrix[i-1][j] > matrix[i][j] && matrix[i][j+1] > matrix[i][j]){
            CalcBasinSize(seen, matrix, i, j);
        }
      } else if(j == COLS - 1){ // right column
        if(matrix[i+1][j] > matrix[i][j] && matrix[i-1][j] > matrix[i][j] && matrix[i][j-1] > matrix[i][j]){
            CalcBasinSize(seen, matrix, i, j);
        }
      } else { // body of matrix
        if(matrix[i+1][j] > matrix[i][j] && matrix[i-1][j] > matrix[i][j] && matrix[i][j-1] > matrix[i][j] &&  matrix[i][j+1] > matrix[i][j]){
            CalcBasinSize(seen, matrix, i, j);
        }
      }
    }
  }


  fclose(fd);
  return 0;
}

int CalcBasinSize(int seen[ROWS][COLS], int matrix[ROWS][COLS], int i, int j)
{
  // This is depth first search stuff
  static int first = 0;
  static int second = 0;
  static int third = 0;
  int size = 0;
  DFS(seen, matrix, i , j, &size);

  if(size >= first){
    third = second;
    second = first;
    first = size;
  } else if(size >= second){
    third = second;
    second = size;
  } else if(size > third){
    third = size;
  }

  printf("%d %d %d\n", first, second, third);

  return size;
}

void DFS(int seen[ROWS][COLS], int matrix[ROWS][COLS], int i, int j, int *size)
{
  if(!seen[i][j]){
    *size += 1;
  }
  seen[i][j] = 1;
  if(i > 0 && matrix[i-1][j] < 9 && seen[i-1][j] == 0)
    DFS(seen, matrix, i-1, j, size);
  if(j > 0 && matrix[i][j-1] < 9 && seen[i][j-1] == 0)
    DFS(seen, matrix, i, j-1, size);
  if(j < 99 && matrix[i][j+1] < 9 && seen[i][j+1] == 0)
    DFS(seen, matrix, i, j+1, size);
  if(i < 99 && matrix[i+1][j] < 9 && seen[i+1][j] == 0)
    DFS(seen, matrix, i+1, j, size);
}
