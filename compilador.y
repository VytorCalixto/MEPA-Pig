
// Testar se funciona corretamente o empilhamento de par�metros
// passados por valor ou por refer�ncia.


%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "compilador.h"

#include "dataStructures.c"
#include "definitions.h"


Stack symbolTable, labels, params;
int lexicalLevel = 0;
int typeCount = 0;
int labelCount = 0;
int subRoutineType = -1;
int constType = -1;
int category = -1;
int isReference = -1;

void verifyType(int type, int first, int third){
  if(first != type || third != type){
    imprimeErro("Erro de sintaxe.");
  }
}

void nextLabel(char* label){
  sprintf(label,"R%02d",labelCount);
  labelCount++;
} 

Symbol* getSymbol(char name[TAM_TOKEN]){
  Symbol* symbol = findSymbol(name, &symbolTable);
  if(symbol == NULL){
    imprimeErro("S�mbolo inexistente.");
  }
  return symbol;
}

void generateExprCode(Expr expr, int loadAddress){
  printf("\tAvaliated: %d\tValue: %s\n",expr.avaliated, expr.value);
  if(expr.value[0] != '\0' && expr.avaliated == 0){
    expr.avaliated = 1;
    if(expr.exprType == VARIABLE){
      Symbol* var = getSymbol(expr.value);
      if(var->category != FUNC){
        char cr[CMD_MAX];
        if((loadAddress && var->types[0]->isReference)
            ||(!loadAddress && !var->types[0]->isReference)){
          sprintf(cr,"CRVL %d,%d", var->lexicalLevel, var->displacement);
        }else if(loadAddress){
          sprintf(cr,"CREN %d,%d", var->lexicalLevel, var->displacement);
        }else{
          sprintf(cr,"CRVI %d,%d", var->lexicalLevel, var->displacement);
        }
        geraCodigo(NULL, cr);
      }
    }else if(expr.exprType == CONSTANT){
      char crct[CMD_MAX];
      sprintf(crct,"CRCT %s", expr.value);
      geraCodigo(NULL, crct);
    }else if(expr.exprType == COMMAND || expr.exprType == BOOLCOMMAND){
      geraCodigo(NULL, expr.value);
    }
  }
}

void generateStorageCode(char name[TAM_TOKEN]){
  Symbol* var = getSymbol(name);
  char arm[CMD_MAX];
  if(!var->types[0]->isReference || var->category == FUNC){
    sprintf(arm,"ARMZ %d,%d",var->lexicalLevel,var->displacement);
  }else{
    sprintf(arm,"ARMI %d,%d",var->lexicalLevel,var->displacement);
  }
  geraCodigo(NULL, arm);
}

%}

%union {
  Expr expr;
}

%token PROGRAM ABRE_PARENTESES FECHA_PARENTESES 
%token VIRGULA PONTO_E_VIRGULA DOIS_PONTOS PONTO
%token T_BEGIN T_END VAR IDENT ATRIBUICAO
%token WHILE DO IF THEN ELSE
%token MAIOR MENOR IGUAL DIFERENTE MAIOR_IGUAL MENOR_IGUAL
%token PROCEDURE FUNCTION GOTO LABEL NUMERO READ WRITE
%token MAIS MENOS VEZES DIVIDIDO OR AND TRUE FALSE

%type <expr> expressao expr_e expr_t expr_f relacao constante variavel chamada_subrotina

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

programa: { 
            geraCodigo(NULL, "INPP"); 
          }
          PROGRAM IDENT 
          ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA
          bloco PONTO
          {
            geraCodigo(NULL, "PARA"); 
          }
;

bloco:  parte_declara_rotulos
        parte_declara_vars
        parte_declara_subrotinas
        comando_composto 
        {
          int count = countLevelSymbols(VS,lexicalLevel,&symbolTable);
          if(count > 0){
            char dmem[CMD_MAX];
            sprintf(dmem,"DMEM %d", count);
            geraCodigo(NULL, dmem);
          }
          clearLevel(lexicalLevel, &symbolTable);
        }
;

