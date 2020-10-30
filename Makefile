SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:%.cpp=%.o)
PROG = program.exe

CXX = gcc
CXXFLAGS = -Wall -std=c++11 -Wall -pedantic
LDFLAGS =
INCLUDE = -Iinclude

$(PROG): $(OBJ)
	$(CXX) $(CFLAGS) $(INCLUDE) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm $(OBJ) $(PROG)