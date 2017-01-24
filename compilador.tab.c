/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 6 "compilador.y" /* yacc.c:339  */

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
int expressionLoop = 0;

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
  if(expr.value[0] != '\0'){
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


#line 145 "compilador.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "compilador.tab.h".  */
#ifndef YY_YY_COMPILADOR_TAB_H_INCLUDED
# define YY_YY_COMPILADOR_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    PROGRAM = 258,
    ABRE_PARENTESES = 259,
    FECHA_PARENTESES = 260,
    VIRGULA = 261,
    PONTO_E_VIRGULA = 262,
    DOIS_PONTOS = 263,
    PONTO = 264,
    T_BEGIN = 265,
    T_END = 266,
    VAR = 267,
    IDENT = 268,
    ATRIBUICAO = 269,
    WHILE = 270,
    DO = 271,
    IF = 272,
    THEN = 273,
    ELSE = 274,
    MAIOR = 275,
    MENOR = 276,
    IGUAL = 277,
    DIFERENTE = 278,
    MAIOR_IGUAL = 279,
    MENOR_IGUAL = 280,
    PROCEDURE = 281,
    FUNCTION = 282,
    GOTO = 283,
    LABEL = 284,
    NUMERO = 285,
    READ = 286,
    WRITE = 287,
    MAIS = 288,
    MENOS = 289,
    VEZES = 290,
    DIVIDIDO = 291,
    OR = 292,
    AND = 293,
    TRUE = 294,
    FALSE = 295,
    LOWER_THAN_ELSE = 296
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 85 "compilador.y" /* yacc.c:355  */

  Expr expr;

#line 231 "compilador.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_COMPILADOR_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 246 "compilador.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   132

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  64
/* YYNRULES -- Number of rules.  */
#define YYNRULES  110
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  168

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   296

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   104,   104,   104,   115,   130,   130,   141,   144,   145,
     148,   150,   150,   154,   173,   174,   177,   198,   199,   202,
     203,   206,   207,   209,   210,   213,   216,   217,   218,   219,
     220,   221,   222,   223,   226,   237,   248,   261,   280,   295,
     303,   311,   319,   327,   335,   345,   356,   367,   378,   381,
     392,   403,   414,   417,   418,   419,   420,   423,   434,   442,
     450,   461,   468,   460,   490,   489,   503,   502,   524,   533,
     534,   537,   538,   541,   557,   556,   565,   568,   577,   578,
     581,   582,   583,   586,   586,   591,   590,   639,   653,   655,
     656,   659,   660,   663,   666,   669,   670,   673,   673,   678,
     718,   717,   760,   777,   790,   791,   795,   794,   803,   804,
     807
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PROGRAM", "ABRE_PARENTESES",
  "FECHA_PARENTESES", "VIRGULA", "PONTO_E_VIRGULA", "DOIS_PONTOS", "PONTO",
  "T_BEGIN", "T_END", "VAR", "IDENT", "ATRIBUICAO", "WHILE", "DO", "IF",
  "THEN", "ELSE", "MAIOR", "MENOR", "IGUAL", "DIFERENTE", "MAIOR_IGUAL",
  "MENOR_IGUAL", "PROCEDURE", "FUNCTION", "GOTO", "LABEL", "NUMERO",
  "READ", "WRITE", "MAIS", "MENOS", "VEZES", "DIVIDIDO", "OR", "AND",
  "TRUE", "FALSE", "LOWER_THAN_ELSE", "$accept", "programa", "$@1",
  "bloco", "parte_declara_vars", "$@2", "declara_vars", "declara_var",
  "secao_var", "$@3", "tipo", "lista_id_var", "identificador",
  "lista_idents", "comando_composto", "comando_end", "comandos", "comando",
  "comando_sem_rotulo", "atribuicao", "expressao", "relacao", "expr_e",
  "expr_t", "expr_f", "variavel", "constante", "repetitivo", "$@4", "$@5",
  "condicional", "$@6", "cond_else", "$@7", "parte_declara_rotulos",
  "rotulos", "id_rotulo", "rotulo", "$@8", "desvio",
  "parte_declara_subrotinas", "parte_declara_subrotina", "declara_proc",
  "$@9", "declara_subrotina", "$@10", "bloco_subrotina", "param_formais",
  "secoes_param_formais", "secao_param_formais", "secao_params",
  "var_subrotina", "declara_func", "$@11", "tipo_func",
  "chamada_subrotina", "$@12", "leitura", "impressao",
  "declara_params_reais", "declara_params", "$@13", "param_reais",
  "expr_param", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296
};
# endif

