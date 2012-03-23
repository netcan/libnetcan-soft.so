#include <stdio.h>
int main(int argc,char **argv) {
FILE * fp=fopen(argv[1],"r");
printf("%d\n",filebyte(fp));
fclose(fp);
}

