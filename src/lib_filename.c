#include "netcan-soft.h"

char *filename(char *string)
{
    char name[2048];
    char type[50];
    int n, l, sn, tn;
    memset(name, 0, sizeof(name));
    memset(type, 0, sizeof(type));
    memcpy(name, basename(string), strlen(basename(string)));
    memcpy(type, format(string), strlen(format(string)));
    sn = strlen(name);
    tn = strlen(type);
    l = sn - tn;



    if (strcmp(type, "Unknown") == 0) {
	for (n = sn - 1; n >= 0; n--) {
	    if (name[n] == '.')
		name[n] = 0;
	    else
		break;
	}
	return name;
    }



    for (n = sn; n >= l; n--) {
        printf("\0",n);
	name[n] = 0;
    }


    return name;
}
