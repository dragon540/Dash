CC=gcc
PROGNAME=DashServer
CFLAGS=Wall

all: main.o $(PROGNAME) clean

connect.o: src/connect.c src/connect.h
	$(CC) -c src/connect.c

main.o: src/main.c
	$(CC) -c src/main.c

$(PROGNAME): connect.o main.o
	$(CC) connect.o main.o -o $(PROGNAME)

clean:
	rm *.o

run:
	./$(PROGNAME)


