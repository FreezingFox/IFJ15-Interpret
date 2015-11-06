#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "arg_list.h"
#include "str.h"

/* This holds value of the variables */
union varValue {
    int i;
    double d;
    string s;
};

/* Data belonging to a key */
typedef struct {
    enum dataTypes type;
    union varValue value;        // variable
    struct argumentList *args;   // function
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
} SymbolTable;


void sTableInit(SymbolTable *table);
int sTableInsert(SymbolTable *table,
                 string key, int type,
                 union varValue value,
                 struct argumentList *args);
tData_t *sTableFind(SymbolTable *table, string key);
void sTableFree(SymbolTable *table);

#endif /* SYMBOL_TABLE_H */
