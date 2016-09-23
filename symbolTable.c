typedef struct Type{
  char[3] valueType;
  char[5] primitiveType;
}

typedef struct Symbol{
  char[30] type;
  int lexicalLevel;
  int displacement;
  Type *types;
}

typedef struct SymbolTableRow{
  Symbol symbol;
  struct SymbolTableRow *next;
}SymbolTableRow;

typedef struct{
  SymbolTableRow *head,*tail;
}SymbolTable;

void startSymbolTable(SymbolTable *symbolTable){
  symbolTable->head = (SymbolTableRow*)malloc(sizeof(SymbolTableRow));
  symbolTable->tail = symbolTable->head;
  symbolTable->tail->next = NULL;
}

int emptySymbolTable(SymbolTable symbolTable){
  return (symbolTable.head == symbolTable.tail);
}

void push(Symbol symbol, SymbolTable *symbolTable){
  SymbolTableRow* head = (SymbolTableRow*)malloc(sizeof(SymbolTableRow));
  head->symbol = symbol;
  head->next = symbolTable->head;
  symbolTable->head = head;
}

Symbol pop(SymbolTable *symbolTable){
  SymbolTableRow *aux;
  if(emptySymbolTable(*symbolTable)){
    puts("Erro: não é possível desenfileirar.\nMotivo: a Tabela de Símbolos está vazia.");
    return;
  }else{
    aux = symbolTable->head;
    symbolTable->head = symbolTable->head->next;
    free(aux);
    return symbolTable->head->symbol;
  }
}