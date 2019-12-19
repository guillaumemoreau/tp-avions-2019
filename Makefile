tp1_medev.out: main.o avion.o
	g++ -o tp1_medev.out main.o avion.o

main.o: main.cpp avion.h monde.h
	g++ -c main.cpp

avion.o: avion.cpp avion.h monde.h
	g++ -c avion.cpp

monde.o: monde.cpp monde.h avion.h
	g++ -c monde.cpp
