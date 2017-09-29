OBJ    = LinkedListAPI.o CalendarParser.o
LIB    = liblist.a libparse.a
LIBDIR = bin
CC     = gcc
EXE    = A1
CFLAGS = -std=c11 -Wall -Iinclude

all:$(EXE)

$(EXE): $(OBJ) $(LIB)
	$(CC) $(CFLAGS) -o A1 $(OBJ) $(LIB)

liblist.a: LinkedListAPI.o
	ar cr liblist.a LinkedListAPI.o

libparse.a: CalendarParser.o
	ar cr libparse.a CalendarParser.o

LinkedListAPI.o: src/LinkedListAPI.c include/LinkedListAPI.h
	$(CC) -c src/LinkedListAPI.c $(CFLAGS)

CalendarParser.o: src/CalendarParser.c include/CalendarParser.h
	$(CC) -c src/CalendarParser.c $(CFLAGS)

clear:
	rm $(OBJ)