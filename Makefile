# ---------- Elemental Squad Makefile ----------
# Usage:   make        -> build the game
#          make run    -> build (if needed) and play
#          make clean  -> delete compiled files

CXX      = g++
RAYLIB   = $(HOME)/Documents/raylib-6.0/src
CXXFLAGS = -std=c++17 -Wall -I$(RAYLIB) -MMD -MP
LDFLAGS  = -L$(RAYLIB)
LDLIBS   = -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

TARGET = elemental_squad_graphics

# Add any new .cpp file to this list
SRCS = graphics_main.cpp Grid.cpp Character.cpp Rocky.cpp Sprinty.cpp \
       Blaze.cpp Splash.cpp grid3.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(OBJS:.o=.d) $(TARGET)

-include $(OBJS:.o=.d)

.PHONY: all run clean