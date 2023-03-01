CC := g++
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

all: soccerStars.out 

soccerStars.out: main.o functions.o Ball.o Player.o Field.o Game.o rsdl.o 
	$(CC) main.o functions.o Ball.o Field.o Player.o Game.o rsdl.o $(CCFLAGS) -o soccerStars.out



functions.o: rsdl.hpp functions.cpp functions.hpp
	$(CC) -std=c++11 -c functions.cpp -o functions.o
	
Ball.o: rsdl.hpp Macros.hpp functions.hpp Ball.cpp Ball.hpp 
	$(CC) -std=c++11 -c Ball.cpp -o Ball.o

Player.o: rsdl.hpp Macros.hpp functions.hpp Player.cpp Player.hpp 
	$(CC) -std=c++11 -c Player.cpp -o Player.o	
	
Field.o: rsdl.hpp Macros.hpp functions.hpp Player.hpp Ball.hpp Field.cpp Field.hpp 
	$(CC) -std=c++11 -c Field.cpp -o Field.o
	
Game.o: rsdl.hpp Macros.hpp functions.hpp Player.hpp Ball.hpp Field.hpp Game.cpp Game.hpp 
	$(CC) -std=c++11 -c Game.cpp -o Game.o	


main.o: rsdl.hpp Macros.hpp functions.hpp Field.hpp Player.hpp Ball.hpp Game.o main.cpp 
	$(CC) -std=c++11 -c main.cpp -o main.o


rsdl.o: rsdl.hpp rsdl.cpp
	$(CC) -std=c++11 -c rsdl.cpp -o rsdl.o

.PHONY: clean
clean:
	rm -r *.o
