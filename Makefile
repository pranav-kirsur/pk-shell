CFLAGS = -g -Wall

shell: main.o prompt.o init.o loop.o
	gcc $(CFLAGS) -o shell main.o prompt.o init.o loop.o

main.o:

prompt.o: prompt.c prompt.h
	gcc $(CFLAGS) -c prompt.c