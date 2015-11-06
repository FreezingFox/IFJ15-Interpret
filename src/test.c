#include <stdio.h>
#include "symbol_table.h"
#include "str.h"
#include "scanner.h"
#include "errors.h"

#define OK(s) printf("TEST: %s: OK\n", (s))
#define FAIL(s) printf("TEST: %s: FAIL\n", (s))

int main(int argc, char **argv)
{
	SymbolTable table;
	sTableInit(&table);
	string key;
	strInit(&key);
	strCopyC("keyword", &key);
	union varValue value;
	value.i = 27;
	sTableInsert(&table, key, T_INT, value, NULL);
	strCopyC("yera", &key);
	value.i = 27;
	sTableInsert(&table, key, T_INT, value, NULL);
	strCopyC("cats", &key);
	value.i = 27;
	sTableInsert(&table, key, T_INT, value, NULL);
	strCopyC("rules", &key);
	value.i = 27;
	sTableInsert(&table, key, T_INT, value, NULL);
	strCopyC("xerxes", &key);
	value.i = 27;
	sTableInsert(&table, key, T_INT, value, NULL);
	printf("%s\n", table.first->right->key.str);
	tData_t *data = sTableFind(&table, key);
	if (data == NULL) {
		FAIL("sTableInsert() || sTableFind()");
		return -1;
	} else
		OK("strCopyC() && sTableInsert() && sTableFind()");

	sTableFree(&table);
	strFree(&key);

	if (argc != 2)
		FAIL("enter a file, moron.");

	FILE *f = fopen(argv[1], "r");
	if (f == NULL) {
		FAIL("couldnt open file");
	}

	token_t tok;
	while(1) {
		tok = getToken(f);
		if (getErrFlg() == EOF)
			break;
		if (getErrFlg() != E_SUCCESS) {
			printErrFlg();
			break;
		}

		switch (tok.type) {
			case KW_AUTO:
			case KW_CIN:
			case KW_COUT:
			case KW_DOUBLE:
			case KW_ELSE:
			case KW_FOR:
			case KW_IF:
			case KW_INT:
			case KW_RETURN:
			case KW_STRING:
				printf("a kw: %d\n", tok.type);
				break;
			case TOK_IDENTIFIER:
			case TOK_STRING:
				printf("%d: %s\n",tok.type, strGetStr(&(tok.value.s)));
				strFree(&(tok.value.s));
				break;
			case TOK_INT:
				printf("int: %d\n", tok.value.i);
				break;
			case TOK_DOUBLE:
				printf("double: %g\n", tok.value.d);
				break;
			case TOK_BROKEN_TOKEN:
				printf("something went terribly wrong\n");
				printErrFlg();
				break;
			default:
				printf("token: %d\n", tok.type);
				break;
		}
	}
	fclose(f);
	printErrFlg();
	return 0;
}
