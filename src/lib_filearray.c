#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

int filearray(FILE * file, char *array, int arraysize)
{
    if (file == NULL)
	return 0;
    rewind(file);
    int n, fn;
    fn = filebyte(file) - 1;
    for (n = 0; n < fn; n++)
	array[n] = fgetc(file);
    for (; n <= arraysize; n++)
	array[n] = '\0';



    rewind(file);
}


