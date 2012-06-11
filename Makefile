default: pgmop.elf

# "pgmop.o" linken mit Library "mypgm" (libmypgm.a)
#						zu executionary "pgmop"
pgmop.elf: pgmop.o libmypgm.a
	gcc -g -Wall -std=c99 -o $@ pgmop.o -I. -L. -lmypgm

# "pgmop.c" compilieren zu "pgmop.o"
pgmop.o: pgmop.c
	gcc -g -Wall -std=c99 -O2 -c pgmop.c -I.

# static Library "mypgm" (libmypgm.a) aus libmypgm.o erstellen !
libmypgm.a: libmypgm.o
	ar -rc libmypgm.a libmypgm.o

# "libmypgm.c" compilieren zu "libmypgm.o"
libmypgm.o: libmypgm.c
	gcc -g -Wall -std=c99 -O2 -c libmypgm.c -I.

clean:
	rm -rf *.elf 2>/dev/null
	rm -rf *.a 2>/dev/null
	rm -rf *.o 2>/dev/null

run: pgmop.elf
	./pgmop.elf

#insert this somewhere> ranlib libmypgm.a
