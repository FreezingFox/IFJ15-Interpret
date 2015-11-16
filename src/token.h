#ifndef TOKEN_H
#define TOKEN_H

#include "str.h"

/* This holds value of the variables */
typedef union {
    int i;
    double d;
    string s;
} varVal_t;

/**
 * Enumeration of all possible tokens.
 */
typedef enum {
	KW_AUTO,	             /**< 	auto 					*/
	KW_CIN,					 /**< 	cin 					*/
	KW_COUT,				 /**< 	cout 					*/
	KW_DOUBLE,				 /**< 	double 					*/
	KW_ELSE,				 /**< 	else 					*/
	KW_FOR,					 /**< 	for 					*/
	KW_IF,					 /**< 	if 						*/
	KW_INT,					 /**< 	int 					*/
	KW_RETURN,				 /**< 	return 					*/
	KW_STRING,				 /**< 	string 					*/
	TOK_IDENTIFIER,			 /**< 	varnames, funcnames		*/
	TOK_INT,				 /**< 	42 						*/
	TOK_STRING,				 /**< 	"kittens" 				*/
	TOK_DOUBLE,				 /**< 	0.15e-8 				*/
	TOK_LEFT_PARENTHESIS,	 /**< 	(	 					*/
	TOK_RIGHT_PARENTHESIS,	 /**<	) 						*/
	TOK_LEFT_BRACKET,		 /**<	[ 						*/
	TOK_LEFT_BRACE,			 /**< 	{ 						*/
	TOK_RIGHT_BRACKET,		 /**< 	] 						*/
	TOK_RIGHT_BRACE,		 /**< 	} 						*/
	TOK_GREATER_THAN,		 /**< 	>	 					*/
	TOK_LESSER_THAN,		 /**< 	< 						*/
	TOK_LESSEREQUAL,		 /**< 	<= 						*/
	TOK_GREATEREQUAL,		 /**< 	>= 						*/
	TOK_ASSIGN,				 /**< 	= 						*/
	TOK_EQUAL,				 /**< 	== 						*/
	TOK_NONEQUAL,			 /**< 	!= 						*/
	TOK_PLUS,				 /**< 	+ 						*/
	TOK_MINUS,				 /**<	-- 						*/
	TOK_DIV,				 /**< 	/ 						*/
	TOK_SEMICOLON,			 /**< 	; 						*/
	TOK_MUL,				 /**< 	* 						*/
	TOK_GRGR,				 /**< 	>> 						*/
	TOK_LWLW,				 /**< 	<< 						*/
	TOK_COMMENT,			 /**<   a comment				*/
	TOK_BROKEN_TOKEN		 /**<   uninitialized token     */
} tokenType_t;


/**
 * Tokens are stored in this struct.
 */
typedef struct {
	tokenType_t type;	/**< Type of the token 				*/
	varVal_t value;		/**< Data if applicable				*/
} token_t;

#endif /* TOKEN_H */
