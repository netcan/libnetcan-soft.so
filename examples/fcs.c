#include <stdio.h>
int main(int argc,char **argv){
char files[2048];
printf("%s\n",fcs(argv[2],argv[1],2,files,sizeof(files)));
printf("%s\n",files);

}
