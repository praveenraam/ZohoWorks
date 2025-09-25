gcc -c main.c -o main.o           # Compile main.c into main.o
gcc -c src/slab.c -o slab.o       # Compile slab.c into slab.o
gcc -c src/pointerstack.c -o pointerstack.o
gcc main.o slab.o pointerstack.o -o my_program  