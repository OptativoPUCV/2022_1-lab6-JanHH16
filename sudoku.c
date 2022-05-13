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
  int aux = n->sudo[0][0];
  // Filas
  for(int i = 1 ; i < 9 ; i++)
  {
    if(n->sudo[i][0] == aux)
      return 0;
  }
  // Columnas
  for(int j = 1 ; j < 9 ; j++)
  {
    if(n->sudo[0][j] == aux)
      return 0;
  }
  
  int comprobar[10] = {0};
  int subMatriz = 0;
  while(subMatriz < 9)
  {
    for(int p = 0 ; p < 9 ; p++)
    {
      int i = 3*(subMatriz/3) + (p/3);
      int j = 3*(subMatriz%3) + (p%3);
      aux = n->sudo[i][j];
      if(aux != 0)
      {
        if(comprobar[aux] == 1)
        return 0;
        else  
          comprobar[aux] = 1;
      }
        
      /*
      if(p == 0)
        aux = n->sudo[i][j];
      if(p == 1)
      {
        if(n->sudo[i][j] == aux)
          return 0;
      }
      */
      printf("%d ",n->sudo[i][j]);
      if(p%3 == 2) printf("\n");
    }
    subMatriz++;
  }
    return 1;
}


List* get_adj_nodes(Node* n)
{
    List* list=createList();
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
            pushBack(list,nodo);
            numeroColocar++;
          }
        }
      }
    }
    return list;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
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