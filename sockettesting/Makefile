CC=g++
CFLAGS=-lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lsfml-network -std=c++11
LDFLAGS=

all: main

main: server.cpp client.cpp
	$(CC) server.cpp -o server $(CFLAGS)
	$(CC) client.cpp -o client $(CFLAGS)

clean:
	rm server client

