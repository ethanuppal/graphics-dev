# Copyright (C) 2024 Ethan Uppal. All rights reserved.

SRCDIR		:= ./src
INCLUDEDIR	:= ./src

CC			:= $(shell which gcc || which clang)
CFLAGS		:= -std=c99 -pedantic -Wall -Wextra -I $(INCLUDEDIR)
CDEBUG		:= -g
CRELEASE	:= -O2
TARGET		:= main

# CFLAGS 		+= $(CRELEASE)
CFLAGS 		+= $(CDEBUG) $(shell sdl2-config --cflags --libs)

SRC			:= main.c $(shell find $(SRCDIR) -name "*.c" -type f)
OBJ			:= $(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	@echo 'Compiling $@'
	$(CC) $(CFLAGS) $< -c -o $@

.PHONY: clean
clean:
	rm -rf $(OBJ)
