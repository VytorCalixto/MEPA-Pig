/* -------------------------------------------------------------------
 *            Arquivo: compilaodr.h
 * -------------------------------------------------------------------
 *              Autor: Bruno Muller Junior
 *               Data: 08/2007
 *      Atualizado em: [15/03/2012, 08h:22m]
 *
 * -------------------------------------------------------------------
 *
 * Tipos, prot�tipos e vai�veis globais do compilador
 *
 * ------------------------------------------------------------------- */

#define TAM_TOKEN 16

typedef struct Expr{
  char value[TAM_TOKEN];
  int primitiveType;
  int exprType;
  int avaliated;
}Expr;

typedef enum simbolos { 
  simb_program, simb_var, simb_begin, simb_end, 
  simb_identificador, simb_numero,
  simb_ponto, simb_virgula, simb_ponto_e_virgula, simb_dois_pontos,
  simb_atribuicao, simb_abre_parenteses, simb_fecha_parenteses,
  simb_while, simb_do, simb_if, simb_then, simb_else, simb_procedure,
  simb_function, simb_goto, simb_label, simb_maior_igual, simb_menor_igual,
  simb_diferente, simb_maior, simb_menor, simb_igual, simb_mais, simb_menos,
  simb_vezes, simb_or, simb_and, simb_dividido, simb_true, simb_false,
  simb_read, simb_write
} simbolos;



/* -------------------------------------------------------------------
 * vari�veis globais
 * ------------------------------------------------------------------- */

extern simbolos simbolo, relacao;
extern char token[TAM_TOKEN];
extern int nivel_lexico;
extern int desloc;
extern int nl;


simbolos simbolo, relacao;
char token[TAM_TOKEN];



