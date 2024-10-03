# @file Makefile
# @author Adam Valík <xvalik05@vutbr.cz>

EXEC = isa-top
SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp,%.o,$(SRC))

CPP = g++
CPPFLAGS = -std=c++20 -Wall -Wextra -pedantic -g
LIBS = -lncurses -lpcap

.PHONY: all clean run pack doc

.DEFAULT_GOAL := all

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CPP) $(CPPFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f *.o $(EXEC)

run: all
	./isa-top -i ap1 

pack: clean
	

doc: 
	doxygen Doxyfile