parte_declara_vars: {
                      category = VS;
                      isReference = 0;
                    }
                    VAR declara_vars
                    {
                      int count = countLevelSymbols(VS,lexicalLevel,&symbolTable);
                      char amem[CMD_MAX];
                      sprintf(amem,"AMEM %d", count);
                      geraCodigo(NULL, amem);
                    }
                    |
;

declara_vars: declara_vars declara_var 
            | declara_var 
;

declara_var: secao_var PONTO_E_VIRGULA 

secao_var: {typeCount = 0;}
           lista_id_var DOIS_PONTOS tipo
;

tipo: IDENT
      {
        if((strcmp(token,"integer") != 0) && (strcmp(token,"boolean") != 0)){
          imprimeErro("Tipo de vari�vel n�o permitido.");
        }else{
          Symbol** vars = lastSymbols(typeCount,&symbolTable);
          if(vars == NULL){
            imprimeErro("Erro na tabela de s�mbolos.");
          }
          for(int i = 0; i < typeCount; i++){
            if((strcmp(token,"integer") == 0))
              vars[i]->types[0]->primitiveType = INT;
            else
              vars[i]->types[0]->primitiveType = BOOL;
          }
        }
      }
;

lista_id_var: lista_id_var VIRGULA identificador 
            | identificador
;

identificador: IDENT
              {
                Symbol *newSymbol = (Symbol*)malloc(sizeof(Symbol));
                strcpy(newSymbol->name,token);
                newSymbol->category = category;
                newSymbol->lexicalLevel = lexicalLevel;
                int count = countLevelSymbols(category,lexicalLevel,&symbolTable);
                newSymbol->displacement = count;

                Type **types = (Type**)malloc(sizeof(Type*));
                Type *type = (Type*)malloc(sizeof(Type));
                type->isReference = isReference;
                types[0] = type;
                newSymbol->types = types;
                newSymbol->typesSize = 1;
                
                push(newSymbol,&symbolTable);
                typeCount++;
              }
;

lista_idents: lista_idents VIRGULA IDENT  
            | IDENT
;

comando_composto: T_BEGIN comandos comando_end T_END
                | T_BEGIN comando_end T_END
;

comando_end: comando PONTO_E_VIRGULA
           | comando
;
comandos: comandos comando PONTO_E_VIRGULA
        | comando PONTO_E_VIRGULA
;

comando: rotulo comando_sem_rotulo
;

comando_sem_rotulo: atribuicao
                  | desvio
                  | comando_composto
                  | condicional
                  | repetitivo
                  | chamada_subrotina
                  | leitura
                  | impressao
;

atribuicao: variavel ATRIBUICAO expressao
            {
              if(($1.primitiveType != $3.primitiveType) 
                && $3.primitiveType != INT 
                && $3.primitiveType != BOOL){
                imprimeErro("Erro de sintaxe");
              }else{
                generateExprCode($3,0);
                generateStorageCode($1.value);
              }
            }
;

expressao:  expr_e relacao expr_e 
            {
              if($2.exprType == COMMAND) {
                verifyType(INT, $1.primitiveType, $3.primitiveType);
              } else if ($2.exprType == BOOLCOMMAND) {
                if($1.primitiveType != $3.primitiveType 
                  || ($1.primitiveType != INT && $1.primitiveType != BOOL)) {
                  imprimeErro("Erro de sintaxe.");
                }
              }
              generateExprCode($1,0);
              generateExprCode($3,0);
              generateExprCode($2,0);
              Expr cmd;
              cmd.avaliated = 0;
              cmd.value[0] = '\0';
              cmd.primitiveType=BOOL;
              cmd.exprType=COMMAND;
              $$=cmd;
            }
         | expr_e 
          {
            // printf("\tTIPO DA EXPRESS�O: %d\n", $1.primitiveType);
            if($1.primitiveType != BOOL) imprimeErro("Erro de sintaxe.");
            generateExprCode($1,0);
            $$ = $1;
          }
;

