#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ReturnMostCommon(char *startstr, char *retstr, int position, int length);
#define SIZE 12

int main(int argc, char **argv) {

  FILE *fd = fopen("/home/brendan/S/AoC/AoC-2021/Dec-3/input.txt", "r");
  char buff[14];
  char list[(SIZE + 1) * 1000];
  char answer[(SIZE + 1) * 1000];
  char answer2[(SIZE + 1) * 1000];
  int len = 1000;

  // Get the initial array into memory and make a count of index
  while (fgets(buff, 14, fd) != NULL) {
    strcat(list, buff);
  }

  len = ReturnMostCommon(list, answer, 0, len);
  len = ReturnMostCommon(answer, answer2, 1, len);
  len = ReturnMostCommon(answer2, answer, 2, len);
  len = ReturnMostCommon(answer, answer2, 3, len);
  len = ReturnMostCommon(answer2, answer, 4, len);
  len = ReturnMostCommon(answer, answer2, 5, len);
  len = ReturnMostCommon(answer2, answer, 6, len);
  len = ReturnMostCommon(answer, answer2, 7, len);
  //  len = ReturnMostCommon(answer2, answer, 8, len);
  //  len = ReturnMostCommon(answer, answer2, 9, len);
  //  len = ReturnMostCommon(answer2, answer, 10, len);
  //  len = ReturnMostCommon(answer, answer2, 11, len);

  for (int i = 0; i < len * (SIZE + 1); ++i) {
    printf("%c", answer2[i]);
  }

  fclose(fd);
  return 0;
}

int ReturnMostCommon(char *startstr, char *retstr, int position, int length) {
  int count = 0;
  char most = 0;
  int len = 0;

  /*
  startstr is the stry to be evaluated
  retstr is the returned string with extracted values
  position is the index of interest in the string
  length is the length of the array(startstr)
  R - What number are you looking for
  */

  for (int i = 0; i < length; ++i) {
    count += startstr[i * (SIZE + 1) + position] - '0';
  }
  most = count < (int)(ceilf(((float)length / 2)));

  for (int k = 0; k < length; ++k) { // each entry still available
    if (startstr[k * (SIZE + 1) + position] - '0' == most) {
      for (int i = 0; i < SIZE + 1; ++i) {
        retstr[len * (SIZE + 1) + i] = startstr[k * (SIZE + 1) + i];
      }
      len++;
    }
  }
  printf("%d\n", len);
  return len;
}
