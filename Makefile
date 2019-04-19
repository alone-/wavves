OBJS = test.c src/*.c
CC = gcc
OBJ_NAME = wavves
all: $(OBJS)
	$(CC) $(OBJS) -o $(OBJ_NAME)
