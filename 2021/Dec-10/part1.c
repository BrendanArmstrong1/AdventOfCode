#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main(int argc, char **argv)
{

  FILE *fd = fopen("/home/brendan/S/AoC/AoC-2021/Dec-10/input.txt", "r");
  char buff[200];
  int corrupted = 0;
  int points = 0;

  while(fgets(buff,200,fd) != NULL){
    corrupted = 0;
    for (int i = 0; i < strlen(buff); ++i) {
      if(!corrupted){
        if(buff[i] == '[' || buff[i] == '(' || buff[i] == '<' || buff[i] == '{'){
          continue;
        } else if(buff[i] == ']' || buff[i] == ')' || buff[i] == '>' || buff[i] == '}'){
          for (int j = 1; j <= i; ++j) {
            if(buff[i-j] == '0'){
              ;
            }else if(buff[i] - buff[i-j] < 0 || buff[i] - buff[i-j] > 3){
              if(buff[i] == ']')
                points += 57;
              if(buff[i] == ')')
                points += 3;
              if(buff[i] == '>')
                points += 25137;
              if(buff[i] == '}')
                points += 1197;
              corrupted = 1;
              break;
            }else if(buff[i] - buff[i-j] > 0 && buff[i] - buff[i-j] < 3){
              buff[i] = '0';
              buff[i-j] = '0';
              break;
            }
          }
        }
      }
    }
  }

  printf("%d\n", points);
  fclose(fd);
  return 0;
}

