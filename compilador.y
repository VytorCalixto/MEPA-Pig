
// Testar se funciona corretamente o empilhamento de parâmetros
// passados por valor ou por referência.


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

Address varAddress;

void verifyType(int type, int first, int third){
  if(first != type || third != type){
    imprimeErro("Erro de sintaxe.");
  }
} 

%}

%token PROGRAM ABRE_PARENTESES FECHA_PARENTESES 
%token VIRGULA PONTO_E_VIRGULA DOIS_PONTOS PONTO
%token T_BEGIN T_END VAR IDENT ATRIBUICAO
%token WHILE DO IF THEN ELSE
%token MAIOR MENOR IGUAL DIFERENTE MAIOR_IGUAL MENOR_IGUAL
%token PROCEDURE FUNCTION GOTO LABEL NUMERO
%token MAIS MENOS VEZES DIVIDIDO OR AND TRUE FALSE

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
          char dmem[AMEM_MAX];
          sprintf(dmem,"DMEM %d", idCount);
          geraCodigo(NULL, dmem);
        }
;

parte_declara_vars: {
                      idCount = 0;
                    }
                    VAR declara_vars
                    {
                      char amem[AMEM_MAX];
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
                Address address;
                address.lexicalLevel = lexicalLevel;
                address.displacement = idCount;                
                newSymbol.address = address;

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

comando_composto: T_BEGIN comandos T_END
;

comandos: comandos comando
        | comando
        |
;

comando: rotulo comando_sem_rotulo PONTO_E_VIRGULA
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
            { /*carrega o valor da expressao e armazena no identificador(memória)*/
              /*verifica o tipo (erro)*/
            }
;

variavel: IDENT 
          { 
            Symbol* symbol = findSymbol(token, &symbolTable);
            if(symbol == NULL){
              imprimeErro("Símbolo inexistente.");
            }else{
              varAddress = symbol->address;
            }
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

expressao: expr_e relacao expr_e { verifyType(INT, $1, $3); $$ = BOOL;}
         | expr_e {$$ = $1;}
;

relacao: MAIOR | MENOR | MAIOR_IGUAL | MENOR_IGUAL
       | IGUAL | DIFERENTE
;

expr_e: expr_e MAIS expr_t { verifyType(INT, $1, $3); $$ = INT; }
      | expr_e OR expr_t { verifyType(BOOL, $1, $3); $$ = BOOL; }
      | expr_e MENOS expr_t { verifyType(INT, $1, $3); $$ = INT; }
      | expr_t {$$ = $1;}
;

expr_t: expr_t VEZES expr_f { verifyType(INT, $1, $3); $$ = INT; }
      | expr_t AND expr_f { verifyType(BOOL, $1, $3); $$ = BOOL; }
      | expr_t DIVIDIDO expr_f { verifyType(INT, $1, $3); $$ = INT; }
      | expr_f {$$ = $1;}
;

expr_f: ABRE_PARENTESES expressao FECHA_PARENTESES {$$ = $2;}
      | constante {$$ = $1;}
      | IDENT {$$ = INT;}
;

constante: NUMERO {$$ = INT;}
         | TRUE {$$ = BOOL;}
         | FALSE {$$ = BOOL;}
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
 *  Inicia a Tabela de Símbolos
 * ------------------------------------------------------------------- */
  startSymbolTable(&symbolTable);

   yyin=fp;
   yyparse();

   return 0;
}

