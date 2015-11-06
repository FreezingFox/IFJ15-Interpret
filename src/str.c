#include <stdlib.h>
#include <string.h>
#include "str.h"
#include "errors.h"

/**
 * @brief Initialize string s.
 * @param s address of string to be initialised
 * @return Returns E_INTERNAL in case we fail to malloc() memory for the string,
 * @return and E_SUCCESS on success.
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

/**
 * @brief Frees memory occupied by string s.
 * @param s address of string to be freed
 */
void strFree(string *s)
{
    free(s->str);
}

/**
 * @brief Copy string from to string to.
 * @param from string to copy from
 * @param to string to copy to
 * @return Returns E_INTERNAL on memory allocation error,
 * @return E_SUCCESS otherwise.
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

/**
 * @brief Compare the strings s1 and s2.
 * @brief strcmp() wrapper
 * @param s1 string to compare
 * @param s2 string to compare
 * @return Returns int value less than, equal to or greater than zero
 * @return if s1 is fount to be, respectively, less than, match, greater than
 * @return s2.
 */
int strCompare(string s1, string s2)
{
    return strcmp(s1.str, s2.str);
}

/**
 * @brief Append character c to end of string to.
 * @param to string to which the character will be appended
 * @param c char to append
 * @return Returns E_INTERNAL on memory allocation failure
 * @return and E_SUCCESS otherwise.
 */
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

/**
 * @brief Transform a C string to a string.
 * @param from C string to be transformed
 * @param to string where the final data will be stored
 * @return Returns E_INTERNAL on memory allocation failure,
 * @return E_SUCCESS otherwise.
 */
int strCopyC(char *from, string *to)
{
    to->len = 0;
    for (int i = 0; from[i] != '\0'; i++)
        if (strAppend(to, from[i]) != E_SUCCESS)
            return E_INTERNAL;

    return E_SUCCESS;
}

/**
 * @brief Get a C string from string from.
 * @param from string to make C string from
 * @return Returns C string equivalent to string from.
 */
char *strGetStr(string *from)
{
    return from->str;
}
