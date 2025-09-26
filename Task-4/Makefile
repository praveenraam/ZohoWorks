CC = gcc
CFLAGS = -c
SRC = main.c src/dll.c src/slab.c src/pointerstack.c src/slabcache.c src/slaballocator.c
OBJ = $(SRC:.c=.o)
EXEC = my_program

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ)

allclean: clean
	rm -f $(EXEC)

.PHONY: all clean allclean
