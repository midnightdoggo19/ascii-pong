CC := gcc
CCARGS := -lncurses -o pong

all: pong

pong: pong.c
	$(CC) pong.c $(CCARGS)

clean:
	-rm pong
