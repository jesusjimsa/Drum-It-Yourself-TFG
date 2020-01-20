# Copyright 2020 Jesús Jiménez Sánchez
#

OBJ = obj
BIN = bin
INC = include
LIB = lib
SRC = src
CC = gcc -g -O3 -Wall
DB = lldb

SOUND_LIBS = -lao -lmpg123
CONF_LIBS = -lpthread #-lwiringPi

$(BIN)/main: $(SRC)/main.c $(SRC)/play.c $(INC)/play.h
	@$(CC) $(SRC)/main.c $(SRC)/play.c -o $(BIN)/main $(SOUND_LIBS) $(CONF_LIBS)

keys: $(SRC)/main.c $(SRC)/play.c $(INC)/play.h
	@$(CC) $(SRC)/keys.c $(SRC)/play.c -o $(BIN)/main $(SOUND_LIBS) $(CONF_LIBS)

run: $(BIN)/main
	@$(BIN)/main

debug: $(BIN)/main
	@$(DB) $(BIN)/main

clean:
	@rm -rf $(OBJ)/*
	@rm -rf $(BIN)/*
	@echo "Done!"
