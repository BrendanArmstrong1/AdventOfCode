#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void swap(unsigned long* xp, unsigned long* yp);
void selectionSort(unsigned long arr[], int n);
void printArray(unsigned long arr[], int size);

int main(int argc, char **argv)
{

  FILE *fd = fopen("/home/brendan/ssd/AoC/AoC-2021/Dec-10/input.txt", "r");
  char buff[200];
  unsigned long points[45];
  int corrupted = 0;
  int index = 0;

  while(fgets(buff,200,fd) != NULL){
    corrupted = 0;
    points[index] = 0;
    for (int i = 0; i < strlen(buff); ++i) {
      if(!corrupted){
        if(buff[i] == '[' || buff[i] == '(' || buff[i] == '<' || buff[i] == '{'){
          continue;
        } else if(buff[i] == ']' || buff[i] == ')' || buff[i] == '>' || buff[i] == '}'){
          for (int j = 1; j <= i; ++j) {
            if(buff[i-j] == '0'){
              ;
            }else if(buff[i] - buff[i-j] < 0 || buff[i] - buff[i-j] > 3){
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
    if(!corrupted){
      int i = strlen(buff);
      for (int j = 0; j <= i; ++j) {
          if(buff[i-j] == '['){
            points[index] *= 5;
            points[index] += 2;
          }if(buff[i-j] == '('){
            points[index] *= 5;
            points[index] += 1;
          }if(buff[i-j] == '<'){
            points[index] *= 5;
            points[index] += 4;
          }if(buff[i-j] == '{'){
            points[index] *= 5;
            points[index] += 3;
          }
      }
      index++;
    }
  }

  selectionSort(points, 45);
  printArray(points, 45);

  fclose(fd);
  return 0;
}

void swap(unsigned long* xp, unsigned long* yp)
{
  unsigned long temp = *xp;
  *xp = *yp;
  *yp = temp;
}

void selectionSort(unsigned long arr[], int n)
{
  int i, j, min_idx;
  for (i = 0; i < n - 1; i++) {
    min_idx = i;
    for (j = i + 1; j < n; j++)
      if (arr[j] < arr[min_idx])
          min_idx = j;
    swap(&arr[min_idx], &arr[i]);
  }
}

void printArray(unsigned long arr[], int size)
{
  int i;
  for (i = 0; i < size; i++){
    if(i == 22){
      printf("%lu, %d\n", arr[i], i);
    }
  }
}
