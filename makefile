all: MINESWEEPER

MINESWEEPER.o: main.c
	gcc -c main.c -o main.o
MINESWEEPER: main.o 
	gcc main.o -o MINESWEEPER

