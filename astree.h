#ifndef     ASTREE_HEADER
#define     ASTREE_HEADER

#include "hash.h"

#define MAX_SONS 4

#define AST_PROGRAMA 		100
#define AST_VARIAVEL 		101
#define AST_VETOR_VAZIO 	102
#define AST_VETOR 		103
#define AST_INI_VETOR 		104
#define AST_LISTA_LITERAIS 	105
#define AST_FUNCAO 		106
#define AST_PARAMETRO 		107
#define AST_LISTA_PARAMETRO 	108
#define AST_COMANDOS		144
#define AST_BLOCO		146
#define AST_LISTA_PARAM_CHAMADA 109
#define AST_ACESSO_VETOR 	110
#define AST_CHAMADA_FUNCAO 	111
#define AST_EXPRESSAO_PARENTESES 147
#define AST_OP_SOMA 		112
#define AST_OP_SUB 		113
#define AST_OP_MUL 		114
#define AST_OP_DIV 		115
#define AST_OP_MENOR 		116
#define AST_OP_MAIOR 		117
#define AST_OP_LE 		118
#define AST_OP_GE 		119
#define AST_OP_EQ 		120
#define AST_OP_NE 		121
#define AST_OP_AND 		122
#define AST_OP_OR 		123
#define AST_ATRIBUICAO 		124
#define AST_ATRIBUICAO_VETOR 	125
#define AST_IF 			126
#define AST_IF_ELSE 		127
#define AST_WHILE 		128
#define AST_INPUT 		129
#define AST_LISTA_VARIAVEIS 	130
#define AST_OUTPUT 		131
#define AST_LISTA_ELEM_EXP 	132
#define AST_LISTA_ELEM_STRING 	133
#define AST_RETURN 		134
#define AST_KW_INT 		135
#define AST_KW_BOOL 		136
#define AST_KW_REAL 		137
#define AST_KW_CHAR 		138
#define AST_LIT_INT		145
#define AST_LIT_REAL 		139
#define AST_LIT_TRUE 		140
#define AST_LIT_FALSE 		141
#define AST_LIT_CHAR 		142
#define AST_LIT_STRING 		143
#define AST_IDENTIFIER      148
#define AST_DECLARACOES     149
#define AST_COMANDO_VAZIO 150
#define AST_SYMBOL 283


typedef struct astree_struct {
    int type;
    int nature;
    int dataType;
    struct hash_node_struct* symbol;
    struct astree_struct *son[MAX_SONS];
} ASTREE;

//FILE    *inputFile;
//FILE    *outputFile;

ASTREE* astreeCreate(int type, struct hash_node_struct *symbol, ASTREE *s0, ASTREE *s1, ASTREE *s2, ASTREE *s3);
void    defineDataType(struct hash_node_struct *symbol, int type);
void    astreePrint(ASTREE* node, int level);
void    decompile(ASTREE *root);

#endif
