
// Testar se funciona corretamente o empilhamento de par�metros
// passados por valor ou por refer�ncia.


%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "compilador.h"

#include "symbolTable.c"
#include "definitions.h"


SymbolTable symbolTable;
int lexicalLevel = 0;
int idCount = 0;
int category = VS;
int constType = -1;

void verifyType(int type, int first, int third){
  printf("%d %d \n", first, third);
  if(first != type || third != type){
    imprimeErro("Erro de sintaxe.");
  }
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
                Symbol newSymbol;
                strcpy(newSymbol.name,token);
                newSymbol.category = category;
                newSymbol.lexicalLevel = lexicalLevel;
                newSymbol.displacement = idCount;                

                Type type;
                type.primitiveType = INT;
                type.isReference = 0;
                newSymbol.types = &type;
                newSymbol.typesSize = 1;
                
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

rotulo: NUMERO DOIS_PONTOS
      | /*regra opcional*/
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
              printf("expr = %d", $3);
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

relacao: MAIOR
         {
          strcpy($$,"CMMA");
         } 
       | MENOR 
         {
          strcpy($$,"CMME");
         } 
       | MAIOR_IGUAL 
         {
          strcpy($$,"CMAG");
         } 
       | MENOR_IGUAL
         {
          strcpy($$,"CMEG");
         } 
       | IGUAL 
         {
          strcpy($$,"CMIG");
         } 
       | DIFERENTE
         {
          strcpy($$,"CMDG");
         } 
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

expr_f: ABRE_PARENTESES expressao FECHA_PARENTESES
        {
          $$ = $2;
        }
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
              imprimeErro("S�mbolo inexistente.");
            }else{
              sprintf($$, "%d,%d", symbol->lexicalLevel, symbol->displacement);
              printf("\nint %s \n\n", $$);
            }
          }
;

constante: NUMERO
           {
            strcpy($$,token);
            constType = INT;
            printf("\n int %s %d \n\n", $$, constType);
           }
         | TRUE
           {
            strcpy($$,"1");
            constType = BOOL;
            printf("\n bool %s %d \n\n", $$, constType);
           }
         | FALSE 
           {
            strcpy($$,"0");
            constType = BOOL;
            printf("\n bool %s %d \n\n", $$, constType);
           }
;

repetitivo: WHILE
            { /* rot_in = proxRot();
              geraCodigo(rot_in, "NADA");*/
            } expressao DO
            {/* rot_out = proxRot();
              char dsvf[10];
              sprintf(dsvf, "DSVF %d", rot_in);
              geraCodigo(NULL, dsvf);*/
            } comando_sem_rotulo
;

condicional: IF expressao THEN
            { /*DSVF rot_else*/ }
            comando_sem_rotulo cond_else
            {/*rot_fim_if*/}
;

cond_else: ELSE comando_sem_rotulo
          { /*DSVS rot_fim_if;
              rot_else*/ }
         | %prec LOWER_THAN_ELSE
;

desvio: GOTO NUMERO
;

parte_declara_rotulos: LABEL rotulos PONTO_E_VIRGULA |
;

rotulos: rotulos VIRGULA NUMERO
       | NUMERO
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
 *  Inicia a Tabela de S�mbolos
 * ------------------------------------------------------------------- */
  startSymbolTable(&symbolTable);

   yyin=fp;
   yyparse();

   return 0;
}

