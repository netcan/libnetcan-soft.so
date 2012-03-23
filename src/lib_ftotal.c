#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>
#include <netcan-soft.h>

int ftotal(DIR * pwd)
{
    if (pwd == NULL)
	return 0;
    int total = 0;
    struct dirent *file;
    if (pwd == NULL)
	return 0;
    while ((file = readdir(pwd)) != NULL) {
	if (strcmp(file->d_name, ".") == 0)
	    continue;
	total++;
    }
    return total;
}

