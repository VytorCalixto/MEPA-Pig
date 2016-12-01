#include "definitions.h"

typedef struct Type{
  int primitiveType;
  int isReference;
}Type;

typedef struct Symbol{
  int lexicalLevel;
  int displacement;
  int category;
  int typesSize;
  Type *types;
  char *label;
  char name[TAM_TOKEN];
}Symbol;

typedef struct StackNode{
  void *element;
  struct StackNode *next;
}StackNode;

typedef struct{
  StackNode *head,*tail;
}Stack;

void startStack(Stack *stack){
  stack->head = NULL;
  stack->tail = stack->head;
}

int emptyStack(Stack *stack){
  return (stack->head == NULL);
}

void push(void *element, Stack *stack){
  StackNode* head = (StackNode*)malloc(sizeof(StackNode));
  head->element = element;
  head->next = stack->head;
  stack->head = head;
}

void* pop(Stack *stack){
  StackNode *aux;
  if(emptyStack(stack)){
    return NULL;
  }else{
    aux = stack->head;
    void *element = aux->element;
    stack->head = stack->head->next;
    free(aux);
    return element;
  }
}

void clearLevel(int lexicalLevel, Stack *stack){
  if(!emptyStack(stack)){
    StackNode* iter = stack->head;
    while(iter->next != NULL 
            && ((Symbol*)iter->next->element)->lexicalLevel >= lexicalLevel){
      stack->head = stack->head->next;
      free(iter->element);
      free(iter);
      iter = stack->head;
    }
    if(lexicalLevel == 0){
      stack->head = stack->head->next;
      free(iter->element);
      free(iter);
    }
  }
}

Symbol* findSymbol(char name[TAM_TOKEN], Stack *stack){
  for(StackNode* iter=stack->head; iter != NULL; iter=iter->next){
    Symbol *symbol = (Symbol*)iter->element;
    if(strcmp(symbol->name, name) == 0){
      return symbol;
    }
  }
  return NULL;
}
