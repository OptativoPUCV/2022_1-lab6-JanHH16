#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n)
{
  for(int i = 0 ; i < 9 ; i++)
  {
    int *validarF = calloc(10,sizeof(int));
    for(int j = 0 ; j < 9 ; j++)
    {
      if(validarF[n->sudo[i][j]])
        return 0;
      if(validarF[n->sudo[i][j]] == 0 && n->sudo[i][j] != 0)
        validarF[n->sudo[i][j]] = 1;
    }
  }
  for(int j = 0 ; j < 9 ; j++)
  {
    int *validarC = calloc(10,sizeof(int));
    for(int i = 0 ; i < 9 ; i++)
    {
      if(validarC[n->sudo[i][j]])
        return 0;
      if(validarC[n->sudo[i][j]] == 0 && n->sudo[i][j] != 0)
        validarC[n->sudo[i][j]] = 1;
    }
  }
  for(int subMatriz = 0 ; subMatriz < 9 ; subMatriz++)
  {
    int *validarSM = calloc(10,sizeof(int));
    int k = subMatriz;
    int p;
    for(p = 0 ; p < 9 ; p++){
      int i=3*(k/3) + (p/3);
      int j=3*(k%3) + (p%3);
      if(validarSM[n->sudo[i][j]])
        return 0;
      if(validarSM[n->sudo[i][j]] == 0 && n->sudo[i][j] != 0)
        validarSM[n->sudo[i][j]] = 1;
    }
  }
  return 1;
}


List* get_adj_nodes(Node* n)
{
    List* list = createList();
    int numeroColocar = 1;
    for(int i = 0 ; i < 9 ; i++)
    {
      for(int j = 0 ; j < 9 ; j++)
      {
        if(n->sudo[i][j] == 0)
        {
          Node *nodo =  createNode();
          while(numeroColocar < 10)
          {
            nodo = copy(n);
            nodo->sudo[i][j] = numeroColocar;
            if(is_valid(nodo))
            pushBack(list,nodo);
            numeroColocar++;
          }
        }
      }
    }
    return list;
}


int is_final(Node* n)
{
  for(int i = 0 ; i < 9 ; i++)
  {
    for(int j = 0 ; j < 9 ; j++)
    {
      if(n->sudo[i][j] == 0)
        return 0;
    }
  }
    return 1;
}

Node* DFS(Node* initial, int* cont)
{
  Stack *S = createStack();
  push(S,initial);
  while(get_size(S) != 0)
  {
    Node *aux = top(S);
    pop(S);
    if(is_final(aux)) return aux;
    List* adjList = get_adj_nodes(aux);
    Node *listAux = first(adjList);
    while (listAux)
    {
      push(S,listAux);
      listAux = next(adjList);
    }
    free(aux);
    cont++;
  }
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/