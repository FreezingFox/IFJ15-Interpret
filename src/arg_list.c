#include <stdlib.h>
#include "str.h"
#include "errors.h"
#include "arg_list.h"

/** Initialize an argument list */
void aListInit(funcArgList_t *list)
{
    list->first = NULL;
}

/**
 * Add a new entry to an argument list.
 * Sets errlfg to and returns E_INTERNAL on insufficient memory,
 * E_SUCCESS on success.
 */
int aListAdd(funcArgList_t *list, int type, string name)
{
    struct argument *newItem = malloc(sizeof(struct argument));
    if (newItem == NULL) {
        setErrFlg(E_INTERNAL);
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
        return rc;
    }
    newItem->type = type;

    newItem->next = list->first;
    list->first = newItem;

    return E_SUCCESS;
}

/** Free an argument list */
void aListFree(funcArgList_t *list)
{
    struct argument *currItem = list->first;
    struct argument *next;
    while(currItem != NULL) {
        next = currItem->next;
        free(currItem);
        currItem = next;
    }
}
