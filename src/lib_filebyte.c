#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>


int filebyte(FILE * file)
{
    if (file == NULL)
	return 0;
    rewind(file);
    int bit = 0;
    while (feof(file) == 0) {
	fgetc(file);
	bit++;
    }
    bit -= 1;
    rewind(file);
    return bit;
}

