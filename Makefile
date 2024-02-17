CC=gcc
PROGNAME=DashServer
CFLAGS=Wall

all: main.o $(PROGNAME) clean

main.o: src/main.c
	$(CC) -c src/main.c

$(PROGNAME): main.o
	$(CC) main.o -o $(PROGNAME)

clean:
	rm *.o


