# Copyright (C) 2024 Ethan Uppal. All rights reserved.

SRCDIR		:= ./src
INCLUDEDIR	:= ./src

CC			:= $(shell which gcc || which clang)
CFLAGS		:= -std=c99 -pedantic -Wall -Wextra -I $(INCLUDEDIR)
CDEBUG		:= -g
CRELEASE	:= -O2
TARGET		:= main

# CFLAGS 		+= $(CRELEASE)
CFLAGS 		+= $(shell sdl2-config --cflags --libs)

SRC			:= $(shell find $(SRCDIR) -name "*.c" -type f)
OBJ			:= $(SRC:.c=.o)

$(TARGET): build

.PHONY: build
build: main.c $(OBJ)
	$(CC) $(CFLAGS) $(CDEBUG) -o $(TARGET) $^

.PHONY: release
release: main.c $(OBJ)
	$(CC) $(CFLAGS) $(CRELEASE) -o $(TARGET) $^

.PHONY: test
test: test.c $(OBJ)
	@$(CC) $(CFLAGS) -DTEST -o _temp $^
	@echo 'Running tests...'
	@./_temp
	@rm -f ./_temp

%.o: %.c
	@echo 'Compiling $@'
	$(CC) $(CFLAGS) $< -c -o $@

.PHONY: clean
clean:
	rm -rf $(OBJ) docs

.PHONY: docs
docs:
	doxygen
