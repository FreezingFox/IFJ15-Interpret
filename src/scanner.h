#ifndef SCANNER_H
#define SCANNER_H

#include "token.h"

enum states {
	START = 0,
	IDENTIFIER,
	NUM_INT,
	NUM_DOUBLE_FLOAT_P1,
	NUM_DOUBLE_FLOAT_P2,
	NUM_DOUBLE_EXP1,
	NUM_DOUBLE_EXP2,
	STRING
};


token_t getToken(FILE *f);

#endif /* SCANNER_H */
