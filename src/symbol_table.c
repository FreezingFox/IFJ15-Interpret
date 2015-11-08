#include <stdlib.h>
#include "symbol_table.h"
#include "arg_list.h"
#include "str.h"
#include "errors.h"

/** Initialize the table */
void sTableInit(symbolTable_t *table)
{
    table->first = NULL;
}

/**
 * Insert a new entry to the table.
 * @return Returns E_SEMANTICS if the key is already defined,
 * @return E_INTERNAL when we can't create a new node due to
 * @return infufficient memory, E_SUCCESS on success.
 */
int sTableInsert(symbolTable_t *table,
                 string key, int type,
                 varVal_t value,
                 funcArgList_t *args)
{
    /* Is the key already defined? */
    if (sTableFind(table, key) != NULL)
        return E_SEMANTICS;

    /* Create the new node */
    struct tableNode *newNode = malloc(sizeof(struct tableNode));
    if (newNode == NULL)
        return E_INTERNAL;
    int rc = strInit(&(newNode->key));
    if (rc) {
        free(newNode);
        return rc;
    }
    rc = strCopy(&key, &(newNode->key));
    if (rc) {
        strFree(&(newNode->key));
        free(newNode);
        return rc;
    }
    newNode->data.type = type;
    newNode->data.value = value;
    newNode->data.args = args;
    newNode->left = NULL;
    newNode->right = NULL;

    /* Place the node in the binary tree */
    if (table->first == NULL) {
        table->first = newNode;
        return E_SUCCESS;
    }
    struct tableNode *currentNode = table->first;
    int cmp;
    while (currentNode != NULL) {
        cmp = strCompare(currentNode->key, newNode->key);
        if (cmp < 0) {
            if (currentNode->left == NULL)
                currentNode->left = newNode;
            currentNode = currentNode->left;
        } else if (cmp > 0) {
            if (currentNode->right == NULL)
                currentNode->right = newNode;
            currentNode = currentNode->right;
        } else
            // something went really wrong since i already sTableFind()-ed
            return E_SEMANTICS;
    }
    return E_SUCCESS;
}

/**
 * Tries to find the key in the table.
 * When found, return the data structure, otherwise NULL.
 */
tData_t *sTableFind(symbolTable_t *table, string key)
{

    if (table->first == NULL)
        return NULL;

    struct tableNode *currentNode = table->first;
    int cmp;
    while (1) {
        cmp = strCompare(currentNode->key, key);
        if (cmp < 0)
            currentNode = currentNode->left;
        else if (cmp > 0)
            currentNode = currentNode->right;
        else /* cmp == 0, aka found it */
            return &(currentNode->data);

        /* Fell trough, didnt find it anywhere */
        if (currentNode == NULL)
            return NULL;
    }
}

/** Function to help recursively free the tree */
static void freeNode(struct tableNode *node)
{
    if (node == NULL)
        return;
    freeNode(node->left);
    freeNode(node->right);
    strFree(&(node->key));
    if (node->data.args != NULL)
        aListFree(&(node->data.args));
    free(node);
}

/** Free the tree! */
void sTableFree(symbolTable_t *table)
{
    if (table == NULL)
        return;
    freeNode(table->first);
}
