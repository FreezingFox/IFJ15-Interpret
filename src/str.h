#ifndef __STR_H_
#define __STR_H_

/* Increment value by which is memory increased in each step */
#define STR_INC 10

typedef struct {
    char *str;     /* actual string */
    int len;       /* lenght of the string */
    int mem;       /* memory occupied by the string */
} string;

int strInit(string *s);
void strFree(string *s);

int strCopy(string *from, string *to);
int strCompare(string s1, string s2);
int strAppend(string *to, char c);
int strCopyC(char *from, string *to);
char *strGetStr(string *from);

#endif /* __STR_H_ */
