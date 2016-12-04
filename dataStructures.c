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
  Type **types;
  char *label;
  char name[TAM_TOKEN];
}Symbol;

typedef struct StackNode{
  void *element;
  struct StackNode *next, *previous;
}StackNode;

typedef struct{
  StackNode *head,*tail;
  int size;
}Stack;

void startStack(Stack *stack){
  stack->head = NULL;
  stack->tail = stack->head;
  stack->size = 0;
}

int emptyStack(Stack *stack){
  return (stack->head == NULL);
}

void push(void *element, Stack *stack){
  StackNode* head = (StackNode*)malloc(sizeof(StackNode));
  head->element = element;
  head->previous = NULL;
  head->next = stack->head;
  if(stack->head != NULL){
    stack->head->previous = head;
  }else{
    stack->tail = head;
  }
  stack->head = head;
  stack->size++;
}

void* pop(Stack *stack){
  StackNode *aux;
  if(emptyStack(stack)){
    return NULL;
  }else{
    aux = stack->head;
    void *element = aux->element;
    stack->head = aux->next;
    if(stack->head != NULL){
      stack->head->previous = NULL;
    }else{
      stack->tail = NULL;
    }
    free(aux);
    stack->size--;
    return element;
  }
}

void* reversePop(Stack *stack){
  StackNode *aux;
  if(emptyStack(stack)){
    return NULL;
  }else{
    aux = stack->tail;
    void *element = aux->element;
    stack->tail = stack->tail->previous;
    if(stack->tail != NULL){
      stack->tail->next = NULL;
    }else{
      stack->head = NULL;
    }
    free(aux);
    stack->size--;
    return element;
  }
}

void* getByReversedIndex(int index, Stack *stack){
  int i = 0;
  StackNode* iter=stack->head;
  for(; iter != NULL && i < index; iter=iter->next){
    i++;
  }
  if(iter == NULL){
    return NULL;
  }
  return iter->element;
}

void clearLevel(int lexicalLevel, Stack *stack){
  if(!emptyStack(stack)){
    StackNode* iter = stack->head;
    for(StackNode* iter=stack->head; 
        iter != NULL 
          && ((((Symbol*)iter->element)->category != PROC
                && ((Symbol*)iter->element)->category != FUNC)
              || ((Symbol*)iter->element)->lexicalLevel > lexicalLevel);
        iter=stack->head){
      stack->head = iter->next;
      free(iter->element);
      free(iter);
      stack->size--;
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

Symbol** lastSymbols(int n, Stack *stack){
  Symbol** lastSymbols = (Symbol**)malloc(sizeof(Symbol*)*n);
  int i = 0;
  for(StackNode* iter=stack->head; iter != NULL && i < n; iter=iter->next){
    Symbol* symbol = (Symbol*)iter->element;
    lastSymbols[i] = symbol;
    i++;
  }
  if(i < n){
    return NULL;
  }
  return lastSymbols;
}

int countLevelSymbols(int category, int lexicalLevel, Stack *stack){
  int i = 0;
  for(StackNode* iter=stack->head;
      iter != NULL;
      iter=iter->next){
    Symbol* symbol = (Symbol*)iter->element;
    // printf("\n\n symbol %s, category %d, lexicalLevel %d \n\n",symbol->name, symbol->category, symbol->lexicalLevel);
    if(symbol->category == category && symbol->lexicalLevel == lexicalLevel){
      i++;
    }
  }
  return i;
}