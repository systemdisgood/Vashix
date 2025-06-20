#CC=clang++
CC=gcc
CFLAGS=-c -Wall -pedantic -Werror -std=c89 
LDFLAGS=-lpthread
SOURCES=Vashix.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=Vashix.out

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	rm ./*.o

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

