OBJ    = libllist.so libcparse.so
OBJDIR = bin
CC     = gcc
EXE    = A1
CFLAGS = -std=c11 -Wall -Iinclude

all:$(EXE)

parser:

LinkedListAPI.o: src/LinkedListAPI.c
	$(CC) -c src/LinkedListAPI.c $(CFLAGS)

CalendarParser.o: src/CalendarParser.c
	$(CC) -c src/CalendarParser.c $(CFLAGS)