relacao:  MAIOR
          {
            Expr cmd;
            cmd.avaliated = 0;
            strcpy(cmd.value,"CMMA");
            cmd.primitiveType=BOOL;
            cmd.exprType=COMMAND;
            $$=cmd;
          } 
       |  MENOR
          {
            Expr cmd;
            cmd.avaliated = 0;
            strcpy(cmd.value,"CMME");
            cmd.primitiveType=BOOL;
            cmd.exprType=COMMAND;
            $$=cmd;
          } 
       |  MAIOR_IGUAL
          {
            Expr cmd;
            cmd.avaliated = 0;
            strcpy(cmd.value,"CMAG");
            cmd.primitiveType=BOOL;
            cmd.exprType=COMMAND;
            $$=cmd;
          } 
       |  MENOR_IGUAL 
          {
            Expr cmd;
            cmd.avaliated = 0;
            strcpy(cmd.value,"CMEG");
            cmd.primitiveType=BOOL;
            cmd.exprType=COMMAND;
            $$=cmd;
          } 
       |  IGUAL 
          {
            Expr cmd;
            cmd.avaliated = 0;
            strcpy(cmd.value,"CMIG");
            cmd.primitiveType=BOOL;
            cmd.exprType=BOOLCOMMAND;
            $$=cmd;
          } 
       |  DIFERENTE 
          {
            Expr cmd;
            cmd.avaliated = 0;
            strcpy(cmd.value,"CMDG");
            cmd.primitiveType=BOOL;
            cmd.exprType=BOOLCOMMAND;
            $$=cmd;
          } 
;

expr_e: expr_e MAIS expr_t 
        { 
          verifyType(INT, $1.primitiveType, $3.primitiveType);
          generateExprCode($1,0);
          generateExprCode($3,0);
          Expr cmd;
          cmd.avaliated = 0;
          strcpy(cmd.value,"SOMA");
          cmd.primitiveType=INT;
          cmd.exprType=COMMAND;
          $$=cmd;
        }
      | expr_e OR expr_t 
        { 
          verifyType(BOOL, $1.primitiveType, $3.primitiveType);
          generateExprCode($1,0);
          generateExprCode($3,0);
          Expr cmd;
          cmd.avaliated = 0;
          strcpy(cmd.value,"DISJ");
          cmd.primitiveType=BOOL;
          cmd.exprType=COMMAND;
          $$=cmd;
        }
      | expr_e MENOS expr_t 
        {
          verifyType(INT, $1.primitiveType, $3.primitiveType);
          generateExprCode($1,0);
          generateExprCode($3,0);
          Expr cmd;
          cmd.avaliated = 0;
          strcpy(cmd.value,"SUBT");
          cmd.primitiveType=INT;
          cmd.exprType=COMMAND;
          $$=cmd;
        }
      | expr_t {$$ = $1;}
;

expr_t: expr_t VEZES expr_f 
        {
          verifyType(INT, $1.primitiveType, $3.primitiveType);
          generateExprCode($1,0);
          generateExprCode($3,0);
          Expr cmd;
          cmd.avaliated = 0;
          strcpy(cmd.value,"MULT");
          cmd.primitiveType=INT;
          cmd.exprType=COMMAND;
          $$=cmd;
        }
      | expr_t AND expr_f
        {
          verifyType(BOOL, $1.primitiveType, $3.primitiveType);
          generateExprCode($1,0);
          generateExprCode($3,0);
          Expr cmd;
          cmd.avaliated = 0;
          strcpy(cmd.value,"CONJ");
          cmd.primitiveType=BOOL;
          cmd.exprType=COMMAND;
          $$=cmd;
        }
      | expr_t DIVIDIDO expr_f 
        {
          verifyType(INT, $1.primitiveType, $3.primitiveType);
          generateExprCode($1,0);
          generateExprCode($3,0);
          Expr cmd;
          cmd.avaliated = 0;
          strcpy(cmd.value,"DIVI");
          cmd.primitiveType=INT;
          cmd.exprType=COMMAND;
          $$=cmd;
        }
      | expr_f {$$ = $1;}
;

expr_f: ABRE_PARENTESES expressao FECHA_PARENTESES {$$ = $2;}
      | constante {$$=$1;}
      | variavel {$$=$1;}
      | chamada_subrotina {$$=$1;}
;

variavel: IDENT
          {
            Expr var;
            var.avaliated = 0;
            strcpy(var.value,token);
            var.primitiveType=getSymbol(token)->types[0]->primitiveType;
            var.exprType=VARIABLE;
            $$=var;
          }
;

