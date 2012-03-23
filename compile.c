#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#define BACKDIR "/mnt/Data/NetCan-Soft-Sources/libnetcan-soft.so"

int main(int argc,char **argv) {
int count,n,mkdir=0;
char event[512];
memset(event,0,sizeof(event));

if(argc!=1)
sprintf(event,"make %s",argv[1]);
else
sprintf(event,"make",NULL);

FILE * log=fopen("compile.log","r");
FILE * make=fopen("Makefile","r");
struct dirent ** files;

if(log!=NULL) {
fscanf(log,"Files = %d",&count);
if(count==(scandir("./src",&files,0,alphasort)-1)){
fclose(log);
if(make!=NULL) {
system(event);
return 1;
}
}
}

make=fopen("Makefile","w");

count=scandir("./src",&files,0,alphasort)-1;

if(count<=0) {
fclose(make);
return 0;
}



// fputs("\n",make);
// fprintf(make,"\n",NULL);

fputs("# Define Var\n",make);
fprintf(make,"version=2.0.%d\n",count);
fputs("objs=",make);

for(n=0;n<=count;n++) {
if(strcmp(files[n]->d_name,".")==0||strcmp(files[n]->d_name,"..")==0)
continue;
fprintf(make,"obj/%s.o ",filename(files[n]->d_name));
}

fputs("\nlibdir=libs\n",make);
fputs("libname=libnetcan-soft\n",make);
fputs("\n",make);
fputs("# All\n",make);
fputs("all: $(libdir)/$(libname).so.$(version) $(libdir)/$(libname).a\n",make);

fputs("# Shared Library\n",make);
fputs("$(libdir)/$(libname).so.$(version): $(objs)\n",make);
fputs("\ttest -d libs || mkdir libs\n",make);
fputs("\trm -f $(libdir)/$(libname).so*\n",make);
fputs("\tgcc -O3 -shared -lpthread -Wl,-soname -Wl,libnetcan-soft.so.2 $^ -o $@\n",make);
fputs("\tln -s $(libname).so.$(version) $(libdir)/$(libname).so\n",make);
fputs("\tln -s $(libname).so.$(version) $(libdir)/$(libname).so.2\n",make);
fputs("\tln -s $(libname).so.$(version) $(libdir)/$(libname).so.2.0\n",make);
fputs("\trm -f /usr/local/lib/$(libname).so*\n",make);
fputs("\trm -f /lib/$(libname).so*\n",make);
fputs("\tcp -a $(libdir)/$(libname).so* /usr/local/lib\n",make);
fputs("\tcp -a $(libdir)/$(libname).so* /lib\n",make);
fputs("\n",make);

fputs("# Static Library\n",make);
fputs("$(libdir)/$(libname).a: $(objs)\n",make);
fputs("\ttest -d libs || mkdir libs\n",make);
fputs("\tar rcu $@ $^\n",make);
fputs("\tranlib $@\n",make);
fputs("\tcp -a $@ /usr/local/lib\n",make);
fputs("\tcp -a $@ /lib\n",make);
fputs("\n",make);

fputs("# Create Objects\n",make);
for(n=0;n<=count;n++) {
if(strcmp(files[n]->d_name,".")==0||strcmp(files[n]->d_name,"..")==0)
continue;
fprintf(make,"obj/%s.o: src/%s\n",filename(files[n]->d_name),files[n]->d_name);
if(mkdir==0) {
fputs("\ttest -d obj || mkdir obj\n",make);
mkdir=1;
}
fputs("\tgcc -I ./head -O3 -fPIC -c $< -o $@\n",make);
}
fputs("\n",make);

fputs("# Backup\n",make);
fputs("backup: \n",make);
fprintf(make,"\tcp -a src/*.c* %s/src\n",BACKDIR);
fprintf(make,"\tcp -a doc/* %s/doc\n",BACKDIR);
fprintf(make,"\tcp -a head/*.h* %s/head\n",BACKDIR);
fprintf(make,"\tcp -a examples/*.c* %s/examples\n",BACKDIR);
fprintf(make,"\tcp -a compile.c %s/\n",BACKDIR);

fclose(make);
log=fopen("compile.log","w");
fprintf(log,"Files = %d\n",count);
fclose(log);
system(event);

}






