CC = gcc
CFLAGS = -c
OBJ = main.o dll.o slab.o pointerstack.o slabcache.o
SRC = main.c src/dll.c src/slab.c src/pointerstack.c
EXEC = my_program

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o: main.c
	$(CC) $(CFLAGS) main.c -o main.o

dll.o: src/dll.c
	$(CC) $(CFLAGS) src/dll.c -o dll.o

slab.o: src/slab.c
	$(CC) $(CFLAGS) src/slab.c -o slab.o

pointerstack.o: src/pointerstack.c
	$(CC) $(CFLAGS) src/pointerstack.c -o pointerstack.o


slabcache.o: src/slabcache.c
	$(CC) $(CFLAGS) src/slabcache.c -o slabcache.o

clean:
	rm -f $(OBJ) $(EXEC)
