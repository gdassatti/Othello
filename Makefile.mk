CC = g++
CFLAGS = -g -Wall

all: build archive

build: game

archive: CS3560_HW06.tar.gz

CS3560_HW06.tar.gz:
	tar czf CS3560_HW06.tar.gz

game: game.o othello.o piece.o main.o
	$(CC) game.o othello.o piece.o main.o

game.o: game.cc game.h
	$(CC) $(CFLAGS) game.cc

othello.o: othello.cc othello.h piece.h game.h colors.h
	$(CC) $(CFLAGS) othello.cc

piece.o: piece.cc piece.h colors.h
	$(CC) $(CFLAGS) piece.cc

main.o: main.cc othello.h
	$(CC) $(CFLAGS) main.cc

clean:
	rm -f *.o
	rm -f a.exe

