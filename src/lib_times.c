#include "netcan-soft.h"

int times(char *string, char ch)
{
    int n, t = 0;
    int l = strlen(string);
    char name[2048000];
    memcpy(name, string, l);
    for (n = 0; n <= l; n++)
	if (name[n] == ch)
	    t++;
    return t;
}