#define YYPACT_NINF -142

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-142)))

#define YYTABLE_NINF -101

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -142,     7,    42,  -142,    -3,    12,    20,  -142,    66,    44,
      41,    40,  -142,    50,    70,    69,  -142,    67,  -142,  -142,
      49,    71,    50,  -142,  -142,  -142,    16,  -142,  -142,  -142,
    -142,  -142,    73,    73,    52,  -142,  -142,    74,  -142,    77,
      75,  -142,    78,    81,  -142,    79,    52,    84,    -4,  -142,
    -142,  -142,    58,  -142,    88,    40,  -142,    80,    86,  -142,
      85,    90,    89,  -142,  -142,    -1,    65,    97,    97,  -142,
    -142,  -142,    91,  -142,  -142,  -142,  -142,  -142,  -142,    75,
      93,    92,  -142,    95,  -142,    78,  -142,  -142,    89,    -1,
      -1,  -142,  -142,  -142,    94,    -2,    17,  -142,    99,  -142,
    -142,  -142,  -142,  -142,  -142,    -1,    97,  -142,  -142,  -142,
    -142,    92,  -142,    60,  -142,  -142,  -142,    98,   102,  -142,
    -142,  -142,  -142,  -142,  -142,  -142,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  -142,    30,    37,  -142,  -142,  -142,
      63,  -142,  -142,  -142,  -142,  -142,    -4,    17,    17,    17,
      13,  -142,  -142,  -142,    13,    72,  -142,  -142,    -4,    96,
    -142,    -1,  -142,  -142,  -142,  -142,    -4,  -142
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     0,    18,     0,     0,
       0,    70,    17,     0,     0,     7,    73,     0,    72,     3,
      82,     0,     0,    69,    83,    97,     0,    79,    80,    81,
      11,    71,     0,     0,    76,     4,    78,     6,     9,     0,
       0,    85,     0,     0,    74,     0,    76,    22,     0,     8,
      10,    16,     0,    15,    90,    70,    84,     0,     0,    20,
       0,    22,    24,    57,    61,     0,     0,     0,     0,    28,
      25,    26,   100,    30,    29,    27,    31,    32,    33,     0,
       0,    96,    86,     0,    99,     0,    75,    19,    23,     0,
       0,    58,    59,    60,     0,    38,    48,    52,    55,    54,
      56,    77,   106,   102,   103,     0,   105,    14,    13,    12,
      95,    96,    92,     0,    11,    87,    98,     0,     0,    64,
      39,    40,    43,    44,    41,    42,     0,     0,     0,     0,
       0,     0,     0,     0,    34,    55,    54,   101,   104,    91,
       0,    89,    93,    94,    62,    53,     0,    45,    47,    46,
      37,    49,    51,    50,   110,     0,   109,    88,     0,    68,
     107,     0,    63,    66,    65,   108,     0,    67
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -142,  -142,  -142,    53,  -142,  -142,  -142,    76,    -5,  -142,
    -142,  -142,    38,  -142,   100,    82,  -142,    83,  -141,  -142,
     -75,  -142,  -125,   -68,   -69,   -48,    11,  -142,  -142,  -142,
    -142,  -142,  -142,  -142,  -142,  -142,   101,  -142,  -142,  -142,
    -142,   104,  -142,  -142,    87,  -142,    36,  -142,  -142,    14,
      21,  -142,  -142,  -142,  -142,   -47,  -142,  -142,  -142,  -142,
     -66,  -142,  -142,   -39
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    14,    20,    21,    37,    38,    39,    40,
     109,    52,    53,     8,    69,    45,    46,    47,    70,    71,
      94,   129,    95,    96,    97,    98,    99,    73,    89,   158,
      74,   146,   164,   166,    15,    17,    18,    48,    58,    75,
      26,    27,    28,    32,    42,    54,    56,    82,   111,   112,
     113,   114,    29,    33,    85,   100,   106,    77,    78,   137,
     103,   133,   155,   156
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      72,    76,   104,    90,   150,   159,    34,     3,   154,    63,
       5,    64,    63,    65,   117,   118,     6,   162,   120,   121,
     122,   123,   124,   125,    66,   167,    34,    67,    68,    91,
     134,   126,   127,     7,  -100,   128,   154,   -36,    92,    93,
     138,   -36,    24,    25,   -35,     4,   126,   127,   -35,   -36,
     128,    11,   130,   131,    12,   132,   -35,   135,   147,   148,
     149,   151,   152,   153,    79,   141,    80,   142,   157,    13,
     142,     9,    10,    22,    23,    24,    25,   160,   161,    19,
      16,    -5,    44,    30,    50,    55,    41,   -11,    51,    57,
      59,    62,    81,    84,    86,   101,    87,    88,    72,    76,
     -21,   102,   115,  -100,   110,   105,   108,   145,    83,   143,
      72,    76,   119,    49,   144,   163,   136,   107,    72,    76,
      43,   116,   165,    31,     0,   139,    35,     0,    60,    61,
      36,     0,   140
};

