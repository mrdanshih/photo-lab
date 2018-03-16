CFLAGS = -g -Wall

all: PhotoLab

PhotoLab: PhotoLab.o DIPS.o FileIO.o Image.o
	gcc $(CFLAGS) -o PhotoLab PhotoLab.o DIPS.o FileIO.o Image.o

PhotoLab.o: PhotoLab.c Constants.h
	gcc $(CFLAGS) -c PhotoLab.c

DIPS.o: DIPS.c DIPS.h Constants.h
	gcc $(CFLAGS) -c DIPS.c -o DIPS.o

FileIO.o: FileIO.c FileIO.h Constants.h
	gcc $(CFLAGS) -c FileIO.c -o FileIO.o

Image.o: Image.c Image.h Constants.h
	gcc $(CFLAGS) -c Image.c -o Image.o

clean:
	rm -f *.o
	rm -f PhotoLab

