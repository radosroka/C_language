# Makefile
# Řešení IJC-DU1, příklad b), 25.3.2015
# Autor: Radovan Sroka, FIT

CC = gcc
CFLAGS = -O2 -std=c99 -Wall -pedantic


default: prvocisla prvocisla-inline steg-decode

prvocisla: prvocisla.o eratosthenes.o error.o
	$(CC) prvocisla.o eratosthenes.o error.o -o prvocisla -lm

prvocisla-inline: eratosthenes.o error.o prvocisla-inline.o
	$(CC)  eratosthenes.o error.o prvocisla-inline.o -o prvocisla-inline -lm

steg-decode: steg-decode.o eratosthenes.o error.o ppm.o
	$(CC) steg-decode.o eratosthenes.o error.o ppm.o -o steg-decode -lm

eratosthenes.o: eratosthenes.c bit_array.h error.h
	$(CC) $(CFLAGS) -c eratosthenes.c

error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c

ppm.o: ppm.c error.h ppm.h
	$(CC) $(CFLAGS) -c ppm.c

prvocisla.o: prvocisla.c bit_array.h error.h
	$(CC) $(CFLAGS) -c prvocisla.c

prvocisla-inline.o: prvocisla.c bit_array.h error.h
	$(CC) $(CFLAGS) -c prvocisla.c -o prvocisla-inline.o -DUSE_INLINE

steg-decode.o: steg-decode.c ppm.h bit_array.h error.h
	$(CC) $(CFLAGS) -c steg-decode.c

clean:
	rm *.o 

zip:
	zip xsroka00.zip *.c *.h Makefile