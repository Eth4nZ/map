CXX = g++

CXXFLAGS = -I/usr/include/mysql++ -I/usr/include/mysql
LDFLAGS = -L/usr/lib -lmysqlpp -lmysqlclient -lnsl -lz -lm

SOURCES = insert.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = a

all: $(SOURCES) $(EXECUTABLE)
	    
$(EXECUTABLE): $(OBJECTS)
	#$(CXX) $(OBJECTS) -o $@

.cpp.o:
	$(CXX) $< $(CXXFLAGS) $(LDFLAGS)  -o $@

.phony: clean

clean:
	rm *.o