static const yytype_int16 yycheck[] =
{
      48,    48,    68,     4,   129,   146,    10,     0,   133,    13,
      13,    15,    13,    17,    89,    90,     4,   158,    20,    21,
      22,    23,    24,    25,    28,   166,    10,    31,    32,    30,
     105,    33,    34,    13,     4,    37,   161,     7,    39,    40,
     106,    11,    26,    27,     7,     3,    33,    34,    11,    19,
      37,     7,    35,    36,    13,    38,    19,   105,   126,   127,
     128,   130,   131,   132,     6,     5,     8,     7,     5,    29,
       7,     5,     6,     6,     7,    26,    27,     5,     6,     9,
      30,    12,    30,    12,     7,     7,    13,    13,    13,     8,
      11,     7,     4,    13,     8,    30,    11,     7,   146,   146,
      11,     4,     7,     4,    12,    14,    13,     5,    55,   114,
     158,   158,    18,    37,    16,    19,   105,    79,   166,   166,
      33,    85,   161,    22,    -1,   111,    26,    -1,    46,    46,
      26,    -1,   111
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    43,    44,     0,     3,    13,     4,    13,    55,     5,
       6,     7,    13,    29,    45,    76,    30,    77,    78,     9,
      46,    47,     6,     7,    26,    27,    82,    83,    84,    94,
      12,    78,    85,    95,    10,    56,    83,    48,    49,    50,
      51,    13,    86,    86,    30,    57,    58,    59,    79,    49,
       7,    13,    53,    54,    87,     7,    88,     8,    80,    11,
      57,    59,     7,    13,    15,    17,    28,    31,    32,    56,
      60,    61,    67,    69,    72,    81,    97,    99,   100,     6,
       8,     4,    89,    45,    13,    96,     8,    11,     7,    70,
       4,    30,    39,    40,    62,    64,    65,    66,    67,    68,
      97,    30,     4,   102,   102,    14,    98,    54,    13,    52,
      12,    90,    91,    92,    93,     7,    88,    62,    62,    18,
      20,    21,    22,    23,    24,    25,    33,    34,    37,    63,
      35,    36,    38,   103,    62,    67,    68,   101,   102,    91,
      92,     5,     7,    50,    16,     5,    73,    65,    65,    65,
      64,    66,    66,    66,    64,   104,   105,     5,    71,    60,
       5,     6,    60,    19,    74,   105,    75,    60
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    42,    44,    43,    45,    47,    46,    46,    48,    48,
      49,    51,    50,    52,    53,    53,    54,    55,    55,    56,
      56,    57,    57,    58,    58,    59,    60,    60,    60,    60,
      60,    60,    60,    60,    61,    61,    61,    62,    62,    63,
      63,    63,    63,    63,    63,    64,    64,    64,    64,    65,
      65,    65,    65,    66,    66,    66,    66,    67,    68,    68,
      68,    70,    71,    69,    73,    72,    75,    74,    74,    76,
      76,    77,    77,    78,    80,    79,    79,    81,    82,    82,
      83,    83,    83,    85,    84,    87,    86,    88,    89,    89,
      89,    90,    90,    91,    92,    93,    93,    95,    94,    96,
      98,    97,    99,   100,   101,   101,   103,   102,   104,   104,
     105
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     9,     4,     0,     3,     0,     2,     1,
       2,     0,     4,     1,     3,     1,     1,     3,     1,     4,
       3,     2,     1,     3,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     1,     3,
       3,     3,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     0,     0,     6,     0,     6,     0,     3,     0,     3,
       0,     3,     1,     1,     0,     3,     0,     2,     2,     1,
       1,     1,     0,     0,     4,     0,     3,     3,     4,     3,
       0,     2,     1,     2,     2,     1,     0,     0,     6,     1,
       0,     3,     2,     2,     1,     0,     0,     4,     3,     1,
       1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 104 "compilador.y" /* yacc.c:1646  */
    {
            geraCodigo(NULL, "INPP");
          }
#line 1459 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 110 "compilador.y" /* yacc.c:1646  */
    {
            geraCodigo(NULL, "PARA");
          }
#line 1467 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 119 "compilador.y" /* yacc.c:1646  */
    {
          int count = countLevelSymbols(VS,lexicalLevel,&symbolTable);
          if(count > 0){
            char dmem[CMD_MAX];
            sprintf(dmem,"DMEM %d", count);
            geraCodigo(NULL, dmem);
          }
          clearLevel(lexicalLevel, &symbolTable);
        }
#line 1481 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 130 "compilador.y" /* yacc.c:1646  */
    {
                      category = VS;
                      isReference = 0;
                    }
#line 1490 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 135 "compilador.y" /* yacc.c:1646  */
    {
                      int count = countLevelSymbols(VS,lexicalLevel,&symbolTable);
                      char amem[CMD_MAX];
                      sprintf(amem,"AMEM %d", count);
                      geraCodigo(NULL, amem);
                    }
#line 1501 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 150 "compilador.y" /* yacc.c:1646  */
    {typeCount = 0;}
#line 1507 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 155 "compilador.y" /* yacc.c:1646  */
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
#line 1528 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 178 "compilador.y" /* yacc.c:1646  */
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
#line 1551 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 227 "compilador.y" /* yacc.c:1646  */
    {
              if(((yyvsp[-2].expr).primitiveType != (yyvsp[0].expr).primitiveType)
                && (yyvsp[0].expr).primitiveType != INT
                && (yyvsp[0].expr).primitiveType != BOOL){
                imprimeErro("Erro de sintaxe");
              }else{
                generateExprCode((yyvsp[0].expr),0);
                generateStorageCode((yyvsp[-2].expr).value);
              }
            }
#line 1566 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 238 "compilador.y" /* yacc.c:1646  */
    {
                if(((yyvsp[-2].expr).primitiveType != (yyvsp[0].expr).primitiveType)
                  && (yyvsp[0].expr).primitiveType != INT
                  && (yyvsp[0].expr).primitiveType != BOOL){
                  imprimeErro("Erro de sintaxe");
                }else{
                  generateExprCode((yyvsp[0].expr),0);
                  generateStorageCode((yyvsp[-2].expr).value);
                }
            }
#line 1581 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 249 "compilador.y" /* yacc.c:1646  */
    {
                if(((yyvsp[-2].expr).primitiveType != (yyvsp[0].expr).primitiveType)
                  && (yyvsp[0].expr).primitiveType != INT
                  && (yyvsp[0].expr).primitiveType != BOOL){
                  imprimeErro("Erro de sintaxe");
                }else{
                  generateExprCode((yyvsp[0].expr),0);
                  generateStorageCode((yyvsp[-2].expr).value);
                }
            }
#line 1596 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 262 "compilador.y" /* yacc.c:1646  */
    {
              if((yyvsp[-1].expr).exprType == COMMAND) {
                verifyType(INT, (yyvsp[-2].expr).primitiveType, (yyvsp[0].expr).primitiveType);
              } else if ((yyvsp[-1].expr).exprType == BOOLCOMMAND) {
                if((yyvsp[-2].expr).primitiveType != (yyvsp[0].expr).primitiveType
                  || ((yyvsp[-2].expr).primitiveType != INT && (yyvsp[-2].expr).primitiveType != BOOL)) {
                  imprimeErro("Erro de sintaxe.");
                }
              }
              generateExprCode((yyvsp[-2].expr),0);
              generateExprCode((yyvsp[0].expr),0);
              generateExprCode((yyvsp[-1].expr),0);
              Expr cmd;
              cmd.value[0] = '\0';
              cmd.primitiveType=BOOL;
              cmd.exprType=COMMAND;
              (yyval.expr)=cmd;
            }
#line 1619 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 281 "compilador.y" /* yacc.c:1646  */
    {
            printf("\tTIPO DA EXPRESSÃO: %d\tEXPRTYPE: %d\n", (yyvsp[0].expr).primitiveType, (yyvsp[0].expr).exprType);
            printf("\tLOOP DE EXPRESSÃO? %d\n", expressionLoop);
            if((yyvsp[0].expr).primitiveType != BOOL) imprimeErro("Erro de sintaxe.");
            if(((yyvsp[0].expr).exprType == VARIABLE || (yyvsp[0].expr).exprType == CONSTANT) && expressionLoop == 0){
                printf("\tGerei código para: %s\n", (yyvsp[0].expr).value);
                generateExprCode((yyvsp[0].expr),0);
            } else {
                expressionLoop = 0;
            }
            (yyval.expr) = (yyvsp[0].expr);
          }
#line 1636 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 296 "compilador.y" /* yacc.c:1646  */
    {
            Expr cmd;
            strcpy(cmd.value,"CMMA");
            cmd.primitiveType=BOOL;
            cmd.exprType=COMMAND;
            (yyval.expr)=cmd;
          }
#line 1648 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 304 "compilador.y" /* yacc.c:1646  */
    {
            Expr cmd;
            strcpy(cmd.value,"CMME");
            cmd.primitiveType=BOOL;
            cmd.exprType=COMMAND;
            (yyval.expr)=cmd;
          }
#line 1660 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 312 "compilador.y" /* yacc.c:1646  */
    {
            Expr cmd;
            strcpy(cmd.value,"CMAG");
            cmd.primitiveType=BOOL;
            cmd.exprType=COMMAND;
            (yyval.expr)=cmd;
          }
#line 1672 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 320 "compilador.y" /* yacc.c:1646  */
    {
            Expr cmd;
            strcpy(cmd.value,"CMEG");
            cmd.primitiveType=BOOL;
            cmd.exprType=COMMAND;
            (yyval.expr)=cmd;
          }
#line 1684 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 328 "compilador.y" /* yacc.c:1646  */
    {
            Expr cmd;
            strcpy(cmd.value,"CMIG");
            cmd.primitiveType=BOOL;
            cmd.exprType=BOOLCOMMAND;
            (yyval.expr)=cmd;
          }
#line 1696 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 336 "compilador.y" /* yacc.c:1646  */
    {
            Expr cmd;
            strcpy(cmd.value,"CMDG");
            cmd.primitiveType=BOOL;
            cmd.exprType=BOOLCOMMAND;
            (yyval.expr)=cmd;
          }
#line 1708 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 346 "compilador.y" /* yacc.c:1646  */
    {
          verifyType(INT, (yyvsp[-2].expr).primitiveType, (yyvsp[0].expr).primitiveType);
          generateExprCode((yyvsp[-2].expr),0);
          generateExprCode((yyvsp[0].expr),0);
          Expr cmd;
          strcpy(cmd.value,"SOMA");
          cmd.primitiveType=INT;
          cmd.exprType=COMMAND;
          (yyval.expr)=cmd;
        }
#line 1723 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 357 "compilador.y" /* yacc.c:1646  */
    {
          verifyType(BOOL, (yyvsp[-2].expr).primitiveType, (yyvsp[0].expr).primitiveType);
          generateExprCode((yyvsp[-2].expr),0);
          generateExprCode((yyvsp[0].expr),0);
          Expr cmd;
          strcpy(cmd.value,"DISJ");
          cmd.primitiveType=BOOL;
          cmd.exprType=COMMAND;
          (yyval.expr)=cmd;
        }
#line 1738 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 368 "compilador.y" /* yacc.c:1646  */
    {
          verifyType(INT, (yyvsp[-2].expr).primitiveType, (yyvsp[0].expr).primitiveType);
          generateExprCode((yyvsp[-2].expr),0);
          generateExprCode((yyvsp[0].expr),0);
          Expr cmd;
          strcpy(cmd.value,"SUBT");
          cmd.primitiveType=INT;
          cmd.exprType=COMMAND;
          (yyval.expr)=cmd;
        }
#line 1753 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 378 "compilador.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 1759 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 382 "compilador.y" /* yacc.c:1646  */
    {
          verifyType(INT, (yyvsp[-2].expr).primitiveType, (yyvsp[0].expr).primitiveType);
          generateExprCode((yyvsp[-2].expr),0);
          generateExprCode((yyvsp[0].expr),0);
          Expr cmd;
          strcpy(cmd.value,"MULT");
          cmd.primitiveType=INT;
          cmd.exprType=COMMAND;
          (yyval.expr)=cmd;
        }
#line 1774 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 393 "compilador.y" /* yacc.c:1646  */
    {
          verifyType(BOOL, (yyvsp[-2].expr).primitiveType, (yyvsp[0].expr).primitiveType);
          generateExprCode((yyvsp[-2].expr),0);
          generateExprCode((yyvsp[0].expr),0);
          Expr cmd;
          strcpy(cmd.value,"CONJ");
          cmd.primitiveType=BOOL;
          cmd.exprType=COMMAND;
          (yyval.expr)=cmd;
        }
#line 1789 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 404 "compilador.y" /* yacc.c:1646  */
    {
          verifyType(INT, (yyvsp[-2].expr).primitiveType, (yyvsp[0].expr).primitiveType);
          generateExprCode((yyvsp[-2].expr),0);
          generateExprCode((yyvsp[0].expr),0);
          Expr cmd;
          strcpy(cmd.value,"DIVI");
          cmd.primitiveType=INT;
          cmd.exprType=COMMAND;
          (yyval.expr)=cmd;
        }
#line 1804 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 414 "compilador.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 1810 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 417 "compilador.y" /* yacc.c:1646  */
    {expressionLoop = 1; printf("\tSETEI LOOP\n"); (yyval.expr) = (yyvsp[-1].expr);}
#line 1816 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 418 "compilador.y" /* yacc.c:1646  */
    {expressionLoop = 0; (yyval.expr)=(yyvsp[0].expr);}
#line 1822 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 419 "compilador.y" /* yacc.c:1646  */
    {expressionLoop = 0; (yyval.expr)=(yyvsp[0].expr);}
#line 1828 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 420 "compilador.y" /* yacc.c:1646  */
    {expressionLoop = 0; (yyval.expr)=(yyvsp[0].expr);}
#line 1834 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 424 "compilador.y" /* yacc.c:1646  */
    {
            Expr var;
            strcpy(var.value,token);
            Symbol* symbol = getSymbol(token);
            var.primitiveType=symbol->types[symbol->typesSize-1]->primitiveType;
            var.exprType=VARIABLE;
            (yyval.expr)=var;
          }
#line 1847 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 435 "compilador.y" /* yacc.c:1646  */
    {
              Expr cte;
              strcpy(cte.value,token);
              cte.primitiveType=INT;
              cte.exprType=CONSTANT;
              (yyval.expr)=cte;
            }
#line 1859 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 443 "compilador.y" /* yacc.c:1646  */
    {
              Expr cte;
              strcpy(cte.value,"1");
              cte.primitiveType=BOOL;
              cte.exprType=CONSTANT;
              (yyval.expr)=cte;
            }
#line 1871 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 451 "compilador.y" /* yacc.c:1646  */
    {
              Expr cte;
              strcpy(cte.value,"0");
              cte.primitiveType=BOOL;
              cte.exprType=CONSTANT;
              (yyval.expr)=cte;
            }
#line 1883 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 461 "compilador.y" /* yacc.c:1646  */
    {
              char *labelStart = (char*)malloc(sizeof(char)*CMD_MAX);
              nextLabel(labelStart);
              push(labelStart,&labels);
              geraCodigo(labelStart, "NADA");
            }
#line 1894 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 468 "compilador.y" /* yacc.c:1646  */
    {
              char *labelEnd = (char*)malloc(sizeof(char)*CMD_MAX);
              nextLabel(labelEnd);
              push(labelEnd,&labels);
              char dsvf[CMD_MAX];
              sprintf(dsvf,"DSVF %s",labelEnd);
              geraCodigo(NULL, dsvf);
            }
#line 1907 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 477 "compilador.y" /* yacc.c:1646  */
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
#line 1922 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 490 "compilador.y" /* yacc.c:1646  */
    {
              char *labelElse = (char*)malloc(sizeof(char)*CMD_MAX);
              nextLabel(labelElse);
              push(labelElse,&labels);

              char dsvf[CMD_MAX];
              sprintf(dsvf,"DSVF %s",labelElse);
              geraCodigo(NULL, dsvf);
            }
#line 1936 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 503 "compilador.y" /* yacc.c:1646  */
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
#line 1955 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 518 "compilador.y" /* yacc.c:1646  */
    {
             char *labelEnd = (char*)pop(&labels);
             if(labelEnd == NULL)
                imprimeErro("Pilha vazia");
             geraCodigo(labelEnd, "NADA");
           }
#line 1966 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 525 "compilador.y" /* yacc.c:1646  */
    {
             char *labelElse = (char*)pop(&labels);
             if(labelElse == NULL)
                imprimeErro("Pilha vazia");
             geraCodigo(labelElse, "NADA");
           }
#line 1977 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 542 "compilador.y" /* yacc.c:1646  */
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
#line 1994 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 557 "compilador.y" /* yacc.c:1646  */
    {
          Symbol* symbol = getSymbol(token);
          char enrt[CMD_MAX];
          int count = countLevelSymbols(VS,lexicalLevel,&symbolTable);
          sprintf(enrt,"ENRT %d,%d",lexicalLevel,count);
          geraCodigo(symbol->label, enrt);
        }
#line 2006 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 569 "compilador.y" /* yacc.c:1646  */
    {
          Symbol* symbol = getSymbol(token);
          char dsvr[CMD_MAX];
          sprintf(dsvr,"DSVR %s,%d,%d",symbol->label,symbol->lexicalLevel,lexicalLevel);
          geraCodigo(NULL, dsvr);
        }
#line 2017 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 586 "compilador.y" /* yacc.c:1646  */
    {subRoutineType = PROC;}
#line 2023 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 591 "compilador.y" /* yacc.c:1646  */
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
#line 2056 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 620 "compilador.y" /* yacc.c:1646  */
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
#line 2078 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 640 "compilador.y" /* yacc.c:1646  */
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
#line 2094 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 669 "compilador.y" /* yacc.c:1646  */
    { isReference = 1; }
#line 2100 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 670 "compilador.y" /* yacc.c:1646  */
    { isReference = 0; }
#line 2106 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 673 "compilador.y" /* yacc.c:1646  */
    {subRoutineType = FUNC;}
#line 2112 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 679 "compilador.y" /* yacc.c:1646  */
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
                else if(strcmp(token,"boolean") == 0)
                  type->primitiveType = BOOL;
                else
                  imprimeErro("Tipo inexistente.");

                if(count > 0){
                  Type** tmp = (Type**)realloc(func->types,sizeof(Type*)*func->typesSize+1);
                  if(tmp == NULL){
                    imprimeErro("Erro na alocação de memória.");
                  }else{
                    func->types = tmp;
                    func->types[func->typesSize] = type;
                    func->typesSize = func->typesSize+1;
                  }
                }else{
                  func->typesSize = 1;
                  func->types = (Type**)malloc(sizeof(Type*));
                  func->types[0] = type;
                }
                func->displacement = -4-count;
              }
            }
