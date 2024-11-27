#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void printResult(int coords[1000][2], int index);
void callfold(int coords[1000][2], int number, char Dir, int index);

int main(int argc, char **argv)
{

  FILE *fd = fopen("/home/brendan/ssd/AoC/AoC-2021/Dec-13/input.txt", "r");
  char buff[200];
  int coords[1000][2] = {};
  char folds[20][200];
  char *token;
  
  int index = 0;
  int foldex = 0;
  while(fgets(buff,200,fd) != NULL){
    if(isdigit(buff[0])){
      // Reversing indices because it makes sense
      coords[index][1]= atoi(strtok(buff, ",\n"));
      coords[index][0]= atoi(strtok(NULL, ",\n"));
      index++;
    }else{
      token = strtok(buff, " ");
      do{
        if(token[0] == 'x' || token[0] == 'y')
          strcpy(folds[foldex],token);
        if(isdigit(token[0]))
          strcat(folds[foldex++],token);
      }while((token = strtok(NULL, " =\n")) != NULL);
    }
  }

  for (int i = 0; i < foldex; ++i) {
    if(folds[i][0] == 'x'){
      callfold(coords, atoi(&folds[i][1]), folds[i][0], index);
    }
    if(folds[i][0] == 'y'){
      callfold(coords, atoi(&folds[i][1]), folds[i][0], index);
    }
  }

  printResult(coords, index);
  
  fclose(fd);
  return 0;
}

void callfold(int coords[1000][2],int number,char Dir, int index)
{
  int ref;
  int diff;
  if(Dir == 'x'){
    ref = 1;
  }else if(Dir == 'y'){
    ref = 0;
  }
  for (int i = 0; i < index; ++i) {
    if(coords[i][ref] > number){
      diff = coords[i][ref] - number;
      coords[i][ref] = number - diff; 
    }
  }
}

void printResult(int coords[1000][2], int index)
{
  int matrix[1000][1000] = {};
  for (int i = 0; i < index; ++i) {
    matrix[coords[i][0]][coords[i][1]] = 1;    
  }
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 50; ++j) {
      if(matrix[i][j] == 1){
        printf("#");
      }else{
        printf(" ");
      }
    }
    printf("\n");
  }
}
