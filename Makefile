CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs`

SOURCES = main.cpp game.cpp utils.cpp
EXEC = game

all: $(EXEC)

$(EXEC): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(EXEC) $(LDFLAGS)

clean:
	rm -f $(EXEC)

run: $(EXEC)
	./$(EXEC)

.PHONY: all clean run