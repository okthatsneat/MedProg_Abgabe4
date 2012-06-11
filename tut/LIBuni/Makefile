#
# "probe.o" linken mit Library "uni" (libuni.a)
#						zu executionary "probe"
#
probe.elf:probe.o libuni.a
	gcc -g -Wall -o probe.elf probe.o -I. -L. -luni
#

#
# "probe.c" compilieren zu "probe.o"
#
probe.o:probe.c
	gcc -g -Wall -O2 -c probe.c -I.
#

#
# static Library "uni" (libuni.a) aus libuni.o erstellen !
#
libuni.a:libuni.o
	ar -rc libuni.a libuni.o
#

#
# "libuni.c" compilieren zu "libuni.o"
#
libuni.o:libuni.c
	gcc -g -Wall -O2 -c libuni.c -I.
#

#
#
#
clean:
	rm -rf *.o 2>/dev/null
	rm -rf *~ 2>/dev/null
#
clear:
	rm -rf *.elf 2>/dev/null
	rm -rf *.a 2>/dev/null
	rm -rf *.o 2>/dev/null
	rm -rf *~ 2>/dev/null
#
run:
	./probe.elf
#
