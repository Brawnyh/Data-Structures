CC=gcc
CFLAGS=-std=c99 -Wextra -Wall -Werror -pedantic 
LDFLAGS=


ECHO=@
ifeq ($(VERBOSE),1)
# VERBOSE : when compiling, echo the executed command line
	ECHO=
endif

EXEC=stack_ex2
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)




all: 
	@$(MAKE) $(EXEC)

ifeq ($(DEBUG),yes)
	CFLAGS += -g
	LDFLAGS =
else
	CFLAGS += -O3 -DNDEBUG
	LDFLAGS =
endif

all:
ifeq ($(DEBUG),yes)
	@echo "Generating in debug mode"
else
	@echo "Generating in release mode"
endif
	@$(MAKE) $(EXEC)

doc:stack.h main.c
	$(ECHO) doxygen documentation/TP1


$(EXEC): $(OBJ)
	$(ECHO)$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(ECHO)$(CC) -o $@ -c $< $(CFLAGS)

clean:
	$(ECHO)rm -rf *.o

mrproper: clean
	$(ECHO)rm -rf $(EXEC)

dynamicstack.o : stack.h
main.o: stack.h

