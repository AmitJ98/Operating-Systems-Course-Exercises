CXX = g++

CXXFLAGS = -Wall -std=c++11

SRC = VirtualMemory.cpp

HEADERS = VirtualMemory.h

OBJ = $(SRC:.cpp=.o)

LIB = libVirtualMemory.a

all: $(LIB)

$(LIB): $(OBJ)
	ar rcs $@ $(OBJ)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

tar:
	tar -cvf ex4.tar $(SRC) Makefile README

clean:
	rm -f $(OBJ) $(LIB) 