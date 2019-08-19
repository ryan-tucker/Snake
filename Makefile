main: world.o snake.o linked_list.o main.o display.o file_tools.o
	gcc -Wall -g -o main snake.o linked_list.o world.o main.o display.o file_tools.o -lncurses

snake.o : snake.c linked_list.h snake.h world.h
	gcc -c snake.c

linked_list.o : linked_list.c 
	gcc -c linked_list.c

world.o : world.c snake.h linked_list.h world.h
	gcc -c world.c

main.o : main.c world.h snake.h display.h
	gcc -c main.c

display.o : display.c snake.h linked_list.h world.h
	gcc -c display.c

file_tools.o : file_tools.c file_tools.h score.h
	gcc -c file_tools.c

clean : 
	rm snake.o linked_list.o world.o main.o display.o file_tools.o main


