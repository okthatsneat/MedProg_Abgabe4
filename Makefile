#creating the shared library
libmypgmMake: libmypgm.c
#create the object file
	gcc -c -fPIC libmypgm.c -o libmypgm.o
# create the library
	gcc -shared -Wl,-soname,libmypgm.so.1 -o libmypgm.so.1.0.1  libmypgm.o

# link against the shared library

libmypgmMake: pgmop.c libmypgm.so.1.0.1
	gcc pgmop.c -o pgmop -L. -lmypgm
	

