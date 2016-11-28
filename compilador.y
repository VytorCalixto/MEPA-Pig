
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

%}

%token PROGRAM ABRE_PARENTESES FECHA_PARENTESES 
%token VIRGULA PONTO_E_VIRGULA DOIS_PONTOS PONTO
%token T_BEGIN T_END VAR IDENT ATRIBUICAO
%token WHILE DO IF THEN ELSE
%token MAIOR MENOR IGUAL DIFERENTE MAIOR_IGUAL MENOR_IGUAL
%token PROCEDURE FUNCTION GOTO LABEL NUMERO
%token MAIS MENOS VEZES OR AND

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
        //parte_declara_subrotinas 
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
            { /*carrega o valor da expressao e armazena no identificador(mem�ria)*/
              /*verifica o tipo (erro)*/
            }
;

variavel: IDENT 
          { /* busca identificador na tabela e insere o "endere�o" numa variavel*/}
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

expressao: expressao relacao expr_simples 
         | expr_simples
;

relacao: MAIOR | MENOR | MAIOR_IGUAL | MENOR_IGUAL
       | IGUAL | DIFERENTE
;

expr_simples: ABRE_PARENTESES expressao FECHA_PARENTESES
            | IDENT
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

