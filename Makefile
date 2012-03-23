# Define Var
version=2.0.13
objs=obj/lib_basename.o obj/lib_encrypt.o obj/lib_fcs.o obj/lib_filearray.o obj/lib_filebyte.o obj/lib_filename.o obj/lib_fline.o obj/lib_format.o obj/lib_ftotal.o obj/lib_getch.o obj/lib_times.o obj/lib_unencry.o 
libdir=libs
libname=libnetcan-soft

# All
all: $(libdir)/$(libname).so.$(version) $(libdir)/$(libname).a
# Shared Library
$(libdir)/$(libname).so.$(version): $(objs)
	test -d libs || mkdir libs
	test -d obj || mkdir obj
	rm -f $(libdir)/$(libname).so*
	gcc -O3 -shared -lpthread -Wl,-soname -Wl,libnetcan-soft.so.2 $^ -o $@
	ln -s $(libname).so.$(version) $(libdir)/$(libname).so
	ln -s $(libname).so.$(version) $(libdir)/$(libname).so.2
	ln -s $(libname).so.$(version) $(libdir)/$(libname).so.2.0
	rm -f /usr/local/lib/$(libname).so*
	rm -f /lib/$(libname).so*
	cp -a $(libdir)/$(libname).so* /usr/local/lib
	cp -a $(libdir)/$(libname).so* /lib

# Static Library
$(libdir)/$(libname).a: $(objs)
	test -d libs || mkdir libs
	ar rcu $@ $^
	ranlib $@
	cp -a $@ /usr/local/lib
	cp -a $@ /lib

# Create Objects
obj/lib_basename.o: src/lib_basename.c
	gcc -I ./head -O3 -fPIC -c $< -o $@
obj/lib_encrypt.o: src/lib_encrypt.c
	gcc -I ./head -O3 -fPIC -c $< -o $@
obj/lib_fcs.o: src/lib_fcs.c
	gcc -I ./head -O3 -fPIC -c $< -o $@
obj/lib_filearray.o: src/lib_filearray.c
	gcc -I ./head -O3 -fPIC -c $< -o $@
obj/lib_filebyte.o: src/lib_filebyte.c
	gcc -I ./head -O3 -fPIC -c $< -o $@
obj/lib_filename.o: src/lib_filename.c
	gcc -I ./head -O3 -fPIC -c $< -o $@
obj/lib_fline.o: src/lib_fline.c
	gcc -I ./head -O3 -fPIC -c $< -o $@
obj/lib_format.o: src/lib_format.c
	gcc -I ./head -O3 -fPIC -c $< -o $@
obj/lib_ftotal.o: src/lib_ftotal.c
	gcc -I ./head -O3 -fPIC -c $< -o $@
obj/lib_getch.o: src/lib_getch.c
	gcc -I ./head -O3 -fPIC -c $< -o $@
obj/lib_times.o: src/lib_times.c
	gcc -I ./head -O3 -fPIC -c $< -o $@
obj/lib_unencry.o: src/lib_unencry.c
	gcc -I ./head -O3 -fPIC -c $< -o $@

# Backup
backup: 
	cp -a src/*.c* /mnt/Data/NetCan-Soft-Sources/libnetcan-soft.so/src
	cp -a doc/* /mnt/Data/NetCan-Soft-Sources/libnetcan-soft.so/doc
	cp -a head/*.h* /mnt/Data/NetCan-Soft-Sources/libnetcan-soft.so/head
	cp -a examples/*.c* /mnt/Data/NetCan-Soft-Sources/libnetcan-soft.so/examples
	cp -a compile.c /mnt/Data/NetCan-Soft-Sources/libnetcan-soft.so/
