#include <stdlib.h>
#include "str.h"
#include "errors.h"
#include "arg_list.h"

/** Initialize an argument list */
void aListInit(struct argumentList *list)
{
    list->first = NULL;
}

/**
 * Add a new entry to an argument list.
 * Sets errlfg to and returns E_INTERNAL on insufficient memory,
 * E_SUCCESS on success.
 */
int aListAdd(struct argumentList *list, int type, string name)
{
    struct argument *newItem = malloc(sizeof(struct argument));
    if (newItem == NULL) {
        errflg = E_INTERNAL;
        return E_INTERNAL;
    }

    int rc = strInit(&(newItem->name));
    if (rc) {
        free(newItem);
        return rc;
    }
    rc = strCopy(&name, &(newItem->name));
    if (rc) {
        strFree(&(newItem->name));
        free(newItem);
        errflg = rc;
        return rc;
    }
    newItem->type = type;

    newItem->next = list->first;
    list->first = newItem;

    errflg = E_SUCCESS;
    return E_SUCCESS;
}

/** Free an argument list */
void aListFree(struct argumentList *list)
{
    struct argument *currItem = list->first;
    struct argument *next;
    while(currItem != NULL) {
        next = currItem->next;
        free(currItem);
        currItem = next;
    }
}
