LDLIBS=-lncursesw
snake: main.o screen_set.o screen.o game.o field.o display_character.o
	cc -o snake main.o screen_set.o screen.o game.o field.o display_character.o -lncursesw
main.o: main.h
screen_set.o: main.h
screen.o: main.h
game.o: main.h
field.o: main.h
display_character.o: main.h