constante:  NUMERO 
            {
              Expr cte;
              cte.avaliated = 0;
              strcpy(cte.value,token);
              cte.primitiveType=INT;
              cte.exprType=CONSTANT;
              $$=cte;
            }
         |  TRUE
            {
              Expr cte;
              cte.avaliated = 0;
              strcpy(cte.value,"1");
              cte.primitiveType=BOOL;
              cte.exprType=CONSTANT;
              $$=cte;
            }
         |  FALSE
            {
              Expr cte;
              cte.avaliated = 0;
              strcpy(cte.value,"0");
              cte.primitiveType=BOOL;
              cte.exprType=CONSTANT;
              $$=cte;
            }
;

repetitivo: WHILE
            { 
              char *labelStart = (char*)malloc(sizeof(char)*CMD_MAX);
              nextLabel(labelStart);
              push(labelStart,&labels);
              geraCodigo(labelStart, "NADA");
            } 
            expressao DO
            {
              char *labelEnd = (char*)malloc(sizeof(char)*CMD_MAX);
              nextLabel(labelEnd);
              push(labelEnd,&labels);
              char dsvf[CMD_MAX];
              sprintf(dsvf,"DSVF %s",labelEnd);
              geraCodigo(NULL, dsvf);
            }
            comando_sem_rotulo
            {
              char *labelEnd = (char*)pop(&labels);
              char *labelStart = (char*)pop(&labels);
              if(labelStart == NULL || labelEnd == NULL) 
                imprimeErro("Pilha vazia");
              char dsvs[CMD_MAX];
              sprintf(dsvs,"DSVS %s",labelStart);
              geraCodigo(NULL, dsvs);
              geraCodigo(labelEnd, "NADA");
            }
;

condicional: IF expressao THEN
            { 
              char *labelElse = (char*)malloc(sizeof(char)*CMD_MAX);
              nextLabel(labelElse);
              push(labelElse,&labels);

              char dsvf[CMD_MAX];
              sprintf(dsvf,"DSVF %s",labelElse);
              geraCodigo(NULL, dsvf);
            }
            comando_sem_rotulo cond_else
;

cond_else: ELSE
           {
             char *labelElse = (char*)pop(&labels);
             if(labelElse == NULL) 
                imprimeErro("Pilha vazia");

             char *labelEnd = (char*)malloc(sizeof(char)*CMD_MAX);
             nextLabel(labelEnd);
             push(labelEnd,&labels);

             char dsvs[CMD_MAX];
             sprintf(dsvs,"DSVS %s",labelEnd);
             geraCodigo(NULL, dsvs);
             geraCodigo(labelElse, "NADA");
           }
           comando_sem_rotulo
           {
             char *labelEnd = (char*)pop(&labels);
             if(labelEnd == NULL) 
                imprimeErro("Pilha vazia");
             geraCodigo(labelEnd, "NADA");
           }
         | %prec LOWER_THAN_ELSE
           {
             char *labelElse = (char*)pop(&labels);
             if(labelElse == NULL) 
                imprimeErro("Pilha vazia");
             geraCodigo(labelElse, "NADA");
           }
;

parte_declara_rotulos: LABEL rotulos PONTO_E_VIRGULA 
                     |
;

rotulos: rotulos VIRGULA id_rotulo
       | id_rotulo
;

id_rotulo: NUMERO
        {
          Symbol *newSymbol = (Symbol*)malloc(sizeof(Symbol));
          strcpy(newSymbol->name,token);
          newSymbol->category = LABL;
          newSymbol->lexicalLevel = lexicalLevel;

          char *label = (char*)malloc(sizeof(char)*CMD_MAX);
          nextLabel(label);
          newSymbol->label = label;
          
          push(newSymbol,&symbolTable);
        }
;

rotulo: NUMERO
        {
          Symbol* symbol = getSymbol(token);
          char enrt[CMD_MAX];
          int count = countLevelSymbols(VS,lexicalLevel,&symbolTable);
          sprintf(enrt,"ENRT %d,%d",lexicalLevel,count);
          geraCodigo(symbol->label, enrt);
        }
        DOIS_PONTOS
      | 
;

