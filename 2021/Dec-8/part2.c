#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void decrypy_time(char *, int *);

int main(int argc, char **argv)
{
  FILE *fd = fopen("/home/brendan/ssd/AoC/AoC-2021/Dec-8/input.txt", "r");
  char buff[200];
  int total = 0;

  while(fgets(buff, 200, fd) != NULL){
  decrypy_time(buff, &total);
  }

  printf("%d\n", total);
  fclose(fd);
  return 0;
}

void decrypy_time(char *buff, int *total)
{
  int index[7] = {};
  char *substring;
  char *token;
  char answer[4];
  substring = strtok(buff, "|");
  buff = strtok(NULL, "\n");

  token = strtok(substring, " ");
  do{
    for (int i = 0; i < strlen(token); ++i) {
      index[token[i]-'a']++;
    }
  }while((token = strtok(NULL, " \n")) != NULL);

  token = strtok(buff, " \n");
  int count = 0;
  int key = 0;
  do{
    for (int i = 0; i < strlen(token); ++i) {
      count += index[token[i] - 'a'];
    }
    if(count == 42){ // zero
      answer[key] = '0';
    } else if(count == 17){// one
      answer[key] = '1';
    } else if(count == 34){ // two
      answer[key] = '2';
    } else if(count == 39){// three
      answer[key] = '3';
    } else if(count == 30){// four
      answer[key] = '4';
    } else if(count == 37){// five
      answer[key] = '5';
    } else if(count == 41){// six
      answer[key] = '6';
    } else if(count == 25){// seven
      answer[key] = '7';
    } else if(count == 49){// eight
      answer[key] = '8';
    } else if(count == 45){// nine
      answer[key] = '9';
    }
    count = 0;
    key++;
  }while((token = strtok(NULL, " \n")) != NULL);
  *total += atoi(answer);
}

