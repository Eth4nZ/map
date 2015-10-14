CC = g++
CFLAGS = -c -Wall

SOURCES = main.cpp FloydWarshall.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = a

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.phony: clean

clean:
	-rm *o a
