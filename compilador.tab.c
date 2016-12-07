/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

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
    imprimeErro("Símbolo inexistente.");
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


#line 146 "compilador.tab.c" /* yacc.c:339  */

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

union YYSTYPE
{
#line 86 "compilador.y" /* yacc.c:355  */

  Expr expr;

#line 232 "compilador.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_COMPILADOR_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 249 "compilador.tab.c" /* yacc.c:358  */

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
#define YYLAST   137

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  64
/* YYNRULES -- Number of rules.  */
#define YYNRULES  108
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  166

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
       0,   105,   105,   105,   116,   131,   131,   142,   145,   146,
     149,   151,   151,   155,   174,   175,   178,   199,   200,   203,
     204,   207,   208,   210,   211,   214,   217,   218,   219,   220,
     221,   222,   223,   224,   227,   240,   260,   269,   278,   287,
     296,   305,   314,   325,   337,   349,   361,   364,   376,   388,
     400,   403,   404,   405,   406,   409,   420,   429,   438,   450,
     457,   449,   479,   478,   492,   491,   513,   522,   523,   526,
     527,   530,   546,   545,   554,   557,   566,   567,   570,   571,
     572,   575,   575,   580,   579,   628,   642,   644,   645,   648,
     649,   652,   655,   658,   659,   662,   662,   667,   700,   699,
     743,   760,   773,   774,   778,   777,   786,   787,   790
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

#define YYPACT_NINF -140

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-140)))

#define YYTABLE_NINF -99

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -140,     7,    13,  -140,    -3,    29,    28,  -140,    31,    44,
      51,    37,  -140,    42,    62,    61,  -140,    40,  -140,  -140,
      41,    63,    42,  -140,  -140,  -140,    16,  -140,  -140,  -140,
    -140,  -140,    65,    65,    46,  -140,  -140,    66,  -140,    67,
      68,  -140,    70,    72,  -140,    71,    46,    76,    -4,  -140,
    -140,  -140,    53,  -140,    80,    37,  -140,    73,    77,  -140,
      78,    81,    79,  -140,  -140,    -1,    57,    87,    87,  -140,
    -140,  -140,    84,  -140,  -140,  -140,  -140,  -140,  -140,    68,
      82,    88,  -140,    85,  -140,    70,  -140,  -140,    79,    -1,
      -1,  -140,  -140,  -140,    75,    -2,    14,  -140,    90,  -140,
    -140,  -140,  -140,  -140,  -140,    -1,    87,  -140,  -140,  -140,
    -140,    88,  -140,    55,  -140,  -140,  -140,    83,    96,  -140,
    -140,  -140,  -140,  -140,  -140,  -140,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  -140,  -140,  -140,  -140,    58,  -140,
    -140,  -140,  -140,  -140,    -4,    14,    14,    14,    11,  -140,
    -140,  -140,    11,    64,  -140,  -140,    -4,    86,  -140,    -1,
    -140,  -140,  -140,  -140,    -4,  -140
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     0,    18,     0,     0,
       0,    68,    17,     0,     0,     7,    71,     0,    70,     3,
      80,     0,     0,    67,    81,    95,     0,    77,    78,    79,
      11,    69,     0,     0,    74,     4,    76,     6,     9,     0,
       0,    83,     0,     0,    72,     0,    74,    22,     0,     8,
      10,    16,     0,    15,    88,    68,    82,     0,     0,    20,
       0,    22,    24,    55,    59,     0,     0,     0,     0,    28,
      25,    26,    98,    30,    29,    27,    31,    32,    33,     0,
       0,    94,    84,     0,    97,     0,    73,    19,    23,     0,
       0,    56,    57,    58,     0,    36,    46,    50,    53,    52,
      54,    75,   104,   100,   101,     0,   103,    14,    13,    12,
      93,    94,    90,     0,    11,    85,    96,     0,     0,    62,
      37,    38,    41,    42,    39,    40,     0,     0,     0,     0,
       0,     0,     0,     0,    34,    99,   102,    89,     0,    87,
      91,    92,    60,    51,     0,    43,    45,    44,    35,    47,
      49,    48,   108,     0,   107,    86,     0,    66,   105,     0,
      61,    64,    63,   106,     0,    65
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -140,  -140,  -140,    47,  -140,  -140,  -140,    69,   -11,  -140,
    -140,  -140,    25,  -140,    89,    74,  -140,    91,  -139,  -140,
     -75,  -140,  -125,   -73,   -74,   -48,  -140,  -140,  -140,  -140,
    -140,  -140,  -140,  -140,  -140,  -140,    92,  -140,  -140,  -140,
    -140,    93,  -140,  -140,    94,  -140,    22,  -140,  -140,     0,
       1,  -140,  -140,  -140,  -140,   -47,  -140,  -140,  -140,  -140,
     -66,  -140,  -140,   -49
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    14,    20,    21,    37,    38,    39,    40,
     109,    52,    53,     8,    69,    45,    46,    47,    70,    71,
      94,   129,    95,    96,    97,    98,    99,    73,    89,   156,
      74,   144,   162,   164,    15,    17,    18,    48,    58,    75,
      26,    27,    28,    32,    42,    54,    56,    82,   111,   112,
     113,   114,    29,    33,    85,   100,   106,    77,    78,   135,
     103,   133,   153,   154
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      72,    76,   104,    90,   148,   157,    34,     3,   152,    63,
       5,    64,    63,    65,   117,   118,     4,   160,   120,   121,
     122,   123,   124,   125,    66,   165,    34,    67,    68,    91,
     134,   126,   127,     6,   152,   128,     9,    10,    92,    93,
     136,     7,    24,    25,   126,   127,    22,    23,   128,   130,
     131,    11,   132,   145,   146,   147,   149,   150,   151,    79,
     139,    80,   140,   155,    12,   140,    13,    24,    25,   158,
     159,    19,    16,    -5,    50,    30,    44,    55,    41,   -11,
      57,    51,    59,    62,    81,    86,    84,   101,    88,    87,
     -21,   102,   115,   119,   -98,   108,    72,    76,   105,   142,
     110,   143,    83,   141,   107,   161,    49,   116,    72,    76,
     163,   137,   138,     0,    31,    35,    72,    76,     0,    36,
      60,     0,     0,     0,     0,     0,     0,    43,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    61
};

