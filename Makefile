# @file Makefile
# @author Adam Valík <xvalik05@vutbr.cz>

EXEC = isa-top
SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp,%.o,$(SRC))

CPP = g++
CPPFLAGS = -std=c++20 -Wall -Wextra -pedantic
LIBS = -lncurses -lpcap

.PHONY: all clean run pack doc remake

.DEFAULT_GOAL := all

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CPP) $(CPPFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f *.o $(EXEC)

remake: clean all

run: all
	./isa-top -i ap1 

pack: clean
#tbd

doc: 
	doxygen Doxyfile
