CFLAGS = -g -Wall
OBJECTS = main.o prompt.o init.o loop.o parse.o execute.o exec_pwd.o exec_cd.o exec_echo.o exec_ls.o launch.o exec_pinfo.o bg_terminate.o

shell: $(OBJECTS)
	gcc $(CFLAGS) -o shell $(OBJECTS)

main.o: shell.h init.h loop.h main.c
	gcc $(CFLAGS) -c main.c
	
prompt.o: prompt.c prompt.h shell.h
	gcc $(CFLAGS) -c prompt.c

init.o: init.h shell.h init.c bg_terminate.h
	gcc $(CFLAGS) -c init.c

loop.o: loop.h loop.c prompt.h shell.h parse.h execute.h
	gcc $(CFLAGS) -c loop.c

parse.o: parse.c parse.h 
	gcc $(CFLAGS) -c parse.c

execute.o : execute.h execute.c exec_pwd.h exec_cd.h exec_echo.h exec_ls.h launch.h exec_pinfo.h
	gcc $(CFLAGS) -c execute.c

exec_pwd.o : exec_pwd.h exec_pwd.c
	gcc $(CFLAGS) -c exec_pwd.c

exec_cd.o : exec_cd.h exec_cd.c shell.h
	gcc $(CFLAGS) -c exec_cd.c

exec_echo.o : exec_echo.h exec_echo.c
	gcc $(CFLAGS) -c exec_echo.c

exec_ls.o : exec_ls.h exec_ls.c shell.h
	gcc $(CFLAGS) -c exec_ls.c

launch.o: launch.h launch.c
	gcc $(CFLAGS) -c launch.c

exec_pinfo.o : exec_pinfo.h exec_pinfo.c parse.h
	gcc $(CFLAGS) -c exec_pinfo.c

bg_terminate.o : bg_terminate.h bg_terminate.c
	gcc $(CFLAGS) -c bg_terminate.c

.PHONY: clean


clean:
	rm shell $(OBJECTS)