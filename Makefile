CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -O2
LDLIBS =

SRC = src
OBJ = obj
BIN = bin

OBJS_ = symbol_table.o arg_list.o str.o errors.o scanner.o
OBJS = $(addprefix $(OBJ)/,$(notdir $(OBJS_)))
BINARY = test

vpath %.c $(SRC)
vpath %.h $(SRC)

all: $(BIN)/test

$(OBJ)/symbol_table.o: symbol_table.c symbol_table.h arg_list.h str.h errors.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -c -o $@

$(OBJ)/arg_list.o: arg_list.c arg_list.h str.h errors.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -c -o $@

$(OBJ)/str.o: str.c str.h errors.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -c -o $@

$(OBJ)/errors.o: errors.c errors.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -c -o $@

$(OBJ)/scanner.o: scanner.c scanner.h token.h str.h errors.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -c -o $@

$(BIN)/test: test.c $(OBJS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(LDLIBS) $^ -o $@

clean:
	rm -rf $(OBJ)
	rm -rf $(BIN)
	rm -f "IFJ15 Interpret.zip"

zip:
	zip "IFJ15 Interpret.zip" */*.c */*.h res/* Makefile -x "IFJ15 Interpret.zip"