desvio: GOTO NUMERO
        {
          Symbol* symbol = getSymbol(token);
          char dsvr[CMD_MAX];
          sprintf(dsvr,"DSVR %s,%d,%d",symbol->label,symbol->lexicalLevel,lexicalLevel);
          geraCodigo(NULL, dsvr);
        }
;

parte_declara_subrotinas: parte_declara_subrotinas parte_declara_subrotina
                        | parte_declara_subrotina
;

parte_declara_subrotina: declara_proc
                       | declara_func
                       |
;

declara_proc: PROCEDURE {subRoutineType = PROC;} 
              declara_subrotina bloco_subrotina
;

declara_subrotina: IDENT
                   {
                     lexicalLevel++;
                     char dsvs[CMD_MAX];
                     char *labelBegin = (char*)malloc(sizeof(char)*CMD_MAX);
                     nextLabel(labelBegin);
                     push(labelBegin,&labels);
                     sprintf(dsvs,"DSVS %s",labelBegin);
                     geraCodigo(NULL, dsvs);

                     Symbol *newSymbol = (Symbol*)malloc(sizeof(Symbol));
                     strcpy(newSymbol->name,token);
                     newSymbol->category = subRoutineType;
                     newSymbol->lexicalLevel = lexicalLevel;
                     newSymbol->types = NULL;
                     newSymbol->typesSize = 0;

                     char *labelSubRoutine = (char*)malloc(sizeof(char)*CMD_MAX);
                     nextLabel(labelSubRoutine);
                     newSymbol->label = labelSubRoutine;
                     
                     push(newSymbol,&symbolTable);
                     
                     category = PF;

                     char enpr[CMD_MAX];
                     sprintf(enpr,"ENPR %d",lexicalLevel);
                     geraCodigo(newSymbol->label, enpr);
                   }
                   param_formais
                   {
                     int count = countLevelSymbols(PF,lexicalLevel,&symbolTable);
                     if(count > 0){
                       Symbol** vars = lastSymbols(count+1,&symbolTable);
                       if(vars == NULL){
                         imprimeErro("Erro na tabela de s�mbolos.");
                       }
                       Symbol* subRoutine = vars[count];
                       subRoutine->types = (Type**)malloc(sizeof(Type*)*count);

                       for(int i = 0; i < count; i++){
                         vars[i]->displacement = -4-i;
                         subRoutine->types[i] = vars[i]->types[0];
                       }
                       subRoutine->typesSize = count;
                     }
                   }
;

bloco_subrotina: PONTO_E_VIRGULA bloco PONTO_E_VIRGULA
                   {
                     Symbol* subRoutine = (Symbol*)getByReversedIndex(0,&symbolTable);
                     char rtpr[CMD_MAX];
                     int returnSize = subRoutine->category == FUNC;
                     sprintf(rtpr,"RTPR %d,%d",lexicalLevel,subRoutine->typesSize-returnSize);
                     geraCodigo(NULL, rtpr);

                     lexicalLevel--;
                     char *label = (char*)pop(&labels);
                     geraCodigo(label, "NADA");
                   }
;

param_formais: ABRE_PARENTESES secoes_param_formais 
               secao_params FECHA_PARENTESES
             | ABRE_PARENTESES secao_params FECHA_PARENTESES
             |
;

secoes_param_formais: secoes_param_formais secao_param_formais
                    | secao_param_formais
;

secao_param_formais: secao_params PONTO_E_VIRGULA
;

secao_params: var_subrotina secao_var
;

var_subrotina: VAR { isReference = 1; }
             | { isReference = 0; }
;

declara_func: FUNCTION {subRoutineType = FUNC;} 
              declara_subrotina DOIS_PONTOS tipo_func
              bloco_subrotina
;

tipo_func:  IDENT
            {
              if((strcmp(token,"integer") != 0) && (strcmp(token,"boolean") != 0)){
                imprimeErro("Tipo de fun��o n�o permitido.");
              }else{
                int count = countLevelSymbols(PF,lexicalLevel,&symbolTable);
                Symbol* func = (Symbol*)getByReversedIndex(count,&symbolTable);
                if(func == NULL){
                  imprimeErro("Erro na tabela de s�mbolos.");
                }

                Type *type = (Type*)malloc(sizeof(Type));
                type->isReference = 0;
                if(strcmp(token,"integer") == 0) 
                  type->primitiveType = INT;
                else
                  type->primitiveType = BOOL;

                if(count > 0){
                  func->typesSize = func->typesSize+1;
                  func->types = (Type**)realloc(func->types,sizeof(Type*)*func->typesSize);
                  func->types[func->typesSize] = type;
                }else{
                  func->typesSize = 1;
                  func->types = (Type**)malloc(sizeof(Type*));
                  func->types[0] = type;
                }
                func->displacement = -4-count;
              }
            }
