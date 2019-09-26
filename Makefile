CFLAGS = -g -Wall
OBJECTS = main.o prompt.o init.o loop.o parse.o execute.o exec_pwd.o exec_cd.o exec_echo.o exec_ls.o launch.o exec_pinfo.o bg_terminate.o history.o nightswatch.o countargs.o exec_setenv.o exec_unsetenv.o linkedlist.o exec_jobs.o exec_kjob.o exec_fg.o exec_bg.o overkill.o quit.o sighandlers.o execute_command.o execute_pipeline.o

shell: $(OBJECTS)
	gcc $(CFLAGS) -o shell $(OBJECTS)

main.o: shell.h init.h loop.h main.c
	gcc $(CFLAGS) -c main.c
	
prompt.o: prompt.c prompt.h shell.h
	gcc $(CFLAGS) -c prompt.c

init.o: init.h shell.h init.c bg_terminate.h sighandlers.h
	gcc $(CFLAGS) -c init.c

loop.o: loop.h loop.c prompt.h shell.h parse.h execute.h execute_command.h execute_pipeline.h
	gcc $(CFLAGS) -c loop.c

parse.o: parse.c parse.h 
	gcc $(CFLAGS) -c parse.c

execute.o : execute.h execute.c exec_pwd.h exec_cd.h exec_echo.h exec_ls.h launch.h exec_pinfo.h history.h nightswatch.h exec_setenv.h exec_unsetenv.h exec_jobs.h exec_kjob.h exec_fg.h exec_bg.h overkill.h quit.h
	gcc $(CFLAGS) -c execute.c

exec_pwd.o : exec_pwd.h exec_pwd.c
	gcc $(CFLAGS) -c exec_pwd.c

exec_cd.o : exec_cd.h exec_cd.c shell.h
	gcc $(CFLAGS) -c exec_cd.c

exec_echo.o : exec_echo.h exec_echo.c
	gcc $(CFLAGS) -c exec_echo.c

exec_ls.o : exec_ls.h exec_ls.c shell.h
	gcc $(CFLAGS) -c exec_ls.c

launch.o: launch.h launch.c shell.h linkedlist.h
	gcc $(CFLAGS) -c launch.c

exec_pinfo.o : exec_pinfo.h exec_pinfo.c parse.h
	gcc $(CFLAGS) -c exec_pinfo.c

bg_terminate.o : bg_terminate.h bg_terminate.c shell.h linkedlist.h
	gcc $(CFLAGS) -c bg_terminate.c

history.o : history.h history.c shell.h
	gcc $(CFLAGS) -c history.c

nightswatch.o : nightswatch.h nightswatch.c
	gcc $(CFLAGS) -c nightswatch.c

countargs.o : countargs.h countargs.c
	gcc $(CFLAGS) -c countargs.c

exec_setenv.o : exec_setenv.h exec_setenv.c countargs.h
	gcc $(CFLAGS) -c exec_setenv.c

exec_unsetenv.o : exec_unsetenv.h exec_unsetenv.c countargs.h
	gcc $(CFLAGS) -c exec_unsetenv.c

linkedlist.o : linkedlist.h linkedlist.c shell.h
	gcc $(CFLAGS) -c linkedlist.c

exec_jobs.o : exec_jobs.h exec_jobs.c shell.h linkedlist.h parse.h
	gcc $(CFLAGS) -c exec_jobs.c

exec_kjob.o : exec_kjob.h exec_kjob.c shell.h linkedlist.h countargs.h
	gcc $(CFLAGS) -c exec_kjob.c

exec_fg.o : exec_fg.h exec_fg.c shell.h linkedlist.h countargs.h
	gcc $(CFLAGS) -c exec_fg.c

exec_bg.o : exec_bg.h exec_bg.c linkedlist.h shell.h countargs.h
	gcc $(CFLAGS) -c exec_bg.c

overkill.o : overkill.h overkill.c shell.h linkedlist.h countargs.h
	gcc $(CFLAGS) -c overkill.c

quit.o : quit.h quit.c countargs.h
	gcc $(CFLAGS) -c quit.c

sighandlers.o : sighandlers.h sighandlers.c shell.h linkedlist.h
	gcc $(CFLAGS) -c sighandlers.c

execute_command.o : execute_command.h execute_command.c execute.h
	gcc $(CFLAGS) -c execute_command.c

execute_pipeline.o : execute_pipeline.h execute_pipeline.c execute_command.h countargs.h parse.h
	gcc $(CFLAGS) -c execute_pipeline.c

.PHONY: clean


clean:
	rm shell .pksh_history $(OBJECTS)