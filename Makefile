.c.o:   $*.h
	gcc -c $*.c

.cpp.o:	$*.h
	g++	-c $*.cpp

all:	game

game:  main.o asteroid.o ilpgame.o
	gcc -o $@ $^

clean:
	rm *.o *.*~ *~ game
