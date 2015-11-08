#ifndef STR_H
#define STR_H

typedef struct {
    char *str;     /* actual string */
    int len;       /* length of the string */
    int mem;       /* memory occupied by the string */
} string;

int strInit(string *s);
void strFree(string *s);

int strCopy(string *from, string *to);
int strCompare(string s1, string s2);
int strAppend(string *to, char c);
int strCopyC(char *from, string *to);
char *strGetCStr(string *from);

/* Built-in functions */
int length(string s);
string substr(string s, int i, int n);
string concat(string s1, string s2);
int find(string s, string search);
string sort(string s);

#endif /* STR_H */
