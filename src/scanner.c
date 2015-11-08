#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"
#include "token.h"
#include "str.h"
#include "errors.h"

static bool isDelim(char c);

/* Returns next token from file f.
 * On error, sets errflg.
 * On EOF, sets errflg to EOF.
 */
token_t getToken(FILE *f)
{
	enum states state = START;
	token_t token;
	token.type = TOK_BROKEN_TOKEN;
	token.value.i = 0;

	string buff;
	if (strInit(&buff) != E_SUCCESS)
		return token;

	int c;
	char hexS[3];
	long hex;
	bool done = false;
	while(!done) {
		c = fgetc(f);
		switch(state) {
			case START:
				if (isspace(c))
					;
				else if (isdigit(c)) {
					if (strAppend(&buff, c) != E_SUCCESS) {
						strFree(&buff);
						return token;
					}
					state = NUM_INT;
				} else if (c == '"') {
					state = STRING;
				} else if (isalpha(c) || c == '_') {
					if (strAppend(&buff, c) != E_SUCCESS) {
						strFree(&buff);
						return token;
					}
					state = IDENTIFIER;
				} else if (c == EOF) { // TODO: other things before this
					setErrFlg(EOF);
					strFree(&buff);
					return token;
				} else {
					switch (c) {
						case '(':
							token.type = TOK_LEFT_PARENTHESIS;
							break;
						case ')':
							token.type = TOK_RIGHT_PARENTHESIS;
							break;
						case '[':
							token.type = TOK_LEFT_BRACKET;
							break;
						case ']':
							token.type = TOK_RIGHT_BRACKET;
							break;
						case '{':
							token.type = TOK_LEFT_BRACE;
							break;
						case '}':
							token.type = TOK_RIGHT_BRACE;
							break;
						case '>':
							c = fgetc(f);
							if (c == EOF) {
								setErrFlg(E_SCANNER);
							} else if (c == '>') {
								token.type = TOK_GRGR;
							} else if (c == '=') {
								token.type = TOK_GREATEREQUAL;
							} else {
								if (ungetc(c, f) == EOF) {
									setErrFlg(E_INTERNAL);
								}
								token.type = TOK_GREATER_THAN;
							}
							break;
						case '<':
							c = fgetc(f);
							if (c == EOF) {
								setErrFlg(E_SCANNER);
							} else if (c == '<') {
								token.type = TOK_LWLW;
							} else if (c == '=') {
								token.type = TOK_LESSEREQUAL;
							} else {
								if (ungetc(c, f) == EOF) {
									setErrFlg(E_INTERNAL);
								}
								token.type = TOK_LESSER_THAN;
							}
							break;
						case '=':
							c = fgetc(f);
							if (c == EOF) {
								setErrFlg(E_SCANNER);
							} else if (c == '=') {
								token.type = TOK_EQUAL;
							} else {
								if (ungetc(c, f) == EOF) {
									setErrFlg(E_INTERNAL);
									printf("this failed\n");
								}
								token.type = TOK_ASSIGN;
							}
							break;
						case '+':
							token.type = TOK_PLUS;
							break;
						case '-':
							token.type = TOK_MINUS;
							break;
						case '*':
							token.type = TOK_MUL;
							break;
						case '/':
							c = fgetc(f);
							if (c == '/') {
								while ((c = fgetc(f)) != '\n')
									if (c == EOF) {
										setErrFlg(E_SCANNER);
										strFree(&buff);
										return token;
									}
								token.type = TOK_COMMENT;
							} else if (c == '*') {
								while (1) {
									c = fgetc(f);
									if (c == '*') {
										c = fgetc(f);
										if (c == '/') {
											token.type = TOK_COMMENT;
											break;
										} else if (c == EOF) {
											setErrFlg(E_SCANNER);
											strFree(&buff);
											return token;
										} else {
											if (ungetc(c, f) == EOF
												|| ungetc('*', f) == EOF)
											{
												setErrFlg(E_INTERNAL);
												strFree(&buff);
												return token;
											}
										}
									} else if (c == EOF) {
										setErrFlg(E_SCANNER);
										strFree(&buff);
										return token;
									}
								}
							} else {
								if (ungetc(c, f) == EOF) {
									setErrFlg(E_INTERNAL);
									strFree(&buff);
									return token;
								}
								token.type = TOK_DIV;
							}
							break;
						case '!':
							c = fgetc(f);
							if (c == EOF) {
								setErrFlg(E_SCANNER);
							} else if (c == '=') {
								token.type = TOK_NONEQUAL;
							} else {
								setErrFlg(E_SCANNER);
							}
							break;
						case ';':
							token.type = TOK_SEMICOLON;
							break;
						default:
							setErrFlg(E_SCANNER);
					}
					strFree(&buff);
					return token;
				}
				break;

			case NUM_INT:
				if (isdigit(c)) {
					if (strAppend(&buff, c) != E_SUCCESS) {
						strFree(&buff);
						return token;
					}
				} else if (c == '.') {
					if (strAppend(&buff, c) != E_SUCCESS) {
						strFree(&buff);
						return token;
					}
					state = NUM_DOUBLE_FLOAT_P1;
				} else if (tolower(c) == 'e') {
					if (strAppend(&buff, c) != E_SUCCESS) {
						strFree(&buff);
						return token;
					}
					state = NUM_DOUBLE_EXP1;
				} else if (isDelim(c)) {
					if (ungetc(c, f) == EOF) {
						setErrFlg(E_INTERNAL);
						strFree(&buff);
						return token;
					}
					token.type = TOK_INT;
					done = true;
				} else {
					setErrFlg(E_SCANNER);
					strFree(&buff);
					return token;
				}
				break;

			case NUM_DOUBLE_FLOAT_P1:
				if (isdigit(c)) {
					if (strAppend(&buff, c) != E_SUCCESS) {
						strFree(&buff);
						return token;
					}
					state = NUM_DOUBLE_FLOAT_P2;
				} else {
					setErrFlg(E_SCANNER);
					strFree(&buff);
					return token;
				}
				break;

			case NUM_DOUBLE_FLOAT_P2:
				if (isdigit(c)) {
					if (strAppend(&buff, c) != E_SUCCESS) {
						strFree(&buff);
						return token;
					}
					state = NUM_DOUBLE_FLOAT_P2;
				} else if (tolower(c) == 'e') {
					if (strAppend(&buff, c) != E_SUCCESS) {
						strFree(&buff);
						return token;
					}
					state = NUM_DOUBLE_EXP1;
				} else if (isDelim(c)) {
					if (ungetc(c, f) == EOF) {
						setErrFlg(E_INTERNAL);
						strFree(&buff);
						return token;
					}
					token.type = TOK_DOUBLE;
					done = true;
				} else {
					setErrFlg(E_SCANNER);
					strFree(&buff);
					return token;
				}
				break;

			case NUM_DOUBLE_EXP1:
				if (c == '+' || c == '-') {
					if (strAppend(&buff, c) != E_SUCCESS) {
						strFree(&buff);
						return token;
					}
				} else if (isdigit(c)) {
					if (strAppend(&buff, c) != E_SUCCESS) {
						strFree(&buff);
						return token;
					}
					state = NUM_DOUBLE_EXP2;
				} else {
					setErrFlg(E_SCANNER);
					strFree(&buff);
					return token;
				}
				break;

			case NUM_DOUBLE_EXP2:
				if (isdigit(c)) {
					if (strAppend(&buff, c) != E_SUCCESS) {
						strFree(&buff);
						return token;
					}
				} else if (isDelim(c)) {
					if (ungetc(c, f) == EOF) {
						setErrFlg(E_INTERNAL);
						strFree(&buff);
						return token;
					}
					token.type = TOK_DOUBLE;
					done = true;
				} else {
					setErrFlg(E_SCANNER);
					strFree(&buff);
					return token;
				}
				break;

			case STRING:
				switch(c) {
					case '\\':
						c = fgetc(f);
						switch(c) {
							case '"':
								if (strAppend(&buff, '"') != E_SUCCESS) {
									strFree(&buff);
									return token;
								}
								break;
							case 'n':
								if (strAppend(&buff, '\n') != E_SUCCESS) {
									strFree(&buff);
									return token;
								}
								break;
							case 't':
								if (strAppend(&buff, '\t') != E_SUCCESS) {
									strFree(&buff);
									return token;
								}
								break;
							case '\\':
								if (strAppend(&buff, '\\') != E_SUCCESS) {
									strFree(&buff);
									return token;
								}
								break;
							case 'x':
								for (int j, i = 0; i < 2; j = fgetc(f), i++)
									if (j == EOF || !isxdigit(j)) {
										setErrFlg(E_SCANNER);
										strFree(&buff);
										return token;
									} else {
										hexS[i] = j;
									}
								hexS[2] = '\0';
								hex = strtol(hexS, NULL, 16);
								if (strAppend(&buff, (char)hex) != E_SUCCESS) {
									strFree(&buff);
									return token;
								}
								break;
							default:
								if (strAppend(&buff, c) != E_SUCCESS) {
									strFree(&buff);
									return token;
								}
								break;
						}
						break;

					case '\n':
						setErrFlg(E_SCANNER);
						strFree(&buff);
						return token;
						break;

					case '"':
						token.type = TOK_STRING;
						done = true;
						break;

					default:
						if (strAppend(&buff, c) != E_SUCCESS) {
							strFree(&buff);
							return token;
						}
						break;
				}
				break;

			case IDENTIFIER:
				if (isalnum(c) || c == '_') {
					if (strAppend(&buff, c) != E_SUCCESS) {
						strFree(&buff);
						return token;
					}
				} else if (isDelim(c)) {
					if (ungetc(c, f) == EOF) {
						setErrFlg(E_INTERNAL);
						strFree(&buff);
						return token;
					}
					token.type = TOK_IDENTIFIER;
					done = true;
				} else {
					setErrFlg(E_SCANNER);
					strFree(&buff);
					return token;
				}
		}
	}

	char *cBuff = strGetCStr(&buff);
	switch(token.type) {
		case TOK_INT:
			token.value.i = atoi(cBuff);
			break;
		case TOK_DOUBLE:
			token.value.d = strtod(cBuff, NULL);
			break;
		case TOK_STRING:
			if (strInit(&(token.value.s)) != E_SUCCESS) {
				strFree(&buff);
				return token;
			}
			if (strCopy(&buff, &(token.value.s)) != E_SUCCESS) {
				strFree(&buff);
				strFree(&(token.value.s));
				return token;
			}
			break;
		case TOK_IDENTIFIER:
			if (strcmp(cBuff, "auto") == 0)
				token.type = KW_AUTO;
			else if (strcmp(cBuff, "cin") == 0)
				token.type = KW_CIN;
			else if (strcmp(cBuff, "cout") == 0)
				token.type = KW_COUT;
			else if (strcmp(cBuff, "double") == 0)
				token.type = KW_DOUBLE;
			else if (strcmp(cBuff, "else") == 0)
				token.type = KW_ELSE;
			else if (strcmp(cBuff, "for") == 0)
				token.type = KW_FOR;
			else if (strcmp(cBuff, "if") == 0)
				token.type = KW_IF;
			else if (strcmp(cBuff, "int") == 0)
				token.type = KW_INT;
			else if (strcmp(cBuff, "return") == 0)
				token.type = KW_RETURN;
			else if (strcmp(cBuff, "string") == 0)
				token.type = KW_STRING;
			else {
				if (strInit(&(token.value.s)) != E_SUCCESS) {
					strFree(&buff);
					return token;
				}
				if (strCopy(&buff, &(token.value.s)) != E_SUCCESS) {
					strFree(&buff);
					strFree(&(token.value.s));
					return token;
				}
			}
			break;
		default:
			token.type = TOK_BROKEN_TOKEN;
	}

	strFree(&buff);
	setErrFlg(E_SUCCESS);
	return token;
}

static bool isDelim(char c)
{
	return !isalnum(c);
	// switch (c) {
	// 	case '(':
	// 	case ')':
	// 	case '[':
	// 	case ']':
	// 	case '{':
	// 	case '}':
	// 	case '>':
	// 	case '<':
	// 	case '=':
	// 	case '+':
	// 	case '-':
	// 	case '*':
	// 	case '/':
	// 	case '!': //TODO is this okay or do i need the = after it too?
	// 	case ';':
	// 		return true;
	// 		break;
	// 	default:
	// 		if (isspace(c))
	// 			return true;
	// 		break;
	// }
	// return false;
}
