LINK_TARGET = UTTC

BIN = bin
SRC = src
TEMP = temp

FILES = board.c node.c ai.c engine.c
OBJECTS = $(patsubst %.c,$(TEMP)/%.o,$(FILES))

COMPILER = gcc

all: $(LINK_TARGET)

clean:
	rm -f temp/*
	rm -f bin/$(LINK_TARGET)

$(LINK_TARGET) : $(OBJECTS)
	$(COMPILER) -g $(INCLUDES) -o $(BIN)/$@ $^ $(LIBS)

$(TEMP)/%.o : $(SRC)/%.c
	$(COMPILER) -g -c $< -o $@

run:
	$(BIN)/$(LINK_TARGET)

valgrind:
	valgrind $(BIN)/$(LINK_TARGET)

test: clean $(LINK_TARGET) valgrind

.PHONY: clean

 