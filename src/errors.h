#ifndef ERRORS_H
#define ERRORS_H

#include <stdio.h>
/* Just some error codes */
enum errCodes {
    E_SUCCESS = 0,
    E_SCANNER,
    E_SYNTAX,
    E_SEMANTICS,
    E_TYPE_MISMATCH,
    E_AUTO,
    E_O_SEMANTICS,
    E_READ,
    E_UNITIALIZED,
    E_ZERO_DIV,
    E_OTHERS,
    E_INTERNAL = 99
};

extern int errflg;

inline void printErrFlg() { printf("%d\n", errflg); }
inline int getErrFlg() { return errflg; }
inline void setErrFlg(const int val) { errflg = val; }

#endif /* ERRORS_H */
