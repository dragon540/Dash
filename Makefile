CC=gcc
PROGNAME=DashServer
CFLAG1=-Wall

all: $(PROGNAME) clean

page_map.o: src/page_map.c src/page_map.h
	$(CC) -c src/page_map.c

connect.o: src/connect.c src/connect.h
	$(CC) -c src/connect.c

communicate.o: src/communicate.c src/communicate.h
	$(CC) -c src/communicate.c

read_resource.o: src/read_resource.c src/read_resource.h
	$(CC) -c src/read_resource.c

helper.o: src/helper.c src/helper.h
	$(CC) -c src/helper.c

main.o: src/main.c
	$(CC) -c src/main.c

$(PROGNAME): page_map.o connect.o communicate.o read_resource.o helper.o main.o
	$(CC) $(CFLAG1) page_map.o connect.o communicate.o read_resource.o helper.o main.o -o $(PROGNAME)

clean:
	rm *.o

run:
	./$(PROGNAME)


