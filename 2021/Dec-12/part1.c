#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cave {
  char *name;
  int visited;
  int connections;
  struct cave** connect;
}cave;

void pathFind(cave *, int *);

int main(int argc, char **argv)
{

  FILE *fd = fopen("/home/brendan/ssd/AoC/AoC-2021/Dec-12/input.txt", "r");
  char buff[20];
  char *C1;
  char *C2;
  char log[200];
  cave nodes[13];
  int index = 0;
  int num_paths = 0;

  for (int i = 0; i < 13; ++i) {
    nodes[i].name = malloc(10 * sizeof(char));
    nodes[i].visited = 0;
    nodes[i].connections = 0;
    nodes[i].connect = malloc(20 * sizeof(cave));
  }

  while(fgets(buff, 20,fd)!= NULL){
    C1 = strtok(buff, "-\n ");
    C2 = strtok(NULL, "-\n ");
    if(!strstr(log,C1)){
      strcat(log,C1);
      strcat(log," ");
      strcpy(nodes[index].name,C1);
      index += 1;
    }
    if(!strstr(log,C2)){
      strcat(log,C2);
      strcat(log," ");
      strcpy(nodes[index].name,C2);
      index += 1;
    }
    for (int i = 0; i < 13; ++i) {
      if(!strcmp(nodes[i].name,C1)){
        for (int j = 0; j < 13; ++j) {
          if(!strcmp(nodes[j].name,C2)){
            nodes[i].connect[nodes[i].connections] = &nodes[j];
            nodes[j].connect[nodes[j].connections] = &nodes[i];
            nodes[i].connections += 1;
            nodes[j].connections += 1;
          }
        } 
      }
    }
  }

  for (int i = 0; i < 13; ++i) {
    if(!strcmp(nodes[i].name,"start")){
      pathFind(&nodes[i], &num_paths);
    }
  } 

  printf("%d\n", num_paths);


  for (int i = 0; i < 13; ++i) {
    free(nodes[i].name);
    free(nodes[i].connect);
  }
  fclose(fd);
  return 0;
}

void pathFind(cave *node, int *paths)
{
  if(!strcmp(node->name,"end")){
    *paths += 1;
    return;
  }
  if(node->visited && node->name[0] >= 'a'){
    printf("\tdead end %s\n", node->name);
    return;
  }else{
    node->visited += 1; 
    for (int i = 0; i < node->connections; ++i) {
      printf("visiting %s: from %s\n", node->name, node->connect[i]->name);
      pathFind(node->connect[i],paths);
    }
  }
}
