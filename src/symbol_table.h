#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "arg_list.h"
#include "str.h"
#include "token.h"

#define NOVAL       ((varVal_t){ .i = 0 })

/* Data belonging to a key */
typedef struct {
    dataType_t type;
    varVal_t value;        // variable
    funcArgList_t *args;   // function
} tData_t;

/* Node of the tree */
struct tableNode {
    string key;
    tData_t data;
    struct tableNode *left;
    struct tableNode *right;
};

/* The symbol table */
typedef struct {
    struct tableNode *first;
} symbolTable_t;


void sTableInit(symbolTable_t *table);
int sTableInsert(symbolTable_t *table,
                 string key, int type,
                 varVal_t value,
                 funcArgList_t *args);
tData_t *sTableFind(symbolTable_t *table, string key);
void sTableFree(symbolTable_t *table);

#endif /* SYMBOL_TABLE_H */
