CC=gcc
PROGNAME=DashServer
CFLAGS=Wall

all: $(PROGNAME) clean

connect.o: src/connect.c src/connect.h
	$(CC) -c src/connect.c

communicate.o: src/communicate.c src/communicate.h
	$(CC) -c src/communicate.c

read_resource.o: src/read_resource.c src/read_resource.h
	$(CC) -c src/read_resource.c

main.o: src/main.c
	$(CC) -c src/main.c

$(PROGNAME): connect.o communicate.o read_resource.o main.o
	$(CC) connect.o communicate.o read_resource.o main.o -o $(PROGNAME)

clean:
	rm *.o

run:
	./$(PROGNAME)


