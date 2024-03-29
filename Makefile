IDIR=../include
CC=gcc
CFLAGS=-I(IDIR)
DEPS = fhchelper.h fhc.h
OBJ = fhc.c main.c fhchelper.c 

ODIR=OBJ
LDIR=../lib

LIBS=-lm

%.0: %. $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

FHC: $(OBJ)
	gcc -O3 -o FHC fhc.c fhchelper.c main.c
	
clean:
	rm -f FHC FHC.exe