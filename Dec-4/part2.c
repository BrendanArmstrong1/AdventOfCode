#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Board {
  char value[5][16];
  int matrix[5][5];
  int col[5];
  int row[5];
  int found;
} Board;

void PrintBoardInfo(Board *board, char *calledNumber);
void FindBoardMatches(int numOfBoards, Board *bd, char *calledNumber);
int SetBoards(FILE *, Board *);
Board *CheckForCompletion(int numOfBoards, Board *bd);

int main(int argc, char **argv) {

  FILE *fd = fopen("input.txt", "r");
  char calledNumbersList[1000];
  char *calledNumber;
  char correctedNumber[5];
  Board bd[100];
  int numOfBoards;
  Board *completeboard;

  for (int i = 0; i < 100; ++i) {
    memset(bd[i].matrix, 0, 25 * sizeof(int));
    memset(bd[i].col, 0, 5 * sizeof(int));
    memset(bd[i].row, 0, 5 * sizeof(int));
    bd[i].found = 0;
  }

  fgets(calledNumbersList, 1000, fd);
  calledNumber = strtok(calledNumbersList, ",");

  numOfBoards = SetBoards(fd, bd); // Set the boards with the file data

  do {
    if (strlen(calledNumber) == 1) {
      correctedNumber[0] = ' ';
      correctedNumber[1] = *calledNumber;
      correctedNumber[2] = ' ';
    } else {
      strcpy(correctedNumber, calledNumber);
    }
    FindBoardMatches(numOfBoards, bd, correctedNumber);
    if ((completeboard = CheckForCompletion(numOfBoards, bd)) != NULL)
      break;
  } while ((calledNumber = strtok(NULL, ",\n")) != NULL);

  PrintBoardInfo(completeboard, correctedNumber);

  fclose(fd);
  return 0;
}

int SetBoards(FILE *fd, Board *bd) {
  char board[100];
  int count = -1;
  int row = 0;
  while (fgets(board, 100, fd) != NULL) {
    if (!strcmp(board, "\n")) {
      count++;
      row = 0;
      continue;
    }
    strcpy(bd[count].value[row], board);
    bd[count].value[row][15] = '\0';
    row++;
  }
  return count + 1;
}

void FindBoardMatches(int numOfBoards, Board *bd, char *calledNumber) {
  char *remainder;
  for (int i = 0; i < numOfBoards; ++i) {
    for (int j = 0; j < 5; ++j) {
      if ((remainder = strstr(bd[i].value[j], calledNumber)) != NULL) {
        bd[i].matrix[j][(15 - strlen(remainder)) / 3] = 1;
        bd[i].row[j] += 1;
        bd[i].col[(15 - strlen(remainder)) / 3] += 1;
      }
    }
  }
}

Board *CheckForCompletion(int numOfBoards, Board *bd) {
  static int found = 0;
  for (int i = 0; i < numOfBoards; ++i) {
    for (int j = 0; j < 5; ++j) {
      for (int k = 0; k < 5; ++k) {
        if (bd[i].matrix[j][k]) {
          if (bd[i].row[j] == 5 || bd[i].col[k] == 5) {
            if (bd[i].found == 0) {
              bd[i].found = 1;
              found += 1;
            }
            if (found == 99) {
              return &bd[i];
            }
          }
        }
      }
    }
  }
  return NULL;
};

void PrintBoardInfo(Board *board, char *calledNumber) {
  char converter[2];
  int sum = 0;
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      if (!board->matrix[i][j]) {
        converter[0] = board->value[i][j * 3];
        converter[1] = board->value[i][j * 3 + 1];
        sum += atoi(converter);
      }
    }
  }
  printf("With Number: %s\n", calledNumber);
  for (int i = 0; i < 5; ++i) {
    printf("%s", board->value[i]);
  }
  printf("\n");

  for (int i = 0; i < 5; ++i) {
    printf("%d|", board->row[i]);
    for (int j = 0; j < 5; ++j) {
      printf("%d ", board->matrix[i][j]);
    }
    printf("\n");
  }
  printf("  ");
  for (int i = 0; i < 5; ++i) {
    printf("- ");
  }
  printf("\n  ");
  for (int i = 0; i < 5; ++i) {
    printf("%d ", board->col[i]);
  }
  printf("\n");
  printf("\n");
  printf("Answer is %d\n", sum * atoi(calledNumber));
  printf("\n");
};
