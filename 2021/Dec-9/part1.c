#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main(int argc, char **argv)
{

  FILE *fd = fopen("/home/brendan/ssd/AoC/AoC-2021/Dec-9/input.txt", "r");
  char buff[200];
  int matrix[100][100];

  int i = 0;
  while(fgets(buff,200,fd) != NULL){
    for (int j = 0; j < 100; ++j) {
      matrix[i][j] = buff[j] - '0';
    }
    i++;
  }
  int sum = 0;
  for (int i = 0; i < 100; ++i) {
    for (int j = 0; j < 100; ++j) {
      if( i == 0 ){
        if(j == 0){ // top left corner
          if(matrix[i+1][j] > matrix[i][j] && matrix[i][j+1] > matrix[i][j]){
            sum += 1 + matrix[i][j];
          }
        } else if(j == 99){ // top right corner
          if(matrix[i+1][j] > matrix[i][j] && matrix[i][j-1] > matrix[i][j]){
            sum += 1 + matrix[i][j];
          }
        } else { // top row
          if(matrix[i+1][j] > matrix[i][j] && matrix[i][j+1] > matrix[i][j] && matrix[i][j-1] > matrix[i][j]){
            sum += 1 + matrix[i][j];
          }
        }
      } else if(i == 99){
        if(j == 0){ // bottom left corner
          if(matrix[i-1][j] > matrix[i][j] && matrix[i][j+1] > matrix[i][j]){
            sum += 1 + matrix[i][j];
          }
        } else if(j == 99){ // bottom right corner
          if(matrix[i-1][j] > matrix[i][j] && matrix[i][j-1] > matrix[i][j]){
            sum += 1 + matrix[i][j];
          }
        } else { // bottom row
          if(matrix[i-1][j] > matrix[i][j] && matrix[i][j+1] > matrix[i][j] && matrix[i][j-1] > matrix[i][j]){
            sum += 1 + matrix[i][j];
          }
        }
      } else if(j == 0){ // left column
        if(matrix[i+1][j] > matrix[i][j] && matrix[i-1][j] > matrix[i][j] && matrix[i][j+1] > matrix[i][j]){
          sum += 1 + matrix[i][j];
        }
      } else if(j == 99){ // right column
        if(matrix[i+1][j] > matrix[i][j] && matrix[i-1][j] > matrix[i][j] && matrix[i][j-1] > matrix[i][j]){
          sum += 1 + matrix[i][j];
        }
      } else { // body of matrix
        if(matrix[i+1][j] > matrix[i][j] && matrix[i-1][j] > matrix[i][j] && matrix[i][j-1] > matrix[i][j] &&  matrix[i][j+1] > matrix[i][j]){
          sum += 1 + matrix[i][j];
        }
      }
    }
  }
  printf("%d\n", sum);




  fclose(fd);
  return 0;
}
