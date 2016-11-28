#include "definitions.h"

typedef struct Type{
  int primitiveType;
  int isReference;
}Type;

typedef struct Symbol{
  int category;
  int lexicalLevel;
  int displacement;
  int typesSize;
  Type *types;
  char name[TAM_TOKEN];
}Symbol;

typedef struct SymbolTableRow{
  Symbol symbol;
  struct SymbolTableRow *next;
}SymbolTableRow;

typedef struct{
  SymbolTableRow *head,*tail;
}SymbolTable;

void startSymbolTable(SymbolTable *symbolTable){
  symbolTable->head = NULL;
  symbolTable->tail = symbolTable->head;
}

int emptySymbolTable(SymbolTable *symbolTable){
  return (symbolTable->head == NULL);
}

void push(Symbol symbol, SymbolTable *symbolTable){
  SymbolTableRow* head = (SymbolTableRow*)malloc(sizeof(SymbolTableRow));
  head->symbol = symbol;
  head->next = symbolTable->head;
  symbolTable->head = head;
}

// Symbol pop(SymbolTable *symbolTable){
//   SymbolTableRow *aux;
//   if(emptySymbolTable(symbolTable)){
//     return NULL;
//   }else{
//     aux = symbolTable->head;
//     Symbol value = aux->symbol;
//     symbolTable->head = symbolTable->head->next;
//     free(aux);
//     return value;
//   }
// }

void clearLevel(int lexicalLevel, SymbolTable *symbolTable){
  if(!emptySymbolTable(symbolTable)){
    SymbolTableRow* iter = symbolTable->head;
    while(iter->next != NULL 
            && iter->next->symbol.lexicalLevel >= lexicalLevel){
      symbolTable->head = symbolTable->head->next;
      free(iter);
      iter = symbolTable->head;
    }
    if(lexicalLevel == 0){
      symbolTable->head = symbolTable->head->next;
      free(iter);
    }
  }
}