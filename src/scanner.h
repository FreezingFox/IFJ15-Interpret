#ifndef __SCANNER_H_
#define __SCANNER_H_

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

#endif /* __SCANNER_H_ */
