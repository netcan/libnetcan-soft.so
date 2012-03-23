#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

char *basename(char *string)
{
    int n, ch = 0;
    char name[2048];
    memset(name, 0, sizeof(name));
    memcpy(name, string, strlen(string));
    for (n = 0; n <= strlen(string); n++)
	if (string[n] == '/')
	    ch++;
    if (ch == strlen(string))
	return "/";

    char *s = strrchr(name, '/');
    if (s == NULL) {
	return string;
    } else {
	if (strlen(s) != 1)
	    return s + 1;
	else {
	    for (n = strlen(string) - 1; n > 0; n--) {
		if (name[n] == '/')
		    name[n] = 0;
		else
		    break;
	    }


	    s = strrchr(name, '/');
	    if (s != NULL)
		return s + 1;
	    else
		return name;
	}

    }

}


