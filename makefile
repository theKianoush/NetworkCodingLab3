CC = gcc
OBJSS = drone3.c
CFLAGS =  -g -Wall

# setup for system
LIBS =

all: drone3

drone3: $(OBJSS)
	$(CC) $(CFLAGS) -o $@ $(OBJSS) $(LIBS)

clean:
	rm -f drone3