;

chamada_subrotina:  variavel
                    {
                      Symbol* symbol = getSymbol($1.value);
                      if(symbol->category == FUNC){
                        char amem[CMD_MAX];
                        sprintf(amem,"AMEM 1");
                        geraCodigo(NULL, amem);
                      }
                    }
                    declara_params_reais
                    {
                      Symbol* symbol = getSymbol($1.value);
                      int returnSize = symbol->category == FUNC;
                      Stack* subRoutineParams = (Stack*)pop(&params);
                      if(subRoutineParams != NULL){
                        if(subRoutineParams->size != symbol->typesSize-returnSize){
                          imprimeErro("N�mero incorreto de argumentos.");
                        }else{
                          for(int i=symbol->typesSize-returnSize-1; i>=0;i--){
                            Expr* expr = (Expr*)reversePop(subRoutineParams);
                            if(expr->primitiveType != INT
                              || (symbol->types[i]->isReference 
                                  && expr->exprType != VARIABLE)){
                              imprimeErro("Erro de sintaxe.");
                            }else{
                              generateExprCode(*expr,symbol->types[i]->isReference);
                            }
                          }
                        }
                      }else if(symbol->typesSize-returnSize > 0){
                        imprimeErro("N�mero incorreto de argumentos.");
                      }
                      char chpr[CMD_MAX];
                      sprintf(chpr,"CHPR %s,%d",symbol->label,lexicalLevel);
                      geraCodigo(NULL, chpr);
                      Expr func;
                      func.avaliated = 0;
                      strcpy(func.value,$1.value);
                      func.primitiveType= returnSize ? INT : VOID;
                      func.exprType=VARIABLE;
                      $$=func;
                    }
;

leitura:  READ declara_params
          {
            Stack* readParams = (Stack*)pop(&params);
            while(!emptyStack(readParams)){
              Expr* expr = (Expr*)reversePop(readParams);
              if(expr->exprType != VARIABLE){
                imprimeErro("Erro de sintaxe.");
              }else{
                char leit[CMD_MAX];
                sprintf(leit,"LEIT");
                geraCodigo(NULL, leit);
                generateStorageCode(expr->value);
              }
            }
          }
;

impressao:  WRITE declara_params
            {
              Stack* writeParams = (Stack*)pop(&params);
              while(!emptyStack(writeParams)){
                Expr* expr = (Expr*)reversePop(writeParams);
                generateExprCode(*expr,0);
                char impr[CMD_MAX];
                sprintf(impr,"IMPR");
                geraCodigo(NULL, impr);
              }
            }
;

declara_params_reais: declara_params
                    |
;

declara_params: ABRE_PARENTESES 
                {
                  Stack* subRoutineParams = (Stack*)malloc(sizeof(Stack));
                  startStack(subRoutineParams);
                  push(subRoutineParams,&params);
                }
                param_reais FECHA_PARENTESES
;

param_reais: param_reais VIRGULA expr_param 
           | expr_param
;

expr_param: expr_e {push(&$1,(Stack*)getByReversedIndex(0,&params));}
;

%%

int main (int argc, char** argv) {
   FILE* fp;
   extern FILE* yyin;

   if (argc<2 || argc>2) {
         printf("usage compilador <arq>a %d\n", argc);
         return(-1);
      }

   fp=fopen (argv[1], "r");
   if (fp == NULL) {
      printf("usage compilador <arq>b\n");
      return(-1);
   }


/* -------------------------------------------------------------------
 *  Inicia a Tabela de S�mbolos
 * ------------------------------------------------------------------- */
  startStack(&symbolTable);
  startStack(&labels);
  startStack(&params);

   yyin=fp;
   yyparse();

   return 0;
}

