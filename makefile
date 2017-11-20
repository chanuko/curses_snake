LDLIBS=-lncursesw 
snake: main.o ScreenSet.o Screen.o Game.o field.o chara.o
	cc -o snake main.o ScreenSet.o Screen.o Game.o field.o chara.o -lncursesw 
main.o: main.h
ScreenSet.o: main.h
Screen.o: main.h
Game.o: main.h 
field.o: main.h
chara.o: main.h