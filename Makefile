CC=g++
CFLAGS= -O2 -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -std=c++11
LDFLAGS=
SOURCES=src/Main/*.cpp src/Game/*.cpp src/Options/*.cpp

EXECUTABLE=game

all: main

main: $(SOURCES)
	$(CC) $(SOURCES) -o $(EXECUTABLE) $(CFLAGS)

clean:
	rm $(EXECUTABLE)

