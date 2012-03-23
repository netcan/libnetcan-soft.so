#include <stdio.h>

encrypt(char *text, int textsize, char *code, int codesize, int process)
{
    int c = 0, t;
    for (t = 0; t <= textsize; t++) {
	if (process == 1) {
	    if (100 * t / textsize < 10)
		printf("\b\b%d%%", 100 * t / textsize);
	    if (100 * t / textsize >= 10)
		printf("\b\b\b%d%%", 100 * t / textsize);
	}
	if (c >= codesize)
	    c = 0;
	while (c < codesize) {
	    text[t] += (int) code[c] - 48;
	    c++;
	    break;
	}
    }
}

