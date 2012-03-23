#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

char *format(char *string)
{
    char *type;
    int bool, n;
    type = strrchr(string, '.');
    if(type==NULL)
	return "Unknown";
    
    for (n = 0; n <= strlen(type); n++)
	if (type[n] == '/') {
	    bool = 0;
	    break;
	} else
	    bool = 1;

    if (type == NULL || strlen(type) == 1 || bool == 0)
	return "Unknown";
    else
	return strrchr(string, '.');
}
