#ifndef ARG_LIST_H
#define ARG_LIST_H

#include "str.h"

/* Possible data types */
enum dataTypes {
    T_INT,
    T_DOUBLE,
    T_STRING
};

/* Item of the list to hold arguments of functions */
struct argument {
    enum dataTypes type;
    string name;
    struct argument *next;
};

/* List of the arguments to functions */
struct argumentList {
    struct argument *first;
};

#endif /* ARG_LIST_H */
