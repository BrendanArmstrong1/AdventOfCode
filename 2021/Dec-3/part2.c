#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ReturnMostCommon(char *startstr, char *retstr, int position, int length,
                     int form);
#define SIZE 12

int main(int argc, char **argv) {

  FILE *fd = fopen("/home/brendan/ssd/AoC/AoC-2021/Dec-3/input.txt", "r");
  char buff[14];
  char list[(SIZE + 1) * 1000];
  char answer[(SIZE + 1) * 1000];
  char answer2[(SIZE + 1) * 1000];
  int len = 1000;
  int sh = 0;
  int ans1[12];
  int ans2[12];
  int oxy = 0;
  int c02 = 0;

  // Get the initial array into memory and make a count of index
  while (fgets(buff, 14, fd) != NULL) {
    strcat(list, buff);
  }

  len = ReturnMostCommon(list, answer, 0, len, 0);
  for (int i = 1; i < SIZE; ++i) {
    if (len == 1) {
      break;
    }
    if (!sh) {
      len = ReturnMostCommon(answer, answer2, i, len, 0);
      sh = 1;
    } else {
      len = ReturnMostCommon(answer2, answer, i, len, 0);
      sh = 0;
    }
  }

  for (int i = 0; i < SIZE; ++i) {
    if (!sh) {
      ans1[i] = answer[i] - '0';
    } else {
      ans1[i] = answer2[i] - '0';
    }
  }
  for (int i = 0; i < SIZE; ++i) {
    printf("%d", ans1[i]);
  }
  printf(" c02 final binary");

  printf("\n");
  len = 1000;
  len = ReturnMostCommon(list, answer, 0, len, 1);
  for (int i = 1; i < SIZE; ++i) {
    if (len == 1) {
      break;
    }
    if (!sh) {
      len = ReturnMostCommon(answer, answer2, i, len, 1);
      sh = 1;
    } else {
      len = ReturnMostCommon(answer2, answer, i, len, 1);
      sh = 0;
    }
  }

  for (int i = 0; i < SIZE; ++i) {
    if (!sh) {
      ans2[i] = answer[i] - '0';
    } else {
      ans2[i] = answer2[i] - '0';
    }
  }
  for (int i = 0; i < SIZE; ++i) {
    printf("%d", ans2[i]);
  }
  printf(" oxygen final binary");

  printf("\n");
  for (int i = 0; i < 12; ++i) {
    oxy += (int)pow(2, 11 - i) * ans2[i];
    c02 += (int)pow(2, 11 - i) * ans1[i];
  }
  printf("oxy: %d\nc02: %d\nProduct: %d\n", oxy, c02, oxy * c02);

  fclose(fd);
  return 0;
}

int ReturnMostCommon(char *startstr, char *retstr, int position, int length,
                     int form) {
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
  if (!form) {
    most = count < (int)(ceilf(((float)length / 2)));
  } else {
    most = count >= (int)(ceilf(((float)length / 2)));
  }

  for (int k = 0; k < length; ++k) { // each entry still available
    if (startstr[k * (SIZE + 1) + position] - '0' == most) {
      for (int i = 0; i < SIZE + 1; ++i) {
        retstr[len * (SIZE + 1) + i] = startstr[k * (SIZE + 1) + i];
      }
      len++;
    }
  }
  return len;
}
