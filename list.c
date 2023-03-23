#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List* L = (List*) malloc(sizeof(List));
  L->head = NULL;
  L->tail = NULL;
  L->current = NULL;
  
  return L;
}

void * firstList(List * list) {
if(!list->head) return NULL;
  list->current=list->head;
  return (list->current->data);
}

void * nextList(List * list) 
{  
  if(list->current == NULL || list ->current->next == NULL) 
  {
    return NULL;
  }
  
  list->current = list->current->next;    
  
  return (list->current->data);
}

void * lastList(List * list) {
  if(list ->tail == NULL) return NULL;

  list->current = list->tail;
  
  return (list->current->data);
}

void * prevList(List * list) {
  if(list->current == NULL || list ->current->prev == NULL) 
  {
    return NULL;
  }
  list->current = list->current->prev;
    
    return list->current->data;
}

void pushFront(List * list, void * data) 
{
  Node* nodito=createNode(data);
  
  if(list->head == NULL)
  {
    list->head = nodito;
    list->tail = nodito;
  }
  else
  {
    nodito->next = list->head;
    list->head->prev = nodito;
    list->head = nodito;
  }
  
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List *list, void *data) {

  if(list->current == NULL) return;
  
  Node *nodito = createNode(data);

  nodito->next = list->current->next;
  nodito->prev = list->current;

  if(list->current->next == NULL)
  {
    list->tail = nodito;
  }
  else
  {
    list->current->next->prev = nodito;
  }
  list->current->next = nodito; 
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void *popCurrent(List *list) { 
  
  if(list->current == NULL) return NULL;
  
  void* aEliminar = list->current->data;
  
  
  if(list->current == list->head)
  {
    
    list->head = list->head->next;

    if(list->head->prev != NULL)
    {
      list->head->prev = NULL;
    }
  }
  else
  {
    list->current->prev->next = list->current->next;
  }
  
  if(list->current == list->tail)
  {
    list->tail = list->current->prev;
    list->tail->next = NULL;
  }
  else
  {   
    list->current->next->prev = list->current->prev; 
  }
  
  Node *nodoAux = list->current->next;
  
  free(list->current);

  list->current = nodoAux;

  return aEliminar;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}