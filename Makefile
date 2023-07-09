# Makefile
#King's sacrifice

all: Main GUIv2 chess

clean:

	rm -f chess

GUIv2: GUIv2.c
	gcc GUIv2.c -o GUIv2 -Wall -lSDL

Object.o: Object.c Object.h
	gcc -c Object.c -o Object.o -Wall -std=c11 -g

Move.o: Move.c Move.h Object.h
	gcc -c Move.c -o Move.o -Wall -std=c11 -g
	
	AI.o: AI.c Move.h AI.h Object.h
	gcc -c AI.c -o AI.o -Wall -std=c11 -g 

#V1.0
Main1.o: Main1.c Object.h Move.h
	gcc -c Main1.c -o Main1.o -Wall -lSDL -std=c11 -g

chess: Main1.o Object.o Move.o AI.o
	gcc Main1.o Object.o Move.o AI.o -o chess -Wall -lSDL -std=c11 -g

#DEBUGGING
Main2.o: Main2.c Object.h Move.h
	gcc -c Main1.c -o Main1.o -Wall -lSDL -std=c11 -g
Main2: Main2.o Object.o Move.o
	gcc Main2.o Object.o Move.o -o Main2 -Wall -lSDL -std=c11 -g
