#compiler
CC=g++
#compiler options
OPTS=-Wall -pedantic -g -std=c++11
#source files
SOURCES=$(wildcard src/*.cpp src/network/*.cpp)
#object files
OBJECTS=$(SOURCES:.cpp=.o)
#sdl-config or any other library here. 
#``- ensures that the command between them is executed, and the result is put into LIBS
LIBS=-pthread
#executable filename
EXECUTABLE=server.out
#Special symbols used:
#$^ - is all the dependencies (in this case =$(OBJECTS) )
#$@ - is the result name (in this case =$(EXECUTABLE) )

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@echo Building project $(OBJECTS)
	$(LINK.o) $^ -o $@ $(LIBS)
	@echo Build completed!

clean:
	@echo Cleaning files
	rm $(EXECUTABLE) $(OBJECTS)
	@echo Done!