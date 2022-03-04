# Makefile: PhotoLab2

all: PhotoLab2

clean: 
	rm -f *.o
	rm -f PhotoLab2

PhotoLab2: PhotoLab.o FileIO.o DIPs.o Advanced.o
	gcc -Wall -std=c11 FileIO.o DIPs.o Advanced.o PhotoLab.o -o PhotoLab

PhotoLabTest: PhotoLab.o FileIO.o DIPs.o Advanced.o
	gcc -Wall -std=c11 -g -DDEBUG FileIO.o DIPs.o Advanced.o PhotoLab.o -o PhotoLabTest

PhotoLab.o: PhotoLab.c FileIO.h DIPs.h Advanced.h Constants.h
	gcc -c -Wall -std=c11 PhotoLab.c -o PhotoLab.o

FileIO.o: FileIO.h Constants.h FileIO.c
	gcc -c -Wall -std=c11 FileIO.c -o FileIO.o

DIPs.o: DIPs.h Constants.h DIPs.c
	gcc -c -Wall -std=c11 DIPs.c -o DIPs.o

Advanced.o: Advanced.c Advanced.h Constants.h
	gcc -c -Wall -std=c11 Advanced.c -o Advanced.o
	
