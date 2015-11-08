#ifndef ARG_LIST_H
#define ARG_LIST_H

#include "str.h"

/* Possible data types */
typedef enum {
    T_INT,
    T_DOUBLE,
    T_STRING
} dataType_t;

/* Item of the list to hold arguments of functions */
struct argument {
    dataType_t type;
    string name;
    struct argument *next;
};

/* List of the arguments to functions */
typedef struct {
    struct argument *first;
} funcArgList_t;


void aListInit(funcArgList_t *list);
int aListAdd(funcArgList_t *list, int type, string name);
void aListFree(funcArgList_t *list);

#endif /* ARG_LIST_H */
