
all: Cosmic_Yonder

things.o : things.c params.h
	gcc -c things.c -lncursesw -lm -o things.o
	
enemy.o : enemy.c params.h
	gcc -c enemy.c -lncursesw -lm -o enemy.o

room.o : room.c params.h
	gcc -c room.c -lncursesw -lm -o room.o

heros.o : heros.c params.h
	gcc -c heros.c -lncursesw -lm -o heros.o

display.o : display.c params.h
	gcc -c display.c -lncursesw -lm -o display.o

main.o : main.c things.o enemy.o room.o heros.o display.o params.h
	gcc -c main.c -lncursesw -lm -o main.o

Cosmic_Yonder : main.o things.o enemy.o room.o heros.o display.o
	gcc main.o things.o enemy.o room.o heros.o display.o -o Cosmic_Yonder -lncursesw -lm

clean:
	rm -f *.o
	rm -f Cosmic_Yonder
	

