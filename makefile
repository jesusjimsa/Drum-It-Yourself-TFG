OBJ = obj
BIN = bin
INC = include
LIB = lib
SRC = src
CC = gcc -g -O3 -Wall
DB = lldb

SOUND_LIBS = -lao -lmpg123
CONF_LIBS = 

$(BIN)/main:
	@$(CC) $(SRC)/main.c $(SRC)/play.c -o $(BIN)/main $(SOUND_LIBS) $(CONF_LIBS)

run: $(BIN)/main
	@$(BIN)/main

debug: $(BIN)/main
	@$(DB) $(BIN)/main

clean:
	@rm -rf $(OBJ)/*
	@rm -rf $(BIN)/*
	@echo "Done!"
