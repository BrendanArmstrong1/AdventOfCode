#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>


/*  int regexec(const regex_t *restrict preg, const char *restrict string,
                    size_t nmatch, regmatch_t pmatch[restrict], int eflags);

    int regcomp(regex_t *restrict preg, const char *restrict regex,
                        int cflags);
*/

int main(int argc, char **argv)
{
  FILE *fd = fopen("/home/brendan/S/AoC/AoC-2021/Dec-8/input.txt", "r");
  int status;
  regex_t re;
  regmatch_t match[200];
  char buff[200];
  char pattern[100] = "| .*";
  char substring[100];
  int count = 0;
  if(regcomp(&re, pattern, 0) != 0){
    printf("Error in regex complition\n");
    return(0); // error reporting
  }

  while(fgets(buff, 200, fd) != NULL){
    // First filter to get rid of everything before '|'
    status = regexec(&re, buff,(size_t)200,match,REG_EXTENDED);
    if(!status){
      strncpy(substring,&buff[match[0].rm_so+2],match[0].rm_eo-match[0].rm_so);
    }
    // tokenize the string with spaces
    char *token = strtok(substring, " \n");
    int len;
    do{
      len = strlen(token);
      if(len == 4 || len == 2 || len == 7 || len == 3){
        count++;
      }
    }while((token = strtok(NULL," \n")) != NULL);
  }
  printf("%d\n", count);
  regfree(&re);
  fclose(fd);
  return 0;
}
