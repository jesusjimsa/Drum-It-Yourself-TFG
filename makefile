OBJ = obj
BIN = bin
INC = include
LIB = lib
SRC = src
CC = gcc -g -O3 -Wall

SOUND_LIBS = -lao -lmpg123

$(BIN)/main: $(SRC)/main.c
	$(CC) $(SRC)/main.c -o $(BIN)/main $(SOUND_LIBS)

run:
	$(BIN)/main
