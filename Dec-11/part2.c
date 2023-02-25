#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 10
#define COLS 10

void print_matrix(int matrix[ROWS][COLS]);
void step(int matrix[ROWS][COLS]);
int flash(int matrix[ROWS][COLS], int *N_flashes);

int main(int argc, char **argv)
{

  FILE *fd = fopen("/home/brendan/S/AoC/AoC-2021/Dec-11/input.txt", "r");
  char buff[200];
  int matrix[ROWS][COLS];
  int N_flashes = 0;

  int index = 0; 
  while(fgets(buff,200,fd) != NULL){
    for (int i = 0; i < 10; ++i) {
      matrix[index][i] = buff[i] - '0';
    }
    index++;
  }
  int number = 0;
  int Nstep = 0;
  print_matrix(matrix);
  while(number != 100){
    step(matrix);
    number = flash(matrix, &N_flashes);
    printf("number: %d\n", number);
    Nstep++;
  }
  print_matrix(matrix);
  printf("step: %d\n", Nstep);

  fclose(fd);
  return 0;
}

int flash(int matrix[ROWS][COLS],int *N_flashes)
{
  int numberOfFlashes = 0;
  int mirror[ROWS][COLS];
  for (int i = 0; i < ROWS; ++i)
    for (int j = 0; j < COLS; ++j)
      mirror[i][j] = matrix[i][j];
  int seen[ROWS][COLS] = {};
  int flashed = 1;
  while(flashed){
    flashed = 0;
    for (int i = 0; i < ROWS; ++i) {
      for (int j = 0; j < COLS; ++j) {
        if(matrix[i][j] >= 10 && seen[i][j] == 0){
          *N_flashes += 1;
          seen[i][j] = 1;
          flashed = 1;
          numberOfFlashes++;
          if(i==0){
            if(j==0){
            mirror[i+1][j] += 1;
            mirror[i][j+1] += 1;
            mirror[i+1][j+1] += 1;
            }else if(j==9){
            mirror[i+1][j] += 1;
            mirror[i][j-1] += 1;
            mirror[i+1][j-1] += 1;
            }else{
            mirror[i+1][j] += 1;
            mirror[i][j+1] += 1;
            mirror[i][j-1] += 1;
            mirror[i+1][j+1] += 1;
            mirror[i+1][j-1] += 1;
            }
          }else if(i==9){
            if(j==0){
            mirror[i-1][j] += 1;
            mirror[i][j+1] += 1;
            mirror[i-1][j+1] += 1;
            }else if(j==9){
            mirror[i-1][j] += 1;
            mirror[i][j-1] += 1;
            mirror[i-1][j-1] += 1;
            }else{
            mirror[i-1][j] += 1;
            mirror[i][j+1] += 1;
            mirror[i][j-1] += 1;
            mirror[i-1][j-1] += 1;
            mirror[i-1][j+1] += 1;
            }
          }else{
            if(j==0){
              mirror[i+1][j] += 1;
              mirror[i-1][j] += 1;
              mirror[i][j+1] += 1;
              mirror[i+1][j+1] += 1;
              mirror[i-1][j+1] += 1;
            }else if(j==9){
              mirror[i+1][j] += 1;
              mirror[i-1][j] += 1;
              mirror[i][j-1] += 1;
              mirror[i-1][j-1] += 1;
              mirror[i+1][j-1] += 1;
            }else{
              mirror[i+1][j] += 1;
              mirror[i-1][j] += 1;
              mirror[i][j+1] += 1;
              mirror[i][j-1] += 1;
              mirror[i+1][j+1] += 1;
              mirror[i-1][j-1] += 1;
              mirror[i+1][j-1] += 1;
              mirror[i-1][j+1] += 1;
            }
          }
        }
      }
    }
  for (int i = 0; i < ROWS; ++i)
    for (int j = 0; j < COLS; ++j)
      matrix[i][j] = mirror[i][j];
  }
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      if(seen[i][j]){
        matrix[i][j] = 0;  
      }
    }
  }
  return numberOfFlashes;
}

void step(int matrix[ROWS][COLS])
{
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      matrix[i][j] += 1;
    }
  }
}

void print_matrix(int matrix[ROWS][COLS])
{
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      printf("%d", matrix[i][j]); 
    }
    printf("\n");
  }
  printf("\n");
}
