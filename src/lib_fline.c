#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

int fline(FILE * fp)
{
    rewind(fp);
    int line = 0;
    while (!feof(fp))
	if (fgetc(fp) == '\n')
	    line++;
    rewind(fp);
    return line;
}



