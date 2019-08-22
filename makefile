OBJ = obj
BIN = bin
INC = include
LIB = lib
SRC = src
CC = gcc -g -O3 -Wall
DB = lldb

SOUND_LIBS = -lao -lmpg123
CONF_LIBS = -lpthread

$(BIN)/main: $(SRC)/main.c
	@$(CC) $(SRC)/main.c -o $(BIN)/main $(SOUND_LIBS) $(CONF_LIBS)

run:
	@$(BIN)/main

debug: $(BIN)/main
	@$(DB) $(BIN)/main

clean:
	@rm -rf $(OBJ)/*
	@rm -rf $(BIN)/*
	@echo "Done!"
