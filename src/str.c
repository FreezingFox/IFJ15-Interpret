#include <stdlib.h>
#include <string.h>
#include "str.h"
#include "errors.h"

/* Initializes the string.
 * Returns E_INTERNAL in case we fail to malloc() memory for the string,
 * and E_SUCCESS on success.
 */
int strInit(string *s)
{
    /* Allocate starting memory */
    s->str = malloc(STR_INC);
    if (s->str == NULL) {
        setErrFlg(E_INTERNAL);
        return E_INTERNAL;
    }

    /* Initialize the base values */
    s->str[0] = '\0';
    s->len = 0;
    s->mem = STR_INC;

    setErrFlg(E_SUCCESS);
    return E_SUCCESS;
}

/* Free the memory */
void strFree(string *s)
{
    free(s->str);
}

/* Copy string from to string to.
 * Returns E_INTERNAL if infufficient memory (unable to realloc()),
 * E_SUCCESS otherwise.
 */
int strCopy(string *from, string *to)
{
    /* Check if there is enough space in *to to occupy the value of *from */
    if (from->len >= to->mem) {
        /* Call realloc() on insufficient memory in *to */
        char *newStr = realloc(to->str, from->len+1);
        if (newStr == NULL) {
            return E_INTERNAL;
            setErrFlg(E_INTERNAL);
        }
        to->str = newStr;
        to->mem = from->len+1;
    }
    to->len = from->len;
    /* Actually copy it */
    strcpy(to->str, from->str);

    setErrFlg(E_SUCCESS);
    return E_SUCCESS;
}

/* Copmares s1 and s2. Works the same as strcmp().
 * Thats maybe because it actually is strcmp().
 */
int strCompare(string s1, string s2)
{
    return strcmp(s1.str, s2.str);
}

int strAppend(string *to, char c)
{
    if (to->len+1 >= to->mem) {
        char *newStr = realloc(to->str, to->mem + STR_INC);
        if (newStr == NULL) {
            setErrFlg(E_INTERNAL);
            return E_INTERNAL;
        }
        to->mem += STR_INC;
        to->str = newStr;
    }
    to->str[to->len] = c;
    to->str[++(to->len)] = '\0';

    setErrFlg(E_SUCCESS);
    return E_SUCCESS;
}

int strCopyC(char *from, string *to)
{
    to->len = 0;
    for (int i = 0; from[i] != '\0'; i++)
        if (strAppend(to, from[i]) != E_SUCCESS)
            return E_INTERNAL;

    return E_SUCCESS;
}

char *strGetStr(string *from)
{
    return from->str;
}