static const yytype_int16 yycheck[] =
{
      48,    48,    68,     4,   129,   144,    10,     0,   133,    13,
      13,    15,    13,    17,    89,    90,     3,   156,    20,    21,
      22,    23,    24,    25,    28,   164,    10,    31,    32,    30,
     105,    33,    34,     4,   159,    37,     5,     6,    39,    40,
     106,    13,    26,    27,    33,    34,     6,     7,    37,    35,
      36,     7,    38,   126,   127,   128,   130,   131,   132,     6,
       5,     8,     7,     5,    13,     7,    29,    26,    27,     5,
       6,     9,    30,    12,     7,    12,    30,     7,    13,    13,
       8,    13,    11,     7,     4,     8,    13,    30,     7,    11,
      11,     4,     7,    18,     4,    13,   144,   144,    14,    16,
      12,     5,    55,   114,    79,    19,    37,    85,   156,   156,
     159,   111,   111,    -1,    22,    26,   164,   164,    -1,    26,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    46
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
      35,    36,    38,   103,    62,   101,   102,    91,    92,     5,
       7,    50,    16,     5,    73,    65,    65,    65,    64,    66,
      66,    66,    64,   104,   105,     5,    71,    60,     5,     6,
      60,    19,    74,   105,    75,    60
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    42,    44,    43,    45,    47,    46,    46,    48,    48,
      49,    51,    50,    52,    53,    53,    54,    55,    55,    56,
      56,    57,    57,    58,    58,    59,    60,    60,    60,    60,
      60,    60,    60,    60,    61,    62,    62,    63,    63,    63,
      63,    63,    63,    64,    64,    64,    64,    65,    65,    65,
      65,    66,    66,    66,    66,    67,    68,    68,    68,    70,
      71,    69,    73,    72,    75,    74,    74,    76,    76,    77,
      77,    78,    80,    79,    79,    81,    82,    82,    83,    83,
      83,    85,    84,    87,    86,    88,    89,    89,    89,    90,
      90,    91,    92,    93,    93,    95,    94,    96,    98,    97,
      99,   100,   101,   101,   103,   102,   104,   104,   105
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     9,     4,     0,     3,     0,     2,     1,
       2,     0,     4,     1,     3,     1,     1,     3,     1,     4,
       3,     2,     1,     3,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     1,     3,     3,     3,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     0,
       0,     6,     0,     6,     0,     3,     0,     3,     0,     3,
       1,     1,     0,     3,     0,     2,     2,     1,     1,     1,
       0,     0,     4,     0,     3,     3,     4,     3,     0,     2,
       1,     2,     2,     1,     0,     0,     6,     1,     0,     3,
       2,     2,     1,     0,     0,     4,     3,     1,     1
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
#line 105 "compilador.y" /* yacc.c:1646  */
    { 
            geraCodigo(NULL, "INPP"); 
          }
#line 1459 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 111 "compilador.y" /* yacc.c:1646  */
    {
            geraCodigo(NULL, "PARA"); 
          }
#line 1467 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 120 "compilador.y" /* yacc.c:1646  */
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
#line 131 "compilador.y" /* yacc.c:1646  */
    {
                      category = VS;
                      isReference = 0;
                    }
#line 1490 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 136 "compilador.y" /* yacc.c:1646  */
    {
                      int count = countLevelSymbols(VS,lexicalLevel,&symbolTable);
                      char amem[CMD_MAX];
                      sprintf(amem,"AMEM %d", count);
                      geraCodigo(NULL, amem);
                    }
#line 1501 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 151 "compilador.y" /* yacc.c:1646  */
    {typeCount = 0;}
#line 1507 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 156 "compilador.y" /* yacc.c:1646  */
    {
        if((strcmp(token,"integer") != 0) && (strcmp(token,"boolean") != 0)){
          imprimeErro("Tipo de variável não permitido.");
        }else{
          Symbol** vars = lastSymbols(typeCount,&symbolTable);
          if(vars == NULL){
            imprimeErro("Erro na tabela de símbolos.");
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
#line 179 "compilador.y" /* yacc.c:1646  */
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
#line 228 "compilador.y" /* yacc.c:1646  */
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
#line 241 "compilador.y" /* yacc.c:1646  */
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
              cmd.avaliated = 0;
              cmd.value[0] = '\0';
              cmd.primitiveType=BOOL;
              cmd.exprType=COMMAND;
              (yyval.expr)=cmd;
            }
#line 1590 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 261 "compilador.y" /* yacc.c:1646  */
    {
            // printf("\tTIPO DA EXPRESSÃO: %d\n", $1.primitiveType);
            if((yyvsp[0].expr).primitiveType != BOOL) imprimeErro("Erro de sintaxe.");
            generateExprCode((yyvsp[0].expr),0);
            (yyval.expr) = (yyvsp[0].expr);
          }
#line 1601 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 270 "compilador.y" /* yacc.c:1646  */
    {
            Expr cmd;
            cmd.avaliated = 0;
            strcpy(cmd.value,"CMMA");
            cmd.primitiveType=BOOL;
            cmd.exprType=COMMAND;
            (yyval.expr)=cmd;
          }
#line 1614 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 279 "compilador.y" /* yacc.c:1646  */
    {
            Expr cmd;
            cmd.avaliated = 0;
            strcpy(cmd.value,"CMME");
            cmd.primitiveType=BOOL;
            cmd.exprType=COMMAND;
            (yyval.expr)=cmd;
          }
#line 1627 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 288 "compilador.y" /* yacc.c:1646  */
    {
            Expr cmd;
            cmd.avaliated = 0;
            strcpy(cmd.value,"CMAG");
            cmd.primitiveType=BOOL;
            cmd.exprType=COMMAND;
            (yyval.expr)=cmd;
          }
#line 1640 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 297 "compilador.y" /* yacc.c:1646  */
    {
            Expr cmd;
            cmd.avaliated = 0;
            strcpy(cmd.value,"CMEG");
            cmd.primitiveType=BOOL;
            cmd.exprType=COMMAND;
            (yyval.expr)=cmd;
          }
#line 1653 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 306 "compilador.y" /* yacc.c:1646  */
    {
            Expr cmd;
            cmd.avaliated = 0;
            strcpy(cmd.value,"CMIG");
            cmd.primitiveType=BOOL;
            cmd.exprType=BOOLCOMMAND;
            (yyval.expr)=cmd;
          }
#line 1666 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 315 "compilador.y" /* yacc.c:1646  */
    {
            Expr cmd;
            cmd.avaliated = 0;
            strcpy(cmd.value,"CMDG");
            cmd.primitiveType=BOOL;
            cmd.exprType=BOOLCOMMAND;
            (yyval.expr)=cmd;
          }
#line 1679 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 326 "compilador.y" /* yacc.c:1646  */
    { 
          verifyType(INT, (yyvsp[-2].expr).primitiveType, (yyvsp[0].expr).primitiveType);
          generateExprCode((yyvsp[-2].expr),0);
          generateExprCode((yyvsp[0].expr),0);
          Expr cmd;
          cmd.avaliated = 0;
          strcpy(cmd.value,"SOMA");
          cmd.primitiveType=INT;
          cmd.exprType=COMMAND;
          (yyval.expr)=cmd;
        }
#line 1695 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 338 "compilador.y" /* yacc.c:1646  */
    { 
          verifyType(BOOL, (yyvsp[-2].expr).primitiveType, (yyvsp[0].expr).primitiveType);
          generateExprCode((yyvsp[-2].expr),0);
          generateExprCode((yyvsp[0].expr),0);
          Expr cmd;
          cmd.avaliated = 0;
          strcpy(cmd.value,"DISJ");
          cmd.primitiveType=BOOL;
          cmd.exprType=COMMAND;
          (yyval.expr)=cmd;
        }
#line 1711 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 350 "compilador.y" /* yacc.c:1646  */
    {
          verifyType(INT, (yyvsp[-2].expr).primitiveType, (yyvsp[0].expr).primitiveType);
          generateExprCode((yyvsp[-2].expr),0);
          generateExprCode((yyvsp[0].expr),0);
          Expr cmd;
          cmd.avaliated = 0;
          strcpy(cmd.value,"SUBT");
          cmd.primitiveType=INT;
          cmd.exprType=COMMAND;
          (yyval.expr)=cmd;
        }
#line 1727 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 361 "compilador.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 1733 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 365 "compilador.y" /* yacc.c:1646  */
    {
          verifyType(INT, (yyvsp[-2].expr).primitiveType, (yyvsp[0].expr).primitiveType);
          generateExprCode((yyvsp[-2].expr),0);
          generateExprCode((yyvsp[0].expr),0);
          Expr cmd;
          cmd.avaliated = 0;
          strcpy(cmd.value,"MULT");
          cmd.primitiveType=INT;
          cmd.exprType=COMMAND;
          (yyval.expr)=cmd;
        }
#line 1749 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 377 "compilador.y" /* yacc.c:1646  */
    {
          verifyType(BOOL, (yyvsp[-2].expr).primitiveType, (yyvsp[0].expr).primitiveType);
          generateExprCode((yyvsp[-2].expr),0);
          generateExprCode((yyvsp[0].expr),0);
          Expr cmd;
          cmd.avaliated = 0;
          strcpy(cmd.value,"CONJ");
          cmd.primitiveType=BOOL;
          cmd.exprType=COMMAND;
          (yyval.expr)=cmd;
        }
#line 1765 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 389 "compilador.y" /* yacc.c:1646  */
    {
          verifyType(INT, (yyvsp[-2].expr).primitiveType, (yyvsp[0].expr).primitiveType);
          generateExprCode((yyvsp[-2].expr),0);
          generateExprCode((yyvsp[0].expr),0);
          Expr cmd;
          cmd.avaliated = 0;
          strcpy(cmd.value,"DIVI");
          cmd.primitiveType=INT;
          cmd.exprType=COMMAND;
          (yyval.expr)=cmd;
        }
#line 1781 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 400 "compilador.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 1787 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 403 "compilador.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[-1].expr);}
#line 1793 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 404 "compilador.y" /* yacc.c:1646  */
    {(yyval.expr)=(yyvsp[0].expr);}
#line 1799 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 405 "compilador.y" /* yacc.c:1646  */
    {(yyval.expr)=(yyvsp[0].expr);}
#line 1805 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 406 "compilador.y" /* yacc.c:1646  */
    {(yyval.expr)=(yyvsp[0].expr);}
#line 1811 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 410 "compilador.y" /* yacc.c:1646  */
    {
            Expr var;
            var.avaliated = 0;
            strcpy(var.value,token);
            var.primitiveType=getSymbol(token)->types[0]->primitiveType;
            var.exprType=VARIABLE;
            (yyval.expr)=var;
          }
#line 1824 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 421 "compilador.y" /* yacc.c:1646  */
    {
              Expr cte;
              cte.avaliated = 0;
              strcpy(cte.value,token);
              cte.primitiveType=INT;
              cte.exprType=CONSTANT;
              (yyval.expr)=cte;
            }
#line 1837 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 430 "compilador.y" /* yacc.c:1646  */
    {
              Expr cte;
              cte.avaliated = 0;
              strcpy(cte.value,"1");
              cte.primitiveType=BOOL;
              cte.exprType=CONSTANT;
              (yyval.expr)=cte;
            }
#line 1850 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 439 "compilador.y" /* yacc.c:1646  */
    {
              Expr cte;
              cte.avaliated = 0;
              strcpy(cte.value,"0");
              cte.primitiveType=BOOL;
              cte.exprType=CONSTANT;
              (yyval.expr)=cte;
            }
#line 1863 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 450 "compilador.y" /* yacc.c:1646  */
    { 
              char *labelStart = (char*)malloc(sizeof(char)*CMD_MAX);
              nextLabel(labelStart);
              push(labelStart,&labels);
              geraCodigo(labelStart, "NADA");
            }
#line 1874 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 457 "compilador.y" /* yacc.c:1646  */
    {
              char *labelEnd = (char*)malloc(sizeof(char)*CMD_MAX);
              nextLabel(labelEnd);
              push(labelEnd,&labels);
              char dsvf[CMD_MAX];
              sprintf(dsvf,"DSVF %s",labelEnd);
              geraCodigo(NULL, dsvf);
            }
#line 1887 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 466 "compilador.y" /* yacc.c:1646  */
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
#line 1902 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 479 "compilador.y" /* yacc.c:1646  */
    { 
              char *labelElse = (char*)malloc(sizeof(char)*CMD_MAX);
              nextLabel(labelElse);
              push(labelElse,&labels);

              char dsvf[CMD_MAX];
              sprintf(dsvf,"DSVF %s",labelElse);
              geraCodigo(NULL, dsvf);
            }
#line 1916 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 492 "compilador.y" /* yacc.c:1646  */
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
#line 1935 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 507 "compilador.y" /* yacc.c:1646  */
    {
             char *labelEnd = (char*)pop(&labels);
             if(labelEnd == NULL) 
                imprimeErro("Pilha vazia");
             geraCodigo(labelEnd, "NADA");
           }
#line 1946 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 514 "compilador.y" /* yacc.c:1646  */
    {
             char *labelElse = (char*)pop(&labels);
             if(labelElse == NULL) 
                imprimeErro("Pilha vazia");
             geraCodigo(labelElse, "NADA");
           }
#line 1957 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 531 "compilador.y" /* yacc.c:1646  */
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
#line 1974 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 546 "compilador.y" /* yacc.c:1646  */
    {
          Symbol* symbol = getSymbol(token);
          char enrt[CMD_MAX];
          int count = countLevelSymbols(VS,lexicalLevel,&symbolTable);
          sprintf(enrt,"ENRT %d,%d",lexicalLevel,count);
          geraCodigo(symbol->label, enrt);
        }
#line 1986 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 558 "compilador.y" /* yacc.c:1646  */
    {
          Symbol* symbol = getSymbol(token);
          char dsvr[CMD_MAX];
          sprintf(dsvr,"DSVR %s,%d,%d",symbol->label,symbol->lexicalLevel,lexicalLevel);
          geraCodigo(NULL, dsvr);
        }
#line 1997 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 575 "compilador.y" /* yacc.c:1646  */
    {subRoutineType = PROC;}
#line 2003 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 580 "compilador.y" /* yacc.c:1646  */
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
#line 2036 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 609 "compilador.y" /* yacc.c:1646  */
    {
                     int count = countLevelSymbols(PF,lexicalLevel,&symbolTable);
                     if(count > 0){
                       Symbol** vars = lastSymbols(count+1,&symbolTable);
                       if(vars == NULL){
                         imprimeErro("Erro na tabela de símbolos.");
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
#line 2058 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 629 "compilador.y" /* yacc.c:1646  */
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
#line 2074 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 658 "compilador.y" /* yacc.c:1646  */
    { isReference = 1; }
#line 2080 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 659 "compilador.y" /* yacc.c:1646  */
    { isReference = 0; }
#line 2086 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 662 "compilador.y" /* yacc.c:1646  */
    {subRoutineType = FUNC;}
#line 2092 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 668 "compilador.y" /* yacc.c:1646  */
    {
              if((strcmp(token,"integer") != 0) && (strcmp(token,"boolean") != 0)){
                imprimeErro("Tipo de função não permitido.");
              }else{
                int count = countLevelSymbols(PF,lexicalLevel,&symbolTable);
                Symbol* func = (Symbol*)getByReversedIndex(count,&symbolTable);
                if(func == NULL){
                  imprimeErro("Erro na tabela de símbolos.");
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
#line 2126 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 700 "compilador.y" /* yacc.c:1646  */
    {
                      Symbol* symbol = getSymbol((yyvsp[0].expr).value);
                      if(symbol->category == FUNC){
                        char amem[CMD_MAX];
                        sprintf(amem,"AMEM 1");
                        geraCodigo(NULL, amem);
                      }
                    }
#line 2139 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 709 "compilador.y" /* yacc.c:1646  */
    {
                      Symbol* symbol = getSymbol((yyvsp[-2].expr).value);
                      int returnSize = symbol->category == FUNC;
                      Stack* subRoutineParams = (Stack*)pop(&params);
                      if(subRoutineParams != NULL){
                        if(subRoutineParams->size != symbol->typesSize-returnSize){
                          imprimeErro("Número incorreto de argumentos.");
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
                        imprimeErro("Número incorreto de argumentos.");
                      }
                      char chpr[CMD_MAX];
                      sprintf(chpr,"CHPR %s,%d",symbol->label,lexicalLevel);
                      geraCodigo(NULL, chpr);
                      Expr func;
                      func.avaliated = 0;
                      strcpy(func.value,(yyvsp[-2].expr).value);
                      func.primitiveType= returnSize ? INT : VOID;
                      func.exprType=VARIABLE;
                      (yyval.expr)=func;
                    }
#line 2176 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 744 "compilador.y" /* yacc.c:1646  */
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
#line 2195 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 761 "compilador.y" /* yacc.c:1646  */
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
#line 2210 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 778 "compilador.y" /* yacc.c:1646  */
    {
                  Stack* subRoutineParams = (Stack*)malloc(sizeof(Stack));
                  startStack(subRoutineParams);
                  push(subRoutineParams,&params);
                }
#line 2220 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 790 "compilador.y" /* yacc.c:1646  */
    {push(&(yyvsp[0].expr),(Stack*)getByReversedIndex(0,&params));}
#line 2226 "compilador.tab.c" /* yacc.c:1646  */
    break;


#line 2230 "compilador.tab.c" /* yacc.c:1646  */
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
#line 793 "compilador.y" /* yacc.c:1906  */


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
  startStack(&params);

   yyin=fp;
   yyparse();

   return 0;
}

