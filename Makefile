CFLAGS = -g -Wall
OBJECTS = main.o prompt.o init.o loop.o

shell: $(OBJECTS)
	gcc $(CFLAGS) -o shell $(OBJECTS)

main.o: shell.h init.h loop.h main.c
	gcc $(CFLAGS) -c main.c
	
prompt.o: prompt.c prompt.h shell.h
	gcc $(CFLAGS) -c prompt.c

init.o: init.h shell.h init.c
	gcc $(CFLAGS) -c init.c

prompt.o: prompt.c prompt.h shell.h 
	gcc $(CFLAGS) -c prompt.c

.PHONY: clean
	rm shell $(OBJECTS)