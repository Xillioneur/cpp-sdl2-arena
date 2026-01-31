CXX = g++
CXXSTD = -std=c++17
WARNINGS = -Wall -Wextra
OPT = -O2

PKG_CONFIG = pkg-config
SDL2_CFLAGS = $(shell $(PKG_CONFIG) --cflags sdl2)
SDL2_LIBS   = $(shell $(PKG_CONFIG) --libs sdl2)

CXXFLAGS = $(CXXSTD) $(WARNINGS) $(OPT) $(SDL2_CFLAGS)
LDFLAGS  = $(SDL2_LIBS)

SOURCES = main.cpp game.cpp enemy.cpp utils.cpp
EXEC = game

all: $(EXEC)

$(EXEC): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(EXEC) $(LDFLAGS)

clean:
	rm -f $(EXEC)

run: $(EXEC)
	./$(EXEC)

.PHONY: all clean run
