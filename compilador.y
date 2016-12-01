
// Testar se funciona corretamente o empilhamento de parâmetros
// passados por valor ou por referência.


%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "compilador.h"

#include "dataStructures.c"
#include "definitions.h"


Stack symbolTable, labels;
int lexicalLevel = 0;
int idCount = 0;
int constType = -1;
int labelCount = 0;

void verifyType(int type, int first, int third){
  if(first != type || third != type){
    imprimeErro("Erro de sintaxe.");
  }
}

void nextLabel(char* label){
  sprintf(label,"R%02d",labelCount);
  labelCount++;
} 

%}

%union {
  char string[CMD_MAX];
  int integer;
}

%token PROGRAM ABRE_PARENTESES FECHA_PARENTESES 
%token VIRGULA PONTO_E_VIRGULA DOIS_PONTOS PONTO
%token T_BEGIN T_END VAR IDENT ATRIBUICAO
%token WHILE DO IF THEN ELSE
%token MAIOR MENOR IGUAL DIFERENTE MAIOR_IGUAL MENOR_IGUAL
%token PROCEDURE FUNCTION GOTO LABEL NUMERO
%token MAIS MENOS VEZES DIVIDIDO OR AND TRUE FALSE

%type <integer> expressao expr_e expr_t expr_f
%type <string> relacao constante variavel

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
        {
          lexicalLevel++;
        }
        parte_declara_subrotinas 
        {
          lexicalLevel--;
        }
        comando_composto 
        {
          clearLevel(lexicalLevel, &symbolTable);
          char dmem[CMD_MAX];
          sprintf(dmem,"DMEM %d", idCount);
          geraCodigo(NULL, dmem);
        }
;

parte_declara_vars: {
                      idCount = 0;
                    }
                    VAR declara_vars
                    {
                      char amem[CMD_MAX];
                      sprintf(amem,"AMEM %d", idCount);
                      geraCodigo(NULL, amem);
                    }
                    |
;

declara_vars: declara_vars declara_var 
            | declara_var 
;

declara_var:  lista_id_var DOIS_PONTOS tipo PONTO_E_VIRGULA
;

tipo: IDENT
;

lista_id_var: lista_id_var VIRGULA identificador 
            | identificador
;

identificador: IDENT
              {
                Symbol *newSymbol = (Symbol*)malloc(sizeof(Symbol));
                strcpy(newSymbol->name,token);
                newSymbol->category = VS;
                newSymbol->lexicalLevel = lexicalLevel;
                newSymbol->displacement = idCount;                

                Type *type = (Type*)malloc(sizeof(Type));
                type->primitiveType = INT;
                type->isReference = 0;
                newSymbol->types = type;
                newSymbol->typesSize = 1;
                
                push(newSymbol,&symbolTable);
                idCount++;
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
;

atribuicao: variavel ATRIBUICAO expressao
            {
              if($3 != INT){
                imprimeErro("Erro de sintaxe");
              }else{
                char armz[CMD_MAX];
                sprintf(armz,"ARMZ %s", $1);
                geraCodigo(NULL, armz);
              }
            }
;

expressao: expr_e relacao expr_e 
           {
            verifyType(INT, $1, $3);
            geraCodigo(NULL, $2);
            $$ = BOOL;
           }
         | expr_e {$$ = $1;}
;

relacao: MAIOR { strcpy($$,"CMMA"); } 
       | MENOR { strcpy($$,"CMME"); } 
       | MAIOR_IGUAL { strcpy($$,"CMAG"); } 
       | MENOR_IGUAL { strcpy($$,"CMEG"); } 
       | IGUAL { strcpy($$,"CMIG"); } 
       | DIFERENTE { strcpy($$,"CMDG"); } 
;

expr_e: expr_e MAIS expr_t 
        { 
          verifyType(INT, $1, $3);
          $$ = INT;
          geraCodigo(NULL, "SOMA");
        }
      | expr_e OR expr_t 
        { 
          verifyType(BOOL, $1, $3);
          $$ = BOOL;
          geraCodigo(NULL, "DISJ");
        }
      | expr_e MENOS expr_t 
        { 
          verifyType(INT, $1, $3);
          $$ = INT;
          geraCodigo(NULL, "SUBT");
        }
      | expr_t {$$ = $1;}
;

expr_t: expr_t VEZES expr_f 
        {
          verifyType(INT, $1, $3);
          $$ = INT;
          geraCodigo(NULL, "MULT");
        }
      | expr_t AND expr_f
        {
          verifyType(BOOL, $1, $3);
          $$ = BOOL;
          geraCodigo(NULL, "CONJ");
        }
      | expr_t DIVIDIDO expr_f 
        {
          verifyType(INT, $1, $3);
          $$ = INT;
          geraCodigo(NULL, "DIVI");
        }
      | expr_f {$$ = $1;}
;

expr_f: ABRE_PARENTESES expressao FECHA_PARENTESES { $$ = $2; }
      | constante 
        {
          char crct[CMD_MAX];
          sprintf(crct,"CRCT %s", $1);
          geraCodigo(NULL, crct);
          $$ = constType;
        }
      | variavel
        {
          char crvl[CMD_MAX];
          sprintf(crvl,"CRVL %s", $1);
          geraCodigo(NULL, crvl);
          $$ = INT;
        }
;

variavel: IDENT 
          { 
            Symbol* symbol = findSymbol(token, &symbolTable);
            if(symbol == NULL){
              imprimeErro("Variável inexistente.");
            }else{
              sprintf($$, "%d,%d", symbol->lexicalLevel, symbol->displacement);
            }
          }
;

constante: NUMERO
           {
            strcpy($$,token);
            constType = INT;
           }
         | TRUE
           {
            strcpy($$,"1");
            constType = BOOL;
           }
         | FALSE 
           {
            strcpy($$,"0");
            constType = BOOL;
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
          Symbol* symbol = findSymbol(token, &symbolTable);
          if(symbol == NULL){
            imprimeErro("Rótulo inexistente.");
          }else{
            char enrt[CMD_MAX];
            sprintf(enrt,"ENRT %d,%d",lexicalLevel,idCount);
            geraCodigo(symbol->label, enrt);
          }
        }
        DOIS_PONTOS
      | 
;

desvio: GOTO NUMERO
        {
          Symbol* symbol = findSymbol(token, &symbolTable);
          if(symbol == NULL){
            imprimeErro("Rótulo inexistente.");
          }else{
            char dsvr[CMD_MAX];
            sprintf(dsvr,"DSVR %s,%d,%d",symbol->label,symbol->lexicalLevel,lexicalLevel);
            geraCodigo(NULL, dsvr);
          }
        }
;

parte_declara_subrotinas: declara_proc
                        | declara_func
                        |
;

declara_proc: PROCEDURE declara_subrotina
;

declara_subrotina: IDENT param_formais PONTO_E_VIRGULA bloco
;

param_formais: ABRE_PARENTESES secoes_param_formais FECHA_PARENTESES
             | /*regra opcional*/
;

secoes_param_formais: secoes_param_formais secao_param_formais
                    | secao_param_formais
;

secao_param_formais: var_subrotina lista_id_var DOIS_PONTOS tipo
;

var_subrotina: VAR | /*regra opcional*/
;

declara_func: FUNCTION declara_subrotina

//chama_func: //TODO

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
 *  Inicia a Tabela de Símbolos
 * ------------------------------------------------------------------- */
  startStack(&symbolTable);
  startStack(&labels);

   yyin=fp;
   yyparse();

   return 0;
}

