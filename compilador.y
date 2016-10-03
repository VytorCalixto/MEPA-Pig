
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

%}

%token PROGRAM ABRE_PARENTESES FECHA_PARENTESES 
%token VIRGULA PONTO_E_VIRGULA DOIS_PONTOS PONTO
%token T_BEGIN T_END VAR IDENT ATRIBUICAO

%%

programa    :{ 
             geraCodigo (NULL, "INPP"); 
             }
             PROGRAM IDENT 
             ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA
             bloco PONTO {
             geraCodigo (NULL, "PARA"); 
             }
;

bloco       : 
              parte_declara_vars
              { 
              }

              comando_composto 
              ;




parte_declara_vars:  var 
;


var         : {
                idCount = 0;
              }
              VAR declara_vars
              {
                char amem[10];
                sprinf(amem,"AMEM %d", idCount);
                geraCodigo(NULL, amem);
              }
              |
;

declara_vars: declara_vars declara_var 
            | declara_var 
;

declara_var : { } 
              lista_id_var DOIS_PONTOS 
              tipo 
              { /* AMEM */
              }
              PONTO_E_VIRGULA
;

tipo        : IDENT
;

lista_id_var: lista_id_var VIRGULA identificador 
              { /* insere �ltima vars na tabela de s�mbolos */ }
            | identificador { /* insere vars na tabela de s�mbolos */}
;

identificador: IDENT
              {
                Symbol newSymbol;
                strcopy(newSymbol.name,token);
                newSymbol.category = VS;
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

comandos:    
;


%%

main (int argc, char** argv) {
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

