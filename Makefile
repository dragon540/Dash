CC=gcc
PROGNAME=DashServer
CFLAGS=Wall

all: main.o $(PROGNAME) clean

connect.o: src/connect.c src/connect.h
	$(CC) -c src/connect.c

communicate.o: src/communicate.c src/communicate.h
	$(CC) -c src/communicate.c

main.o: src/main.c
	$(CC) -c src/main.c

$(PROGNAME): connect.o communicate.o main.o
	$(CC) connect.o communicate.o main.o -o $(PROGNAME)

clean:
	rm *.o

run:
	./$(PROGNAME)


