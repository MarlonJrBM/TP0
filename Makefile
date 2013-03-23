CC = gcc
CFLAGS = -g -Wall
SOURCES = main.c quadtree.c lista.c node.c
OBJS = main.o quadtree.o lista.o node.o
HDR = quadtree.h
EXECUTABLE = tp0

build: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXECUTABLE)

run: build
	./$(EXECUTABLE) input.txt output.txt

clean:
	rm -rf *o *~ $(EXECUTABLE)

%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $<