CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -O2
LDLIBS =

SRC = src
OBJ = obj
BIN = bin

vpath %.c $(SRC)/

SRCS = $(wildcard $(SRC)/*.c)
OBJS = $(SRCS:$(SRC)/%.c=$(OBJ)/%.o)
BINARY = test
LOGIN = xsrnam00

all: $(BIN)/$(BINARY)

$(OBJ)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -c -o $@

$(BIN)/$(BINARY): $(OBJS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(LDLIBS) $^ -o $@

final:
	@mkdir -p tmp/
	@cp src/* tmp/
	@cp Makefile.fin tmp/Makefile
	@zip -j "$(LOGIN).zip" tmp/*
	@rm -rf tmp/

clean:
	@rm -rf $(OBJ)
	@rm -rf $(BIN)
	@rm -f *.zip

zip:
	@zip -r "IFJ15 Interpret.zip" * .gitignore -x "*.zip" -x "obj*" -x "doc*" -x "bin*" -x "Doxyfile"