#line 2153 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 718 "compilador.y" /* yacc.c:1646  */
    {
                      Symbol* symbol = getSymbol((yyvsp[0].expr).value);
                      if(symbol->category == FUNC){
                        char amem[CMD_MAX];
                        sprintf(amem,"AMEM 1");
                        geraCodigo(NULL, amem);
                      }
                    }
#line 2166 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 727 "compilador.y" /* yacc.c:1646  */
    {
                      Symbol* symbol = getSymbol((yyvsp[-2].expr).value);
                      int returnSize = symbol->category == FUNC;
                      Stack* subRoutineParams = (Stack*)pop(&params);
                      if(subRoutineParams != NULL){
                        if(subRoutineParams->size != symbol->typesSize-returnSize){
                          imprimeErro("N�mero incorreto de argumentos.");
                        }else{
                          for(int i=symbol->typesSize-returnSize-1; i>=0;i--){
                            Expr* expr = (Expr*)reversePop(subRoutineParams);
                            if(expr->primitiveType != symbol->types[i]->primitiveType
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
                      strcpy(func.value,(yyvsp[-2].expr).value);
                      func.primitiveType = returnSize ? symbol->types[symbol->typesSize-1]->primitiveType : VOID;
                      func.exprType=VARIABLE;
                      (yyval.expr)=func;
                    }
#line 2202 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 761 "compilador.y" /* yacc.c:1646  */
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
#line 2221 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 778 "compilador.y" /* yacc.c:1646  */
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
#line 2236 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 795 "compilador.y" /* yacc.c:1646  */
    {
                  Stack* subRoutineParams = (Stack*)malloc(sizeof(Stack));
                  startStack(subRoutineParams);
                  push(subRoutineParams,&params);
                }
#line 2246 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 807 "compilador.y" /* yacc.c:1646  */
    {push(&(yyvsp[0].expr),(Stack*)getByReversedIndex(0,&params));}
#line 2252 "compilador.tab.c" /* yacc.c:1646  */
    break;


#line 2256 "compilador.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 810 "compilador.y" /* yacc.c:1906  */


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
