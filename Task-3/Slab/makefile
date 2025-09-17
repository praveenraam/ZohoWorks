CXX = g++
CXXFLAGS = -std=c++17 -Wall -g
TARGET = executable_file
SOURCES = main.cpp Slab.cpp SlabAllocator.cpp SlabCache.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)